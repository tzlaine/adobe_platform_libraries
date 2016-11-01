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

struct slider_t;
struct checkbox_t;
struct radio_button_t;
struct group_t;

/****************************************************************************************************/

/// The adobe::metrics suite of functions can fetch information
/// on ideal widget sizes. The design of this suite is to provide
/// simple metric and text information for a particular widget, and
/// require clients of the function suite to compose the metrics
/// information in a way that is meaningful for them.

/****************************************************************************************************/

namespace metrics {

/****************************************************************************************************/

namespace detail {

/****************************************************************************************************/

float measurement_size (FSlateFontInfo const & font_info);

/****************************************************************************************************/

}

/****************************************************************************************************/

/// Get the extents for the given text string, in the specified font.

FVector2D get_text_extents(std::string const & text, FSlateFontInfo const & font_info);

/****************************************************************************************************/

float measure_baseline(TSharedRef<FSlateFontMeasure> const & font_measure,
                       FSlateFontInfo const & font_info);

/****************************************************************************************************/

float measure_baseline(FSlateFontInfo const & font_info);

/****************************************************************************************************/

//
/// Measure text (given a control and font) and return the optimal extents.
//

/****************************************************************************************************/

FVector2D get_size (slider_t const & control);
FVector2D get_size (group_t const & control);

template <typename Control>
FVector2D get_size (Control const & control)
{ return FVector2D(0, 0); }

/****************************************************************************************************/

extents_t measure_text (
    std::string const & text,
    FVector2D size_without_text,
    FSlateFontInfo const & font_info
);

/****************************************************************************************************/

template <typename Control>
extents_t measure_text (std::string const & text, Control const & control, FSlateFontInfo const & font_info)
{ return measure_text(text, get_size(control), font_info); }

/****************************************************************************************************/

} // namespace metrics

/****************************************************************************************************/

} // namespace adobe

/****************************************************************************************************/

#endif

/****************************************************************************************************/
