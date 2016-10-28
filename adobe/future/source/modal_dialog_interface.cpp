/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#ifndef BUILD_FOR_TEST
#include "Spaceport.h"
#endif

#define ADOBE_DLL_SAFE 0

#include <adobe/config.hpp>

#include <adobe/future/modal_dialog_interface.hpp>

#include <adobe/adam_evaluate.hpp>
#include <adobe/adam_parser.hpp>
#include <adobe/future/assemblage.hpp>
#include <adobe/future/resources.hpp>
#include <adobe/future/widgets/headers/widget_factory.hpp>
#include <adobe/future/widgets/headers/widget_utils.hpp>
#include <adobe/keyboard.hpp>
#include <adobe/xstring.hpp>

/****************************************************************************************************/

namespace adobe {

/****************************************************************************************************/

std::string getline(std::istream& stream)
{
    std::string result;

    result.reserve(128);

    while (true)
    {
        int c(stream.get());

        if (c == EOF || c == '\n')
        {
            break;
        }
        else if (c == '\r')
        {
            c = stream.get();

            if (c != '\n')
                stream.putback(c);

            break;
        }

        result += static_cast<char>(c);
    }

    return result;
}

/****************************************************************************************************/

std::string mdi_error_getline(std::istream& layout_definition, name_t, std::streampos line_start_position)
{
    std::streampos old_pos(layout_definition.tellg());

    layout_definition.clear();

    layout_definition.seekg(line_start_position);

    std::string result(getline(layout_definition));

    layout_definition.seekg(old_pos);

    return result;
}

/****************************************************************************************************/

} // namespace adobe

/****************************************************************************************************/

namespace adobe {

/****************************************************************************************************/

modal_dialog_t::modal_dialog_t() :
    display_options_m(dialog_display_s),
    parent_m(platform_display_type()),
    root_behavior_m(false)
{ }

/****************************************************************************************************/

platform_display_type modal_dialog_t::init (std::istream & layout,
                                            std::string const & layout_source,
                                            std::istream & sheet,
                                            std::string const & sheet_source)
{
    resource_context_t res_context(working_directory_m);

    vm_lookup_m.attach_to(sheet_m);
    vm_lookup_m.attach_to(sheet_m.machine_m);

    result_m = dialog_result_t();

    //
    // Parse the proprty model stream
    //

    try
    {
        parse( sheet, line_position_t(sheet_source.c_str()), bind_to_sheet( sheet_m ) );
    }
    catch (const stream_error_t& error)
    {
        throw std::logic_error(format_stream_error(sheet, error));
    }
    catch (...)
    {
        throw; // here for completeness' sake
    }

    //
    // REVISIT (2006/09/28, fbrereto): The sheet initializers don't run until the first update().
    //                                 To keep them from blowing away your sets in a couple of
    //                                 lines we need to add an update before the first set()
    //                                 on the sheet (this will get fixed with the proprty model
    //                                 library rewrite so mark it with a revisit comment).
    //

    sheet_m.update();

    //
    // Set up the sheet with initial inputs, etc.
    //

    sheet_m.set(input_m);
    sheet_m.set(record_m);

    need_ui_m = false;

    sheet_m.update();

    //
    // Save off the contributing set for potential reset action later
    //

    contributing_m = sheet_m.contributing();

    //
    // Set up the callback functions now so the contributing mark is meaningful, then update again
    //

    try
    {
        name_t result_cell("result"_name);

        attach_view(assemblage_m, result_cell, *this, sheet_m);

        sheet_m.monitor_invariant_dependent(result_cell, boost::bind(&modal_dialog_t::monitor_invariant, boost::ref(*this), _1));
        sheet_m.monitor_contributing(result_cell, sheet_m.contributing(), boost::bind(&modal_dialog_t::monitor_record, boost::ref(*this), _1));
    }
    catch (...)
    {
        // result cell wasn't found. While this isn't a deal-breaker, it's not
        // going to do much in the way of getting results from this dialog.
    }

    sheet_m.update();

    if (display_options_m == dialog_never_display_s && need_ui_m)
        throw std::runtime_error("handle_dialog: Invalid command parameters and UI not permitted.");

    if ((display_options_m == dialog_no_display_s && need_ui_m) ||
        display_options_m == dialog_display_s)
    {
        line_position_t::getline_proc_t getline_proc(new line_position_t::getline_proc_impl_t(boost::bind(&mdi_error_getline, boost::ref(layout), _1, _2)));

        view_m.reset(
            make_view(
                layout_source,
                getline_proc,
                layout,
                sheet_m,
                root_behavior_m,
                vm_lookup_m,
                button_callback_m,
                boost::bind(&modal_dialog_t::latch_button_callback, boost::ref(*this), _1, _2),
                boost::bind(&modal_dialog_t::latch_signal_callback, boost::ref(*this), _1, _2, _3, _4),
                size_normal_s,
                default_widget_factory_proc(),
                parent_m
            ).release()
        );

        // Set up the view's sheet with display state values, etc.
        //
        view_m->layout_sheet_m.set(display_state_m);

        sheet_m.update();

        //
        // Show the GUI.
        //
        view_m->eve_m.evaluate(eve_t::evaluate_nested);
        view_m->show_window_m();
    }

    return view_m->root_display_m;
}

/****************************************************************************************************/

dialog_result_t modal_dialog_t::go()
{
    if ((display_options_m == dialog_no_display_s && need_ui_m) ||
        display_options_m == dialog_display_s) {
        platform_display_type dlg = view_m->root_display_m;
        // TODO dlg->Run();
        // TODO: view_m->show_and_run_modal(); // TODO: Look in SlateApplication.cpp for an event loop impl.
        result_m.display_state_m = view_m->layout_sheet_m.contributing();
        view_m.reset(0);
    }

    return result_m;
}

/****************************************************************************************************/

bool modal_dialog_t::latch_button_callback(name_t action, const any_regular_t& value)
try
{
    bool retval = false;

    assert(view_m);
    assert(callback_m);

    if (action == "reset"_name) {
        sheet_m.set(contributing_m);
        sheet_m.update();
    } else if (action == "cancel"_name) {
        sheet_m.set(contributing_m);
        sheet_m.update();
        retval = true;
    } else if (action == "ok"_name || button_callback_m(action, value)) {
        retval = true;
    }

    if (retval) {
        result_m.terminating_action_m = action;
        // TODO view_m->root_display_m->EndRun();
    }

    return retval;
}
catch(const std::exception& error)
{
    std::cerr << "Exception (modal_dialog_t::latch_button_callback) : " << error.what() << std::endl;
    return false;
}
catch(...)
{
    std::cerr << "Unknown exception (modal_dialog_t::latch_button_callback)" << std::endl;
    return false;
}

/****************************************************************************************************/

void modal_dialog_t::latch_signal_callback(name_t widget_type_name,
                                           name_t signal_name,
                                           name_t widget_id,
                                           const any_regular_t& value)
{
    if (signal_notifier_m)
        signal_notifier_m(widget_type_name, signal_name, widget_id, value);
}

/****************************************************************************************************/

void modal_dialog_t::display(const model_type& value)
{
    result_m.command_m = value.cast<dictionary_t>();
}

/****************************************************************************************************/

keyboard_t& modal_dialog_t::keyboard()
{
    return view_m->keyboard_m;
}

/****************************************************************************************************/

const dialog_result_t& modal_dialog_t::result()
{
    return result_m;
}

/****************************************************************************************************/

sheet_t& modal_dialog_t::sheet()
{
    return sheet_m;
}

/****************************************************************************************************/

void modal_dialog_t::monitor_record(const dictionary_t& record_info)
{
    result_m.record_m = record_info;
}

/****************************************************************************************************/

void modal_dialog_t::monitor_invariant(bool is_set)
{
    need_ui_m = !is_set;
}

/****************************************************************************************************/

} // namespace adobe

/****************************************************************************************************/
