#include "../../../util/print.h"

#include "customer.h"

#include <vector>

Customer createCustomer()
{
    Customer c { "createCustomer" };
    return c; // uses move semantics if not optimized away
}

/*
 * Use move semantics when initializing members
 * Use move semantics to make getter both safe and fast
 */

/*
 * When is Move semantics Autmatically Enabled in Classes?
 *
 *  the automatic generation of move operations is disabled when at least one of the following special
 *  member functions is user-declared:
 *
 *  Copy constructor
 *  Copy assignment operator
 *  Another move operation
 *  Destructor
 */

int main()
{
    Customer c { "Wolfgang Amadeus Mozart" };
    for ( int v : { 0, 8, 15 } ) {
        c.addVal( v );
    }

    println( "c :", c );

    std::vector<Customer> customers;
    customers.push_back( c );              //copy into the vector
    customers.push_back( std::move( c ) ); // move into the vector
    println( " after move c:", c );

    println( "customers:" );
    for ( auto const & c : customers ) {
        println( c );
    }

    customers.push_back( createCustomer() ); // use move semantics

    //  A move constructor that moves the members if we create a new object from a source we no longer need the value

    {
        Customer c1 { "hello" };
        Customer c2 { std::move( c1 ) };
    }

    // A move assignment operator that move assigns the members if we assign the value from a source where we no longer need value
    {
        Customer c1 { "hello" }, c2 { "world" };
        c2 = std::move( c1 );
    }
    return 0;
}
