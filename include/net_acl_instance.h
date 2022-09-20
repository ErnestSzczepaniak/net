#ifndef _net_acl_instance_h
#define _net_acl_instance_h

/**
 * @file	net_acl_instance.h
 * @author	en2
 * @date	20-09-2022
 * @brief	
 * @details	
**/

#include "net_acl_type.h"

namespace net::acl
{

class Instance
{
    static constexpr auto size_policy = 256;
    static constexpr auto number_policy = 256;

public:
    Instance();
    ~Instance();

    bool add(char * policy);
    bool remove(int priority);

protected:
    Policy _parse(int index);

private:
    char _policy[number_policy][size_policy];

}; /* class: Instance */

}; /* namespace: net::acl */

#endif /* define: net_acl_instance_h */