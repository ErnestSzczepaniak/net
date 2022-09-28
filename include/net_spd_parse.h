#ifndef _net_spd_parse_h
#define _net_spd_parse_h

/**
 * @file	net_spd_parse.h
 * @author	en2
 * @date	28-09-2022
 * @brief	
 * @details	
**/

#include "net_spd_type.h"
#include <type_traits>

namespace net::spd
{

class Parse
{
    static constexpr auto ascii_space =     0x20;

    struct Result_address {Group_address address; int next;};
    struct Result_port {Group_port port; int next;};

public:
    Parse();
    ~Parse();

    Policy policy(char * policy);

protected:
    char * _word_point(char * policy, int index);
    bool _word_matches(char * policy, int index, const char * value);
    bool _word_present(char * policy, const char * value);
    int _word_index(char * policy, const char * value);
    template<typename T> T _word_cast(char * policy, int index);

private:
    int _sequence_number(char * policy);
    Condition _condition(char * policy);
    Protocol _protocol(char * policy);
    Result_address _group_address(char * policy, int index);
    Result_port _group_port(char * policy, int index);
    Precedence _precedence(char * policy);
    Dscp _dscp(char * policy);
    bool _log(char * policy);

}; /* class: Parse */

template<typename T> 
T Parse::_word_cast(char * policy, int index)
{
    auto * word = _word_point(policy, index);

    if constexpr (std::is_same_v<T, int>)
    {
        return strtol(word, nullptr, 10);
    }
    else if constexpr (std::is_same_v<T, ip::address::Custom>)
    {
        return ip::address::Custom(word);
    }
}

}; /* namespace: net::spd */

#endif /* define: net_spd_parse_h */