#pragma once
#include "../../../util/print.h"

#include <iterator>
#include <string>
#include <vector>
#include <iostream>
#include <cassert>
#include <iostream>

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

    friend std::ostream & operator<<( std::ostream & os, Customer const & other );

    // copy constructor
    Customer( Customer const & cust )
        : name { cust.name }, values { cust.values }
    {
        println( "COPY ", name );
    }

    // move constructor
    Customer( Customer && cust ) noexcept // DO NOT MISS noexcept
        : name { std::move( cust.name ) }, values { std::move( cust.values ) }
    {
        println( "MOVE ", name );
    }

    // copy assignment
    Customer & operator=( Customer const & cust )
    {
        println( "COPYASSIGN ", cust.name );
        if ( this != &cust ) { // avoid copy assignment to myself
            name = cust.name;
            values = cust.values;
        }
        return *this;
    }

    // move assignment
    Customer & operator=( Customer && cust ) noexcept
    {
        println( "MOVEASSIGN ", cust.name );

        if ( this != &cust ) { // avoid move assignment to myself
            name = std::move( cust.name );
            values = std::move( cust.values );
        }
        return *this;
    }

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

class Base
{
    virtual ~Base()
    {
        // automatic move semantics is disabled
    }
};
