// Copyright (c) 2015-2018 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/json/

#ifndef TAOCPP_JSON_INCLUDE_TO_STREAM_HPP
#define TAOCPP_JSON_INCLUDE_TO_STREAM_HPP

#include <cstddef>
#include <ostream>

#include "events/from_value.hpp"
#include "events/to_pretty_stream.hpp"
#include "events/to_stream.hpp"
#include "events/transformer.hpp"
#include "value.hpp"

namespace tao
{
   namespace json
   {
      template< template< typename... > class... Transformers, template< typename... > class Traits, typename Base >
      void to_stream( std::ostream& os, const basic_value< Traits, Base >& v )
      {
         events::transformer< events::to_stream, Transformers... > consumer( os );
         events::from_value( consumer, v );
      }

      template< template< typename... > class... Transformers, template< typename... > class Traits, typename Base >
      void to_stream( std::ostream& os, const basic_value< Traits, Base >& v, const std::size_t indent )
      {
         events::transformer< events::to_pretty_stream, Transformers... > consumer( os, indent );
         events::from_value( consumer, v );
      }

   }  // namespace json

}  // namespace tao

#endif
