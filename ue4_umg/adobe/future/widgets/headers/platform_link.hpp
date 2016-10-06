/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#ifndef ADOBE_WIDGET_LINK_HPP
#define ADOBE_WIDGET_LINK_HPP

/****************************************************************************************************/

#include <adobe/config.hpp>

#include <adobe/any_regular.hpp>
#include <adobe/extents.hpp>
#include <adobe/layout_attributes.hpp>
#include <adobe/widget_attributes.hpp>
#include <adobe/future/platform_primitives.hpp>

#include <boost/function.hpp>

#include <string>

/****************************************************************************************************/

namespace adobe {

/****************************************************************************************************/

struct link_t
{
    typedef any_regular_t                      model_type;
    typedef boost::function<void (const model_type&)> setter_type;

    link_t(const std::string&          alt_text,
           const any_regular_t& on_value,
           const any_regular_t& off_value,
           long                        count,
           theme_t                     theme);

    void measure(extents_t& result);

    void place(const place_data_t& place_data);

    void enable(bool make_enabled);

    void display(const any_regular_t& to_value);

    void monitor(const setter_type& proc);

#if 1 // TODO
    platform_control_type control_m;
    platform_control_type link_icon_m;
#endif
    std::string          alt_text_m;
    any_regular_t on_value_m;
    any_regular_t off_value_m;
    long                 count_m;
    theme_t              theme_m;
    guide_set_t          prongs_m;
    any_regular_t value_m;
    point_2d_t           tl_m;
    setter_type          hit_proc_m;
};

/****************************************************************************************************/

} // namespace adobe

/****************************************************************************************************/

#endif

/****************************************************************************************************/
