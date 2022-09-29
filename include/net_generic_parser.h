#ifndef _net_generic_parser_h
#define _net_generic_parser_h

/**
 * @file	net_generic_parser.h
 * @author	en2
 * @date	29-09-2022
 * @brief	
 * @details	
**/

#include <type_traits>
#include "string.h"
#include <cstdlib>
#include "net_ip.h"

namespace net::generic
{

class Parser
{
    static constexpr auto ascii_space =     0x20;

public:
    Parser();
    ~Parser();

protected:
    char * _word_point(char * record, int index);
    bool _word_matches(char * record, int index, const char * value);
    bool _word_present(char * record, const char * value);
    int _word_index(char * record, const char * value);
    template<typename T> T _word_cast(char * record, int index);

}; /* class: Parser */

template<typename T> 
T Parser::_word_cast(char * record, int index)
{
    auto * word = _word_point(record, index);

    if constexpr (std::is_same_v<T, int>)
    {
        return strtol(word, nullptr, 10);
    }
    else if constexpr (std::is_same_v<T, unsigned long long int>)
    {
        return strtoull(word, nullptr, 16);
    }
    else if constexpr (std::is_same_v<T, ip::address::Custom>)
    {
        return ip::address::Custom(word);
    }
}

}; /* namespace: net::parser */

#endif /* define: net_generic_parser_h */