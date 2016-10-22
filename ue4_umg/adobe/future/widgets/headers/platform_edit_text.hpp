/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#ifndef ADOBE_EDIT_TEXT_HPP
#define ADOBE_EDIT_TEXT_HPP

/****************************************************************************************************/

#include <adobe/config.hpp>

#include <adobe/layout_attributes.hpp>
#include <adobe/any_regular.hpp>
#include <adobe/future/widgets/headers/widget_utils.hpp>

#include <adobe/future/widgets/headers/platform_label.hpp>
#include <adobe/future/widgets/headers/edit_text_common.hpp>

#include <boost/function.hpp>

#include <string>

/****************************************************************************************************/

namespace adobe {

/****************************************************************************************************/

    struct edit_text_t : boost::noncopyable
{
    typedef std::string                                         model_type;
    typedef boost::function<void (const std::string&, bool&)>   edit_text_pre_edit_proc_t;
    typedef boost::function<void (const model_type&)>           setter_type;
    typedef boost::function<void (modifiers_t)>          edit_text_label_hit_proc_t;

                      edit_text_t(const edit_text_ctor_block_t& block);
	
#if 1 // TODO
    void              initialize(platform_display_type parent);
#endif
    label_t&          get_label();

// placeable

    void              measure(extents_t& result);
    void              place(const place_data_t& place_data);

//controller
    void              monitor(setter_type proc);
    void              enable(bool active);

//view
    void              display(const model_type&);

    void              set_field_text(const std::string& text);
    void              set_static_disabled(bool is_static_disabled);
    void              set_selection(long start_char, long end_char);
    void              signal_pre_edit(edit_text_pre_edit_proc_t proc);
    //
    /// Recalculate the style which should be given as the Window style
    /// of the edit control.
    ///
    /// \return the window style which should be applied to control_m.
    //
    long              get_window_style() const;

#if 1 // TODO
    platform_display_type control_m;
#endif
    label_t                    name_m;
    std::string                alt_text_m;
    std::wstring               field_text_m;
    bool                       using_label_m;
    long                       characters_m;
    long                       rows_m;
    long                       cols_m;
    long                       max_cols_m;
    bool                       scrollable_m;
    bool                       password_m;
    long                       edit_baseline_m;
    long                       edit_height_m;
    long                       static_baseline_m;
    long                       static_height_m;
    edit_text_pre_edit_proc_t  pre_edit_proc_m;
    setter_type                post_edit_proc_m;
    edit_text_label_hit_proc_t label_hit_proc_m;
    bool                       type_2_debounce_m;
    std::string                value_m; // Used to debounce

private: 
    void                       edit_text_label_hit(modifiers_t);

};

inline std::string get_control_string(const edit_text_t& widget)
{
    UTextBlock* text_block = dynamic_cast<UTextBlock*>(widget.control_m);
    return TCHAR_TO_UTF8(*text_block->GetText().ToString());
}

#if 1 // TODO
inline platform_display_type get_display(edit_text_t & widget)
{ return widget.control_m; }
#endif

/****************************************************************************************************/

} // namespace adobe

/****************************************************************************************************/

#endif

/****************************************************************************************************/
