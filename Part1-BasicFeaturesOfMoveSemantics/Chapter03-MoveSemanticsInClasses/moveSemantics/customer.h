#pragma once

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

    /*~Customer()
    {
        // automatic move semantics is disabled
    }*/
    ~Customer() = default; // automatic move semantics is disabled
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

class Base
{
    virtual ~Base()
    {
        // automatic move semantics is disabled
    }
};
