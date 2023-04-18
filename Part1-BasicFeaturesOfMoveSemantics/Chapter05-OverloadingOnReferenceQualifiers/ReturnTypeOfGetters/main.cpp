#include "../../../util/print.h"

#include "person.h"

#include <vector>

Person returnPersonByVal()
{
    return Person { "jackMa" };
}

int main()
{

    std::vector<Person> coll;
    coll.emplace_back( "jack" );
    coll.emplace_back( "" );
    coll.emplace_back( "jeo" );

    for ( auto const & person : coll ) {
        if ( person.getName().empty() ) { //OOPS: copies the name
            println( "found empty name" );
        }
    }

    for ( char c : returnPersonByVal().getName() ) { // OOPS: underfined behavior
        if ( ' ' == c ) {
            println( c );
        }
    }

    println( "============================================================" );

    Person p { "Ben" };
    std::cout << p.getName() << std::endl;    // fast(return reference)
    println( returnPersonByVal().getName() ); // fast(use move() )

    auto str = p.getName();
    println( "p name : ", str );

    std::vector<Person> people;
    people.emplace_back( "" );
    people.emplace_back( "tony" );
    for ( auto const & p : people ) { // fast(return reference)
        if ( p.getName().empty() ) {
            println( "found empty name" );
        }
    }

    for ( char c : returnPersonByVal().getName() ) { // safe and fast(string&& use move())
        if ( c == ' ' ) {
            println( " empty=====" );
        }
    }

    Person atony { "atony" };
    people.push_back( atony.getName() );              // call getName()const&
    people.push_back( std::move( atony ).getName() ); // call getName()&& (ok, atony no longer used)
    print_con( people );

    return 0;
}
