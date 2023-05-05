
/*
 * Value categories play an important role when we bind reference to objects.
 *
 */

#include <string>
#include "../../../util/print.h"

#include "OverloadResolutionWithRvalueRef.h"
#include "OverloadingByRefAndVal.h"

std::string createString()
{
    return "hello";
}

void foo1(std::string const& s){
    println(__PRETTY_FUNCTION__);
}

void foo2(std::string& s){
    println(__PRETTY_FUNCTION__);
}


void bindRef()
{
    const std::string & r1 { createString() }; //OK

    //    std::string&r2 {createString()};//ERROR. cannot bind a non-const lvalue reference to an rvalue
    std::string && r3 { createString() }; //extend lifetime


    foo1(std::string("hello"));//OK
  //  foo2(std::string("world")); // ERROR cannot bind a non-const lvalue reference to an rvalue

}

int main()
{
    overloadRef();
    overloading_by_ref_val();
    return 0;
}
