#pragma once

#include "../../../util/print.h"

#include <string>
#include <vector>
#include <iostream>

/*
 *   Deleting Moving Makes No Sense
 */

/*
 * if you declare the move constructor as deleted, you cannot move(you have disabled this operations, any fallback is not used)
 * and cannot copy(because a declared move constructor disables copy operations)
 */
namespace delete_move_make_no_sense {

class Person
{
public:
    Person( std::string const & first, std::string const & family )
        : firstName { first }, familyName { family } {}
    //  copy constructor/assignment declared explicitly declared
    Person( Person const & ) = default;
    Person & operator=( Person const & ) = default;
    //   move constructor/assignment declared as deleted
    Person( Person && ) = delete;
    Person & operator=( Person && ) = delete;
    // No destructor declared

    friend std::ostream & operator<<( std::ostream & os, Person const & p );

private:
    std::string firstName, familyName;
};
inline std::ostream & operator<<( std::ostream & os, Person const & p )
{
    return os << p.familyName << " " << p.firstName;
}

inline void execute()
{
    println( __PRETTY_FUNCTION__ );

    std::vector<Person> coll;
    Person p { "Tina", "Fox" };
    //    coll.push_back( p );              // ERROR copis disabled
    coll.push_back( p ); // Ok, copying enabled
                         // coll.push_back( std::move( p ) ); // ERROR  moving disabled

    println( p );
}

} // namespace delete_move_make_no_sense
