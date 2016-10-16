/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#ifndef BUILD_FOR_TEST
#include "Spaceport.h"
#endif

#include <adobe/future/cursor.hpp>
#include <adobe/future/image_slurp.hpp>
#include <adobe/future/resources.hpp>
#include <adobe/future/source/cursor_stack.hpp>
#include <adobe/memory.hpp>
#include <boost/gil/algorithm.hpp>
#include <boost/gil/image.hpp>
#include <boost/gil/typedefs.hpp>
#include <boost/gil/rgba.hpp>

/****************************************************************************************************/

adobe_cursor_t make_cursor(const char* cursor_path, float hot_spot_x, float hot_spot_y)
{
    boost::gil::rgba8_image_t cursor_image;

    adobe::image_slurp(boost::filesystem::path(cursor_path, boost::filesystem::native), cursor_image);

#if 0 // TODO
    HBITMAP cursor_bitmap(adobe::to_bitmap(cursor_image));
    HCURSOR result(adobe::to_cursor(cursor_bitmap, static_cast<int>(hot_spot_x), static_cast<int>(hot_spot_y)));

    ::DeleteObject(cursor_bitmap);
    
    return hackery::cast<adobe_cursor_t>(result);
#else
    return adobe_cursor_t();
#endif
}

/****************************************************************************************************/

void push_cursor(adobe_cursor_t cursor)
{
    cursor_stack_push(cursor);

    // TODO ::SetCursor(hackery::cast<HCURSOR>(cursor));
}

/****************************************************************************************************/

adobe_cursor_t pop_cursor()
{
    adobe_cursor_t old_cursor = cursor_stack_top();

    cursor_stack_pop();

    adobe_cursor_t new_cursor = cursor_stack_top();

    if (new_cursor)
    {
        // TODO ::SetCursor(hackery::cast<HCURSOR>(new_cursor));
    }
    else
    {
       // TODO ::SetCursor(hackery::cast<HCURSOR>(IDC_ARROW));
    }

    return old_cursor;
}

/****************************************************************************************************/

void reset_cursor()
{
    cursor_stack_reset();

    // TODO ::SetCursor(hackery::cast<HCURSOR>(IDC_ARROW));
}

/****************************************************************************************************/

void delete_cursor(adobe_cursor_t cursor)
{
    // TODO ::DestroyCursor(hackery::cast<HCURSOR>(cursor));
}

/****************************************************************************************************/
