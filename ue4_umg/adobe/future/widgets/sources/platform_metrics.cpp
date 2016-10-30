/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

// This is the implementation of the class which looks up widget metrics on
// Windows systems. It has two implementations, one uses UxTheme to look up
// widget metrics, and the other uses constant values (and is used on systems
// where UxTheme is unavailable or Visual Styles are disabled).

/****************************************************************************************************/

#ifndef BUILD_FOR_TEST
#include "Spaceport.h"
#endif

#include <adobe/future/widgets/headers/platform_metrics.hpp>
#include <adobe/future/widgets/headers/platform_slider.hpp>
#include <adobe/future/widgets/headers/platform_checkbox.hpp>
#include <adobe/future/widgets/headers/platform_radio_button.hpp>
#include <adobe/future/widgets/headers/platform_group.hpp>

#include <sstream>
#include <stdexcept>
#include <cassert>
#include <cstring>

#include <boost/static_assert.hpp>

/****************************************************************************************************/

namespace adobe {

/****************************************************************************************************/

namespace metrics {

namespace detail {

/****************************************************************************************************/

float measurement_size (FSlateFontInfo const & font_info)
{ return std::sqrt(font_info.Size); }

/****************************************************************************************************/

}

/****************************************************************************************************/

FVector2D get_size(slider_t const & control)
{
    return FVector2D(0, 0); // TODO: Return tab size.
}

FVector2D get_size(checkbox_t const & control)
{
    return FVector2D(0, 0); // TODO: REturn box size + x=5 gap
}

FVector2D get_size(radio_button_t const & control)
{
    return FVector2D(0, 0); // TODO: REturn box size + x=5 gap
}

FVector2D get_size(group_t const & control)
{ return FVector2D(8, 8); }

/****************************************************************************************************/

bool get_button_text_margins(int widget_type, int/*RECT*/& out_margins)
{
    /*
    // in this case, we fall back to the non-theme version if theme is not set.
    if (using_styles() && theme_g->theme_m)
    {
        return S_OK == Button_GetTextMargin(theme_g->window_m, &out_margins);
    }
    else
    {
        if ((target() == L"Button") && (widget_type == BP_CHECKBOX))
        {
            out_margins.top = 1; out_margins.left = 1;
            out_margins.bottom = 1; out_margins.right = 1;
        }
        else
        {
            return false;
        }

        return true;
    }
    */

    // we should never get here, but just in case...
    return false;
}

/****************************************************************************************************/

} // namespace metrics

/****************************************************************************************************/

} // namespace adobe

/****************************************************************************************************/
