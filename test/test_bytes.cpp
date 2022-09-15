#include "test.h"

template<typename T, typename P>
class Base
{
public:
    Base(P * parent) : _parent(parent) {}
    ~Base() {}

    template<typename U>
    bool operator==(const U & other) const
    {
        return (_parent->operator T() == (T) other);
    }

    template<typename U>
    bool operator!=(const U & other) const
    {
        return !operator==(other);
    }

    P * _parent;

}; /* class: Base */

template<typename T>
class Bytes : public Base<T, Bytes<T>>
{
public:
    Bytes() : Base<T, Bytes<T>>(this) {}
    ~Bytes() {}

    operator T() const
    {
        return T();
    }

    Bytes & operator=(const T & value)
    {
        return *this;
    }

protected:
    

private:
    

}; /* class: Bytes */

TEST_CASE("asd")
{
    

    auto b = Bytes<unsigned char>();


    REQUIRE(b != 1);

}


