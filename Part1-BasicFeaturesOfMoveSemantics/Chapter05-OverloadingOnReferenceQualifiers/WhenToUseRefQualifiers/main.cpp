#include "../../../util/print.h"

/*
 * Reference qualifiers allow us to implement functions differently when they are called for objects of a specific
 * value category. The goal is to provide a different implementation when we call a member function for an object
 * that no longer needs its value
 *
 * Although we do have this feature, it is not used as much as it could be, In particular, we could(and should)
 * use it to ensure that operations that modify objects are not called for temporary objects thata are about to die.
 */

#include <ios>
#include <optional>
#include <iomanip>

std::optional<int> getValue()
{
    return std::optional<int>( 43 );
}

std::string getString()
{
    return "hello";
}

void foo( std::string str )
{
    println( __PRETTY_FUNCTION__, " ", str );
}

void foo( bool b )
{
    println( __PRETTY_FUNCTION__, " ", std::boolalpha, b );
}

// In general, you should do this for every member function that might modfiy an object
class MyType
{
public:
    MyType( const char * type )
        : type_name { type } {}
    MyType( std::string type )
        : type_name { std::move( type ) } {}

    // disable assignment value to temporay objects
    MyType & operator=( MyType const & ) & = default;
    MyType & operator=( MyType && ) & = default;

    // Becuase this disables the copy/move constructor, also
    MyType( MyType const & ) = default;
    MyType( MyType && ) = default;

    const std::string & getType() const &
    {
        return type_name;
    }
    std::string getType() &&
    {
        return std::move( type_name );
    }

private:
    std::string type_name;
};

MyType getMyType()
{
    return MyType { "temporary type" };
}

void foo( MyType type )
{
    println( __PRETTY_FUNCTION__, " ", type.getType() );
}

int main()
{

    // Reference Qualifier for Assignment Operators(no use Reference Qualifier)
    {
        // warning: suggest parentheses around assignment used as truth value [-Wparentheses]
        if ( getValue() = 0 ) { // OOPS: compiles although = is used instead of ==
            println( "===ERROR" );
        }

        getString() = "world";   // OK
        foo( getString() = "" ); // passes string instead of bool
    }

    // Use Reference Qualifiers for Assignment Operators
    /* {
        if ( getMyType() = "" ) {
            println( "getMyType  Error" );
        }

        getMyType() = MyType { "bad" };
        // error: could not convert ‘getMyType()().MyType::operator=(MyType(((const char*)"")))’ from ‘MyType’ to ‘bool’
        foo( getMyType() = "" );
    }*/
    return 0;
}
