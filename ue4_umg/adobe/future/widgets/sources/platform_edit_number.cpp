/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#ifndef BUILD_FOR_TEST
#include "Spaceport.h"
#endif

#include <adobe/future/widgets/headers/edit_number.hpp>

/****************************************************************************************************/

namespace adobe {

/****************************************************************************************************/

void edit_number_platform_data_t::initialize()
{
    if (!control_m->edit_text_m.using_label_m)
        return;

    /* TODO
    HWND label(control_m->edit_text_m.name_m.window_m);

    ::SetWindowSubclass(label,
                        &edit_number_label_cursor_handler,
                        hackery::cast<UINT_PTR>(this),
                        0);
    */
}

/****************************************************************************************************/

/* TODO: Deal with these events in a platform-specific way.
LRESULT edit_number_platform_data_t::label_message(UINT message, WPARAM wParam, LPARAM lParam)
{
    HWND label(control_m->edit_text_m.name_m.window_m);

    if (message == WM_NCHITTEST)
    {
        return HTCLIENT;
    }
    else if (message == WM_SETCURSOR)
    {
        static HCURSOR scrubby(0);
        static bool    inited(false);

        if (!inited)
        {
            inited = true;

            try {
                scrubby = hackery::cast<HCURSOR>(edit_number_t::scrubby_cursor());
            }
            catch (...)
            { }
        }

        if (scrubby)
            ::SetCursor(scrubby);

        return 0;
    }
    else if (message == WM_MOUSEMOVE && tracking_m)
    {
        POINTS new_point(MAKEPOINTS(lParam));
        long   delta(last_point_m.y - new_point.y);

        if (last_point_m.y != 0 && delta != 0)
        {
            modifiers_t modifiers(modifier_state());

            if (modifiers & modifiers_any_shift_s)
                delta *= 10;

            control_m->increment_n(delta);
        }

        last_point_m = new_point;
    }
    else if (message == WM_LBUTTONDOWN)
    {
        tracking_m = true;
        prev_capture_m = ::SetCapture(label);
        last_point_m.y = 0;
        last_point_m.x = 0;

        return 0;
    }
    else if (message == WM_LBUTTONUP)
    {
        tracking_m = false;
        ::SetCapture(prev_capture_m);

        return 0;
    }

    return ::DefSubclassProc(label, message, wParam, lParam);
}
*/

/****************************************************************************************************/

edit_number_platform_data_t::~edit_number_platform_data_t()
{ }

/****************************************************************************************************/

} // namespace adobe

/****************************************************************************************************/
