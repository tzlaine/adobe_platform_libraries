/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/****************************************************************************************************/

#ifndef BUILD_FOR_TEST
#include "Spaceport.h"
#endif

#include <adobe/future/platform_locale_data.hpp>

#include <adobe/future/locale.hpp>
#include <adobe/name.hpp>

#include <locale>

/****************************************************************************************************/

namespace adobe {

/****************************************************************************************************/

namespace implementation {

/****************************************************************************************************/

void do_locale_check()
{
    static std::string locale_identifier_s;

    std::locale locale("");
    std::string new_locale_identifier = locale.name();

    if (locale_identifier_s != new_locale_identifier)
    {
        locale_identifier_s = new_locale_identifier;

        dictionary_t new_locale_data;

        // first collect all the relevant information for the locale dictionary

        auto const & numpunct = std::use_facet<std::numpunct<char>>(locale);

        any_regular_t decimal_point(std::string(1, numpunct.decimal_point()));
        any_regular_t thousands_separator(std::string(1, numpunct.thousands_sep()));

        // finally push all the relevant information to the locale dictionary

        new_locale_data.insert(std::make_pair(key_locale_identifier, any_regular_t(new_locale_identifier)));
        new_locale_data.insert(std::make_pair(key_locale_decimal_point, decimal_point));
        new_locale_data.insert(std::make_pair(key_locale_thousands_separator, thousands_separator));

        implementation::signal_locale_change(new_locale_data);
    }
}

/****************************************************************************************************/

} // namespace implementation

/****************************************************************************************************/

} // namespace adobe

/****************************************************************************************************/
