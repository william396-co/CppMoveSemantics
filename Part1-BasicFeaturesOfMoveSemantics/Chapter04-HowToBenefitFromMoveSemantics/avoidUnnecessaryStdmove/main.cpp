#include "../../../util/print.h"

#include <string>

// If you return local objects by value, do not use std::move()
std::string foo()
{
    std::string s { "foo" };

    return std::move( s ); //BAD: dont do this
}

int main()
{

    std::string s { foo() }; // Ok
    println( s );

    std::string s2 { std::move( foo() ) }; // BAD: dont do this
    println( s2 );

    return 0;
}
