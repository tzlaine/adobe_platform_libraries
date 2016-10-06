/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#ifndef ADOBE_UI_CORE_OS_UTILITIES_HPP
#define ADOBE_UI_CORE_OS_UTILITIES_HPP

#include <string>
#include <adobe/name.hpp>
#include <adobe/layout_attributes.hpp>
#include <adobe/widget_attributes.hpp>
#include <adobe/future/platform_primitives.hpp>

/****************************************************************************************************/

namespace adobe {

/****************************************************************************************************/

namespace implementation {

/****************************************************************************************************/

platform_display_type get_parent(platform_control_type control);

std::string get_window_title(platform_display_type window);

inline std::string get_control_string(platform_control_type control)
{ return implementation::get_window_title(control); }

void get_control_bounds(platform_control_type control, int/*RECT*/& bounds);

void set_control_bounds(platform_control_type control, const place_data_t& place_data);

template <typename T>
inline std::string get_field_text(T& x)
{ return get_control_string(x.control_m); }

template <>
inline std::string get_field_text<platform_control_type>(platform_control_type& x)
{ return get_control_string(x); }

/****************************************************************************************************/

template <typename T>
inline bool is_focused(T& control)
{ return is_focused(control.control_m); }

template <>
inline bool is_focused(platform_control_type& control)
{ return false/*::GetFocus() == control*/; }

/****************************************************************************************************/

void throw_last_error_exception(const char* file, long line);

/****************************************************************************************************/

} // namespace implementation

/****************************************************************************************************/

#if 0 // TODO
//
/// Win32's event mechanism is tweaked in that sometimes a parent of a widget is called when the user
/// changes something about the widget. forward_message is intended to let the pertinent window have
/// a stab at the event. We want to use the window's standard message handling system so we don't have
/// to introduce any new event hierarchies.
///
/// /return true if the forward_result should be used as a return value; false otherwise.
//

bool forward_message(UINT message, WPARAM wParam, LPARAM lParam, LRESULT& forward_result);

/****************************************************************************************************/
#endif

//
/// Information on the uxtheme_type parameter's values is
/// available in the "Parts and States" documentation here:
/// http://msdn.microsoft.com/library/default.asp?url=/library/en-us/shellcc/platform/commctls/userex/topics/partsandstates.asp
//

void set_font(platform_display_type window, int uxtheme_type);

/****************************************************************************************************/

inline void set_control_visible(platform_control_type control, bool make_visible)
{
    assert(control);

    // TODO ::ShowWindow(control, make_visible ? SW_SHOWNORMAL : SW_HIDE);
}

/****************************************************************************************************/

inline void set_control_enabled(platform_control_type control, bool make_enabled)
{
    assert(control);

    // TODO ::EnableWindow(control, make_enabled);
}

/****************************************************************************************************/

bool context_menu(platform_display_type parent,
                  long x, long y,
                  const name_t* first,
                  const name_t* last,
                  name_t& result);

/****************************************************************************************************/

#if 0
#if 1 // TODO
void* /*LONG_PTR*/ get_user_reference(platform_control_type control);
#endif

/****************************************************************************************************/

template <typename T>
void set_user_reference(platform_control_type control, T data)
{
    assert(control);

    // TODO ::SetWindowLongPtr(control, GWLP_USERDATA, hackery::cast<LONG>(data));
}

/****************************************************************************************************/
#endif

modifiers_t convert_modifiers(unsigned long/*ULONG*/ os_modifiers);
modifiers_t convert_modifiers(char/*BYTE*/  keyboard_state[256]);

modifiers_t modifier_state();

/****************************************************************************************************/

} // namespace adobe

/****************************************************************************************************/

#ifndef ADOBE_THROW_LAST_ERROR
    #define ADOBE_THROW_LAST_ERROR adobe::implementation::throw_last_error_exception(__FILE__, __LINE__)
#endif

/****************************************************************************************************/

#endif
