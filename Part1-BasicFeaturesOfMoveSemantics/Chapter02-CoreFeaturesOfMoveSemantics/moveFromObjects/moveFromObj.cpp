#include "../../../util/print.h"

#include <iostream>
#include <string>
#include <vector>

template<typename T>
void swap( T & a, T & b )
{
    T tmp { std::move( a ) };
    a = std::move( b );
    b = std::move( tmp );
}

void reusingMovedFromObjs()
{
    println( __PRETTY_FUNCTION__ );

    std::string a = "a";
    std::string b = "b";
    println( "before swap :", a, " ", b );

    swap( a, b );
    println( "after swap:", a, " ", b );

    // Move Assignments of Objects to Themselves
    std::string s = "hello";
    s = std::move( s );   // after x is valid but has an unclear value
    println( "s = ", s ); // s = ''

    std::vector<std::string> allRows;
    std::string row;
    while ( std::getline( std::cin, row ) ) {
        allRows.push_back( std::move( row ) );
    }

    print_con( allRows );
}

void foo( std::string && rv )
{
    println( __PRETTY_FUNCTION__, "(", rv, ")" );
    auto temp = std::move( rv );
}
void validbutUnspecifedState()
{
    println( __PRETTY_FUNCTION__ );
    std::vector<std::string> coll;

    std::string s { "goo" };
    coll.push_back( std::move( s ) );

    println( "after move" );

    // The C++ standard library guarantees that moved-from objects are in a valid but unspecified state
    println( "s = ", s, " size= ", s.size(), " s[0]=", s[0], " s.front()=", s.front() );

    s = "new value";
    println( "s = ", s );

    foo( std::move( s ) );

    for ( size_t i = 0; i < s.size(); ++i ) {
        print( s[i] );
    }
    println();
}

int main()
{

    validbutUnspecifedState();
    reusingMovedFromObjs();

    return 0;
}
