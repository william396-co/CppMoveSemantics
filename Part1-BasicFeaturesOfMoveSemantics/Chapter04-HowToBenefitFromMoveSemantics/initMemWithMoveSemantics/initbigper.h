#pragma once
#include "../../../util/print.h"

#include <string>
#include <vector>

// A surprising consequence is that you can benefit from move semantics even in trivial classes with members
// of types that benefit from move semantics(such as string members or containers)
class Person
{
public:
    Person( std::string n, std::vector<std::string> && v )
        : name { std::move( n ) }, values { std::move( v ) }
    {
        //   println( __PRETTY_FUNCTION__);
    }

    Person( std::string n, std::vector<std::string> const & v )
        : name { std::move( n ) }, values { v }
    { //   println( __PRETTY_FUNCTION__);
    }

private:
    std::string name;
    std::vector<std::string> values;
};
