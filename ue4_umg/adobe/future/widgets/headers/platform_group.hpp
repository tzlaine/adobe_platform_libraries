/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#ifndef ADOBE_WIDGET_GROUP_HPP
#define ADOBE_WIDGET_GROUP_HPP

/****************************************************************************************************/

#include <adobe/config.hpp>

#include <adobe/extents.hpp>
#include <adobe/eve.hpp>
#include <adobe/layout_attributes.hpp>
#include <adobe/widget_attributes.hpp>
#include <adobe/future/platform_primitives.hpp>

#include <string>

/****************************************************************************************************/

namespace adobe {

/****************************************************************************************************/

struct group_t
{
    group_t(const std::string& name,
            const std::string& alt_text,
            theme_t     theme);

    void measure(extents_t& result);

    void place(const place_data_t& place_data);

#if 1 // TODO
    platform_control_type control_m;
#endif
    std::string          name_m;
    std::string          alt_text_m;
    theme_t       theme_m;
};

/****************************************************************************************************/

} // namespace adobe

/****************************************************************************************************/

#endif

/****************************************************************************************************/
