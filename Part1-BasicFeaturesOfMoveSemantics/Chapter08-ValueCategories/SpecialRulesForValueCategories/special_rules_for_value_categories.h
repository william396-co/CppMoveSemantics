#pragma once

#include "../../../util/print.h"

#include <vector>
#include <string>
#include <map>
/*
 * 8.2.1 Value Category of Functions
 * All expressions that are references to functions are lvalues.
 */
inline void f( int i )
{
    println( __PRETTY_FUNCTION__, "(", i, ")" );
}

inline void value_category_of_func()
{
    println( __PRETTY_FUNCTION__ );

    void ( &fref1 )( int ) = f; //fref1 is an lvalue
    void( &&fref2 )( int ) = f; // fref2 is also an lvalue

    //    auto& ar = std::move(f); //OK, ar is lvalue of type void(&)(int)

    fref1( 1 );
    fref2( 2 );
    //   ar(3);
}

/*
 * 8.2.2 Value Category of Data Members
 * In general, the value categories of data members are as follows:
 * . Data members of lvalues are lvalues.
 * . Reference and static data members of rvalue are lvalues.
 * . Plain data members of rvalues are xvalue.
 */

static std::string g_second = "foo_second";

inline std::pair<std::string, std::string &> foo()
{
    return { "foo_first", g_second };
}

struct S
{
    S( std::string & s )
        : refString { s } {}
    static std::string statString;
    std::string & refString;
};

//S::statString{"S static str"};

inline void data_member_value_categories()
{
    println( __PRETTY_FUNCTION__ );

    std::vector<std::string> coll;

    coll.push_back( foo().first );  // moves because first is an xvalue here
    coll.push_back( foo().second ); // copies becuase second is an lvalue here

    //you need std::move() to move the member second here:
    //.std::move(obj).member
    //.std::move(obj.member)
    coll.push_back( std::move( foo().second ) ); // moves

    print_con( coll );
    println( "g_second = ", g_second );

    /*
     * std::move() for Plain Data Members
     */

    std::pair<std::string, std::string> sp;
    sp.first = "how are you doing";
    sp.second = "good";

    coll.push_back( std::move( sp ).first );  // move string first into coll
    coll.push_back( std::move( sp ).second ); // move string second into coll

    println( sp.first, " ", sp.second );

    sp.first = "how are you doing";
    sp.second = "good";

    coll.push_back( std::move( sp.first ) );  // move string first into coll
    coll.push_back( std::move( sp.second ) ); // move string second into coll

    println( sp.first, " ", sp.second );

    /*
     * std::move() for Reference or static Memebers
     */
    std::string local_var = "local var";
    S obj { local_var };

    coll.push_back( std::move( obj ).statString ); // copies statString
    coll.push_back( std::move( obj ).refString );  // copies refString

    print_con( coll );
    println( "S statString = ", S::statString );
    println( "obj.refString = ", obj.refString );

    coll.push_back( std::move( obj.statString ) ); // moves statString
    coll.push_back( std::move( obj.refString ) );  // moves refString

    print_con( coll );
    println( "S statString = ", S::statString );
    println( "obj.refString = ", obj.refString );

    /*
     * In generic code, you might not know whether members are static or references, Therefore, using the approach
     * to mark the object with std::move() is less dangerous
     *
     * coll.push_back(std::move(obj).mem1); // move values, copy reference/static
     * coll.push_back(std::move(obj).mem2); // move values, copy reference/static
     */
}
