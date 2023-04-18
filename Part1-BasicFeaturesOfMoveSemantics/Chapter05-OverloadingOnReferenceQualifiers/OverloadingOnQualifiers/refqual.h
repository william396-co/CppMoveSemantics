#pragma once

#include "../../../util/print.h"

class C
{
public:
#if __cplusplus < 201103L

    // before C++11, only have const and non-const
    void foo()
    {
        println( __PRETTY_FUNCTION__ );
    }
    void foo() const
    {
        println( __PRETTY_FUNCTION__ );
    }
#else
    // Usually, we have two or three of these oveloads, such as using && and const&(and &) for getters.
    void foo() &
    {
        println( __PRETTY_FUNCTION__ );
    }

    void foo() &&
    {
        println( __PRETTY_FUNCTION__ );
    }

    void foo() const &
    {
        println( __PRETTY_FUNCTION__ );
    }

    void foo() const &&
    {
        println( __PRETTY_FUNCTION__ );
    }
#endif
};
