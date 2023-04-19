#pragma once

#include <string>
#include <vector>

class Customer
{
public:
    Customer( std::string n )
        : name { std::move( n ) }
    {
    }

    void addValue( int val )
    {
        values.push_back( val );
    }

    void clear()
    {
        name = "";
        values.clear();
    }

private:
    std::string name;
    std::vector<int> values;
};

inline void process( Customer && c )
{
    c.clear();
}
inline void foo()
{
    Customer c { "Michael Spencer" };
    c.addValue( 100 );

    process( std::move( c ) );

    // both name and values have valid but unspecified states

} // destrcutor of c will clean up name and values (whatever their state is)
