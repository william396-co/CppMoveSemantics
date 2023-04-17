#include "../../../util/print.h"

#include <ostream>
#include <string>
#include <vector>
#include <iostream>

class MyType
{
public:
    MyType( int32_t id, std::string const & str )
        : id { id }, str { str } {}

    friend std::ostream & operator<<( std::ostream & os, MyType const & other );

private:
    int id;
    std::string str;
};
std::ostream & operator<<( std::ostream & os, MyType const & other )
{
    return os << "[ " << other.id << " , " << other.str << " ]";
}

void foo( MyType const & mytype )
{
    println( __PRETTY_FUNCTION__, "(", mytype, ")" );
}

void foo( MyType && mytype )
{
    println( __PRETTY_FUNCTION__, "(", mytype, ")" );
}

int main()
{

    // Avoid Objets with Names
    // .We pass a temporary object that will automatically be destroyed after the statements.
    // .We return a local object by value
    {
        MyType x { 42, "hello" };
        foo( x ); // x not used afterwards
        foo( MyType { 42, "hello" } );
        foo( std::move( x ) );
    }

    // When You cannot Avoid using Names
    {
        std::string str { "good" };
        std::vector<std::string> coll;

        coll.push_back( str );              // copy(still need the value of str)
        coll.push_back( std::move( str ) ); // move(no longer need the value of str)
    }
    {
        std::string line;
        std::vector<std::string> coll;
        while ( std::getline( std::cin, line ) ) {
            coll.push_back( std::move( line ) ); // move(no longer need the value of line)
        }

        print_con( coll );
    }

    return 0;
}
