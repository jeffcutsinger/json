// Copyright (c) 2014-2015 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/ColinH/PEGTL/

#ifndef TAO_CPP_PEGTL_INTERNAL_STAR_MUST_HH
#define TAO_CPP_PEGTL_INTERNAL_STAR_MUST_HH

#include "star.hh"
#include "if_must.hh"

namespace tao_json_pegtl
{
   namespace internal
   {
     template< typename Cond, typename ... Rules >
     using star_must = star< if_must< Cond, Rules ... > >;

   } // namespace internal

} // namespace tao_json_pegtl

#endif
