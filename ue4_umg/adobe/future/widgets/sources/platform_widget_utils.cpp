/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#ifndef BUILD_FOR_TEST
#include "Spaceport.h"
#endif

#include <adobe/future/widgets/headers/widget_utils.hpp>
#include <adobe/future/widgets/headers/platform_metrics.hpp>

#include <adobe/adam.hpp>
#include <adobe/adam_parser.hpp>
#include <adobe/dictionary.hpp>
#include <adobe/unicode.hpp>

#include <boost/cstdint.hpp>

#include <vector>

/****************************************************************************************************/

namespace adobe {

/****************************************************************************************************/

namespace implementation {

/****************************************************************************************************/

bool pick_file(boost::filesystem::path& path, platform_display_type dialog_parent)
{
    bool result = false;
    // TODO: Standard file chooser?
    return result;
}

/****************************************************************************************************/

bool pick_save_path(boost::filesystem::path& path, platform_display_type dialog_parent)
{
    bool result = false;
    // TODO: Standard directory chooser?
    return result;
}

/****************************************************************************************************/

void set_control_alt_text(platform_display_type control, const std::string& alt_text)
{
    control->SetToolTipText(FText::FromString(FString(alt_text.c_str())));
}

/****************************************************************************************************/

Uroot_widget * get_root_widget (platform_display_type control)
{
    Uroot_widget * retval = dynamic_cast<Uroot_widget *>(control);
    platform_display_type parent = control;
    while (parent && !retval) {
        parent = parent->GetParent();
        if (parent)
            retval = dynamic_cast<Uroot_widget *>(parent);
    }
    return retval;
}

/****************************************************************************************************/

std::string get_window_title(platform_display_type window)
{
    assert(window);
    return "";// TODO
}

/****************************************************************************************************/

void get_control_bounds(platform_display_type control, FBox2D & bounds)
{
    assert(control);

    auto const slot = Cast<UCanvasPanelSlot>(control->Slot);
    auto const pos = slot->GetPosition();
    auto const size = slot->GetSize();

    bounds = FBox2D(pos, pos + size);
}

/****************************************************************************************************/

void set_control_bounds(platform_display_type control, const place_data_t& place_data)
{
    assert(control);

    auto const slot = Cast<UCanvasPanelSlot>(control->Slot);
    slot->SetPosition(FVector2D(left(place_data), top(place_data)));
    slot->SetSize(FVector2D(width(place_data), height(place_data)));
}

/****************************************************************************************************/

void throw_last_error_exception(const char* /* file */, long /* line */)
{
    // TODO: Pop up a dialog?  Assert?
    // TODO Do this? throw std::runtime_error(the_message);
}

/****************************************************************************************************/

} // namespace implementation

/****************************************************************************************************/

bool context_menu(platform_display_type parent,
                  long x, long y,
                  const name_t* first,
                  const name_t* last,
                  name_t& result)
{
    // TODO
    return true;
}

/****************************************************************************************************/

namespace {

/****************************************************************************************************/

inline void replace_placeholder(array_t& expression, name_t name, const any_regular_t& value)
{
    for (std::size_t i = 0; i < expression.size(); ++i) {
        name_t element_name;
        if (expression[i].cast<name_t>(element_name) && element_name == name) {
            expression[i] = value;
            expression.erase(expression.begin() + i + 1);
        }
    }
}

/****************************************************************************************************/

inline void replace_placeholders(array_t& expression,
                                 const any_regular_t& _,
                                 const any_regular_t& _1,
                                 name_t _1_name,
                                 const any_regular_t& _2,
                                 name_t _2_name,
                                 const any_regular_t& _3,
                                 name_t _3_name,
                                 const any_regular_t& _4,
                                 name_t _4_name)
{
    replace_placeholder(expression, "_"_name, _);
    replace_placeholder(expression, "_1"_name, _1);
    replace_placeholder(expression, "_2"_name, _2);
    replace_placeholder(expression, "_3"_name, _3);
    replace_placeholder(expression, "_4"_name, _4);
}

/****************************************************************************************************/

} // namespace

/****************************************************************************************************/

void handle_signal(signal_notifier_t const & signal_notifier,
                   name_t widget_name,
                   name_t signal_name,
                   name_t widget_id,
                   sheet_t& sheet,
                   name_t bind,
                   array_t expression,
                   const any_regular_t& _1,
                   name_t _1_name/* = name_t()*/,
                   const any_regular_t& _2/* = any_regular_t()*/,
                   name_t _2_name/* = name_t()*/,
                   const any_regular_t& _3/* = any_regular_t()*/,
                   name_t _3_name/* = name_t()*/,
                   const any_regular_t& _4/* = any_regular_t()*/,
                   name_t _4_name/* = name_t()*/)
{
    if (!bind && !signal_notifier)
        return;

    // TODO: If value is an adam_function_t, call it with the given parameters
    // instead of trying to use placeholders.

    any_regular_t _;
    {
        dictionary_t dict;

        std::size_t count = 0;
        if (_1_name) {
            dict[_1_name] = _1;
            ++count;
        }
        if (_2_name) {
            dict[_2_name] = _2;
            ++count;
        }
        if (_3_name) {
            dict[_3_name] = _3;
            ++count;
        }
        if (_4_name) {
            dict[_4_name] = _4;
            ++count;
        }

        if (count <= 1) {
            _ = _1;
        } else {
            assert(_1_name);
            _ = any_regular_t(dict);
        }
    }

    any_regular_t value;
    if (expression.empty()) {
        value = _;
    } else {
        replace_placeholders(expression, _, _1, _1_name, _2, _2_name, _3, _3_name, _4, _4_name);
        value = sheet.inspect(expression);
    }

    if (bind) {
        sheet.set(bind, value);
        sheet.update();
    } else if (signal_notifier) {
        signal_notifier(widget_name, signal_name, widget_id, value);
    }
}

/****************************************************************************************************/

void cell_and_expression(const any_regular_t& value, name_t& cell, array_t& expression)
{
    array_t cell_and_expression;
    value.cast<name_t>(cell);
    if (!cell && value.cast<array_t>(cell_and_expression)) {
        cell = cell_and_expression[0].cast<name_t>();
        const std::string& expression_string = cell_and_expression[1].cast<std::string>();
        expression = parse_adam_expression(expression_string);
    }
}

/****************************************************************************************************/

modifiers_t convert_modifiers(unsigned long/*ULONG*/ os_modifiers)
{
    modifiers_t result(modifiers_none_s);

    /* TODO: Handle:
       modifiers_caps_lock_s
       modifiers_any_control_s
       modifiers_any_shift_s
       modifiers_any_option_s
    */

    return result;
}

/****************************************************************************************************/

modifiers_t convert_modifiers(char/*BYTE*/ keyboard_state[256])
{
    modifiers_t result(modifiers_none_s);

    /* TODO: Handle:
       result |= modifiers_caps_lock_s;
       result |= modifiers_left_shift_s;
       result |= modifiers_right_shift_s;
       result |= modifiers_left_control_s;
       result |= modifiers_right_control_s;
       result |= modifiers_left_option_s;
       result |= modifiers_right_option_s;
    */

    return result;
}

/****************************************************************************************************/

modifiers_t modifier_state()
{
    // TODO: Read the current modifeir state and return it.
    return modifiers_t();
}

/****************************************************************************************************/

platform_display_type get_top_level_window(platform_display_type thing)
{
    return nullptr; // TODO
}

/****************************************************************************************************/

} // namespace adobe

/****************************************************************************************************/
