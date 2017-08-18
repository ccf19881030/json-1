// Copyright (c) 2017 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/json/

#ifndef TAOCPP_JSON_INCLUDE_JAXN_FROM_STRING_HPP
#define TAOCPP_JSON_INCLUDE_JAXN_FROM_STRING_HPP

#include <cstddef>
#include <string>
#include <utility>

#include "../events/jaxn/from_string.hpp"
#include "../events/to_value.hpp"
#include "../events/transformer.hpp"

namespace tao
{
   namespace json
   {
      namespace jaxn
      {
         template< template< typename... > class Traits, template< typename... > class... Transformers >
         basic_value< Traits > basic_from_string( const char* data, const std::size_t size, const char* source = nullptr, const std::size_t byte = 0, const std::size_t line = 1, const std::size_t column = 0 )
         {
            events::transformer< events::to_basic_value< Traits >, Transformers... > consumer;
            events::jaxn::from_string( data, size, consumer, source, byte, line, column );
            return std::move( consumer.value );
         }

         template< template< typename... > class Traits, template< typename... > class... Transformers >
         basic_value< Traits > basic_from_string( const char* data, const std::size_t size, const std::string& source, const std::size_t byte = 0, const std::size_t line = 1, const std::size_t column = 0 )
         {
            return basic_from_string< Traits, Transformers... >( data, size, source.c_str(), byte, line, column );
         }

         template< template< typename... > class... Transformers >
         value from_string( const char* data, const std::size_t size, const char* source = nullptr, const std::size_t byte = 0, const std::size_t line = 1, const std::size_t column = 0 )
         {
            return basic_from_string< traits, Transformers... >( data, size, source, byte, line, column );
         }

         template< template< typename... > class... Transformers >
         value from_string( const char* data, const std::size_t size, const std::string& source, const std::size_t byte = 0, const std::size_t line = 1, const std::size_t column = 0 )
         {
            return basic_from_string< traits, Transformers... >( data, size, source.c_str(), byte, line, column );
         }

         template< template< typename... > class Traits, template< typename... > class... Transformers >
         basic_value< Traits > from_string( const std::string& data, const char* source = nullptr, const std::size_t byte = 0, const std::size_t line = 1, const std::size_t column = 0 )
         {
            return basic_from_string< Traits, Transformers... >( data.data(), data.size(), source, byte, line, column );
         }

         template< template< typename... > class Traits, template< typename... > class... Transformers >
         basic_value< Traits > from_string( const std::string& data, const std::string& source, const std::size_t byte = 0, const std::size_t line = 1, const std::size_t column = 0 )
         {
            return basic_from_string< Traits, Transformers... >( data.data(), data.size(), source.c_str(), byte, line, column );
         }

         template< template< typename... > class... Transformers >
         value from_string( const std::string& data, const char* source = nullptr, const std::size_t byte = 0, const std::size_t line = 1, const std::size_t column = 0 )
         {
            return from_string< Transformers... >( data.data(), data.size(), source, byte, line, column );
         }

         template< template< typename... > class... Transformers >
         value from_string( const std::string& data, const std::string& source, const std::size_t byte = 0, const std::size_t line = 1, const std::size_t column = 0 )
         {
            return from_string< Transformers... >( data.data(), data.size(), source.c_str(), byte, line, column );
         }

         template< template< typename... > class... Transformers, template< typename... > class Traits, typename... Ts >
         void from_string( basic_value< Traits >& output, Ts&&... ts )
         {
            output = basic_from_string< Traits, Transformers... >( std::forward< Ts >( ts )... );
         }

         inline namespace literals
         {
            inline value operator"" _jaxn( const char* data, const std::size_t size )
            {
               return jaxn::from_string( data, size, "literal" );
            }

         }  // namespace literals

      }  // namespace jaxn

   }  // namespace json

}  // namespace tao

#endif