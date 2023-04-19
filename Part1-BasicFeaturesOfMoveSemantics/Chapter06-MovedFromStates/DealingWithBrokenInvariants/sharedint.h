#pragma once

#include "../../../util/print.h"

#include <list>
#include <memory>
#include <string>

/*
 * 6.3.3 Breaking Invariants Due to Moved Pointer-Like Members
 *
 *  move operations should not bring object into a state that breaks invariants:
 *
 * In this case, we have to do one of the following:
 * . Fix all broken operations of the class by also dealing correctly with all possible moved-from states
 * . Disable move semantics so that there is no optimization when copying objects
 * . Implement move operation explicitly
 * . Adjust and document the invariant(constraints/preconditions) for the class or specific operations(such as
 *   "It is undefined behavior to call asString() for a moved-form object)
 *
 */

#define MOVE_SEMANTICS

#ifndef MOVE_SEMANTICS
class SharedInt
{
public:
    explicit SharedInt( int val )
        : sp { std::make_shared<int>( val ) }
    {
    }

    // Fixing Broken Member Functions
    // Still return a fallback value
#ifdef STILL_RETURN
    std::string asString() const
    {
        return sp ? std::to_string( *sp ) : "";
    }
#endif
    // Throw an exception
#ifdef THROW_EXCEPT
    std::string asString() const
    {
        if ( !sp ) throw std::__throw_bad_cast();
        return std::to_string( *sp );
    }
#endif

    // Force a runtime error in debug mode
#ifdef RUNTIME_ERROR
    std::string asString() const
    {
    }
#endif
    std::string asString() const
    {
        return std::to_string( *sp ); // OOPS: assume there is always an int value
    }

    // Disabling Move Semantics
    SharedInt( SharedInt const & ) = default;
    SharedInt & operator=( SharedInt const & ) = default;

private:
    std::shared_ptr<int> sp;
};

#else

class SharedInt
{
public:
    explicit SharedInt( int val )
        : sp { std::make_shared<int>( val ) } {}

    std::string asString() const
    {
        return std::to_string( *sp );
    }

    // fix moving special memeber functions
    SharedInt( SharedInt && si )
        : sp { std::move( si.sp ) }
    {
        si.sp = moveFromValue;
    }

    SharedInt & operator=( SharedInt && si ) noexcept {
        if ( this != &si ) {
            sp = std::move( si.sp );
            si.sp = moveFromValue;
        }
        return *this;
    }

    // enable copying(deleted with user-declared move operations)
    SharedInt( SharedInt const & ) = default;
    SharedInt & operator=( SharedInt const & ) = default;

private:
    std::shared_ptr<int> sp;
    // special "value for moved-from objects
    inline static std::shared_ptr<int> moveFromValue { std::make_shared<int>( 0 ) };
};

#endif

inline void test_sharedint()
{
    println( __PRETTY_FUNCTION__ );
    SharedInt si1 { 42 };
    SharedInt si2 { si1 }; // copy constructor

    println( si1.asString() );

    println( si2.asString() );

    SharedInt si3 { std::move( si1 ) }; // OOPS: move away the allocated memory in si1
    println( si1.asString() );          // undefined behavior(probably core dump, sis.sp = nullptr)
}
