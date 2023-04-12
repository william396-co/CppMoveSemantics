#include "../../../util/print.h"

#include <ostream>
#include <string>

std::string returnStringByVal()
{
    return std::string( "world" );
}

void RValRefInDetails()
{
    println( __PRETTY_FUNCTION__ );
    // rvalue reference can refere only to temporary object that does not have a name
    // or an object marked with std::move()

    std::string s { "hello" };

    //    std::string && r1 { s }; //ERROR
    std::string && r2 { std::move( s ) };

    std::string && r3 { returnStringByVal() }; //extends lifetime of return value

    println( "r2 = ", r2 );
    println( "r3 = ", r3 );
    println( "s = ", s );

    std::string && r4 = std::move( s );
    std::string && r5 { std::move( s ) };
    std::string && r6( std::move( s ) );

    // All these references have the semantics of "we can steal/modify the object we refer to, provide
    // the state of the object remains a valid state"
    //r4 = "good morning";
    s = std::string( "evening" );
    println( r4, " ", r5, " ", r6 ); //evening evening evening
    println( s );
}

void foo( std::string && rv )
{
    println( __PRETTY_FUNCTION__, "(", rv, ")" );

    rv = "foo";
}

void RValRefAsParam()
{
    println( __PRETTY_FUNCTION__ );

    std::string s { "middle night" };

    //    foo(s); // ERROR
    foo( std::move( s ) ); // OK, value of string might change
    foo( returnStringByVal() );
    println( "after foo s = ", s );

    s = "hello again";
    foo( std::move( s ) );
}

int main()
{

    RValRefInDetails();
    RValRefAsParam();
    return 0;
}
