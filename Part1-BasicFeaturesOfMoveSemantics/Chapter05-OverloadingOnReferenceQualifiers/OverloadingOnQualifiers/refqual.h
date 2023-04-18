#pragma once

#include "../../../util/print.h"

class C
{
public:
#if __cplusplus < 201103L
    void foo()
    {
        println( __PRETTY_FUNCTION__ );
    }
    void foo() const
    {
        println( __PRETTY_FUNCTION__ );
    }
#else
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
