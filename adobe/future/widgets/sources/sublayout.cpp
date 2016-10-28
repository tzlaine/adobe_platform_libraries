/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#ifndef BUILD_FOR_TEST
#include "Spaceport.h"
#endif

#include <adobe/future/widgets/headers/sublayout.hpp>

#include <adobe/adam_evaluate.hpp>
#include <adobe/adam_parser.hpp>
#include <adobe/future/widgets/headers/widget_factory.hpp>
#include <adobe/future/widgets/headers/widget_factory_registry.hpp>

#include <sstream>

/****************************************************************************************************/

namespace adobe {

/****************************************************************************************************/

widget_node_t sublayout_t::evaluate(const std::string&       sheet_description,
                                    const std::string&       layout_description,
                                    const dictionary_t&      parameters,
                                    const widget_node_t&     parent,
                                    const factory_token_t&   token,
                                    const widget_factory_t&  factory,
                                    const button_notifier_t& button_notifier,
                                    behavior_t&              behavior)
{
    static const name_t               panel_name_s("panel"_name);
    static const layout_attributes_t& attrs_s(factory.layout_attributes(panel_name_s));

    std::stringstream sheet_stream(sheet_description);

    parse(sheet_stream, line_position_t("sublayout sheet"), bind_to_sheet( sublayout_sheet_m ) );

    size_enum_t size(parameters.count(key_size) ?
                     implementation::enumerate_size(get_value(parameters, key_size).cast<name_t>()) :
                     parent.size_m);

    platform_display_type display_token(insert(get_main_display(), parent.display_token_m, root_m));

    std::stringstream layout_stream(layout_description);

    platform_display_type display_root = get_display(root_m);

    sublayout_holder_m = make_view("sublayout layout",
                                   line_position_t::getline_proc_t(),
                                   layout_stream,
                                   sublayout_sheet_m,
                                   behavior,
                                   token.vm_lookup_m,
                                   button_notifier,
                                   token.button_notifier_m,
                                   token.signal_notifier_m,
                                   size,
                                   default_widget_factory_proc_with_factory(factory),
                                   display_root);

    eve_t::iterator eve_token =
        attach_placeable<poly_placeable_t>(parent.eve_token_m,
                                                 *this, parameters, token,
                                                 true, attrs_s);

    return widget_node_t(size, eve_token, display_token, parent.keyboard_token_m);
}

/****************************************************************************************************/

} // namespace adobe

/****************************************************************************************************/
