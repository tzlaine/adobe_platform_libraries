/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#ifndef ADOBE_UI_CORE_BUTTON_HPP
#define ADOBE_UI_CORE_BUTTON_HPP

/****************************************************************************************************/

#include "widgets/styleable_button.h"
#include "widgets/styleable_text_block.h"

#include <adobe/config.hpp>

#include <adobe/layout_attributes.hpp>

#include <adobe/future/widgets/headers/button_helper.hpp>
#include <adobe/future/widgets/headers/widget_utils.hpp>

#include <boost/noncopyable.hpp>

/****************************************************************************************************/

namespace adobe {

/****************************************************************************************************/

struct button_t : boost::noncopyable
{
    typedef any_regular_t model_type;

    button_t(bool is_default, bool is_cancel);

    void measure(extents_t& result);

    void place(const place_data_t& place_data);

    void enable(bool make_enabled);

    void display(const any_regular_t& item);

    void set(modifiers_t modifiers, const model_type& value);

    void set_contributing(modifiers_t modifiers, const dictionary_t& value);

    any_regular_t underlying_handler() { return any_regular_t(control_m); }

    bool handle_key(key_type key, bool pressed, modifiers_t modifiers);

    Ustyleable_button * control_m;
    Ustyleable_text_block * control_text_m;

    button_state_set_t state_set_m;
    modifiers_t        modifier_mask_m;
    modifiers_t        modifiers_m;
    bool               is_default_m;
    bool               is_cancel_m;
    bool               enabled_m;
};

/****************************************************************************************************/

} // namespace adobe

/****************************************************************************************************/

#endif

/****************************************************************************************************/
