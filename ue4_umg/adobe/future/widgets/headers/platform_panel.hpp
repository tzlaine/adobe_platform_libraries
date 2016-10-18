/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#ifndef ADOBE_PANEL_HPP
#define ADOBE_PANEL_HPP

#include <adobe/config.hpp>

#include <boost/utility.hpp>

#include <adobe/any_regular.hpp>
#include <adobe/extents.hpp>
#include <adobe/layout_attributes.hpp>
#include <adobe/widget_attributes.hpp>
#include <adobe/future/widgets/headers/widget_utils.hpp>

/****************************************************************************************************/

namespace adobe {

/****************************************************************************************************/

struct panel_t : extents_slices_t, boost::noncopyable
{
    typedef any_regular_t model_type;

    panel_t(const any_regular_t& show_value);

    void        measure(extents_t& result);

    void        place(const place_data_t& place_data);

    void        display(const any_regular_t& value);

    void        set_visible(bool make_visible); 

#if 1 // TODO
    platform_display_type control_m;
#endif
    any_regular_t    show_value_m;
};

/****************************************************************************************************/

inline platform_display_type get_display(panel_t const & panel)
{ return panel.control_m; }

/****************************************************************************************************/

}

/****************************************************************************************************/

#endif

/*************************************************************************************************/
