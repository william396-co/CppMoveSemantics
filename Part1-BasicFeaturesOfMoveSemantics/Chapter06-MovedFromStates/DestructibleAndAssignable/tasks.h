#pragma once

#include <array>
#include <exception>
#include <thread>
#include <chrono>
#include "../../../util/print.h"

/*
 * 6.2.2 Non-Destructible Moved-From Objects
 */

class Tasks
{
public:
    Tasks() = default;

    template<typename T>
    void start( T op )
    {
        threads[numThreads] = std::thread { std::move( op ) };
        ++numThreads;
    }

    // OOPS: enable default move semantics
    Tasks( Tasks && ) = default;
    Tasks & operator=( Tasks && ) = default;

    ~Tasks()
    {
        for ( size_t i = 0; i < numThreads; ++i ) {
            if ( threads[i].joinable() ) // only if joinable() then call join()
                threads[i].join();
        }
    }

private:
    std::array<std::thread, 10> threads;
    size_t numThreads { 0 };
};

inline void test_Tasks()
{

    println( __PRETTY_FUNCTION__ );
    Tasks ts;

    ts.start(
        [] {
            std::this_thread::sleep_for( std::chrono::seconds { 2 } );
            println( "nt1 done" );
        } );
    ts.start(
        [] {
            println( "nt2 done" );
        } );
}

inline void test_Tasks_with_move()
{

    println( __PRETTY_FUNCTION__ );
    try {
        Tasks ts;

        ts.start(
            [] {
                std::this_thread::sleep_for( std::chrono::seconds { 2 } );
                println( "nt1 done" );
            } );
        ts.start(
            [] {
                println( "nt2 done" );
            } );

        Tasks other { std::move( ts ) };
    } catch ( std::exception const & e ) {
        std::cerr << "EXCEPTION: " << e.what() << "\n";
    }
}
