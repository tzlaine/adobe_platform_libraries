/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#ifndef ADOBE_METRICS_HPP
#define ADOBE_METRICS_HPP

/****************************************************************************************************/

#include <adobe/config.hpp>

#include <adobe/extents.hpp>
#include <adobe/future/widgets/headers/widget_utils.hpp>

#include <string>

/****************************************************************************************************/

namespace adobe {

/****************************************************************************************************/

/// The adobe::metrics suite of functions can fetch information
/// on ideal widget sizes. The design of this suite is to provide
/// simple metric and text information for a particular widget, and
/// require clients of the function suite to compose the metrics
/// information in a way that is meaningful for them.

/****************************************************************************************************/

namespace metrics {

/****************************************************************************************************/

/// Get the extents for the given text string, in the specified font.

inline FVector2D get_text_extents(std::string const & text, FSlateFontInfo const & font_info)
{
    const TSharedRef<FSlateFontMeasure> font_measure =
        FSlateApplication::Get().GetRenderer()->GetFontMeasureService();
    return font_measure->Measure(FText::FromString(text.c_str()), font_info, 1.0f);
}

/****************************************************************************************************/

//
/// Measure text (given a control and font) and return the optimal extents.
//

/****************************************************************************************************/

FVector2D get_size(struct slider_t const & control);
FVector2D get_size(struct checkbox_t const & control);
FVector2D get_size(struct radio_button_t const & control);
FVector2D get_size(struct group_t const & control);

template <typename Control>
FVector2D get_size(Control const & control)
{ return FVector2D(); }

/****************************************************************************************************/

template <typename Control>
extents_t measure_text(std::string const & text, Control const & control, FSlateFontInfo const & font_info)
{
    extents_t result;

    const TSharedRef<FSlateFontMeasure> font_measure =
        FSlateApplication::Get().GetRenderer()->GetFontMeasureService();

    FVector2D const text_extents = get_text_extents(text, font_info);
    FVector2D const widget_size = get_size(control);

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

    long const text_height = font_measure->GetMaxCharacterHeight(font_info, 1.0f);

    long const widget_width = widget_size.X;
    long const widget_height = widget_size.Y;

    long baseline = std::abs(font_measure->GetBaseline(font_info, 1.0f));
    baseline += std::max(0l, (widget_height - text_height) / 2);

    result.slice_m[extents_slices_t::vertical].guide_set_m.push_back(baseline);

    result.width() += widget_width;
    result.height() += widget_height;

    result.width() += text_extents.X;
    result.height() = std::max<int>(result.height(), text_height);

    return result;
}

/****************************************************************************************************/

} // namespace metrics

/****************************************************************************************************/

} // namespace adobe

/****************************************************************************************************/

#endif

/****************************************************************************************************/
