/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#ifndef BUILD_FOR_TEST
#include "Spaceport.h"
#endif

#include <adobe/future/file_monitor.hpp>

#include <adobe/algorithm/find.hpp>
#include <adobe/functional.hpp>

#include <boost/bind.hpp>
#include <boost/filesystem/operations.hpp>

#include <vector>
#include <stdexcept>
#include <utility>

/****************************************************************************************************/

namespace {

/****************************************************************************************************/

typedef std::vector<adobe::file_monitor_platform_data_t*> file_set_t;

/****************************************************************************************************/

inline file_set_t& file_set()
{
    static file_set_t file_set_s;

    return file_set_s;
}

/****************************************************************************************************/

void file_monitor_loop()
{
    file_set_t& set(file_set());

    for (auto platform_data : set)
    {
        if (platform_data->last_write_m == 0)
            continue;

        std::time_t new_write_time = boost::filesystem::last_write_time(platform_data->path_m);
        if (new_write_time != platform_data->last_write_m)
        {
            platform_data->last_write_m = new_write_time;
            platform_data->proc_m(platform_data->path_m, adobe::file_monitor_contents_changed_k);
        }
    }
}

/****************************************************************************************************/

void install_timer()
{
    static bool inited(false);
    
    if (inited)
        return;

    // TODO ::SetTimer(NULL, 0, 100, (TIMERPROC)&file_monitor_loop);

    inited = true;
}

/****************************************************************************************************/

} // namespace

/****************************************************************************************************/

namespace adobe {

/****************************************************************************************************/

file_monitor_platform_data_t::file_monitor_platform_data_t() :
    last_write_m(0)
    { file_set().push_back(this); }

file_monitor_platform_data_t::file_monitor_platform_data_t(const file_monitor_path_type&  path,
                                                           const file_monitor_callback_t& proc) :
    path_m(path),
    proc_m(proc),
    last_write_m(0)
{
    // TODO install_timer();

    connect();
}

file_monitor_platform_data_t::file_monitor_platform_data_t(const file_monitor_platform_data_t& rhs) :
    path_m(rhs.path_m),
    proc_m(rhs.proc_m),
    last_write_m(0)
{
    connect();
}

file_monitor_platform_data_t::~file_monitor_platform_data_t()
{
    file_set_t::iterator result(adobe::find(file_set(), this));

    if (result != file_set().end())
        file_set().erase(result); 

    disconnect();
}

file_monitor_platform_data_t& file_monitor_platform_data_t::operator = (const file_monitor_platform_data_t& rhs)
{
    disconnect();

    path_m = rhs.path_m;
    proc_m = rhs.proc_m;

    connect();

    return *this;
}

void file_monitor_platform_data_t::set_path(const file_monitor_path_type& path)
{
    if (!boost::filesystem::exists(path) || path_m == path)
        return;

    // TODO install_timer();

    disconnect();

    path_m = path;

    connect();
}

void file_monitor_platform_data_t::connect()
{
    if (!boost::filesystem::exists(path_m))
        return;

    last_write_m = boost::filesystem::last_write_time(path_m);

    auto const change_handle_path = path_m.branch_path().native();

    // TODO: FindFirstChangeNotificationA
}

void file_monitor_platform_data_t::disconnect()
{
    if (last_write_m == 0)
        return;

    // TODO FindCloseChangeNotification(change_handle_m);
}

/****************************************************************************************************/

file_monitor_t::file_monitor_t()
    { }

file_monitor_t::file_monitor_t(const file_monitor_path_type& path, const file_monitor_callback_t& proc) :
    plat_m(path, proc)
    { }

void file_monitor_t::set_path(const file_monitor_path_type& path)
    { plat_m.set_path(path); }

void file_monitor_t::monitor(const file_monitor_callback_t& proc)
    { plat_m.proc_m = proc; }

/****************************************************************************************************/

} // namespace adobe

/****************************************************************************************************/
