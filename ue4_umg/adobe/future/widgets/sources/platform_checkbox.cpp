/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#ifndef BUILD_FOR_TEST
#include "Spaceport.h"
#endif

#include <adobe/future/widgets/headers/platform_checkbox.hpp>

#include <adobe/future/widgets/headers/widget_utils.hpp>

#include <adobe/future/widgets/headers/platform_metrics.hpp>
#include <adobe/future/widgets/headers/display.hpp>

/****************************************************************************************************/

namespace adobe {

/****************************************************************************************************/

namespace {

/****************************************************************************************************/

void checkbox_checked (checkbox_t & checkbox, bool checked)
{
    if (checkbox.hit_proc_m)
        checkbox.hit_proc_m(checked ? checkbox.true_value_m : checkbox.false_value_m);

    if (checkbox.checked_proc_m)
        checkbox.checked_proc_m(checked ? checkbox.true_value_m : checkbox.false_value_m);
}

/****************************************************************************************************/

} // namespace

/****************************************************************************************************/

checkbox_t::checkbox_t(const std::string& name,
                       const any_regular_t& true_value,
                       const any_regular_t& false_value,
                       const std::string& alt_text,
                       name_t signal_id) :
    control_m(),
    control_text_m(),
    true_value_m(true_value),
    false_value_m(false_value),
    name_m(name),
    alt_text_m(alt_text),
    signal_id_m(signal_id)
{ }

/****************************************************************************************************/

void checkbox_t::measure(extents_t& result)
{
    assert(control_m);
    result = metrics::measure_text(name_m, *this, control_text_m->Font);
}

/****************************************************************************************************/

void checkbox_t::place(const place_data_t& place_data)
{
    assert(control_m);
    implementation::set_control_bounds(control_m, place_data);
}

/****************************************************************************************************/

void checkbox_t::enable(bool make_enabled)
{
    assert(control_m);
    set_control_enabled(control_m, make_enabled);
}

/****************************************************************************************************/

void checkbox_t::display(const any_regular_t& new_value)
{
    assert(control_m);

    if (current_value_m == new_value)
        return;

    current_value_m = new_value;

    /* TODO
    WPARAM state(BST_INDETERMINATE);

    if (current_value_m == true_value_m)
        state = BST_CHECKED;
    else if (current_value_m == false_value_m)
        state = BST_UNCHECKED;

    ::SendMessage(control_m, BM_SETCHECK, state, 0);
    */
}

/****************************************************************************************************/

void checkbox_t::monitor(const setter_type& proc)
{
    assert(control_m);
    hit_proc_m = proc;
}

/****************************************************************************************************/

template <>
platform_display_type insert<checkbox_t>(display_t& display,
                                         platform_display_type& parent,
                                         checkbox_t& element)
{
    assert(element.control_m == nullptr);
    assert(element.control_text_m == nullptr);

    auto root = implementation::get_root_widget(parent);

    if (root == nullptr)
        ADOBE_THROW_LAST_ERROR;

    element.control_m = root->new_child<Ustyleable_check_box>().widget_;
    element.control_text_m = root->new_child<Ustyleable_text_block>().widget_;

    if (element.control_m == nullptr || element.control_text_m == nullptr)
        ADOBE_THROW_LAST_ERROR;

    element.control_m->SetContent(element.control_text_m);

    element.control_text_m->SetText(FText::FromString(FString(element.name_m.c_str())));

    element.control_m->set_signal_forward_fn(
        [&element](bool checked) { checkbox_checked(element, checked); }
    );
    element.control_m->OnCheckStateChanged.AddDynamic(element.control_m, &Ustyleable_check_box::forward_signal);

    if (!element.alt_text_m.empty())
        implementation::set_control_alt_text(element.control_m, element.alt_text_m);

    return display.insert(parent, element.control_m);
}

/****************************************************************************************************/

} // namespace adobe

/****************************************************************************************************/
