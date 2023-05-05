
/*
 * What we Need to Perfect Forward Arguments
 */

#include "../../../util/print.h"

class X
{};

void foo( X const & )
{
    println( __PRETTY_FUNCTION__ );
}
void foo( X & )
{
    println( __PRETTY_FUNCTION__ );
}

void foo( X && )
{
    println( __PRETTY_FUNCTION__ );
}

// Now assume that we want to call foo() for the same arguments indirectly via a helper function callFoo().
// that helper function would also need the three overloads

void callFoo( X const & arg ) // arg bind to all const objects
{
    foo( arg ); // call foo(X const&)
}

void callFoo( X & arg ) // arg binds to lvalue
{
    foo( arg ); // calls foo(X&)
}

void callFoo( X && arg )     // arg binds to rvalue
{                            // move semantics not pass through
    foo( std::move( arg ) ); // needs std::move() to call foo(X&&)
}

int main()
{

    X v;
    const X c;

    foo( v );              // foo(X&)
    foo( c );              // foo(X const&)
    foo( X {} );           // foo(X&&)
    foo( std::move( v ) ); // foo(X&&)
    foo( std::move( c ) ); // fallback foo(X const&)

    println( "========================================" );

    X v1;
    const X c1;
    callFoo( v1 );
    callFoo( c1 );
    callFoo( X {} );
    callFoo( std::move( v1 ) );
    callFoo( std::move( c1 ) );

    return 0;
}
