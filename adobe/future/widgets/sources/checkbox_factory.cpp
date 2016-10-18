/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#ifndef BUILD_FOR_TEST
#include "Spaceport.h"
#endif

// checkbox.hpp needs to come before widget_factory to hook the overrides
#include <adobe/future/widgets/headers/platform_checkbox.hpp>

#include <adobe/future/widgets/headers/checkbox_factory.hpp>
#include <adobe/future/widgets/headers/widget_factory.hpp>
#include <adobe/future/widgets/headers/widget_factory_registry.hpp>

/****************************************************************************************************/

namespace adobe {

/****************************************************************************************************/

void create_widget(const dictionary_t& parameters,
                   size_enum_t         size,
                   checkbox_t* &       checkbox)
{
    std::string    name;
    std::string    alt_text;
    any_regular_t true_value(true);
    any_regular_t false_value(false);

    get_value(parameters, key_name, name);
    get_value(parameters, key_alt_text, alt_text);
    get_value(parameters, key_value_on, true_value);
    get_value(parameters, key_value_off, false_value);

    checkbox = new checkbox_t(name, true_value, false_value, alt_text);
}

/****************************************************************************************************/

template <typename Sheet>
void couple_controller_to_cell(checkbox_t&               controller, 
                               name_t                    cell, 
                               Sheet&                    sheet, 
                               eve_client_holder& client_holder, 
                               const dictionary_t&       parameters)

{
    attach_enabler(client_holder.assemblage_m, cell, controller, sheet, parameters);
    attach_monitor(controller, cell, sheet, client_holder, parameters);
}

/****************************************************************************************************/

widget_node_t make_checkbox(const dictionary_t&     parameters, 
                            const widget_node_t&    parent, 
                            const factory_token_t&  token,
                            const widget_factory_t& factory)
    { return create_and_hookup_widget<checkbox_t, poly_placeable_t>(parameters, parent, token, 
        factory.is_container("checkbox"_name), 
        factory.layout_attributes("checkbox"_name)); }

/****************************************************************************************************/

} // namespace adobe

/****************************************************************************************************/
