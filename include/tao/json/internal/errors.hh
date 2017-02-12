// Copyright (c) 2015-2016 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/json/

#ifndef TAOCPP_JSON_INCLUDE_INTERNAL_ERRORS_HH
#define TAOCPP_JSON_INCLUDE_INTERNAL_ERRORS_HH

#include <string>

#include "../external/pegtl/normal.hh"
#include "../external/pegtl/parse_error.hh"

#include "grammar.hh"

namespace tao
{
   namespace json
   {
      namespace internal
      {
         template< typename Rule >
         struct errors
               : public tao_json_pegtl::normal< Rule >
         {
            static const std::string error_message;

            template< typename Input, typename ... States >
            static void raise( const Input & in, States && ... )
            {
               throw tao_json_pegtl::parse_error( error_message, in );
            }
         };

#if defined(_MSC_VER)
#define WEAK_PREFIX __declspec(selectany)
#define WEAK_SUFFIX
#else
#define WEAK_PREFIX
#define WEAK_SUFFIX __attribute__(( weak ))
#endif

         template<> WEAK_PREFIX const std::string errors< rules::text >::error_message WEAK_SUFFIX = "no valid JSON";

         template<> WEAK_PREFIX const std::string errors< rules::end_array >::error_message WEAK_SUFFIX = "incomplete array, expected ']'";
         template<> WEAK_PREFIX const std::string errors< rules::end_object >::error_message WEAK_SUFFIX = "incomplete object, expected '}'";
         template<> WEAK_PREFIX const std::string errors< rules::member >::error_message WEAK_SUFFIX = "expected member";
         template<> WEAK_PREFIX const std::string errors< rules::name_separator >::error_message WEAK_SUFFIX = "expected ':'";
         template<> WEAK_PREFIX const std::string errors< rules::array_element >::error_message WEAK_SUFFIX = "expected value";
         template<> WEAK_PREFIX const std::string errors< rules::value >::error_message WEAK_SUFFIX = "expected value";

         template<> WEAK_PREFIX const std::string errors< rules::edigits >::error_message WEAK_SUFFIX = "expected at least one exponent digit";
         template<> WEAK_PREFIX const std::string errors< rules::fdigits >::error_message WEAK_SUFFIX = "expected at least one fraction digit";
         template<> WEAK_PREFIX const std::string errors< rules::xdigit >::error_message WEAK_SUFFIX = "incomplete universal character name";
         template<> WEAK_PREFIX const std::string errors< rules::escaped >::error_message WEAK_SUFFIX = "unknown escape sequence";
         template<> WEAK_PREFIX const std::string errors< rules::chars >::error_message WEAK_SUFFIX = "invalid character in string";
         template<> WEAK_PREFIX const std::string errors< rules::string::content >::error_message WEAK_SUFFIX = "unterminated string";
         template<> WEAK_PREFIX const std::string errors< rules::key::content >::error_message WEAK_SUFFIX = "unterminated key";

         template<> WEAK_PREFIX const std::string errors< tao_json_pegtl::eof >::error_message WEAK_SUFFIX = "unexpected character after JSON value";

#undef WEAK_PREFIX
#undef WEAK_SUFFIX

      } // internal

   } // json

} // tao

#endif
