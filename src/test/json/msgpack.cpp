// Copyright (c) 2017 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/json/

#include "test.hpp"
#include "unhex.hpp"

#include <tao/json.hpp>

#include <tao/json/msgpack/to_string.hpp>

namespace tao
{
   namespace json
   {
      template< template< typename... > class Traits >
      void to_msgpack_stream( std::ostream& os, const basic_value< Traits >& v )
      {
         msgpack::to_stream consumer( os );
         events::from_value( v, consumer );
      }

      template< template< typename... > class Traits >
      std::string to_msgpack_string( const basic_value< Traits >& v )
      {
         msgpack::to_string consumer;
         events::from_value( v, consumer );
         return consumer.value();
      }

      void msgpack_encode( const std::string& text, const std::string& data )
      {
         TEST_ASSERT( to_msgpack_string( from_string( text ) ) == internal::unhex( data ) );
      }

      void unit_test()
      {
         msgpack_encode( "null", "c0" );
         msgpack_encode( "true", "c3" );
         msgpack_encode( "false", "c2" );
         msgpack_encode( "\"a\"", "a161" );
         msgpack_encode( "\"ab\"", "a26162" );
         msgpack_encode( "[]", "90" );
         msgpack_encode( "{}", "80" );
         msgpack_encode( "[null]", "91c0" );
         msgpack_encode( "{\"a\":true,\"b\":false}", "82a161c3a162c2" );
         msgpack_encode( "\"000\"", "a3303030" );
         msgpack_encode( "\"01234567890123456789\"", "b43031323334353637383930313233343536373839" );
         msgpack_encode( "\"0123456789012345678901234567890123456789\"", "d92830313233343536373839303132333435363738393031323334353637383930313233343536373839" );
         msgpack_encode( "0", "00" );
         msgpack_encode( "1", "01" );
         msgpack_encode( "127", "7f" );
         msgpack_encode( "128", "cc80" );
         msgpack_encode( "255", "ccff" );
         msgpack_encode( "256", "cd0100" );
         msgpack_encode( "32767", "cd7fff" );
         msgpack_encode( "32768", "cd8000" );
         msgpack_encode( "65535", "cdffff" );
         msgpack_encode( "2147483647", "ce7fffffff" );
         msgpack_encode( "2147483648", "ce80000000" );
         msgpack_encode( "4294967295", "ceffffffff" );
         msgpack_encode( "9223372036854775807", "cf7fffffffffffffff" );
         msgpack_encode( "9223372036854775808", "cf8000000000000000" );
         msgpack_encode( "-1", "ff" );
         msgpack_encode( "-32", "e0" );
         msgpack_encode( "-128", "d080" );
         msgpack_encode( "-129", "d1ff7f" );
         msgpack_encode( "-32768", "d18000" );
         msgpack_encode( "-32769", "d2ffff7fff" );
         msgpack_encode( "-2147483648", "d280000000" );
         msgpack_encode( "-2147483649", "d3ffffffff7fffffff" );
         msgpack_encode( "-9223372036854775808", "d38000000000000000" );
      }

   }  // namespace json

}  // namespace tao

#include "main.hpp"
