#include <string>

/*
 * move semantics is not passed through,
 * If you pass an object with move semantics you have to mark it with std::move() again to forward
 * its semantics to antoher function
 */

void rvFunc( std::string && str )
{
    // move semantics is not pass through
    //    rvFunc(str); //error: cannot bind rvalue reference to lvalue

    /*  in the function, we dealing with an object that has a name, means that we use str as an lvalue */


    //   rvFunc(std::move(str));//OK passing an xvalue
    rvFunc( static_cast<std::string &&>( str ) ); //OK passing an xvalue
}

int main()
{

    rvFunc( "hello" );

    return 0;
}
