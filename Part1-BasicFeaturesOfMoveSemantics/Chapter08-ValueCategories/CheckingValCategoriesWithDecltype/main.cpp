#include <string>
#include <type_traits>
#include <iomanip>

#include "../../../util/print.h"

/*
 * decltype, The primary goal of this keyword is to get the exact type of a declared object,
 * However , it can also be used to determine the value category of an expression
 */

void rvFunc( std::string && str )
{
    print( std::boolalpha );

    // 8.6.1 Using decltype to Check the Type of Names
    println( std::is_same<decltype( str ), std::string>::value );    // false
    println( std::is_same<decltype( str ), std::string &>::value );  // false
    println( std::is_same<decltype( str ), std::string &&>::value ); // true

    println( std::is_reference<decltype( str )>::value );        // true
    println( std::is_lvalue_reference<decltype( str )>::value ); // false
    println( std::is_rvalue_reference<decltype( str )>::value ); // true

    std::remove_reference<decltype( str )>::type tmp;
    println( std::is_same<decltype( tmp ), std::string>::value ); // true
    println( std::is_reference<decltype( tmp )>::value );         // false

    println( "=============================================================" );
    // 8.6.2 Using decltype to Check the Value Category
    // . For a prvalue it just yields its value type: type
    // . For an lvalue it yields its type as an lvalue reference: type&
    // . For an xvalue it yields its type as an rvalue reference: type&&

    decltype( str + str ) x;       // yeilds std::string because s+s is a prvalue
    decltype( str[0] ) y = str[0]; // yeilds char& because the index operator yields an lvalue

    println( std::is_same<decltype( ( str ) ), std::string>::value );    // false
    println( std::is_same<decltype( ( str ) ), std::string &>::value );  // true
    println( std::is_same<decltype( ( str ) ), std::string &&>::value ); // false

    println( std::is_reference<decltype( ( str ) )>::value );        // true
    println( std::is_lvalue_reference<decltype( ( str ) )>::value ); // true
    println( std::is_rvalue_reference<decltype( ( str ) )>::value ); // false
}

int main()
{
    rvFunc( "hello" );

    return 0;
}
