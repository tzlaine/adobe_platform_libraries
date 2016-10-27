/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#ifndef BUILD_FOR_TEST
#include "Spaceport.h"
#endif

#include <adobe/future/widgets/headers/platform_button.hpp>

#include <adobe/future/widgets/headers/platform_label.hpp>

#include <adobe/future/widgets/headers/button_helper.hpp>
#include <adobe/future/widgets/headers/display.hpp>
#include <adobe/future/widgets/headers/platform_metrics.hpp>


/****************************************************************************************************/

namespace adobe {

/****************************************************************************************************/

namespace {

void button_clicked (button_t & button)
{
    button_state_set_t::iterator state(
        button_modifier_state(button.state_set_m,
                                     button.modifier_mask_m,
                                     button.modifiers_m)
    );

    if (state == button.state_set_m.end())
        state = button_default_state(button.state_set_m);

    if (!state->hit_proc_m.empty())
        state->hit_proc_m(state->value_m, state->contributing_m);

    if (!state->clicked_proc_m.empty())
        state->clicked_proc_m(state->value_m);
}

}

/****************************************************************************************************/

button_t::button_t(bool is_default, bool is_cancel) :
    control_m(),
    control_text_m(),
    modifier_mask_m(modifiers_none_s),
    modifiers_m(modifiers_none_s),
    is_default_m(is_default),
    is_cancel_m(is_cancel),
    enabled_m(true)
{ }

/****************************************************************************************************/

void button_t::measure(extents_t& result)
{
    button_state_set_t::iterator state(button_modifier_state(state_set_m,
                                                             modifier_mask_m,
                                                             modifiers_m));

    if (state == state_set_m.end())
        state = button_default_state(state_set_m);

    extents_t cur_text_extents(measure_text(state->name_m, control_text_m));

    result = cur_text_extents;

    result.width() -= cur_text_extents.width();
    result.height() -= cur_text_extents.height();

    long width_additional(0);
    long height_additional(0);

    for (button_state_set_t::iterator iter(state_set_m.begin()), last(state_set_m.end()); iter != last; ++iter)
    {
        extents_t tmp(measure_text(iter->name_m, control_text_m));

        width_additional = std::max<int>(width_additional, tmp.width());
        height_additional = std::max<int>(height_additional, tmp.height());
    }

    result.width() += width_additional;
    result.height() += height_additional;

    // If there was no text...
    if (!width_additional) {
        FVector2D const normal_size = control_m->WidgetStyle.Normal.ImageSize;
        FVector2D const hovered_size = control_m->WidgetStyle.Hovered.ImageSize;
        FVector2D const pressed_size = control_m->WidgetStyle.Pressed.ImageSize;
        FVector2D const disabled_size = control_m->WidgetStyle.Disabled.ImageSize;

        result.width() = (std::max)(
            (std::max)(normal_size.X, hovered_size.X),
            (std::max)(pressed_size.X, disabled_size.X)
        );
        result.height() = (std::max)(
            (std::max)(normal_size.Y, hovered_size.Y),
            (std::max)(pressed_size.Y, disabled_size.Y)
        );
    }

    // TODO (probably inappropriate in UE4): result.width() = std::max<int>(result.width(), 70L);
}

/****************************************************************************************************/

void button_t::place(const place_data_t& place_data)
{
    assert(control_m);
    implementation::set_control_bounds(control_m, place_data);
}

/****************************************************************************************************/

void button_t::enable(bool make_enabled)
{
    enabled_m = make_enabled;
    if (control_m)
        set_control_enabled(control_m, make_enabled);
}

/****************************************************************************************************/

void button_t::set(modifiers_t modifiers, const model_type& value)
{
    button_state_set_t::iterator state(button_modifier_state(state_set_m, modifier_mask_m, modifiers));

    if (state == state_set_m.end())
        state = button_default_state(state_set_m);

    if (state->value_m != value)
        state->value_m = value;
}

/****************************************************************************************************/

void button_t::set_contributing(modifiers_t modifiers, const dictionary_t& value)
{
    button_state_set_t::iterator state(button_modifier_state(state_set_m, modifier_mask_m, modifiers));

    if (state == state_set_m.end())
        state = button_default_state(state_set_m);

    state->contributing_m = value;
}

/****************************************************************************************************/

bool button_t::handle_key(key_type key, bool pressed, modifiers_t /* modifiers */)
{
    if (pressed == false)
        return false;

    modifiers_m = modifier_state();

    //
    // Look up the state which this modifier should trigger.
    //
    button_state_set_t::iterator state(button_modifier_state(state_set_m,
                                                             modifier_mask_m,
                                                             modifiers_m));

    if (state == state_set_m.end())
        state = button_default_state(state_set_m);

    //
    // Set the window text.
    //
    control_text_m->SetText(FText::FromString(FString(state->name_m.c_str())));

    //
    // Set the alt text if need be.
    //
    if (!state->alt_text_m.empty())
        implementation::set_control_alt_text(control_m, state->alt_text_m);

    if (state->hit_proc_m.empty() || enabled_m == false)
        return false;

    if (false/*TODO key == VK_RETURN*/ && is_default_m) // return
    {
        state->hit_proc_m(state->value_m, state->contributing_m);
    }
    else if (false/*TODO key == VK_ESCAPE*/ && is_cancel_m) // escape
    {
        state->hit_proc_m(state->value_m, state->contributing_m);
    }
    else
    {
        return false;
    }

    return true;
}

/****************************************************************************************************/

template <>
platform_display_type insert<button_t>(display_t& display,
                                       platform_display_type& parent,
                                       button_t& element)
{
    assert(element.control_m == nullptr);
    assert(element.control_text_m == nullptr);

    auto root = implementation::get_root_widget(parent);

    if (root == nullptr)
        ADOBE_THROW_LAST_ERROR;

    element.control_m = root->new_child<Ustyleable_button>().widget_;
    element.control_text_m = root->new_child<Ustyleable_text_block>().widget_;

    if (element.control_m == nullptr || element.control_text_m == nullptr)
        ADOBE_THROW_LAST_ERROR;

    element.control_m->SetContent(element.control_text_m);

    button_state_set_t::iterator state(button_default_state(element.state_set_m));

    element.control_text_m->SetText(FText::FromString(FString(state->name_m.c_str())));

    element.control_m->set_signal_forward_fn([&element]() { button_clicked(element); });
    element.control_m->OnClicked.AddDynamic(element.control_m, &Ustyleable_button::forward_signal);

    if (!state->alt_text_m.empty())
        implementation::set_control_alt_text(element.control_m, state->alt_text_m);

    return display.insert(parent, element.control_m);
}

/****************************************************************************************************/

} // namespace adobe

/****************************************************************************************************/
