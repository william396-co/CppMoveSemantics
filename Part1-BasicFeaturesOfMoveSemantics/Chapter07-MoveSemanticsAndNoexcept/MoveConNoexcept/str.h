#include <iostream>
#include <string>
#include <vector>
#include <chrono>

#include "../../../util/print.h"
#include "../../../util/perf_timer.h"

// string wrapper with move constructor
struct Str
{
    std::string val;
    Str()
        : val( 100, 'a' )
    { // don't use braces here
    }

    // enable copying
    Str( Str const & ) = default;

    // enable moving(with and without noexcept)
    Str( Str && s ) noexcept
        : val { std::move( s.val ) }
    {
    }
};

struct Strn
{
    std::string val;
    Strn()
        : val( 100, 'a' ) {}

    Strn( Strn const & ) = default;

    Strn( Strn && s )
        : val { std::move( s.val ) } {}
};

inline void test_str()
{
    println( __PRETTY_FUNCTION__ );

    constexpr auto cnt = 1000000;
    // create vector of 1 Million warpped strings

    constexpr auto times = 10;
    auto test_str_with_noexcept = [&cnt]( int execute_times ) {
        for ( int i = 0; i < execute_times; ++i ) {
            std::vector<Str> coll;
            coll.resize( cnt );
            coll.reserve( coll.capacity() + 1 );
        }
    };

    auto test_str_without_noexcept = [&cnt]( int execute_times ) {
        for ( int i = 0; i < execute_times; ++i ) {
            std::vector<Strn> coll;
            coll.resize( cnt );
            coll.reserve( coll.capacity() + 1 );
        }
    };

    utils::perf_timer_out<std::chrono::milliseconds>( "test_str_with_noexcept", test_str_with_noexcept, times );
    utils::perf_timer_out<std::chrono::milliseconds>( "test_str_without_noexcept", test_str_without_noexcept, times );
}
