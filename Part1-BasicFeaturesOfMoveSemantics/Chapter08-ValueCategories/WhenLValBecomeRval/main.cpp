

#include <string>
#include "../../../util/print.h"

void rvFunc( std::string && s )
{
    println( __PRETTY_FUNCTION__, "(", s, ")" );
}

int main()
{
    std::string s { "hello" };
    //    rvFunc(s);// cannot bind rvalue reference to lvalue

    rvFunc( std::move( s ) );

    // Remember that string literals are lvalues when used as an expression.
    rvFunc( "hello" ); //OK, although "hello" is an lvalue (because const char* not match the type of parameter,
                       // we have an implicit type conversion, performed by the string constructor, which creates
                       // a temporary object that does not have a name.
    // equal to
    rvFunc( std::string( "hello" ) ); // Ok, "hello" converted to a string is a prvalue
}
