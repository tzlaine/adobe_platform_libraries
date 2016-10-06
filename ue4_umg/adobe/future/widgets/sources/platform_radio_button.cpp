/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#include <adobe/future/widgets/headers/platform_radio_button.hpp>

#include <adobe/future/widgets/headers/display.hpp>
#include <adobe/future/widgets/headers/widget_utils.hpp>
#include <adobe/future/widgets/headers/platform_metrics.hpp>

/****************************************************************************************************/

namespace adobe {

/****************************************************************************************************/

radio_button_t::radio_button_t(const std::string& name,
                               const std::string& alt_text,
                               const any_regular_t& set_value,
                               theme_t theme) :
    control_m(0),
    name_m(name),
    alt_text_m(alt_text),
    set_value_m(set_value),
    theme_m(theme)
{ }

/****************************************************************************************************/

void radio_button_t::measure(extents_t& result)
{
    /* TODO
    result = metrics::measure(control_m, BP_RADIOBUTTON);

    //
    // Get the text margins, and factor those into the bounds.
    //
    RECT margins = {0, 0, 0, 0};

    metrics::set_window(control_m);

    if (metrics::get_button_text_margins(BP_RADIOBUTTON, margins))
    {
        //
        // Add the width margins in. The height margins aren't important because
        // the widget is already large enough to contain big text (as calculated
        // by calculate_best_bounds).
        //
        result.width() += margins.left + margins.right;
    }
    */
}

/****************************************************************************************************/

void radio_button_t::place(const place_data_t& place_data)
{
    assert(control_m);

    implementation::set_control_bounds(control_m, place_data);
}

/****************************************************************************************************/

void radio_button_t::enable(bool make_enabled)
{
    assert(control_m);

    //::EnableWindow(control_m, make_enabled);
}

/****************************************************************************************************/

void radio_button_t::display(const any_regular_t& value)
{
    assert(control_m);

    if (last_m == value)
        return;

    last_m = value;

    //::SendMessage(control_m, BM_SETCHECK, last_m == set_value_m ? BST_CHECKED : BST_UNCHECKED, 0);
}

/****************************************************************************************************/

void radio_button_t::monitor(const setter_type& proc)
{
    assert(control_m);

    hit_proc_m = proc;
}

/****************************************************************************************************/

template <>
platform_display_type insert<radio_button_t>(display_t& display,
                                             platform_display_type& parent,
                                             radio_button_t& element)
{
    /* TODO
    HWND parent_hwnd(parent);

    element.control_m = ::CreateWindowExW(WS_EX_COMPOSITED | WS_EX_TRANSPARENT, L"BUTTON",
                                          hackery::convert_utf(element.name_m).c_str(),
                                          WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON | WS_TABSTOP | BS_NOTIFY,
                                          0, 0, 100, 20,
                                          parent_hwnd,
                                          0,
                                          ::GetModuleHandle(NULL),
                                          NULL);

    if (element.control_m == NULL)
        ADOBE_THROW_LAST_ERROR;

    set_font(element.control_m, BP_RADIOBUTTON);
    */

    if (!element.alt_text_m.empty())
        implementation::set_control_alt_text(element.control_m, element.alt_text_m);

    return display.insert(parent, element.control_m);
}

/****************************************************************************************************/

} // namespace adobe

/****************************************************************************************************/
