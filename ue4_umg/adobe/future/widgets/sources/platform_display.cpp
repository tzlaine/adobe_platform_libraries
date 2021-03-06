/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#ifndef BUILD_FOR_TEST
#include "Spaceport.h"
#endif

#include <adobe/future/widgets/headers/display.hpp>
#include <adobe/future/widgets/headers/widget_utils.hpp>

#include <cassert>

/****************************************************************************************************/

namespace adobe {

/****************************************************************************************************/

display_t& get_main_display()
{
    static display_t display_s;

    return display_s;
}

/****************************************************************************************************/

template <typename DisplayElement>
platform_display_type insert(display_t& display, platform_display_type& position, DisplayElement& element)
{ return display.insert(position, element); }

/****************************************************************************************************/

#if 0
    #pragma mark -
#endif

/****************************************************************************************************/

platform_display_type display_t::insert(platform_display_type parent, platform_display_type element)
{
    static const platform_display_type null_parent_s = platform_display_type();

    UCanvasPanelSlot * slot = nullptr;
    if (parent != null_parent_s) {// TODO && parent != get_main_display().root()) {
        auto const root = implementation::get_root_widget(parent);
        root->panel()->AddChildToCanvas(element);
    }

    return element;
}

/****************************************************************************************************/

} // namespace adobe

/****************************************************************************************************/
