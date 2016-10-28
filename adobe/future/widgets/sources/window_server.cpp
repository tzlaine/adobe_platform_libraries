/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#ifndef BUILD_FOR_TEST
#include "Spaceport.h"
#endif

#include <adobe/future/widgets/headers/window_server.hpp>
#include <adobe/future/widgets/headers/factory.hpp>

#include <adobe/algorithm/for_each.hpp>
#include <adobe/future/resources.hpp>

/****************************************************************************************************/

namespace adobe {

/****************************************************************************************************/

window_server_t::window_server_t(sheet_t& sheet,
                                 behavior_t& behavior,
                                 vm_lookup_t& vm_lookup,
                                 const button_notifier_t& button_notifier,
                                 const signal_notifier_t& signal_notifier,
                                 const widget_factory_t& factory) :
    sheet_m(sheet),
    behavior_m(behavior),
    vm_lookup_m(vm_lookup),
    button_notifier_m(button_notifier),
    signal_notifier_m(signal_notifier),
    widget_factory_m(factory)
{ }

/*************************************************************************************************/

window_server_t::~window_server_t()
{
    adobe::for_each(window_list_m, delete_ptr());
}

/*************************************************************************************************/

eve_client_holder& window_server_t::top_client_holder()
{
    if (window_list_m.empty())
        throw std::runtime_error("No top view!");

    return *(window_list_m.back());
}

/*************************************************************************************************/

void window_server_t::push_back(const char* name, size_enum_t dialog_size)
{
    boost::filesystem::path     relative_path(window_list_m.back()->path_m.branch_path() / name);
    iterator                    window(window_list_m.insert(window_list_m.end(), 
                                                            static_cast<eve_client_holder*>(NULL)));
    boost::filesystem::path     file_name;

    try
    {
        file_name = find_resource(name);
    }
    catch (...)
    {
        file_name = relative_path;
    }

    boost::filesystem::ifstream stream(file_name);

    /*
    Update before attaching the window so that we can correctly capture contributing for reset.
    */
    
    sheet_m.update();

    window_list_m.back() = make_view(   name_t(file_name.string().c_str()),
                                        line_position_t::getline_proc_t(),
                                        stream,
                                        sheet_m,
                                        behavior_m,
                                        vm_lookup_m,
                                        button_notifier_m,
                                        boost::bind(&window_server_t::dispatch_window_action,
                                            boost::ref(*this), window, _1, _2),
                                        signal_notifier_m,
                                        dialog_size,
                                        default_widget_factory_proc_with_factory(widget_factory_m)).release();
    
    sheet_m.update(); // Force values to their correct states.

    window_list_m.back()->path_m = file_name;
    window_list_m.back()->eve_m.evaluate(eve_t::evaluate_nested);
    window_list_m.back()->show_window_m();
}

/*************************************************************************************************/

void window_server_t::push_back(std::istream&                                   data,
                                const boost::filesystem::path&                  path,
                                const line_position_t::getline_proc_t&   getline_proc,
                                size_enum_t                              dialog_size)
{
    /*
    Update before attaching the window so that we can correctly capture contributing for reset.
    */
    sheet_m.update();

    iterator window (window_list_m.insert(window_list_m.end(), static_cast<eve_client_holder*>(NULL)));

    //
    // REVISIT (ralpht): Where does this made-up filename get used? Does it need to be localized
    //  or actually be an existing file?
    //
    //  REVISIT (fbrereto) :    The file name is for error reporting purposes; see the const char*
    //                          push_back API where this is filled in. It should be valid, lest the
    //                          user not know the erroneous file.
    //
    window_list_m.back() = make_view(   name_t(path.string().c_str()),
                                        getline_proc,
                                        data,
                                        sheet_m,
                                        behavior_m,
                                        vm_lookup_m,
                                        button_notifier_m,
                                        boost::bind(&window_server_t::dispatch_window_action,
                                            boost::ref(*this), window, _1, _2),
                                        signal_notifier_m,
                                        dialog_size,
                                        default_widget_factory_proc_with_factory(widget_factory_m)).release();

    sheet_m.update(); // Force values to their correct states.

    window_list_m.back()->path_m = path;
    window_list_m.back()->eve_m.evaluate(eve_t::evaluate_nested);
    window_list_m.back()->show_window_m();
}

/*************************************************************************************************/

void window_server_t::erase(iterator window)
{
    delete *window;
    window_list_m.erase(window);
}

/*************************************************************************************************/

bool window_server_t::dispatch_window_action(iterator window, name_t action, const any_regular_t& parameter)
{
    bool retval = false;

    if (action == "reset"_name)
    {
        sheet_m.set((*window)->contributing_m);
        sheet_m.update();
    }
    else if (action == "dialog"_name)
    {
        push_back(parameter.cast<std::string>().c_str(), size_normal_s);
    }
    else if (action == "cancel"_name)
    {
        sheet_m.set((*window)->contributing_m);
        sheet_m.update();

        general_deferred_proc_queue().insert(boost::bind(&window_server_t::erase, boost::ref(*this), window));
        retval = true;
    }
    else if (action == "ok"_name)
    {
        general_deferred_proc_queue().insert(boost::bind(&window_server_t::erase, boost::ref(*this), window));
        retval = true;
    }
    else
    {
        retval = button_notifier_m(action, parameter);
    }

    return retval;
}

/****************************************************************************************************/

}

/****************************************************************************************************/
