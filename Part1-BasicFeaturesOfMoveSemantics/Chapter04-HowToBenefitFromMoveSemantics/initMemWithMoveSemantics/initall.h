#pragma once
#include "../../../util/print.h"

#include <string>

// A surprising consequence is that you can benefit from move semantics even in trivial classes with members
// of types that benefit from move semantics(such as string members or containers)
class Person
{
public:
    Person( std::string const & f, std::string const & l )
        : first { f }, last { l }
    {
        //   println( __PRETTY_FUNCTION__, "(", first, ",", last, ")" );
    }

    Person( std::string const & f, std::string && l )
        : first { f }, last { std::move( l ) }
    {
        // println( __PRETTY_FUNCTION__, "(", first, ",", last, ")" );
    }

    Person( std::string && f, std::string const & l )
        : first { std::move( f ) }, last { l }
    {
        //        println( __PRETTY_FUNCTION__, "(", first, ",", last, ")" );
    }

    Person( std::string && f, std::string && l )
        : first { std::move( f ) }, last { std::move( l ) }
    {
        //      println( __PRETTY_FUNCTION__, "(", first, ",", last, ")" );
    }

    /////////////////////////////////////////////////////////////

    Person( const char * f, const char * l )
        : first { f }, last { l }
    {
        //    println( __PRETTY_FUNCTION__, "(", first, ",", last, ")" );
    }

    Person( const char * f, std::string const & l )
        : first { f }, last { l }
    {
        //  println( __PRETTY_FUNCTION__, "(", first, ",", last, ")" );
    }

    Person( const char * f, std::string && l )
        : first { f }, last { std::move( l ) }
    {
        //println( __PRETTY_FUNCTION__, "(", first, ",", last, ")" );
    }

    Person( std::string & f, const char * l )
        : first { f }, last { l }
    {
        //        println( __PRETTY_FUNCTION__, "(", first, ",", last, ")" );
    }

    Person( std::string && f, const char * l )
        : first { std::move( f ) }, last { l }
    {
        //      println( __PRETTY_FUNCTION__, "(", first, ",", last, ")" );
    }

private:
    std::string first;
    std::string last;
};
