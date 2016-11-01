/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#ifndef ADOBE_WIDGET_CHECKBOX_HPP
#define ADOBE_WIDGET_CHECKBOX_HPP

/****************************************************************************************************/

#include "widgets/styleable_check_box.h"
#include "widgets/styleable_text_block.h"

#include <adobe/config.hpp>

#include <adobe/any_regular.hpp>
#include <adobe/extents.hpp>
#include <adobe/layout_attributes.hpp>
#include <adobe/widget_attributes.hpp>
#include <adobe/future/platform_primitives.hpp>

#include <boost/function.hpp>

#include <string>

/****************************************************************************************************/

namespace adobe {

/****************************************************************************************************/

/*
    \omit from the doxygen documentation (for now)

    \ingroup asl_widgets_win32

    \brief UI core checkbox widget

    Further documentation can be found in the \ref asl_widgets_carbon.
*/

struct checkbox_t
{
    typedef any_regular_t                      model_type;
    typedef boost::function<void (const model_type&)> setter_type;

    checkbox_t(const std::string& name,
               const any_regular_t& true_value,
               const any_regular_t& false_value,
               const std::string& alt_text,
               name_t signal_id);

    void measure(extents_t& result);

    void place(const place_data_t& place_data);

    void enable(bool make_enabled);

    void display(const any_regular_t& value);

    void monitor(const setter_type& proc);

    friend bool operator== (const checkbox_t& x, const checkbox_t& y);

    Ustyleable_check_box * control_m;
    Ustyleable_text_block * control_text_m;

    FVector2D size_without_text_m;

    boost::function<void (any_regular_t const &)> checked_proc_m;

    setter_type hit_proc_m;
    any_regular_t true_value_m;
    any_regular_t false_value_m;
    any_regular_t current_value_m;
    std::string name_m;
    std::string alt_text_m;
    name_t signal_id_m;
};

/****************************************************************************************************/

} // namespace adobe

/****************************************************************************************************/

#endif

/****************************************************************************************************/
