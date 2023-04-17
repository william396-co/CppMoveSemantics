#pragma once

#include "../../../util/print.h"

#include <ostream>
#include <vector>
#include <string>
#include <iostream>
#include <cassert>

namespace moving_for_member_with_disable_move_semantics {

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
    Customer( Customer const & ) = default;             // copying calls enabled
    Customer & operator=( Customer const & ) = default; // copying calss enabled

    Customer( Customer && ) = delete;
    Customer & operator=( Customer && ) = delete;

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

class Invoice
{
public:
    Invoice()
        : id { "0001" }, cust { "Invoice" }
    {
    }

    friend std::ostream & operator<<( std::ostream & os, Invoice const & other );

private:
    std::string id;
    Customer cust;
};

inline std::ostream & operator<<( std::ostream & os, Invoice const & other )
{
    return os << "id:" << other.id << " cust: " << other.cust;
}

inline void execute()
{
    println( __PRETTY_FUNCTION__ );

    Invoice i;
    Invoice i1 { std::move( i ) }; // ok, moves is id, copies cust

    println( i );
    println( i1 );
}

} // namespace moveing_for_member_with_disable_move_semantics
