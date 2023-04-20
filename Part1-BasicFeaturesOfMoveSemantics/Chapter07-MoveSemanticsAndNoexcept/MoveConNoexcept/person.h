#pragma once

#include "../../../util/print.h"
#include <string>
#include <vector>

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
    Person( Person && p ) noexcept
        : name { std::move( p.name ) }
    {
        println( "MOVE ", name );
    }

private:
    std::string name;
};

inline void test_person_without_noexcept()
{
    println( __PRETTY_FUNCTION__ );

    std::vector<Person> coll{"Wolfgang Admaeus Mozart",
        "Johan Sebastian Bach", "Ludwig van Beethoven"};

    println("cap :",coll.capacity());
    coll.push_back("Pjotr Iljitsch Tschaikowski");

}
