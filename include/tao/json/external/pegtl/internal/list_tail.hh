// Copyright (c) 2014-2015 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/ColinH/PEGTL/

#ifndef TAO_CPP_PEGTL_INTERNAL_LIST_TAIL_HH
#define TAO_CPP_PEGTL_INTERNAL_LIST_TAIL_HH

#include "seq.hh"
#include "list.hh"
#include "opt.hh"

namespace tao_json_pegtl
{
   namespace internal
   {
      template< typename Rule, typename Sep >
      using list_tail = seq< list< Rule, Sep >, opt< Sep > >;

   } // namespace internal

} // namespace tao_json_pegtl

#endif
