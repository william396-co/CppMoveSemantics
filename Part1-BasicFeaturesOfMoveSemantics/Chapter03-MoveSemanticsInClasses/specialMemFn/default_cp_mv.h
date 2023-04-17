#pragma once

#include "../../../util/print.h"

#include <string>
#include <vector>
#include <iostream>

/*
 *  By Default, We Have Copying and Moving
 */
namespace default_copy_move {

class Person
{
public:
    Person( std::string const & first, std::string const & family )
        : firstName { first }, familyName { family } {}
    // No copy constructor/assignment declared
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
    coll.push_back( p );
    coll.push_back( std::move( p ) );

    println( "after move p:", p );
    print_con( coll );
}

} // namespace default_copy_move
