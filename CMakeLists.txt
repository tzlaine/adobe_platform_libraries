cmake_minimum_required(VERSION 3.0)
# TODO if (POLICY CMP0054)
#    cmake_policy(SET CMP0054 OLD)
#endif ()
include(CMakeParseArguments)
# TODO enable_testing()

project(platform_libraries CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++0x")
set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")

if (NOT MSVC)
    add_definitions ("-Wall")
    add_definitions ("-Wno-unused-local-typedefs")
    add_definitions ("-std=c++11")
    add_definitions ("-fno-rtti")
    if (UNIX AND NOT APPLE)
        add_definitions ("-pthread")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")
    endif ()
endif ()


# There are two big choices this file makes - how to include Boost, and how to
# include double-conversion, respectively. Build environments vary and we're
# trying to support all of them.
#
# If USE_SYSTEM_BOOST is defined, that means the headers and libraries have been built
# and are ready for use by CMake. Otherwise, we'll have to roll them ourselves.
#
# For double-conversion, the unix makefile setup is able to download the git
# repo and build it

option(USE_SYSTEM_BOOST "use cmake found boost instead of ../boost_libraries" "ON")
option(USE_LOCAL_COPY_OF_BOOST "" "OFF")
set(ASL_ROOT ../adobe_source_libraries CACHE PATH "path to adobe_source_libraries (must include double-conversion as a subdir)" )

set(root_path ${CMAKE_SOURCE_DIR}/../)

if (false)
function(setup_dep)
    set(oneValueArgs URL BRANCH)
    cmake_parse_arguments(setup_dep "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    get_filename_component(name ${setup_dep_URL} NAME_WE)
    set(dep_path ${root_path}/${name})
    if(NOT IS_DIRECTORY ${dep_path})
        execute_process(COMMAND ${GIT_EXECUTABLE} clone ${setup_dep_URL} WORKING_DIRECTORY ${root_path})
        execute_process(COMMAND ${GIT_EXECUTABLE} checkout ${setup_dep_BRANCH} WORKING_DIRECTORY ${dep_path})
    endif()
    add_subdirectory(${dep_path} ${CMAKE_BINARY_DIR}/imported/${name})
endfunction()
endif ()

# TODO add_subdirectory(double-conversion)

function(target_link_boost target)
    if (${USE_SYSTEM_BOOST})
        target_link_libraries(${target} PUBLIC ${Boost_SYSTEM_LIBRARY} ${Boost_FILESYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY})
    else()
        add_dependencies(${target} boost_glob)

        target_link_libraries(${target} PUBLIC boost_glob)
    endif()
endfunction(target_link_boost)

function(target_link_boost_test target)
    if (${USE_SYSTEM_BOOST})
        if (NOT USE_LOCAL_COPY_OF_BOOST OR NOT LOCAL_COPY_OF_BOOST_IS_STATIC)
            target_compile_definitions(${target} PRIVATE BOOST_TEST_DYN_LINK)
        endif ()
        target_link_libraries(${target} PRIVATE ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
    else()
        add_dependencies(${target} boost_unit_test)

        target_link_libraries(${target} PUBLIC boost_unit_test)
    endif()
endfunction(target_link_boost_test)

if (${USE_SYSTEM_BOOST})
    if (USE_LOCAL_COPY_OF_BOOST)
        link_directories(${LOCAL_BOOST_LIBRARYDIR})
        include_directories(${LOCAL_BOOST_INCLUDE_DIRS})
    else ()
        find_package(Boost COMPONENTS system filesystem thread unit_test_framework program_options REQUIRED)
        include_directories(${Boost_INCLUDE_DIRS})
    endif ()
else()
    message("ASL_INFO: Building boost ourselves.")

    # There really isn't a need to separate out these sources, so we build them
    # in one large static library.

    file(GLOB ASL_BOOST_FILESYSTEM_SRC ../boost_libraries/libs/filesystem/src/*.cpp)
    file(GLOB ASL_BOOST_PROGRAM_OPTIONS_SRC ../boost_libraries/libs/program_options/src/*.cpp)
    file(GLOB ASL_BOOST_SYSTEM_SRC ../boost_libraries/libs/system/src/*.cpp)
    file(GLOB ASL_BOOST_THREAD_SRC ../boost_libraries/libs/thread/src/*.cpp)

    if (${UNIX})
        file(GLOB ASL_BOOST_THREAD_TSS ../boost_libraries/libs/thread/src/pthread/*.cpp)
    elseif (${WIN32})
        set(ASL_BOOST_THREAD_TSS
            ../boost_libraries/libs/thread/src/win32/thread.cpp
            ../boost_libraries/libs/thread/src/win32/tss_pe.cpp # no idea if this is right...
        )
    endif()

    add_library(
        boost_glob STATIC
        ${ASL_BOOST_FILESYSTEM_SRC}
        ${ASL_BOOST_PROGRAM_OPTIONS_SRC}
        ${ASL_BOOST_SYSTEM_SRC}
        ${ASL_BOOST_THREAD_SRC}
        ${ASL_BOOST_THREAD_TSS}
    )

    target_include_directories(boost_glob PUBLIC ../boost_libraries)

    # We separate out the unit test framework from the rest of the boost
    # add_library support because it has its own main routine which we only need
    # when building unit tests.

    # I can't find a way to glob these because one infernal file, cpp_main.cpp,
    # mucks with my ability to use it.

    add_library(
        boost_unit_test STATIC
        ../boost_libraries/libs/test/src/compiler_log_formatter.cpp
        ../boost_libraries/libs/test/src/debug.cpp
        ../boost_libraries/libs/test/src/exception_safety.cpp
        ../boost_libraries/libs/test/src/execution_monitor.cpp
        ../boost_libraries/libs/test/src/framework.cpp
        ../boost_libraries/libs/test/src/interaction_based.cpp
        ../boost_libraries/libs/test/src/logged_expectations.cpp
        ../boost_libraries/libs/test/src/plain_report_formatter.cpp
        ../boost_libraries/libs/test/src/progress_monitor.cpp
        ../boost_libraries/libs/test/src/results_collector.cpp
        ../boost_libraries/libs/test/src/results_reporter.cpp
        ../boost_libraries/libs/test/src/test_main.cpp
        ../boost_libraries/libs/test/src/test_tools.cpp
        ../boost_libraries/libs/test/src/unit_test_log.cpp
        ../boost_libraries/libs/test/src/unit_test_main.cpp
        ../boost_libraries/libs/test/src/unit_test_monitor.cpp
        ../boost_libraries/libs/test/src/unit_test_parameters.cpp
        ../boost_libraries/libs/test/src/unit_test_suite.cpp
        ../boost_libraries/libs/test/src/xml_log_formatter.cpp
        ../boost_libraries/libs/test/src/xml_report_formatter.cpp
    )

    target_include_directories(boost_unit_test PRIVATE -DBOOST_TEST_MAIN)
    target_include_directories(boost_unit_test PUBLIC ../boost_libraries)
endif()

set(PLATFORM ue4_umg CACHE STRING "Platform to build for; must be one of cygwin, windows, macintosh, or ue4_umg")

add_subdirectory(source)
if (NOT MSVC)
# TODO    add_subdirectory(test)
endif()
