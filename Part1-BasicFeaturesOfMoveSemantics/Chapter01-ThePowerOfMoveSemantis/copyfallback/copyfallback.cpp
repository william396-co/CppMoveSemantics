#include "../../../util/print.h"
#include <string>

template<typename T>
class MyVectorWithoutMove
{
public:
    void push_back( T const & elem )
    {
        println( __PRETTY_FUNCTION__ );
    }
};

template<typename T>
class MyVectorWithMove
{
public:
    void push_back( T const & elem )
    {
        println( __PRETTY_FUNCTION__ );
    }
    void push_back( T && elem )
    {
        println( __PRETTY_FUNCTION__ );
    }
};

std::string globalStr { "hello world" };
// BAD: disables move semantic for return values
const std::string getValue()
{
    return "42";
}

const std::string & getRef()
{
    return globalStr;
}

const std::string * getPtr()
{
    return &globalStr;
}

/*
 * Summary
 *
 * 1  Move semantics allows us to optimize the copying of objects, where we no longger need the value. It can be used implicitly
 *     (for unnamed temporary object or local return values) or explicitly(with std::move()).
 *
 * 2 std::move() means I no longer need this value here, It marks the object as movable. An object marked with std::move() is
 *      not(partially) destroyed( the destructor still will be called)
 *
 * 3 By declaring a function with a non-const rvalue reference(such as std::string&&), you define an interface where the caller
 *      semantically claim that it no longger needs to passed value. The implementer of the function can use this information
 *      to optimize its task by "stealing" the value of do any other modification with the passed argument. Usually ,the implementer
 *      also has to ensure that the passed argument is in a valid state after the call.
 *
 * 4 Move-from objects of the C++ standard library are still valid objects, but you no longer know their value.
 *
 * 4 Copy semantics is used as a fallback for move semantics(if copy semantics is supported), If there is no implementation taking
 *      an rvalue reference, any implementation taking an ordinary const lvalue reference(such as const std::string&) is used.
 *      This fallback is then used even if the object is explicitly marked with std::move()
 *
 *  5 Calling std::move() for a const object usually has no affect
 *
 *  6 If you return by value(not by reference), do not declare the return value as a whole to be const
 */
int main()
{

    // Copying as a Fallback
    {
        MyVectorWithoutMove<std::string> coll;

        std::string s { "data" };
        coll.push_back( s );              // uses copy semantics
        coll.push_back( std::move( s ) ); // uses copy semantics(copying as a fallback)
    }

    // Move Semantics for const object
    {
        MyVectorWithMove<std::string> coll;
        const std::string cs { "hello" };
        coll.push_back( std::move( cs ) ); // call push_back(T const&)
    }

    // const Return values
    {
        MyVectorWithMove<std::string> coll;
        coll.push_back( getValue() );             // call push_back(T const&)
        coll.push_back( std::move( getRef() ) );  // call push_back(T const&)
        coll.push_back( std::move( *getPtr() ) ); // call push_back(T const&)
    }

    return 0;
}
