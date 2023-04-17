#pragma once

#include "../../../util/print.h"

#include <vector>
#include <string>
#include <iostream>
#include <cassert>

namespace disable_move_enable_copy {

class Customer
{
public:
    Customer( std::string const & name )
        : name { name }
    {
        assert( !name.empty() );
    }
    std::string getName() const { return name; }

    void addVal( int val )
    {
        values.emplace_back( val );
    }

public:
    Customer( Customer const & ) = default;             // disable move semantics
    Customer & operator=( Customer const & ) = default; // disbale move semantics

    friend std::ostream & operator<<( std::ostream & os, Customer const & other );

private:
    std::string name;
    std::vector<int> values;
};
inline std::ostream & operator<<( std::ostream & os, Customer const & other )
{
    os << "[" << other.name << " :";
    for ( auto const & val : other.values ) {
        os << val << ' ';
    }
    return os << "]";
}

inline Customer createCustomer()
{
    return Customer { "createCustomer" };
}

inline void execute()
{
    println( __PRETTY_FUNCTION__ );

    std::vector<Customer> customers;

    customers.push_back( createCustomer() );          // fallback to copying
    customers.push_back( std::move( customers[0] ) ); // fallback to copying

    print_con( customers );
}

} // namespace disable_move_enable_copy
