#pragma once

#include "../../../util/print.h"

#include <string>
#include <vector>
#include <iostream>

/*
 * Declared Copying Disables Moving (Fallback Enabled)
 */
namespace declare_copy_disable_move {

class Person
{
public:
    Person( std::string const & first, std::string const & family )
        : firstName { first }, familyName { family } {}
    // copy constructor/assignment declared
    Person( Person const & ) = default;
    Person & operator=( Person const & ) = default;
    // No move constructor/assignment declared
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
    coll.push_back( p );              // copis p
    coll.push_back( std::move( p ) ); //copis p

    println( "after move p:", p );
    print_con( coll );
}

} // namespace declare_copy_disable_move
