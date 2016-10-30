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

namespace {

/****************************************************************************************************/

void handle_checked_signal(signal_notifier_t signal_notifier,
                           name_t widget_id,
                           sheet_t& sheet,
                           name_t bind,
                           array_t expression,
                           const any_regular_t& value)
{
    handle_signal(signal_notifier,
                  "checkbox"_name,
                  "checked"_name,
                  widget_id,
                  sheet,
                  bind,
                  expression,
                  value);
}

/****************************************************************************************************/

}

/****************************************************************************************************/

void create_widget(const dictionary_t& parameters,
                   size_enum_t         size,
                   checkbox_t* &       checkbox)
{
    std::string    name;
    std::string    alt_text;
    any_regular_t  true_value(true);
    any_regular_t  false_value(false);
    name_t         signal_id;

    get_value(parameters, key_name, name);
    get_value(parameters, key_alt_text, alt_text);
    get_value(parameters, key_value_on, true_value);
    get_value(parameters, key_value_off, false_value);
    get_value(parameters, "signal_id"_name, signal_id);
    // TODO: style, class

    checkbox = new checkbox_t(name, true_value, false_value, alt_text, signal_id);
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

template <>
void attach_view_and_controller(checkbox_t&            control,
                                const dictionary_t&    parameters,
                                const factory_token_t& token,
                                adobe::name_t,
                                adobe::name_t,
                                adobe::name_t)
{
    if (parameters.count(key_bind) != 0) {
        name_t cell(get_value(parameters, key_bind).cast<name_t>());
        attach_view_and_controller_direct(control, parameters, token, cell);
    }

    any_regular_t checked_binding;
    name_t cell;
    array_t expression;
    if (get_value(parameters, "bind_checked_signal"_name, checked_binding)) {
        cell_and_expression(checked_binding, cell, expression);
    }
    control.checked_proc_m = boost::bind(&handle_checked_signal,
                                         token.signal_notifier_m,
                                         control.signal_id_m,
                                         boost::ref(token.sheet_m),
                                         cell,
                                         expression,
                                         _1);
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
