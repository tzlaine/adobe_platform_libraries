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

Uroot_widget * get_root_widget (platform_display_type control);

std::string get_window_title(platform_display_type window);

void get_control_bounds(platform_display_type control, FBox2D & bounds);

void set_control_bounds(platform_display_type control, const place_data_t& place_data);

/****************************************************************************************************/

template <typename T>
inline bool is_focused(T const & control)
{ return is_focused(control.control_m); }

template <>
inline bool is_focused(platform_display_type const & control)
{ return control->HasKeyboardFocus(); }

/****************************************************************************************************/

void throw_last_error_exception(const char* file, long line);

/****************************************************************************************************/

} // namespace implementation

/****************************************************************************************************/

inline void set_control_visible(platform_display_type control, bool make_visible)
{
    assert(control);
    control->SetVisibility(make_visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

/****************************************************************************************************/

inline void set_control_enabled(platform_display_type control, bool make_enabled)
{
    assert(control);
    control->SetIsEnabled(make_enabled);
}

/****************************************************************************************************/

bool context_menu(platform_display_type parent,
                  long x, long y,
                  const name_t* first,
                  const name_t* last,
                  name_t& result);

/****************************************************************************************************/

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
