/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#ifndef BUILD_FOR_TEST
#include "Spaceport.h"
#endif

#include <adobe/future/number_formatter.hpp>
#include <adobe/future/widgets/headers/display.hpp>
#include <adobe/future/widgets/headers/widget_utils.hpp>
#include <adobe/future/widgets/headers/platform_display_number.hpp>
#include <adobe/future/widgets/headers/platform_label.hpp>
#include <adobe/future/widgets/headers/platform_metrics.hpp>
#include <adobe/unicode.hpp>

#include <string>
#include <cassert>
#include <sstream>

/****************************************************************************************************/

namespace {

/****************************************************************************************************/

std::string set_field_text(std::string label,
                           double value,
                           const std::vector<adobe::unit_t>& unit_set,
                           std::string::size_type* label_chars=0)
{
    std::stringstream result;

    // this is called by a subview when its value changes.
    // we are only concerned with changing our actual value when
    // the view that changed is also the current view.

    std::string suffix;
    adobe::number_formatter_t number_formatter;

    if (!unit_set.empty())
    {
        std::vector<adobe::unit_t>::const_iterator i(unit_set.begin());
        std::vector<adobe::unit_t>::const_iterator end(unit_set.end());

        while (i != end && i->scale_m_m <= value)
            ++i;

        if (i != unit_set.begin())
            --i;

        value = adobe::to_base_value(value, *i);

        suffix = i->name_m;

        number_formatter.set_format(i->format_m);
    }

    if (!label.empty())
    {
        result << label << " ";

        if(label_chars)
            *label_chars = label.length();
    }

    result << number_formatter.format(value);

    if (!suffix.empty())
        result << " " << suffix;

    return result.str();
}

/****************************************************************************************************/

} // namespace

/****************************************************************************************************/

namespace adobe {

/****************************************************************************************************/

void display_number_t::place(const place_data_t& place_data)
{
    assert(control_m);
    implementation::set_control_bounds(control_m, place_data);
}

/****************************************************************************************************/

void display_number_t::display(const model_type& value)
{
    assert(control_m);
    std::string const & value_text = set_field_text(name_m, value, unit_set_m);
    control_m->SetText(FText::FromString(FString(value_text.c_str())));
}

/****************************************************************************************************/

void display_number_t::measure(extents_t& result)
{
    assert(control_m);

    label_t tmp("", "", 0);

    extents_t space_extents =
        metrics::measure_text(" ", tmp, control_m->Font);
    extents_t unit_max_extents;
    extents_t label_extents =
        metrics::measure_text(name_m, tmp, control_m->Font);
    extents_t characters_extents =
        metrics::measure_text(std::string(characters_m, '0'), tmp, control_m->Font);

    for (unit_t const & unit : unit_set_m) {
        extents_t tmp_extents(metrics::measure_text(unit.name_m, tmp, control_m->Font));

        if (tmp_extents.width() > unit_max_extents.width())
            unit_max_extents = tmp_extents;
    }

    // set up default settings (baseline, etc.)
    result = space_extents;

    // set the width to the label width (if any)
    result.width() = label_extents.width();

    // add a guide for the label
    result.horizontal().guide_set_m.push_back(label_extents.width());

    // if there's a label, add space for a space
    if (label_extents.width() != 0)
        result.width() += space_extents.width();

    // append the character extents (if any)
    result.width() += characters_extents.width();

    // if there are character extents, add space for a space
    if (characters_extents.width() != 0)
        result.width() += space_extents.width();

    // append the max unit extents (if any)
    result.width() += unit_max_extents.width();

    assert(result.horizontal().length_m);
}

/****************************************************************************************************/

void display_number_t::measure_vertical(extents_t& calculated_horizontal, const place_data_t& placed_horizontal)
{ ::adobe::measure_vertical(control_m, calculated_horizontal, placed_horizontal); }

/****************************************************************************************************/

// REVISIT: MM--we need to replace the display_t mechanism with concepts/any_*/container idiom for event and drawing system.

template <>
platform_display_type insert<display_number_t>(display_t& display,
                                               platform_display_type& parent,
                                               display_number_t& element)
{
    assert(element.control_m == nullptr);

    auto root = implementation::get_root_widget(parent);

    if (root == nullptr)
        ADOBE_THROW_LAST_ERROR;

    element.control_m = root->new_child<Ustyleable_text_block>().widget_;

    if (element.control_m == nullptr)
        ADOBE_THROW_LAST_ERROR;

    element.control_m->SetText(FText::FromString(FString(element.name_m.c_str())));

    if (!element.alt_text_m.empty())
        implementation::set_control_alt_text(element.control_m, element.alt_text_m);

    return display.insert(parent, element.control_m);
}


/****************************************************************************************************/

} // namespace adobe

/****************************************************************************************************/
