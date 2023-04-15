#include "customer.h"

#include <string>
#include <vector>
#include <algorithm>

// move semantic is not passed through, when we initialize the members with the
void insertTwice( std::vector<std::string> & coll, std::string && str )
{
    coll.push_back( str );              //copy str into coll
    coll.push_back( std::move( str ) ); // move str into coll
}

int main()
{

    // move semantics is not pass through
    {
        std::vector<std::string> coll;
        std::string str { "jely" };
        insertTwice( coll, std::move( str ) );
        println( str );
        print_con( coll );
    }

    Customer c { "GNU's Not Unix" };
    c = std::move( c ); // move assigns c to itself
    println( c );

    println( "======================================" );
    std::vector<Customer> coll;
    for ( int i = 0; i != 12; ++i ) {
        coll.push_back( Customer { "TestCustomer " + std::to_string( i - 5 ) } );
    }

    println( "============================================" );
    std::sort( coll.begin(), coll.end(), []( auto const & c1, auto const & c2 ) {
        return c1.getName() < c2.getName();
    } );

    println( "===========================================" );
    print_con( coll );
    return 0;
}
