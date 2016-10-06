set(sources
    adobe/future/source/platform_file_monitor_impl.cpp
    adobe/future/widgets/sources/platform_widget_utils.cpp
)

file(GLOB_RECURSE INC_LIST adobe/*.hpp)
add_library(apl_platform_impl ${sources} ${INC_LIST})

target_include_directories(apl_platform_impl PRIVATE adobe/future/source adobe/future/widgets/sources)
target_compile_definitions(apl_platform_impl PRIVATE ADOBE_STD_SERIALIZATION)

# otherwise boost concept checking fails on adobe::selection_t because it lacks non const begin/end
target_compile_definitions(apl_platform_impl PRIVATE -DBOOST_RANGE_ENABLE_CONCEPT_ASSERT=0)

# GCC6 warning on boost 1.60
# right operand of shift expression '(1u << 63u)' is >= than the precision of the left operand [-fpermissive]
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR
    ${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    target_compile_definitions(apl_platform_impl PRIVATE ADOBE_FNV_NO_BIGINTS)
endif()

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" OR
    ${CMAKE_CXX_COMPILER_ID} STREQUAL "AppleClang")
    target_compile_options(apl_platform_impl PRIVATE -fconstexpr-depth=1024)
    target_compile_options(apl_platform_impl PRIVATE -ftemplate-depth=1024)
endif()

#target_link_boost(apl_platform_impl)
