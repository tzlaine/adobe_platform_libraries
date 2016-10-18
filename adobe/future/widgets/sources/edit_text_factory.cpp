/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#ifndef BUILD_FOR_TEST
#include "Spaceport.h"
#endif

// .hpp needs to come before widget_factory to hook the overrides
#include <adobe/future/widgets/headers/platform_edit_text.hpp>

#include <adobe/future/widgets/headers/edit_text_factory.hpp>
#include <adobe/future/widgets/headers/widget_factory.hpp>
#include <adobe/future/widgets/headers/widget_factory_registry.hpp>
#include <adobe/layout_attributes.hpp>

/****************************************************************************************************/

namespace adobe {

/****************************************************************************************************/

void create_widget(const dictionary_t&   parameters,
                   size_enum_t           size,
                   edit_text_t*&         widget)
{
    edit_text_ctor_block_t block;

    get_value(parameters, key_name, block.name_m);
    get_value(parameters, key_alt_text, block.alt_text_m);
    get_value(parameters, key_characters, block.min_characters_m);
    get_value(parameters, key_max_characters, block.max_characters_m);
    get_value(parameters, key_lines, block.num_lines_m);
    get_value(parameters, key_monospaced, block.monospaced_m);
    get_value(parameters, key_scrollable, block.scrollable_m);
    get_value(parameters, key_password, block.password_m);

    widget = new edit_text_t(block);
}
    
/****************************************************************************************************/

namespace implementation {

/****************************************************************************************************/

widget_node_t make_edit_text(const dictionary_t&     parameters, 
                             const widget_node_t&    parent, 
                             const factory_token_t&  token,
                             const widget_factory_t& factory)
{ 
     return create_and_hookup_widget<edit_text_t, poly_placeable_t>(
        parameters,
        parent,
        token, 
        factory.is_container("edit_text"_name),
        factory.layout_attributes("edit_text"_name)); 
}

/****************************************************************************************************/

} // namespace implementation

/****************************************************************************************************/

} // namespace adobe

/****************************************************************************************************/
