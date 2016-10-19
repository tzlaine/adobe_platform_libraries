/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef ADOBE_LABEL_T_HPP
#define ADOBE_LABEL_T_HPP

#include "widgets/styleable_text_block.h"

#include <adobe/memory.hpp>
#include <adobe/layout_attributes.hpp>
#include <adobe/widget_attributes.hpp>
#include <adobe/future/platform_primitives.hpp>
#include <boost/noncopyable.hpp>
#include <string>


namespace adobe {

    struct label_t : boost::noncopyable
    {
        label_t(const std::string& name,
                const std::string& alt_text,
                std::size_t characters);

        ~label_t();

        Ustyleable_text_block * control_m;
        std::string name_m;
        std::string alt_text_m;
        std::size_t characters_m;
    };

    void measure(label_t& value, extents_t& result);

    void measure_vertical(label_t& value,
                          extents_t& calculated_horizontal,
                          const place_data_t& placed_horizontal);

    void place(label_t& value, const place_data_t& place_data);

    void enable(label_t& value, bool make_enabled);

    void initialize(label_t& value, platform_display_type parent);

    void measure_label_text(const label_t& label, extents_t& result, platform_display_type temp_parent);

    extents_t measure_text(const std::string& text, platform_display_type temp_parent);

    std::string get_control_string(const label_t& widget);

    inline platform_display_type get_display(label_t & widget)
    { return widget.control_m; }

} // namespace adobe


#endif

/****************************************************************************************************/
