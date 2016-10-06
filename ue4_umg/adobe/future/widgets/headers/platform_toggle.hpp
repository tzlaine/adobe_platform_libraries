/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#ifndef ADOBE_WIDGET_TOGGLE_HPP
#define ADOBE_WIDGET_TOGGLE_HPP

/****************************************************************************************************/

#include <adobe/config.hpp>

#include <adobe/any_regular.hpp>
#include <adobe/layout_attributes.hpp>
#include <adobe/widget_attributes.hpp>
#include <adobe/future/platform_primitives.hpp>

#include <boost/function.hpp>
#include <boost/gil/gil_all.hpp>

/****************************************************************************************************/

namespace adobe {

/****************************************************************************************************/

struct toggle_t
{
    typedef any_regular_t model_type;

    typedef boost::function<void (const model_type&)> setter_type;

    typedef boost::gil::rgba8_image_t image_type;

    toggle_t(const std::string&  alt_text,
             const any_regular_t value_on,
             const image_type&   image_on,
             const image_type&   image_off,
             const image_type&   image_disabled,
             theme_t             theme);

    void measure(extents_t& result);

    void place(const place_data_t& place_data);

    void monitor(const setter_type& proc);

    void enable(bool make_enabled);

    void display(const any_regular_t& to_value);

#ifndef ADOBE_NO_DOCUMENTATION
#if 1 // TODO
    platform_control_type control_m;
#endif
    theme_t                    theme_m;
    std::string                alt_text_m;
    image_type                 image_on_m;
    image_type                 image_off_m;
    image_type                 image_disabled_m;
    setter_type                setter_proc_m;
    any_regular_t              value_on_m;
    any_regular_t              last_m;
#if 0 // TODO
    HBITMAP                    bitmap_on_m;
    HBITMAP                    bitmap_off_m;
    HBITMAP                    bitmap_disabled_m;
#endif
#endif
};

/****************************************************************************************************/

} // namespace adobe

/****************************************************************************************************/

#endif

/****************************************************************************************************/
