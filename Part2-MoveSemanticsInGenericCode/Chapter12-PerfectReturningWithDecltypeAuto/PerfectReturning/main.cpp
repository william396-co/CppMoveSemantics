#include "../../../util/print.h"
#include <string>

/*
 * 12.1 Perfect Returning
 *
 * In generic code, we often compute a value that we then return to the caller, The question is,
 * how do we perfectly return the value but still keep whatever type and value category it has?
 *
 * A couple of options do not work:
 * 1. Return type auto will remove the reference of the return of foo(), If, for examp,e we give
 *    access to the element of a container(consider foo() as the at() member function or index operator
 *    of a vector), callFoo() would no longer give access to the element, In addition, we might create
 *    an unnecessary copy(if no optimized away).
 *  2.Any return type that is a reference(auto&, const auto&, and auto&&) will return a reference to a local
 *   object if foo() return a temporary object by value, Fortunately, compilers can issue a warning when
 *   they detect such a bug.
 *
 *  That is ,we need a way to say:
 *  . Return by value if we got/have a value
 *  . Return by reference if we got/have a reference
 *
 *  but still keep both the type and value category of what we return.
 *  C++14 introduced a new placeholder type for this purpose: decltype(auto)
 */


void foo(std::string const& s){
    println(__PRETTY_FUNCTION__,"(",s,")");
}

std::string foo(std::string&& s){
    return std::move(s);
}

template<typename T>
decltype(auto) callFoo(T&& arg){
    return foo(std::forward<T>(arg));
}


int main(){


    std::string s{"hi"};
    callFoo(s);
    println(callFoo(std::move(s)));

    return 0;
}
