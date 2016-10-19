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

#include <adobe/name.hpp>
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
    Uroot_widget * retval = nullptr;
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

void get_control_bounds(platform_display_type control, int/*RECT*/& bounds)
{
    assert(control);

    // TODO ::GetWindowRect(control, &bounds);
}

/****************************************************************************************************/

void set_control_bounds(platform_display_type control, const place_data_t& place_data)
{
    assert(control);

    // TODO ::MoveWindow(control, left(place_data), top(place_data), width(place_data), height(place_data), TRUE);
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

void set_font(platform_display_type window, int uxtheme_type)
{
    // TODO: Take a different font parameter, and set it on window.
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
