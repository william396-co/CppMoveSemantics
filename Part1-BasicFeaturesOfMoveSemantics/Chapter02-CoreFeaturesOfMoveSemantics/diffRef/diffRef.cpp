#include "../../../util/print.h"
#include <string>

// const lvalue reference
// You can pass everything to a function declare that way if the type fits:
// A modifiable name object
// A const named object
// A temporary object that does not have a name
// An object marked with std::move
void fooByCRef( std::string const & arg )
{
    println( __PRETTY_FUNCTION__, "(", arg, ")" );
}

// non-const lvalue referencei
// You can only pass:
// A modifiable named object
void fooByRef( std::string & arg )
{
    println( __PRETTY_FUNCTION__, "(", arg, ")" );
}

// non-const rvalue reference
// you can only pass:
// A temporary object that doest not have a name
// An non-const object  marked with std::move
void fooByRRef( std::string && arg )
{
    println( __PRETTY_FUNCTION__, "(", arg, ")" );
    auto temp = std::move( arg );
}

std::string getTemporaryObj()
{
    return "temporary string";
}

// const rvalue reference
// the restrictions would be that you can only pass:
// A temporary object that doest not have a name
// A const or non-const object marked with std::move
void fooByCRRef( std::string const && arg )
{
    // However, there is no useful semantic meaning of this case, As an rvalue reference, stealing
    // the value is allowed, but being const, we disable any modification of the pass argument,
    // this is a contradiction in itself(这本身就是矛盾的)
    println( __PRETTY_FUNCTION__, "(", arg, ")" );

    auto temp = std::move( arg );
}

// Tips std::optional<> uses const rvalue reference
int main()
{

    std::string s = "non-const string";
    const std::string cs = "const string";
    fooByCRef( s );
    fooByCRef( cs );
    fooByCRef( getTemporaryObj() );
    fooByCRef( std::move( s ) );
    fooByCRef( std::move( cs ) );

    println( "=================" );
    fooByRef( s ); // only modifiable named object
    /* fooByRef( cs );
     * fooByRef( getTemporaryObj() );
     * fooByRef( std::move( s ) );
     * fooByRef( std::move( cs ) );
    */

    println( "================" );
    /*  fooByRRef( s );
     *  fooByFRef( cs );
     */
    fooByRRef( getTemporaryObj() ); // a temporary object that does not have a name
    fooByRRef( std::move( s ) );    //an non-const object markeds with std::move()
    /* fooByRRef( std::move( cs ) );*/

    println( "======================" );
    std::string s1 = "non-const string";
    /* fooByCRRef( s );
    fooByCRRef( cs );*/
    fooByCRRef( getTemporaryObj() );
    fooByCRRef( std::move( s1 ) );
    fooByCRRef( std::move( cs ) );

    println( cs );
    println( s1 ); // non-const string (can not stealing)

    return 0;
}
