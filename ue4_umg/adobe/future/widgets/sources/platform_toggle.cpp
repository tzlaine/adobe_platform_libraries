/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#include <adobe/future/widgets/headers/platform_toggle.hpp>

#include <adobe/future/widgets/headers/button_helper.hpp>
#include <adobe/future/widgets/headers/display.hpp>
#include <adobe/future/widgets/headers/widget_utils.hpp>

/****************************************************************************************************/

namespace {

/****************************************************************************************************/

adobe::toggle_t::texture_type to_texture(adobe::toggle_t::image_type const & image)
{
    return adobe::toggle_t::texture_type(); // TODO
}

/****************************************************************************************************/

bool enabled(adobe::platform_control_type control)
{
    return false; // TODO
}

/****************************************************************************************************/

const adobe::toggle_t::image_type& current_image(adobe::toggle_t& toggle)
{
    if (enabled(toggle.control_m))
    {
        if (toggle.last_m == toggle.value_on_m)
            return toggle.image_on_m;
        else
            return toggle.image_off_m;
    }
    else // disabled_button
    {
        return toggle.image_disabled_m;
    }
}

/****************************************************************************************************/

adobe::toggle_t::texture_type current_texture(adobe::toggle_t& toggle)
{
    if (enabled(toggle.control_m))
    {
        if (toggle.last_m == toggle.value_on_m)
            return toggle.texture_on_m;
        else
            return toggle.texture_off_m;
    }
    else // disabled_button
    {
        return toggle.texture_disabled_m;
    }
}

/****************************************************************************************************/

/* TODO: Add this functionality in a platform-specific way.
LRESULT CALLBACK toggle_subclass_proc(HWND     window,
                                      UINT     message,
                                      WPARAM   wParam,
                                      LPARAM   lParam,
                                      UINT_PTR ptr,
                                      DWORD_PTR ref)
{
    adobe::toggle_t& toggle(*reinterpret_cast<adobe::toggle_t*>(ptr));

    if (message == WM_COMMAND && HIWORD(wParam) == STN_CLICKED)
    {
        if (toggle.setter_proc_m.empty())
            return 0;

        // toggle it.
        adobe::any_regular_t new_value =
            toggle.last_m == toggle.value_on_m ?
                adobe::any_regular_t(adobe::empty_t()) :
                toggle.value_on_m;

        toggle.setter_proc_m(new_value);

        return 0;
    }

    // nevermind.
    return DefSubclassProc(window, message, wParam, lParam);
}
*/

/****************************************************************************************************/

} // namespace

/****************************************************************************************************/

namespace adobe {

/****************************************************************************************************/

toggle_t::toggle_t(const std::string& alt_text,
                   const any_regular_t value_on,
                   const image_type& image_on,
                   const image_type& image_off,
                   const image_type& image_disabled,
                   theme_t theme) :
    control_m(0),
    theme_m(theme),
    alt_text_m(alt_text),
    image_on_m(image_on),
    image_off_m(image_off),
    image_disabled_m(image_disabled),
    value_on_m(value_on),
    texture_on_m(to_texture(image_on)),
    texture_off_m(to_texture(image_off)),
    texture_disabled_m(to_texture(image_disabled))
{ }

/****************************************************************************************************/

void toggle_t::measure(extents_t& result)
{
    assert(control_m);

    result = extents_t();

    const adobe::toggle_t::image_type& image(current_image(*this));

    result.height() = static_cast<long>(image.height());
    result.width() = static_cast<long>(image.width());
}

/****************************************************************************************************/

void toggle_t::place(const place_data_t& place_data)
{
    implementation::set_control_bounds(control_m, place_data);
}

/****************************************************************************************************/

void toggle_t::enable(bool make_enabled)
{
    assert(control_m);

    set_control_enabled(control_m, make_enabled);

    // TODO ::SendMessage(control_m, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) current_bitmap(*this));
}

/****************************************************************************************************/

void toggle_t::display(const any_regular_t& to_value)
{
    assert(control_m);

    if (last_m == to_value)
        return;

    last_m = to_value;

    // TODO ::SendMessage(control_m, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) current_bitmap(*this));
}

/****************************************************************************************************/

void toggle_t::monitor(const setter_type& proc)
{
    assert(control_m);

    setter_proc_m = proc;
}

/****************************************************************************************************/

template <>
platform_display_type insert<toggle_t>(display_t& display,
                                       platform_display_type& parent,
                                       toggle_t& element)
{
    assert(!element.control_m);

    /* TODO
    element.control_m = ::CreateWindowExW(  WS_EX_COMPOSITED | WS_EX_TRANSPARENT, L"STATIC",
                                    NULL,
                                    WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_NOTIFY,
                                    0, 0, 100, 20,
                                    parent,
                                    0,
                                    ::GetModuleHandle(NULL),
                                    NULL);

    if (element.control_m == NULL)
        ADOBE_THROW_LAST_ERROR;

    set_font(element.control_m, EP_EDITTEXT); // REVISIT (fbrereto) : a better type?

    ::SetWindowSubclass(element.control_m, &toggle_subclass_proc, reinterpret_cast<UINT_PTR>(&element), 0);
    */

    if (!element.alt_text_m.empty())
        implementation::set_control_alt_text(element.control_m, element.alt_text_m);

    return display.insert(parent, element.control_m);
}

/****************************************************************************************************/

} // namespace adobe

/****************************************************************************************************/
