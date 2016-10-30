/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#ifndef BUILD_FOR_TEST
#include "Spaceport.h"
#endif

#include <adobe/future/widgets/headers/platform_label.hpp>

#include <adobe/future/widgets/headers/display.hpp>
#include <adobe/future/widgets/headers/widget_utils.hpp>
#include <adobe/future/widgets/headers/platform_metrics.hpp>
#include <adobe/placeable_concept.hpp>
#include <string>
#include <cassert>

/****************************************************************************************************/

namespace adobe {

/****************************************************************************************************/

label_t::label_t(const std::string& name,
                 const std::string& alt_text,
                 std::size_t characters) :
    control_m(),
    name_m(name),
    alt_text_m(alt_text),
    characters_m(characters)
{ }

/****************************************************************************************************/

label_t::~label_t()
{ }

/****************************************************************************************************/

void place(label_t& value, const place_data_t& place_data)
{
    implementation::set_control_bounds(value.control_m, place_data);

    if (!value.alt_text_m.empty())
        implementation::set_control_alt_text(value.control_m, value.alt_text_m);
}

/****************************************************************************************************/

void measure(label_t& value, extents_t& result)
{
    assert(value.control_m);

    FVector2D characters_extents(10000, 10000);
    if (value.characters_m) {
        std::string const text(value.characters_m * 2, '0');
        characters_extents = metrics::get_text_extents(text, value.control_m->Font);
    }

    FVector2D const text_extents = metrics::get_text_extents(value.name_m, value.control_m->Font);

    result.horizontal().length_m = (std::min)(text_extents.X, characters_extents.X);
    result.vertical().length_m = 10000;

    assert(result.horizontal().length_m);
}

/****************************************************************************************************/

void measure_vertical(label_t& label,
                      extents_t& calculated_horizontal, 
                      const place_data_t& placed_horizontal)
{ measure_vertical(label.control_m, calculated_horizontal, placed_horizontal); }

/****************************************************************************************************/

void measure_vertical(Ustyleable_text_block * control,
                      extents_t& calculated_horizontal, 
                      const place_data_t& placed_horizontal)
{
    assert(control);

    control->set_wrap_width(width(placed_horizontal));
    control->TakeWidget();
    control->SynchronizeProperties();
    control->ForceLayoutPrepass();
    FVector2D const desired_size = control->GetDesiredSize();

    extents_t::slice_t & vert = calculated_horizontal.vertical();
    vert.length_m = desired_size.Y;

    long const baseline = metrics::measure_baseline(control->Font);
    vert.guide_set_m.push_back(baseline);
    // TODO: Originally this was:
    // distance from top to baseline
    // vert.guide_set_m.push_back(widget_tm.tmHeight - widget_tm.tmDescent);
    // ... but the original code does not match what was in measure_text()
}

/****************************************************************************************************/

void enable(label_t& value, bool make_enabled)
{ set_control_enabled(value.control_m, make_enabled); }

/****************************************************************************************************/

void initialize(label_t& label, platform_display_type parent)
{
    assert(!label.control_m);

    auto root = implementation::get_root_widget(parent);

    if (root == nullptr)
        ADOBE_THROW_LAST_ERROR;

    label.control_m = root->new_child<Ustyleable_text_block>().widget_;

    if (label.control_m == nullptr)
        ADOBE_THROW_LAST_ERROR;

    label.control_m->SetText(FText::FromString(FString(label.name_m.c_str())));

    if (!label.alt_text_m.empty())
        implementation::set_control_alt_text(label.control_m, label.alt_text_m);
}

/****************************************************************************************************/

extents_t measure_text(const std::string& text, UTextBlock * text_block)
{
    assert(text_block);
    label_t temp(std::string(), std::string(), 0);
    return metrics::measure_text(text, temp, text_block->Font);
}

/****************************************************************************************************/

void measure_label_text(const label_t& label, extents_t& result)
{
    label_t& temp(const_cast<label_t&>(label));

    assert(temp.control_m);

    measure(temp, result);
    place_data_t p;
    p.horizontal().length_m = result.width();
    measure_vertical(temp, result, p);
}

/****************************************************************************************************/

std::string get_control_string(const label_t& widget)
{
    UTextBlock* text_block = dynamic_cast<UTextBlock*>(widget.control_m);
    return TCHAR_TO_UTF8(*text_block->GetText().ToString());
}

/****************************************************************************************************/

// REVISIT: MM--we need to replace the display_t mechanism with concepts/any_*/
//              container idiom for event and drawing system.

template <>
platform_display_type insert<label_t>(display_t& display,
                                      platform_display_type& parent,
                                      label_t& element)
{
    initialize(element, parent);
    return display.insert(parent, get_display(element));
}


/****************************************************************************************************/

} // namespace adobe

/****************************************************************************************************/
