#pragma once

#include "../../../util/print.h"

#include <iostream>
#include <string>

// 6.3.2 Breaking Invariants Due to Moved Consistent Value Members

/*
 * In general, when the state of an object has members that depend on each other in some way, you have to explicitly
 * ensure that the moved-form state is in a valid state, Examples where this might be broken are:
 * .We have differenct representations of the same value but some of them were moved away.
 * .A member such as a counter corresponds with the number of elements in a member
 * .A Boolean value claims that a string value was validated but the validated value was moved away.
 * .A cached value for the average values of all elements is still there but the values(being in container member)
 * were moved away
 */
class IntString
{
public:
    IntString( int i = 0 )
        : val { i }, sval { std::to_string( i ) }
    {
    }

    void setValue( int i )
    {
        val = i;
        sval = std::to_string( i );
    }

    friend std::ostream & operator<<( std::ostream & os, IntString const & is );

private:
    int val;
    std::string sval;
};

inline std::ostream & operator<<( std::ostream & os, IntString const & is )
{
    return os << "[" << is.val << "/" << is.sval << "]";
}

inline void test_intstring()
{
    println( __PRETTY_FUNCTION__ );

    IntString is1 { 42 };
    IntString is2;
    println( "is1 and is2 before moved:" );
    println( is1 );
    println( is2 );

    is2 = std::move( is1 );
    println( "is1 and is2 after moved:" );
    println( is1 );
    println( is2 );
}
