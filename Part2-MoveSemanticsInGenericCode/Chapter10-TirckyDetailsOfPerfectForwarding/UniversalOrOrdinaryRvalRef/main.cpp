
#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include "../../../util/print.h"

/*
 * 10.2.1 Rvalue References of Members of Generic Types
 *
 * An rvalue reference to a member type of a template parameter is not a universal reference.
 */

template<typename T>
void insert( T & coll, typename T::value_type && arg ) // arg is not universal reference
{
    coll.push_back( arg );
}

/*
 * 10.2.2 Rvalue References of Parameters in Class Templates
 *
 * An rvalue reference to a template of a class template is not a universal reference
 */

template<typename T>
class Coll
{
public:
    Coll() = default;

    void insert( T && val )// val is not a universal reference
    {
        values.push_back( val );
    }

    std::vector<T> getValues() &&
    {
        return std::move( values );
    }
    const std::vector<T> getValues() const &
    {
        return values;
    }

private:
    std::vector<T> values;
};

/*
 * 10.2.3 Rvalue References of Parameter in Full Specialization
 *
 * An rvalue reference to a parameter of a full specialization of a function template is not a universal reference.
 */
namespace sample_10_2_3 {

// primary template taking a universal reference
template<typename Coll, typename T>
void insert( Coll & coll, T && arg )
{
    println( "primary template for type T called" );
    coll.push_back( arg );
}

// full specialization for rvalues of type std::string
template<>
void insert( std::vector<std::string> & coll, std::string && arg )
{
    println( "full specialization for type std::string&& called" );
    coll.push_back( arg );
}

// full specialization for lvalues of type std::string const&
template<>
void insert(std::vector<std::string>& coll, std::string const& arg){
    println("full specialization for type std::string const& called");
    coll.push_back(arg);
}

} // namespace sample_10_2_3

template<typename T>
class Cont
{
public:
    template<typename U>
    void insert( U && v )
    { // universal reference
        coll.push_back( std::forward<U>( v ) );
    }

private:
    std::vector<T> coll;
};

// full specialization for Cont<T>::insert<>();
// - have to be outside the clas
// - need specialization for rvalue and lvalue

template<>
template<>
void Cont<std::string>::insert( std::string && v )
{
    // rvalue reference not pass through
    coll.push_back( std::move( v ) );
}

template<>
template<>
void Cont<std::string>::insert( std::string const & v )
{
    coll.push_back( v );
}

int main()
{
    {
        println( "===========================" );

        std::vector<std::string> coll;
        insert( coll, std::string { "prvalue" } ); // OK

        std::string str { "lvalue" };
        //        insert(coll,str); // ERROR T::value_type is not an universal reference
        insert( coll, std::move( str ) ); // OK
        print_con( coll );
    }

    {
        println( "===========================" );

        Coll<std::string> coll;
        coll.insert( std::string { "prvalue" } );
        std::string str { "lvalue" };
        //        coll.insert(str);//ERROR
        coll.insert( std::move( str ) );

        print_con( coll.getValues() );
    }

    {
        println( "===========================" );

        std::vector<std::string> coll;
        sample_10_2_3::insert( coll, std::string { "prvalue" } ); // call full specialization for rvalue

        std::string str { "lvalue" };
        sample_10_2_3::insert( coll, str );              // call full specialization for lvalue
        sample_10_2_3::insert( coll, std::move( str ) ); // call full specialization for rvalue

        print_con( coll );
    }

    {
        println( "===========================" );
        Cont<std::string> coll;
        coll.insert( std::string { "prvalue" } );
        std::string str { "lvalue" };
        coll.insert( str );
        coll.insert( std::move( str ) );

        println( " str = ", str );
    }

    return 0;
}
