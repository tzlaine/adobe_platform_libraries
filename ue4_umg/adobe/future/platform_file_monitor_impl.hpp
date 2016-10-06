/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#ifndef ADOBE_FILE_MONITOR_IMPL_HPP
#define ADOBE_FILE_MONITOR_IMPL_HPP

/****************************************************************************************************/

#include <ctime>

/****************************************************************************************************/

namespace adobe {

/****************************************************************************************************/

struct file_monitor_platform_data_t
{
    file_monitor_platform_data_t();

    file_monitor_platform_data_t(const file_monitor_path_type&  path, const file_monitor_callback_t& proc);

    file_monitor_platform_data_t(const file_monitor_platform_data_t& rhs);

    ~file_monitor_platform_data_t();

    file_monitor_platform_data_t& operator = (const file_monitor_platform_data_t& rhs);

    void set_path(const file_monitor_path_type& path);

    void connect();

    void disconnect();

    file_monitor_path_type         path_m;
    adobe::file_monitor_callback_t proc_m;
    std::time_t                    last_write_m;
};

/****************************************************************************************************/

} // namespace adobe

/****************************************************************************************************/

#endif

/****************************************************************************************************/
