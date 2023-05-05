#pragma once

#include "../../../util/print.h"

class X
{
};

// Table Rules for binding references lists the formal rules for binding reference to passed arguments if
// we provide all the reference overloads fo a function f()
inline void f( X const & )
{ // read-only access
    println( __PRETTY_FUNCTION__ );
}

inline void f( X & )
{ // OUT parameter( usually long-living object)
    println( __PRETTY_FUNCTION__ );
}


inline void f( X && )
{ // can steal value(object usually about to die)
    println( __PRETTY_FUNCTION__ );
}

inline void f( X const && )
{ // no clear semantics meaning
    println( __PRETTY_FUNCTION__ );
}


// The numbers list the priority for overload resolution so that you can see which function is called when multiple
// overloads are provided. The smaller the number, the higher the priority(priority 1 means that this is first tired first)

//---------------------------------------------------------------------------
//  Call      |   f(X&)   |  f(X const&)  |   f(X&&)     |   f(X const&&)   |
//==========================================================================|
//  f(v)      |    1     |     2         |    no        |       no          |
//  f(c)      |    no    |     1         |    no        |       no          |
// f(X{})     |    no    |     3         |    1         |       2           |
// f(move(v)) |    no    |     3         |    1         |       2           |
// f(move(c)) |    no    |     2         |    no        |       1           |
//--------------------------------------------------------------------------
//
//.A non-const lvalue reference takes only non-const lvalues.
//.An rvalue reference tatkes only non-const rvalues.
//.A const lvalue reference can take everthing and servers as the fallback mechanism in case other overloads are not provided.
//
//--------------------------------------
//  Call       | f(X const&) |  f(X&&) |
//=====================================|
//  f(X{})     |    3        |     1   |
//  f(move(v)) |    3        |     1   |
//-------------------------------------

inline void overloadRef()
{
    println( __PRETTY_FUNCTION__ );

    X x {};
    f( x ); //non-const lvalue reference f(X&)
    const X cx {};
    f( cx ); // const lvalue reference f(X const&)

    f( std::move( x ) ); // rvalue reference f(X&&)   if no define f(X&&) fallback f(X const&)
    f( X {} );           // rvalue reference  f(X&&) if no define f(X&&) fallback f(X const&)

    f(std::move(cx));  // const rvalue refernce f(X const&&) if no define f(X&&) fallback f(X const&)
}
