// Copyright (c) 2014-2016 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/ColinH/PEGTL/

#ifndef TAO_CPP_PEGTL_INTERNAL_INPUT_MARK_HH
#define TAO_CPP_PEGTL_INTERNAL_INPUT_MARK_HH

#include "input_data.hh"

namespace tao_json_pegtl
{
   namespace internal
   {
      class input_mark
      {
      public:
         explicit
         input_mark( input_data & i )
               : m_byte( i.byte ),
                 m_line( i.line ),
                 m_byte_in_line( i.byte_in_line ),
                 m_begin( i.begin ),
                 m_input( & i )
         { }

         input_mark( input_mark && i ) noexcept
               : m_byte( i.m_byte ),
                 m_line( i.m_line ),
                 m_byte_in_line( i.m_byte_in_line ),
                 m_begin( i.m_begin ),
                 m_input( i.m_input )
         {
            i.m_input = nullptr;
         }

         ~input_mark()
         {
            if ( m_input != nullptr ) {
               m_input->byte = m_byte;
               m_input->line = m_line;
               m_input->byte_in_line = m_byte_in_line;
               m_input->begin = m_begin;
            }
         }

         input_mark( const input_mark & ) = delete;
         void operator= ( const input_mark & ) = delete;

         bool operator() ( const bool result )
         {
            if ( result ) {
               m_input = nullptr;
               return true;
            }
            return false;
         }

         std::size_t byte() const
         {
            return m_byte;
         }

         std::size_t line() const
         {
            return m_line;
         }

         std::size_t byte_in_line() const
         {
            return m_byte_in_line;
         }

         const char * begin() const
         {
            return m_begin;
         }

      private:
         const std::size_t m_byte;
         const std::size_t m_line;
         const std::size_t m_byte_in_line;
         const char * const m_begin;
         input_data * m_input;
      };

   } // namespace internal

} // namespace tao_json_pegtl

#endif
