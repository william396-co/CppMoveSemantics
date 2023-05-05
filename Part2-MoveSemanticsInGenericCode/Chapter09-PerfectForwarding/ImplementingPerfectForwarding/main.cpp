#include <utility>

/*
 * To avoid overloading functions for parameters with different value categories, C++ introduced a special
 * mechanism for perfect forwarding ,You need three things:
 * 1. Take the call parameter as a pure rvalue reference(declared with && but without const or volatile).
 * 2. The type of parameter has to be a template parameter of function.
 * 3.When forwarding the parameter to another function. use a helper function called std::forward<>(), which declared in <utility>
 */

template<typename T>
void callFoo( T && arg )
{
    foo( std::forward<T>( arg ) );
}
// std::forward<>() is effectively a conditional std::move() so that we get the same behavior
// as three(or four) overloads of callFoo above
// .If we pass an rvalue to arg, we have the same effect as calling foo(std::move(arg))
// .If we pass an lvalue to arg, we have the same effect as calling foo(arg)

template<typename T1, typename T2>
void callFoo( T1 && arg1, T2 && arg2 )
{
    foo( std::forward<T1>( arg1 ), std::forward<T2>( arg2 ) );
}

// we can also apply std::forward<>() to each argument of a variadic number of parameters to perfectly forward them all.
template<typename... Ts>
void callFoo( Ts &&... args )
{
    foo( std::forward<Ts>( args )... );
}


/*
 * 9.2.1 Universal(or Forwarding) References
 */


int main()
{

    return 0;
}
