#pragma once

#include <string>
#include <utility>
 namespace hc {
     enum class TokenType  {
         START_TAG,
         END_TAG,
         TEXT,
         COMMENT,
         ATTRIBUTE,
         END_OF_FILE,
         UNKNOWN
     };

     class Token {
     public:
         TokenType type=TokenType::UNKNOWN;
         std::string value;

         Token()=default;
         Token(TokenType type, std::string value) : type(type), value(value) {}

     };
 }