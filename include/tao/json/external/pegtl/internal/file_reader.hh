// Copyright (c) 2014-2017 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/ColinH/PEGTL/

#ifndef TAO_CPP_PEGTL_INTERNAL_FILE_READER_HH
#define TAO_CPP_PEGTL_INTERNAL_FILE_READER_HH

#include <cstdio>
#include <memory>
#include <string>
#include <utility>

#include "../input_error.hh"

namespace tao_json_pegtl
{
   namespace internal
   {
      class file_reader
      {
      public:
         explicit
         file_reader( std::string filename )
               : m_source( std::move( filename ) ),
                 m_file( open(), & std::fclose )
         { }

         file_reader( const file_reader & ) = delete;
         void operator= ( const file_reader & ) = delete;

         std::size_t size() const
         {
            errno = 0;
            if ( std::fseek( m_file.get(), 0, SEEK_END ) != 0 ) {
               TAO_CPP_PEGTL_THROW_INPUT_ERROR( "unable to fseek() to end of file " << m_source );  // LCOV_EXCL_LINE
            }
            errno = 0;
            const auto s = std::ftell( m_file.get() );
            if ( s < 0 ) {
               TAO_CPP_PEGTL_THROW_INPUT_ERROR( "unable to ftell() file size of file " << m_source );  // LCOV_EXCL_LINE
            }
            errno = 0;
            if ( std::fseek( m_file.get(), 0, SEEK_SET ) != 0 ) {
               TAO_CPP_PEGTL_THROW_INPUT_ERROR( "unable to fseek() to beginning of file " << m_source );  // LCOV_EXCL_LINE
            }
            return s;
         }

         std::string read() const
         {
            std::string nrv;
            nrv.resize( size() );
            errno = 0;
            if ( ( nrv.size() != 0 ) && ( std::fread( & nrv[ 0 ], nrv.size(), 1, m_file.get() ) != 1 ) ) {
               TAO_CPP_PEGTL_THROW_INPUT_ERROR( "unable to fread() file " << m_source << " size " << nrv.size() );  // LCOV_EXCL_LINE
            }
            return nrv;
         }

      private:
         const std::string m_source;
         const std::unique_ptr< std::FILE, decltype( & std::fclose ) > m_file;

         std::FILE * open() const
         {
            errno = 0;
#ifdef _WIN32
            std::FILE* file;
            if ( ::fopen_s( & file, m_source.c_str(), "rb" ) == 0 )
#else
            if ( auto * file = std::fopen( m_source.c_str(), "rb" ) )
#endif
            {
               return file;
            }
            TAO_CPP_PEGTL_THROW_INPUT_ERROR( "unable to fopen() file " << m_source << " for reading" );
         }
      };

   } // namespace internal

} // namespace tao_json_pegtl

#endif
