/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#ifndef ADOBE_SLIDER_HPP
#define ADOBE_SLIDER_HPP

/****************************************************************************************************/

#include <adobe/config.hpp>

#include <adobe/extents.hpp>
#include <adobe/future/widgets/headers/slider_helper.hpp>
#include <adobe/layout_attributes.hpp>
#include <adobe/widget_attributes.hpp>
#include <adobe/future/platform_primitives.hpp>

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>

#include <string>

/****************************************************************************************************/

namespace adobe {

/****************************************************************************************************/

struct slider_t : boost::noncopyable
{
    typedef double                                    model_type;
    typedef boost::function<void (const model_type&)> setter_type;

    slider_t(const std::string&          alt_text,
             bool                        is_vertical,
             slider_style_t              style,
             std::size_t                 num_ticks,
             const value_range_format_t& format,
             theme_t                     theme);

    void measure(extents_t& result);

    void place(const place_data_t& place_data);

    void display(const model_type& item);

    void enable(bool make_enabled);

    void monitor(const setter_type& proc)
        { value_proc_m = proc; }

#if 1 // TODO
    platform_display_type control_m;
#endif
    std::string          alt_text_m;
    bool                 is_vertical_m;
    slider_style_t       style_m;
    std::size_t          num_ticks_m;
    value_range_format_t format_m;
    theme_t       theme_m;
    setter_type          value_proc_m;
    long                 last_m; // Used to debounce
    model_type           value_m;
};

/****************************************************************************************************/

} // namespace adobe

/****************************************************************************************************/

#endif

/****************************************************************************************************/
