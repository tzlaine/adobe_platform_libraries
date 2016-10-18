/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#ifndef BUILD_FOR_TEST
#include "Spaceport.h"
#endif

#include <adobe/future/widgets/headers/platform_group.hpp>

#include <adobe/future/widgets/headers/widget_utils.hpp>
#include <adobe/future/widgets/headers/platform_label.hpp>
#include <adobe/future/widgets/headers/platform_metrics.hpp>
#include <adobe/future/widgets/headers/display.hpp>


/****************************************************************************************************/

namespace adobe {

/****************************************************************************************************/

group_t::group_t(const std::string& name,
                 const std::string& alt_text,
                 theme_t theme) :
    control_m(),
    name_m(name),
    alt_text_m(alt_text),
    theme_m(theme)
{ }

/****************************************************************************************************/

void group_t::measure(extents_t& result)
{
    assert(control_m);

    if (name_m.empty())
    {
        result.height() = 15;
        result.width() = 15;

        return;
    }

    // REVISIT (fbrereto) : A lot of static metrics values added here

    // TODO result = measure_text(name_m, theme_m, ::GetParent(control_m));

    result.width() += 15;

    result.vertical().frame_m.first = result.height() + 7;

    result.height() = 5;
}

/****************************************************************************************************/

void group_t::place(const place_data_t& place_data)
{
    assert(control_m);

    implementation::set_control_bounds(control_m, place_data);
}

/****************************************************************************************************/

template <>
platform_display_type insert<group_t>(display_t& display,
                                      platform_display_type& parent,
                                      group_t& element)
{
    /* TODO
    element.control_m = ::CreateWindowExW(WS_EX_CONTROLPARENT | WS_EX_COMPOSITED | WS_EX_TRANSPARENT,
                                          L"BUTTON",
                                          hackery::convert_utf(element.name_m).c_str(),
                                          WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                                          0, 0, 10, 10,
                                          parent_hwnd,
                                          0,
                                          ::GetModuleHandle(NULL),
                                          NULL);

    if (element.control_m == NULL)
        ADOBE_THROW_LAST_ERROR;

    set_font(element.control_m, BP_GROUPBOX);

    ::SetWindowSubclass(element.control_m, &group_subclass_proc, reinterpret_cast<UINT_PTR>(&element), 0);
    */

    return display.insert(parent, element.control_m);
}

/****************************************************************************************************/

} // namespace adobe

/****************************************************************************************************/
