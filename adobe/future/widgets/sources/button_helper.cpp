/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#include <adobe/future/widgets/headers/button_helper.hpp>

// REVISIT (fbrereto) : This source file should not reach into widgets
#include <adobe/future/widgets/headers/widget_tokens.hpp>

#include <adobe/array.hpp>
#include <adobe/name.hpp>
#include <adobe/string.hpp>

/****************************************************************************************************/

namespace adobe {

/*************************************************************************************************/

modifiers_t name_to_modifer(name_t name)
{
    /*
        REVISIT (sparent) : need a little lookup table here. I would still like to see us get
        to a semantic notion for modifiers.
    */
    if (name == key_modifier_option) return modifiers_any_option_s;
    if (name == key_modifier_command) return modifiers_any_command_s;
    if (name == key_modifier_control) return modifiers_any_control_s;
    if (name == key_modifier_shift) return modifiers_any_shift_s;
    
    // REVISIT (sparent) : put an assert here later to clean out these older names.
    
    if (name == key_modifiers_cmd)
        return modifiers_any_command_s;
    if (name == key_modifiers_ctl)
        return modifiers_any_control_s;
    if (name == key_modifiers_ctlcmd)
        return modifiers_any_control_s | modifiers_any_command_s;
    if (name == key_modifiers_opt)
        return modifiers_any_option_s;
    if (name == key_modifiers_optcmd)
        return modifiers_any_option_s | modifiers_any_command_s;
    if (name == key_modifiers_optctl)
        return modifiers_any_option_s | modifiers_any_control_s;
    if (name == key_modifiers_optctlcmd)
        return modifiers_any_option_s | modifiers_any_control_s | modifiers_any_command_s;
    
    throw std::invalid_argument(std::string() + "unknown modifier: " + name.c_str());
}

/*************************************************************************************************/

modifiers_t value_to_modifier(const any_regular_t& modifier_set)
{
    modifiers_t result(modifiers_none_s);

    if (modifier_set.type_info() == boost::typeindex::type_id<name_t>())
    {
        result |= name_to_modifer(modifier_set.cast<name_t>());
    }
    else
    {
        const array_t& array = modifier_set.cast<array_t>();
        
        /*
            REVISIT (sparent) : This is a transform and accumulate - should be an
            easy way to compose such a thing.
        */
        for (array_t::const_iterator first(array.begin()), last(array.end());
                first != last; ++first)
        {
            result |= name_to_modifer(first->cast<name_t>());
        }
        
    }
    return result;
}

/****************************************************************************************************/

} // namespace adobe

/****************************************************************************************************/
