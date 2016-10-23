/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#ifndef BUILD_FOR_TEST
#include "Spaceport.h"
#endif

#include <adobe/future/widgets/headers/platform_window.hpp>

#include <adobe/future/widgets/headers/display.hpp>
#include <adobe/future/widgets/headers/widget_utils.hpp>
#include <adobe/future/widgets/headers/platform_label.hpp>
#include <adobe/future/widgets/headers/platform_metrics.hpp>
#include <adobe/keyboard.hpp>

/****************************************************************************************************/

namespace adobe {

/****************************************************************************************************/

UWorld * window_t::create_widget_world_ = nullptr;

/****************************************************************************************************/

window_t::window_t(const std::string&  name,
                   window_style_t style,
                   window_attributes_t attributes,
                   window_modality_t modality) :
    window_m(nullptr),
    name_m(name),
    style_m(style),
    attributes_m(attributes),
    modality_m(modality),
    debounce_m(false),
    placed_once_m(false)
{ }

/****************************************************************************************************/

window_t::~window_t()
{
    if (window_m) {
        window_m->RemoveFromParent();
        delete window_m;
    }
}

/****************************************************************************************************/

void window_t::measure(extents_t& result)
{
    assert(window_m);

    if (name_m.empty())
    {
        result.height() = 15; // TODO
        result.width() = 15;

        return;
    }

    result = measure_text(name_m, window_m);

    result.width() = static_cast<long>(result.width() * 1.5);
}

/****************************************************************************************************/

void window_t::place(const place_data_t& place_data)
{
    assert(window_m);

    if (placed_once_m)
    {
        set_size(point_2d_t(width(place_data), height(place_data)));
    }
    else
    {
        placed_once_m = true;

        place_data_m = place_data;

        window_m->SetPositionInViewport(FVector2D(left(place_data), top(place_data)));
        window_m->SetDesiredSizeInViewport(FVector2D(width(place_data), height(place_data)));
        resize_proc_m(width(place_data), height(place_data));
    }
}

/****************************************************************************************************/

void window_t::set_size(const point_2d_t& size)
{
    assert(window_m);

    if (debounce_m)
        return;

    debounce_m = true;

    width(place_data_m) = size.x_m;
    height(place_data_m) = size.y_m;

    window_m->SetDesiredSizeInViewport(FVector2D(size.x_m, size.y_m));
    resize_proc_m(size.x_m, size.y_m);

    debounce_m = false;
}

/****************************************************************************************************/

void window_t::set_visible(bool make_visible)
{
    assert(window_m);
    window_m->SetVisibility(make_visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

/****************************************************************************************************/

void window_t::monitor_resize(const window_resize_proc_t& proc)
{
    resize_proc_m = proc;
}

/****************************************************************************************************/

template <>
platform_display_type insert<window_t>(display_t& display,
                                       platform_display_type& parent,
                                       window_t& element)
{
    assert(!element.window_m);

    element.window_m = CreateWidget<Uroot_widget>(window_t::create_widget_world_, Uroot_widget::StaticClass());

    if (!element.window_m)
        ADOBE_THROW_LAST_ERROR;

    element.window_m->SetAnchorsInViewport(FAnchors(0, 0, 0, 0));

    if (!element.window_m)
        ADOBE_THROW_LAST_ERROR;

    element.window_m->set_resize_callback(
        [&element](long width, long height) {
            if (element.debounce_m == false && element.resize_proc_m) {
                element.debounce_m = true;

                if (height < element.min_size_m.y_m)
                    height = element.min_size_m.y_m;

                if (width < element.min_size_m.x_m)
                    width = element.min_size_m.x_m;

                if (adobe::width(element.place_data_m) != width ||
                    adobe::height(element.place_data_m) != height)
                {
                    element.resize_proc_m(width, height);

                    adobe::width(element.place_data_m) = width;
                    adobe::height(element.place_data_m) = height;
                }

                element.debounce_m = false;
            }
        }
    );

    return display.insert(parent, element.window_m);
}

/****************************************************************************************************/

} // namespace adobe

/****************************************************************************************************/
