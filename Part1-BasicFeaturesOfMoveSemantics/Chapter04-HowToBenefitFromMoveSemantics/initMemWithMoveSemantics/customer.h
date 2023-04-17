#pragma once

#include <ostream>
#include <string>
#include <vector>
#include <iostream>

#include "../../../util/print.h"

/*
 * Should We Now Always Pass by Value and Move ?
 *
 *
 * Taking a parameter by value and moving it to where the new value is needed only useful when
 * we store the passed value somewhere as a new value(so that we need new memory for it anyway)
 * When modifying an existing value, this policy might be counterproductive.
 *
 */
class Customer
{
public:
    Customer( std::string n, std::vector<std::string> v )
        : name { std::move( n ) }, values { std::move( v ) }
    {
        println( __PRETTY_FUNCTION__ );
    }

    // modifying existing element may no benefit for( pass by value and moving it )
    void setName( std::string const & name )
    {
        this->name = name;
    }
    void setName( std::string && name )
    {
        this->name = std::move( name );
    }

    // better pass by value and move to create a new element
    void addvalue( std::string s ) // take by value
    {
        values.push_back( std::move( s ) ); // and move into the collection
    }

    friend std::ostream & operator<<( std::ostream & os, Customer const & cust );

private:
    std::string name;
    std::vector<std::string> values;
};

inline std::ostream & operator<<( std::ostream & os, Customer const & cust )
{
    os << "name :" << cust.name << "\n";
    for ( auto const & val : cust.values ) {
        os << val << ",";
    }
    return os << "\n";
}
