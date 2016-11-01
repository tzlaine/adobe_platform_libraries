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

FVector2D get_text_extents(std::string const & text, FSlateFontInfo const & font_info)
{
    const TSharedRef<FSlateFontMeasure> font_measure =
        FSlateApplication::Get().GetRenderer()->GetFontMeasureService();
    return font_measure->Measure(
        FText::FromString(text.c_str()),
        font_info,
        detail::measurement_size(font_info)
    );
}

/****************************************************************************************************/

float measure_baseline(TSharedRef<FSlateFontMeasure> const & font_measure,
                       FSlateFontInfo const & font_info)
{ return std::abs(font_measure->GetBaseline(font_info, detail::measurement_size(font_info))); }

/****************************************************************************************************/

float measure_baseline(FSlateFontInfo const & font_info)
{
    TSharedRef<FSlateFontMeasure> const font_measure =
        FSlateApplication::Get().GetRenderer()->GetFontMeasureService();
    return measure_baseline(font_measure, font_info);
}

/****************************************************************************************************/

FVector2D get_size (slider_t const & control)
{ return FVector2D(8, 8); /* minimal tab size */ }

FVector2D get_size (group_t const & control)
{ return FVector2D(8, 8); }

/****************************************************************************************************/

extents_t measure_text (
    std::string const & text,
    FVector2D size_without_text,
    FSlateFontInfo const & font_info
) {
    extents_t result;

    const TSharedRef<FSlateFontMeasure> font_measure =
        FSlateApplication::Get().GetRenderer()->GetFontMeasureService();

    FVector2D const text_extents = get_text_extents(text, font_info);

    //
    // Now we can calculate the baseline of this widget. There are two cases:
    //
    //  (a) The text height is larger or the same as the widget height.
    //  (b) The text height is smaller than the widget height.
    //
    // The height which we return as our best bound is the maximum of the
    // text height and the widget height (with margins added).
    //
    // In case (a) the baseline (measured from the top) is the ascent of the
    // text plus the top margin. In case (b) the baseline is the ascent of the
    // text plus the top margin, plus (widget height - text height)/2.
    //

    long const text_height =
        font_measure->GetMaxCharacterHeight(font_info, detail::measurement_size(font_info));

    long const widget_width = size_without_text.X;
    long const widget_height = size_without_text.Y;

    long baseline = measure_baseline(font_measure, font_info);
    baseline += std::max(0l, (widget_height - text_height) / 2);

    result.slice_m[extents_slices_t::vertical].guide_set_m.push_back(baseline);

    result.width() += widget_width;
    result.height() += widget_height;

    result.width() += text_extents.X;
    result.height() = std::max<int>(result.height(), text_height);

    return result;
}

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
