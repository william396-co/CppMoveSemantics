#include "../../../util/print.h"

#include <string>
#include <type_traits>
#include <utility> //std::move

// Implementation of std::move()
namespace details {

// remove_reference
template<typename _Tp>
struct remove_reference
{
    typedef _Tp type;
};

template<typename _Tp>
struct remove_reference<_Tp &>
{
    typedef _Tp type;
};

template<typename _Tp>
struct remove_reference<_Tp &&>
{
    typedef _Tp type;
};

template<typename T>
constexpr typename remove_reference<T>::type && move( T && t ) noexcept
{
    return static_cast<typename remove_reference<T>::type &&>( t );
}
} // namespace details

void foo1( std::string const & lr )
{
    println( __PRETTY_FUNCTION__, "(", lr, ")" );
}

void foo1( std::string && rv )
{
    println( __PRETTY_FUNCTION__, "(", rv, ")" );
}

void foo2( std::string const & lr )
{
    println( __PRETTY_FUNCTION__, "(", lr, ")" );
}

void foo3( std::string & r )
{
    println( __PRETTY_FUNCTION__, "(", r, ")" );
}

int main()
{

    std::string s { "hello" };
    foo1( s );                  // call reference to const
    foo1( std::move( s ) );     // call rvalue reference
    foo1( details::move( s ) ); // equal to std::move()

    foo2( s );                  // call reference to const
    foo2( std::move( s ) );     // fallback reference to const parameter
    foo2( details::move( s ) ); // explicitly cast to rvalue reference

    foo3( s ); // call reference
    //    foo3(std::move(s));//ERROR , na matching foo3() declared

    return 0;
}
