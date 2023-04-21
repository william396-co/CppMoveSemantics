#pragma once

#include "../../../util/print.h"
#include <string>
#include <vector>
#include <type_traits>
#include <iostream>

#define CONDITION_NOEXCEPT

#define DEFAULT_MOVE
class Person
{
public:
    Person( const char * n )
        : name { n } {}

    Person( Person const & p )
        : name { p.name }
    {
        println( "COPY ", name );
    }

#ifdef DEFAULT_MOVE
    Person( Person && ) = default; // default move semantics also provide noexcept guarantee
#else
#ifndef CONDITION_NOEXCEPT
    Person( Person && p ) noexcept( std::is_nothrow_move_constructible<std::string>::value && noexcept( std::cout << p.name ) )
        : name { std::move( p.name ) }
    {
        println( "MOVE ", name );
    }
#else
    Person( Person && p ) noexcept
        : name { std::move( p.name ) }
    {
        println( "MOVE ", name );
    }
#endif
#endif

private:
    std::string name;
};

/*
 * Strong Exception Safety Guarantee
 *
 * The reason that vector reallocation does not use move semantics is the strong exception handling guarantee
 * we give for push_back(): When an exception is thrown in the middle of the reallocation of the vector the
 * C++ standard library guarantees to roll back the vector to its previous state. That is, push_back() gives a
 * kind of a transactional guarantee: either it succeeds or it has no effect.
 *
 * The C++ standard was able to give this guarantee in C++98 and C++03 because there C++ could only
 * copy the elements. If something goes wrong while copying the elements, the source objects are still
 * available. Internal code that handles the exception simply destroys the copies created so far
 * and release the new  memory to bring the vector back to its previous state (the C++ standard
 * library assumes and requires that destructors do not throw; otherwise, it would not be able to roll back)
 *
 * Reallocation is a perfect place for move semantics because we move elements from one location to the
 * other. Therefore, since C++11, we want to use move semantics here. However, then we are in trouble: if
 * an exception is thrown during the reallocation, we might not be able to roll back. The elements in the new
 * memory have already stolen the values of the elements in the old memory. Therefore, destroying the new
 * elements would not be enough; we have to move them back. But how do we know that moving them back
 * does not fail?
 *
 * You might argue that a move constructor should never throw. This might be correct for strings (because
 * we just move integral values and pointers around), but because we require that moved-from objects are in a
 * valid state, this state may need memory, which means that the move might throw if we are out of memory
 * (e.g., node-based containers of Visual C++ are implemented that way).
 *
 * We also cannot give up the guarantee because programs might have used this feature to avoid creating a
 * backup of a vector and losing that data could be (safety) critical. And no longer supporting push_back()
 * would be a nightmare for the acceptance of C++11.
 *
 * The final decision was to use move semantics on reallocation only when the move constructor of the
 * element types guarantees not to throw.
 *
 */

inline void test_person_without_noexcept()
{
    println( __PRETTY_FUNCTION__ );

    std::vector<Person> coll { "Wolfgang Admaeus Mozart",
        "Johan Sebastian Bach",
        "Ludwig van Beethoven" };

    println( "cap :", coll.capacity() );
    coll.push_back( "Pjotr Iljitsch Tschaikowski" );

    println( "cap :", coll.capacity() );
}
