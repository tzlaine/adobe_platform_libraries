/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#ifndef ADOBE_TAB_GROUP_HPP
#define ADOBE_TAB_GROUP_HPP

#include <adobe/config.hpp>

#include <vector>

#include <boost/utility.hpp>
#include <boost/function.hpp>

#include <adobe/any_regular.hpp>
#include <adobe/extents.hpp>
#include <adobe/layout_attributes.hpp>
#include <adobe/widget_attributes.hpp>
#include <adobe/future/widgets/headers/widget_utils.hpp>

/****************************************************************************************************/

namespace adobe {

/****************************************************************************************************/

struct tab_group_t : boost::noncopyable
{
    typedef any_regular_t model_type;
    typedef tab_group_t  widget_type_t;
    typedef boost::function<void (const any_regular_t&)> tab_group_value_proc_t;

    struct tab_t {
        std::string name_m;
        any_regular_t value_m;
    };

    typedef std::vector<tab_t>  tab_set_t;
    
    tab_group_t(const tab_t* first, const tab_t* last, theme_t theme);


#if 1 // TODO
    void        initialize(platform_display_type parent);
#endif

    void        measure(extents_t& result);
    void        place(const place_data_t& place_data);

    void        display(const any_regular_t& new_value);
    void        monitor(const tab_group_value_proc_t& proc);

    void        enable(bool make_enabled) { set_control_enabled(control_m, make_enabled); }
    void        set_visible(bool make_visible) { set_control_visible(control_m, make_visible); }


#if 1 // TODO
    platform_control_type control_m;
#endif
    theme_t theme_m;
    tab_group_value_proc_t value_proc_m;
    tab_set_t items_m;
};

/****************************************************************************************************/

} //namespace adobe
/****************************************************************************************************/


#endif 
