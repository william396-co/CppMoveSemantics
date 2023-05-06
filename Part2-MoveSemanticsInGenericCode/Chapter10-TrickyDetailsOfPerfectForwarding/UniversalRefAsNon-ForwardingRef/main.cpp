
#include <ios>
#include <string>
#include <type_traits>
#include <iomanip>
#include "../../../util/print.h"

/*
 * 10.1.1 Universal References and const
 */

void iterate( std::string::iterator beg, std::string::iterator end )
{
    println( "do som non-const stuff with the passed range" );
}
void iterate( std::string::const_iterator beg, std::string::const_iterator end )
{
    println( "do some const stuff with the passed range" );
}

template<typename T>
void process( T && coll )
{
    // Note that, we do not use (perfect) forwarding ,
    // we just want to refere universally to both const and non-const objects
    iterate( coll.begin(), coll.end() );
}

/*
 * 10.1.2 Universal References in Details
 */

/*
 * When we declare arg we have a reference that can bind universally to all types and value categories.
 * For a non-const object v and a const object c the Type T and the type of arg is deduced as follows:
--------------------------------------------
             |  T          |  arg
============================================
foo(v)       | Type&       |  Type&
foo(c)       | const Type& | const Type&
foo(Type{})  | Type        | Type&&
foo(move(v)) | Type        | Type&&
foo(move(c)) | const Type  | const Type&&
--------------------------------------------
That means that the information about the passed argument is split as follows:
. arg still knows the value and its type including whether or not it is const, It is an lvalue reference if an
 lvalue was passed and an rvalue reference if an rvalue was passed, does also know whether an lvalue or
 an rvalue was passed.

. T knows the type and has some information about the value category of the passed argument(whether an
  lvalue or rvalue was passed). According to a specific template type deducation rule, if an lvalue was
  passed, T is an lvalue reference; otherwise ,T is not a reference.
*/

// Constness Dependent Code
// If you only have to know whether the passed argument was const, you can use both arg and T,
template<typename T>
void foo( T && arg )
{
    /*
     * Note that it is important to use std::remove_reference_t<> to remove the reference of T before
     * we check for its constness, A reference to a const type is not considered to be const as a whole:
     */
    if constexpr ( std::is_const_v<std::remove_reference_t<T>> ) {
        println( "passed argument is const" );
    } else {
        println( "pass argument is not const" );
    }
}

/*
 * 10.1.3 Universal Reference of Specific Types
 */

#if __cplusplus > 201703L
template<typename T>
requires std::is_same_v<std::remove_cvref_t<T>,std::string>
void processString(T&& arg){
}
#else
template<typename T,
    typename = typename std::enable_if<std::is_same_v<typename std::decay<T>::type, std::string>>::type>
void processString( T && arg )
{
    println(__PRETTY_FUNCTION__);
}

#endif

int main()
{
    std::string v { "v" };
    const std::string c { "c" };

    process( v );
    process( c );
    process( std::string { "t" } );
    process( std::move( v ) );
    process( std::move( c ) );

    println( "==============================" );
    foo( v );                  // non-const
    foo( c );                  // const
    foo( std::string { "" } ); //non-const
    foo( std::move( v ) );     // non-const
    foo( std::move( c ) );     // const

    println( "==============================" );
    print( std::boolalpha );
    println( "[int] is const = ", std::is_const_v<int> );                                       // false
    println( "[const int] is const = ", std::is_const_v<const int> );                           // true
    println( "[const int&] is const = ", std::is_const_v<const int &> );                        // false
    println( "[const int&] is const = ", std::is_const_v<std::remove_reference_t<const int &>> ); // true

    println("=================================");
    processString(v);
    processString(c);
    processString(std::string{""});
    processString(std::move(v));
    processString(std::move(c));
    return 0;
}
