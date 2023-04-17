#include "../../../util/print.h"
#include "../../../util/perf_timer.h"

//#include "initclassic.h"
//#include "initmove.h"
#include "initall.h"
#include "customer.h"

#include <chrono>
#include <ratio>

void measure( int num )
{

    for ( int i = 0; i < num; ++i ) {

        std::string fname { "a firstnmae a bit too long for SSO" };
        std::string lname { "a lastname a bit too long for SSO" };

        Person p1 { "a firstname too long for SSO", "a lastname too long for SSO" };
        Person p2 { fname, lname };
        Person p3 { std::move( fname ), std::move( lname ) };
    }
}

/*
 * As a summary , to initialize members for which move semantics make a significant difference( strings,
 * container, or classes/arrays with such members), you should use move semantics on of the following alternatives:
 * 1. swith from taking the parameter by lvalue reference to taking it by value and move it into the member
 * 2. Overload the constructor for move semantics
 */
int main()
{

    Person p { "Ben", "Cook" }; // string&&

    std::string name1 { "Jane" }, name2 { "White" };
    Person p2 { name1, name2 }; // string const&

    Person p3 { std::move( name1 ), std::move( name2 ) };

    {
        int num = 100;
        utils::perf_timer_out<>( "all measure ", measure, num );
    }

    Customer c { "hello", { "good" } };

    c.addvalue( "baiddu" );
    c.addvalue( " how are you " );
    println( c );

    c.setName( " morning" );
    println( c );
    return 0;
}
