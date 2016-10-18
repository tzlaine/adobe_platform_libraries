/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#ifndef BUILD_FOR_TEST
#include "Spaceport.h"
#endif

#include <adobe/future/widgets/headers/platform_checkbox.hpp>

#include <adobe/future/widgets/headers/widget_utils.hpp>

#include <adobe/future/widgets/headers/platform_metrics.hpp>
#include <adobe/future/widgets/headers/display.hpp>

/****************************************************************************************************/

namespace adobe {

/****************************************************************************************************/

checkbox_t::checkbox_t(const std::string& name,
                       const any_regular_t& true_value,
                       const any_regular_t& false_value,
                       const std::string& alt_text) :
    control_m(),
    true_value_m(true_value),
    false_value_m(false_value),
    name_m(name),
    alt_text_m(alt_text)
{ }

/****************************************************************************************************/

void checkbox_t::measure(extents_t& result)
{
    /* TODO
    result = metrics::measure(control_m, BP_CHECKBOX);

    //
    // Get the text margins, and factor those into the bounds.
    //
    RECT margins = {0, 0, 0, 0};

    metrics::set_window(control_m);

    if (metrics::get_button_text_margins(BP_CHECKBOX, margins))
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

void checkbox_t::place(const place_data_t& place_data)
{
    assert(control_m);
    
    implementation::set_control_bounds(control_m, place_data);
}

/****************************************************************************************************/

void checkbox_t::enable(bool make_enabled)
{
    assert(control_m);

    set_control_enabled(control_m, make_enabled);
}

/****************************************************************************************************/

void checkbox_t::display(const any_regular_t& new_value)
{
    assert(control_m);

    if (current_value_m == new_value)
        return;

    current_value_m = new_value;

    /* TODO
    WPARAM state(BST_INDETERMINATE);

    if (current_value_m == true_value_m)
        state = BST_CHECKED;
    else if (current_value_m == false_value_m)
        state = BST_UNCHECKED;

    ::SendMessage(control_m, BM_SETCHECK, state, 0);
    */
}

/****************************************************************************************************/

void checkbox_t::monitor(const setter_type& proc)
{
    assert(control_m);

    hit_proc_m = proc;
}

/****************************************************************************************************/

template <>
platform_display_type insert<checkbox_t>(display_t& display,
                                         platform_display_type& parent,
                                         checkbox_t& element)
{
    /* TODO
    HWND parent_hwnd(parent);

    initialize(element, parent_hwnd);

    return display.insert(parent, element.control_m);
    */
    return platform_display_type();
}

/****************************************************************************************************/

} // namespace adobe

/****************************************************************************************************/
