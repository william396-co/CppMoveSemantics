#include "../../../util/print.h"

#include <string>

void fooByVal( std::string str )
{
    println( __PRETTY_FUNCTION__, "(", str, ")" );
}

void fooByRRef( std::string && rstr )
{
    println( __PRETTY_FUNCTION__, "(", rstr, ")" );
    auto temp = std::move( rstr );
}

std::string returnStrinByVal()
{
    return "hello";
}

/*
 * A function declared to support move semantics might not use move semantics
 * A function declared to take an argument by value will use move semantics
 */
int main()
{
    /*
     *  If the caller signal that it no longer needs the value of the pass argument(by using std::move() or
     *  pass a temporary object without a name), the parameter str is initialized with the value moved from
     *  the pass argument
     */
    std::string s = "foo";
    fooByVal( s );                  // str becomes a copy of s
    fooByVal( std::move( s ) );     // s is moved to str
    fooByVal( returnStrinByVal() ); // return value is moved to str
    println( "after move s = ", s );

    std::string s1 { "world" }, s2 { "earth" };
    fooByVal( std::move( s1 ) );  // s1 is moved
    fooByRRef( std::move( s2 ) ); // s2 might be moved( whether s2 is stolen/modified depends on the implementation of the fooByRRef()

    println( " after move s1 = ", s1, " s2= ", s2 );

    return 0;
}
