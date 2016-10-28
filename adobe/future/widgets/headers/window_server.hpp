/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#ifndef ADOBE_WIDGET_WINDOW_SERVER_HPP
#define ADOBE_WIDGET_WINDOW_SERVER_HPP

/****************************************************************************************************/

#include <adobe/config.hpp>

#include <adobe/adam.hpp>
#include <adobe/any_regular.hpp>
#include <adobe/dictionary.hpp>
#include <adobe/eve.hpp>
#include <adobe/future/assemblage.hpp>
#include <adobe/future/debounce.hpp>
#include <adobe/future/widgets/headers/display.hpp>
#include <adobe/future/widgets/headers/widget_tokens.hpp>
#include <adobe/future/widgets/headers/widget_factory.hpp>
#include <adobe/future/widgets/headers/widget_factory_registry.hpp>
#include <adobe/istream.hpp>
#include <adobe/memory.hpp>
#include <adobe/name.hpp>

#include <boost/function.hpp>
#include <boost/filesystem/path.hpp>

#include <list>
#include <vector>

/*************************************************************************************************/

namespace adobe {

/*************************************************************************************************/
/*
    This is a basic "Window Server" - it can be called to construct a window by name. The window
    is attached to a sheet as a slave (meaning the Window must be destructed before the sheet).

    REVISIT (sparent) : Here are some thoughts on the direction this design should be going...
    
    We have an assemblage (or package of items with the same lifespace) for the window which
    includes the eve structure and the slave connection (the wire bundle to attach the
    assamblage to a sheet).
*/

struct eve_client_holder;

//
/// The window_server_t class can open Eve definitions from file and
/// input stream, and can display them. It also looks after all of
/// the memory allocated to display an Eve definition.
//
class window_server_t
{
public:
    //
    /// This constructor tells the window_server_t where to find
    /// Eve definitions referenced in @dialog commands, and which
    /// sheet to bind against.
    ///
    /// \param  sheet       the sheet to bind against. This
    ///             sheet should contain all of the
    ///             cells referenced in the Eve file
    ///             which is loaded (either via
    ///             push_back or @dialog).
    //
    window_server_t(sheet_t& sheet,
                    behavior_t& behavior,
                    vm_lookup_t& vm_lookup,
                    const button_notifier_t& button_notifier,
                    const signal_notifier_t& signal_notifier,
                    const widget_factory_t& factory);
    //
    /// Hide and release all Eve dialogs created by this window server.
    //
    ~window_server_t();
    //
    /// Load the given file out of the directory_path and display the
    /// dialog it contains. If the file cannot be found, or the file
    /// contains errors (e.g.: syntax errors, references non-existant
    /// widgets) then an exception is thrown.
    ///
    /// \param  name the name of the Eve file inside
    ///             the directory given to the constructor.
    /// \param  dialog_size the size of the dialog to create,
    ///             note that individual widgets may
    ///             override this value in the Eve file.
    //
    void push_back(const char* name, size_enum_t dialog_size);
    //
    /// Load an Eve definition from the given std::istream and display
    /// the dialog it contains. If any errors are found in the data
    /// then an exception is thrown.
    ///
    /// \param  data an std::istream open on the Eve
    ///             definition to be loaded.
    /// \param  ident_pair identification name and callback proc (two parameters)
    ///             that represents the data stream
    /// \param  dialog_size the size of the dialog to create,
    ///             note that individual widgets may
    ///             override this value in the Eve
    ///             definition.
    //
    void push_back(std::istream& data, const boost::filesystem::path& file_path, const line_position_t::getline_proc_t& getline_proc, size_enum_t dialog_size);
    
    //
    /// Return the number of windows which this window_server has open.
    ///
    /// \return the number of windows which this window_server has open.
    //
    std::size_t size() const { return window_list_m.size(); }

    //
    /// \return The top eve client holder in the window list
    ///
    //
    eve_client_holder& top_client_holder();

private:
    typedef std::list<eve_client_holder*>   window_list_t;
    typedef window_list_t::iterator         iterator;
    
    bool dispatch_window_action(iterator window, name_t action, const any_regular_t& parameter);
    void erase(iterator window);
    
    sheet_t&                 sheet_m;
    behavior_t&              behavior_m;
    window_list_t            window_list_m;
    vm_lookup_t&             vm_lookup_m;
    const button_notifier_t& button_notifier_m;
    const signal_notifier_t& signal_notifier_m;
    widget_factory_t         widget_factory_m;
};

/*************************************************************************************************/

}

/*************************************************************************************************/

#endif
