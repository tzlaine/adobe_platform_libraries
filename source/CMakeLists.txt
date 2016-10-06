set(sources
    dictionary_set.cpp
    keyboard.cpp
    sequence_model.cpp

#    ../adobe/future/source/drag_and_drop.cpp
    ../adobe/future/source/cursor_stack.cpp
    ../adobe/future/source/modal_dialog_interface.cpp
    ../adobe/future/source/behavior.cpp
    ../adobe/future/source/cmd_system.cpp
    ../adobe/future/source/image_slurp.cpp
    ../adobe/future/source/resources.cpp
    ../adobe/future/source/menu_system.cpp
    ../adobe/future/source/locale.cpp

    ../adobe/future/widgets/sources/slider_factory.cpp
    ../adobe/future/widgets/sources/default_factory.cpp
    ../adobe/future/widgets/sources/checkbox_factory.cpp
    ../adobe/future/widgets/sources/group_factory.cpp
    ../adobe/future/widgets/sources/label_factory.cpp
    ../adobe/future/widgets/sources/button_factory.cpp
    ../adobe/future/widgets/sources/window_server.cpp
    ../adobe/future/widgets/sources/popup_factory.cpp
    ../adobe/future/widgets/sources/edit_text_factory.cpp
    ../adobe/future/widgets/sources/progress_bar_factory.cpp
    ../adobe/future/widgets/sources/separator_factory.cpp
    ../adobe/future/widgets/sources/edit_number.cpp
    ../adobe/future/widgets/sources/widget_utils.cpp
    ../adobe/future/widgets/sources/alert.cpp
    ../adobe/future/widgets/sources/presets_factory.cpp
    ../adobe/future/widgets/sources/widget_factory.cpp
    ../adobe/future/widgets/sources/optional_panel_factory.cpp
    ../adobe/future/widgets/sources/edit_number_factory.cpp
    ../adobe/future/widgets/sources/image_factory.cpp
    ../adobe/future/widgets/sources/tab_group_factory.cpp
    ../adobe/future/widgets/sources/display_number_factory.cpp
    ../adobe/future/widgets/sources/widget_tokens.cpp
    ../adobe/future/widgets/sources/reveal_factory.cpp
    ../adobe/future/widgets/sources/window_factory.cpp
    ../adobe/future/widgets/sources/toggle_factory.cpp
    ../adobe/future/widgets/sources/widget_factory_registry.cpp
    ../adobe/future/widgets/sources/preview_factory.cpp
    ../adobe/future/widgets/sources/panel_factory.cpp
    ../adobe/future/widgets/sources/sublayout.cpp
    ../adobe/future/widgets/sources/control_button_factory.cpp
    ../adobe/future/widgets/sources/control_button.cpp
    ../adobe/future/widgets/sources/radio_button_factory.cpp
    ../adobe/future/widgets/sources/presets_common.cpp
    ../adobe/future/widgets/sources/link_factory.cpp
    ../adobe/future/widgets/sources/button_helper.cpp
    ../adobe/future/widgets/sources/number_unit.cpp
    ../adobe/future/widgets/sources/virtual_machine_extension.cpp

    ../ue4_umg/adobe/future/source/platform_file_monitor_impl.cpp
    ../ue4_umg/adobe/future/source/platform_locale_data.cpp
    ../ue4_umg/adobe/future/source/platform_number_formatter_data.cpp
    ../ue4_umg/adobe/future/source/platform_periodical_data.cpp

    ../ue4_umg/adobe/future/widgets/sources/platform_button.cpp
    ../ue4_umg/adobe/future/widgets/sources/platform_checkbox.cpp
    ../ue4_umg/adobe/future/widgets/sources/platform_display.cpp
    ../ue4_umg/adobe/future/widgets/sources/platform_display_number.cpp
    ../ue4_umg/adobe/future/widgets/sources/platform_edit_number.cpp
    ../ue4_umg/adobe/future/widgets/sources/platform_edit_text.cpp
#    ../ue4_umg/adobe/future/widgets/sources/platform_group.cpp
    ../ue4_umg/adobe/future/widgets/sources/platform_image.cpp
    ../ue4_umg/adobe/future/widgets/sources/platform_label.cpp
#    ../ue4_umg/adobe/future/widgets/sources/platform_link.cpp
    ../ue4_umg/adobe/future/widgets/sources/platform_metrics.cpp
#    ../ue4_umg/adobe/future/widgets/sources/platform_optional_panel.cpp
#    ../ue4_umg/adobe/future/widgets/sources/platform_panel.cpp
    ../ue4_umg/adobe/future/widgets/sources/platform_popup.cpp
#    ../ue4_umg/adobe/future/widgets/sources/platform_presets.cpp
#    ../ue4_umg/adobe/future/widgets/sources/platform_preview.cpp
#    ../ue4_umg/adobe/future/widgets/sources/platform_progress_bar.cpp
    ../ue4_umg/adobe/future/widgets/sources/platform_radio_button.cpp
#    ../ue4_umg/adobe/future/widgets/sources/platform_reveal.cpp
#    ../ue4_umg/adobe/future/widgets/sources/platform_separator.cpp
    ../ue4_umg/adobe/future/widgets/sources/platform_slider.cpp
#    ../ue4_umg/adobe/future/widgets/sources/platform_tab_group.cpp
#    ../ue4_umg/adobe/future/widgets/sources/platform_toggle.cpp
    ../ue4_umg/adobe/future/widgets/sources/platform_widget_utils.cpp
    ../ue4_umg/adobe/future/widgets/sources/platform_window.cpp
)

file(GLOB_RECURSE INC_LIST ../adobe/*.hpp)
add_library(apl ${sources} ${INC_LIST})

target_include_directories(apl PUBLIC .. ${CMAKE_SOURCE_DIR}/${ASL_ROOT} ${CMAKE_SOURCE_DIR}/${PLATFORM})
target_compile_definitions(apl PUBLIC -DADOBE_STD_SERIALIZATION -DADOBE_PLATFORM_UE4_UMG)

# otherwise boost concept checking fails on adobe::selection_t because it lacks non const begin/end
target_compile_definitions(apl PUBLIC -DBOOST_RANGE_ENABLE_CONCEPT_ASSERT=0)

# GCC6 warning on boost 1.60
# right operand of shift expression '(1u << 63u)' is >= than the precision of the left operand [-fpermissive]
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR
    ${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    target_compile_definitions(apl PUBLIC ADOBE_FNV_NO_BIGINTS)
endif()

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" OR
    ${CMAKE_CXX_COMPILER_ID} STREQUAL "AppleClang")
    target_compile_options(apl PUBLIC -fconstexpr-depth=1024)
    target_compile_options(apl PUBLIC -ftemplate-depth=1024)
endif()

#target_link_libraries(apl PUBLIC double-conversion)

target_link_boost(apl)

if (apl_install_directory)
    install(
        TARGETS apl
        DESTINATION ${apl_install_directory}
    )
endif()
