/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#ifndef ADOBE_WIDGET_REVEAL_HPP
#define ADOBE_WIDGET_REVEAL_HPP

/****************************************************************************************************/

#include <adobe/config.hpp>

#include <adobe/any_regular.hpp>

#include <adobe/future/widgets/headers/platform_label.hpp>

#include <boost/function.hpp>

/****************************************************************************************************/

namespace adobe {

/****************************************************************************************************/

struct reveal_t : boost::noncopyable
{
    typedef any_regular_t model_type;

    typedef boost::function<void (const model_type&)> setter_type;

    reveal_t(const std::string& name,
             const any_regular_t& show_value,
             theme_t theme,
             const std::string& alt_text);

#if 1 // TODO
    void initialize(platform_display_type parent);
#endif

    void measure(extents_t& result);

    void place(const place_data_t& place_data);

    void display(const any_regular_t& value);

    void monitor(const setter_type& proc);

#if 1 // TODO
    platform_control_type control_m;
#endif
    theme_t          theme_m;
    label_t			name_m;
    bool                    using_label_m;
    setter_type				hit_proc_m;
    any_regular_t	show_value_m;
    any_regular_t	current_value_m;
    std::string				alt_text_m;
};

/****************************************************************************************************/

namespace view_implementation {

/****************************************************************************************************/

void set_value_from_model(reveal_t& value, const any_regular_t& new_value);

/****************************************************************************************************/

} // namespace view_implementation

/****************************************************************************************************/

} // namespace adobe

/****************************************************************************************************/

#endif

/****************************************************************************************************/
