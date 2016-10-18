/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#ifndef BUILD_FOR_TEST
#include "Spaceport.h"
#endif

// group.hpp needs to come before widget_factory to hook the overrides
#include <adobe/future/widgets/headers/platform_group.hpp>

#include <adobe/future/widgets/headers/group_factory.hpp>
#include <adobe/future/widgets/headers/widget_factory.hpp>
#include <adobe/future/widgets/headers/widget_factory_registry.hpp>


namespace adobe {

/****************************************************************************************************/

void create_widget(const dictionary_t&   parameters,
                   size_enum_t               size,
                   group_t*&                 group)
{
    std::string    name;
    std::string    alt_text;

    get_value(parameters, key_name, name);
    get_value(parameters, key_alt_text, alt_text);

    group = new group_t(name, alt_text);
}

/****************************************************************************************************/

template <>
void attach_view_and_controller(group_t&,
                                const dictionary_t&,
                                const factory_token_t&,
                                adobe::name_t,
                                adobe::name_t,
                                adobe::name_t)
{
    // no adam interaction
}

/****************************************************************************************************/

widget_node_t make_group(const dictionary_t&     parameters, 
                         const widget_node_t&    parent, 
                         const factory_token_t&  token,
                         const widget_factory_t& factory)
{
    return create_and_hookup_widget<group_t, poly_placeable_t>(parameters,
                                                               parent,
                                                               token,
                                                               factory.is_container("group"_name),
                                                               factory.layout_attributes("group"_name));
}

/****************************************************************************************************/

} // namespace adobe

/****************************************************************************************************/
