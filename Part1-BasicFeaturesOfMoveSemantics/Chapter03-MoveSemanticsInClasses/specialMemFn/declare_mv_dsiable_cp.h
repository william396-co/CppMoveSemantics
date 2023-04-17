#pragma once

#include "../../../util/print.h"

#include <string>
#include <vector>
#include <iostream>

/*
 *  Declared Moving Disables Copying
 */
namespace declare_move_disable_copy {

class Person
{
public:
    Person( std::string const & first, std::string const & family )
        : firstName { first }, familyName { family } {}
    // No copy constructor/assignment declared
    //  move constructor/assignment declared
    Person( Person && ) = default;
    Person & operator=( Person && ) = default;
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
    //coll.push_back( p );              // ERROR copis disabled
    coll.push_back( std::move( p ) ); // moves p

    coll.push_back( Person { "Ben", "Cook" } ); // move temporary person into coll

    println( "after move p:", std::move( p ) );

    for ( auto & p : coll ) {
        println( p );
    }
}

} // namespace declare_move_disable_copy
