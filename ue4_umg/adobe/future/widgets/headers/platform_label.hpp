/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef ADOBE_LABEL_T_HPP
#define ADOBE_LABEL_T_HPP


#include <string>

#include <boost/noncopyable.hpp>

#include <adobe/memory.hpp>
#include <adobe/layout_attributes.hpp>
#include <adobe/widget_attributes.hpp>
#include <boost/noncopyable.hpp>
#include <adobe/future/platform_primitives.hpp>


namespace adobe {
    struct label_t  : boost::noncopyable {

        label_t(const std::string& name, 
                const std::string& alt_text, 
                std::size_t        characters,
                theme_t            theme
                );

        ~label_t();

#if 1 // TODO
        platform_display_type control_m;
#endif
        theme_t     theme_m;
        std::string name_m;
        std::string alt_text_m;
        std::size_t characters_m;
    };

#if 1 // TODO
    void               initialize(label_t& value, platform_display_type parent);
#endif


    void measure(label_t& value, extents_t& result);
    
    void measure_vertical(label_t& value, extents_t& calculated_horizontal, 
        const place_data_t& placed_horizontal);       

    void place(label_t& value, const place_data_t& place_data);
    

    void enable(label_t& value, bool make_enabled);

#if 1 // TODO
    void measure_label_text(const label_t& label, extents_t& result, platform_display_type temp_parent);

    extents_t measure_text(const std::string& text, theme_t theme, platform_display_type temp_parent);
#endif

    std::string get_control_string(const label_t& widget);

    inline platform_display_type & get_display(label_t & widget)
    { return widget.control_m; }

} // namespace adobe


#endif

/****************************************************************************************************/
