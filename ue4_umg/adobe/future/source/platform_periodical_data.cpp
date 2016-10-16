/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#ifndef BUILD_FOR_TEST
#include "Spaceport.h"
#endif

#include <adobe/future/platform_periodical_data.hpp>

#include <vector>

namespace adobe {

/****************************************************************************************************/

periodical_platform_data_t::periodical_platform_data_t(const fire_proc_t& fire_proc,
                                                       std::size_t millisecond_delay) :
    fire_m(fire_proc)
{
    // TODO: Start timer; call fire_m() every time it goes off.
}

/****************************************************************************************************/

periodical_platform_data_t::~periodical_platform_data_t()
{
    // TODO: Stop, then destroy the timer resource.
}

/****************************************************************************************************/

} // namespace adobe

/****************************************************************************************************/
