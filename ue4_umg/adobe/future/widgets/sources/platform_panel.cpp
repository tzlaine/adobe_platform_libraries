/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#include <adobe/future/widgets/headers/platform_panel.hpp>

#include <adobe/future/widgets/headers/display.hpp>
#include <adobe/future/widgets/headers/platform_metrics.hpp>


/****************************************************************************************************/

namespace adobe {

/****************************************************************************************************/

panel_t::panel_t(const any_regular_t& show_value, theme_t theme) :
    control_m(0),
    theme_m(theme),
    show_value_m(show_value)
{ }

/****************************************************************************************************/

void panel_t::display(const any_regular_t& value)
{
    bool visible (value == show_value_m);

    set_visible(visible);
}

/*************************************************************************************************/

void panel_t::measure(extents_t& result)
{ 
    result = extents_t(); 
}

/*************************************************************************************************/

void panel_t::place(const place_data_t& place_data)
{    
    implementation::set_control_bounds(control_m, place_data);
}

/*************************************************************************************************/

void panel_t::set_visible(bool make_visible)
{ 
    set_control_visible(control_m, make_visible); 
}

/****************************************************************************************************/

template <>
platform_display_type insert<panel_t>(display_t& display,
                                      platform_display_type& parent,
                                      panel_t& element)
{
    assert(!element.control_m);

    /* TODO
    element.control_m = ::CreateWindowEx(   WS_EX_CONTROLPARENT | WS_EX_COMPOSITED,
                    _T("eve_panel"),
                    NULL,
                    WS_CHILD | WS_VISIBLE,
                    0, 0, 10, 10,
                    parent_hwnd,
                    0,
                    ::GetModuleHandle(NULL),
                    NULL);

    if (element.control_m == NULL)
        ADOBE_THROW_LAST_ERROR;
    */

    return display.insert(parent, element.control_m);
}

/*************************************************************************************************/

} //namespace adobe

/*************************************************************************************************/


