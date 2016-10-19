/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#ifndef ADOBE_IMAGE_T_HPP
#define ADOBE_IMAGE_T_HPP

/****************************************************************************************************/

#include <adobe/dictionary.hpp>
#include <adobe/memory.hpp>
#include <adobe/layout_attributes.hpp>

#include <boost/function.hpp>
#include <boost/gil/gil_all.hpp>
#include <boost/noncopyable.hpp>
#include <adobe/future/platform_primitives.hpp>

#include <string>

/****************************************************************************************************/

namespace adobe {

/****************************************************************************************************/

struct image_t : boost::noncopyable
{
    /// model types for this widget
    typedef dictionary_t                                         controller_model_type;
    typedef boost::gil::rgba8_image_t                            view_model_type;
    typedef boost::function<void (const controller_model_type&)> setter_proc_type;

    image_t(const view_model_type& image);

    void display(const view_model_type& value);

    void monitor(const setter_proc_type& proc);
    void enable(bool make_enabled);

#if 1 // TODO
    platform_display_type              control_m;
#endif
    view_model_type                    image_m;
    setter_proc_type                   callback_m;
    dictionary_t                       metadata_m;
    bool                               enabled_m;

#if 0 // TODO: Replace with a signal.
    // mouse tracking stuff
    std::unique_ptr<message_handler_t> handler_m;
#endif
    bool                               tracking_m;
#if 1 // TODO
    int                                last_point_m;
#endif
    std::pair<long, long>              origin_m;
};

/****************************************************************************************************/

#if 1 // TODO
void initialize(image_t& value, platform_display_type parent);

inline platform_display_type get_display(image_t & widget)
{ return widget.control_m; }
#endif

/****************************************************************************************************/

void measure(image_t& value, extents_t& result);

void measure_vertical(image_t& value, extents_t& calculated_horizontal, 
                      const place_data_t& placed_horizontal);

void place(image_t& value, const place_data_t& place_data);

void enable(image_t& value, bool make_enabled);

/****************************************************************************************************/

template <typename T> struct controller_model_type;
template <>
struct controller_model_type<adobe::image_t>
{ typedef adobe::image_t::controller_model_type type; };

template <typename T> struct view_model_type;
template <>
struct view_model_type<adobe::image_t>
{ typedef adobe::image_t::view_model_type type; };

/****************************************************************************************************/

} // namespace adobe

/****************************************************************************************************/

#endif
