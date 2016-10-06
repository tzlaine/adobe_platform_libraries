/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#ifndef ADOBE_DISPLAY_NUMBER_HPP
#define ADOBE_DISPLAY_NUMBER_HPP

/****************************************************************************************************/

#include <adobe/memory.hpp>
#include <boost/operators.hpp>
#include <adobe/layout_attributes.hpp>
#include <adobe/widget_attributes.hpp>
#include <string>
#include <boost/noncopyable.hpp>
#include <adobe/future/widgets/headers/number_unit.hpp>
#include <adobe/future/platform_primitives.hpp>

/****************************************************************************************************/

namespace adobe {

/****************************************************************************************************/

struct display_number_t  : boost::noncopyable 
{
    typedef double  model_type;

    typedef std::vector<unit_t> unit_set_t;

    template <class ForwardIterator>
    display_number_t(const std::string& name,
                     const std::string& alt_text,
                     ForwardIterator first,
                     ForwardIterator last, 
                     theme_t theme,
                     int characters);

#if 1 // TODO
    platform_display_type     window_m;
#endif
#if 0 // TODO
    WNDPROC                  default_window_proc_m;
#endif
#if 1 // TODO
    int                      bounds_m;
#endif
    std::string              name_m;
    std::string              alt_text_m;
    unit_set_t               unit_set_m;
    theme_t                  theme_m;
    std::wstring::size_type  label_chars_m;
    int                      characters_m;

#if 1 // TODO
    void initialize(platform_display_type parent);
#endif

    void measure(extents_t& result);
    void measure_vertical(extents_t& calculated_horizontal, const place_data_t& placed_horizontal);       

    void place(const place_data_t& place_data);

    void display(const model_type& value);
};

/****************************************************************************************************/

template <typename ForwardIterator>
display_number_t::display_number_t(
    const std::string& name,
    const std::string& alt_text,
    ForwardIterator first,
    ForwardIterator last, 
    theme_t theme,
    int characters) 
    : name_m(name),
      alt_text_m(alt_text),
      unit_set_m(first, last),
      theme_m(theme),
      label_chars_m(0),
      characters_m(characters)
{ }

/****************************************************************************************************/

#if 1 // TODO
inline platform_display_type get_display(const display_number_t& widget)
{ return widget.window_m; }
#endif

/****************************************************************************************************/

} // namespace adobe

/****************************************************************************************************/

#endif

/****************************************************************************************************/
