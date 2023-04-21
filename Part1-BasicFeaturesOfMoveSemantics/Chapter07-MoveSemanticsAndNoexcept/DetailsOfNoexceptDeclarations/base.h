#include "../../../util/print.h"

#include <string>

/*
 * 7.2.1 Rules for Declaring Functions with noexcept
 *
 * A couple of rules apply when declaring noexcept conditions:
 * . The noexcept condition must  be a compile-time expression that yields a value convertible to bool.
 * . You cannot overload functions that have only different noexcept conditions.
 * . In class hierarchies, a noexcept condtion is part of sepcified interface. Overwriting a base class
 *   function that is noexcept with a function that is not noexcept is an error(but not the other way around)
 */

class Base
{

public:
    virtual void foo( int ) noexcept
    {
        println( __PRETTY_FUNCTION__ );
    }
    //    virtual void foo( int ){} // ERROR: overload on different noexcept clause only
    virtual void bar( int )
    {
        println( __PRETTY_FUNCTION__ );
    }

    void say( std::string const & msg ) noexcept
    {
        println( __PRETTY_FUNCTION__, " :", msg );
    }

    virtual void func() noexcept( sizeof( int ) < 8 ) // might throw is sizeof(int)>=8
    {
        println( __PRETTY_FUNCTION__ );
    }
};

// However, for non-virtual functions, derived-class member can hide-base-class member with a different noexcept declaration
class Derived : public Base
{
    virtual void foo( int ) noexcept override
    {
        Base::foo( 1 );
        println( __PRETTY_FUNCTION__ );
    }
    virtual void bar( int ) noexcept // Ok(here we also guarantee not to throw)
    {
        println( __PRETTY_FUNCTION__ );
    }
    void say( std::string const & msg ) // OK, hidding instead of overriding
    {
        println( __PRETTY_FUNCTION__, " :", msg );
    }
    void func() noexcept( sizeof( int ) < 5 ) override //might throw if sizeof(int) >=5
    {
        println( __PRETTY_FUNCTION__ );
    }
};

inline void test_base_derived()
{
    println( __PRETTY_FUNCTION__ );

    Base * pb = new Derived;
    pb->foo( 1 );
    pb->bar( 1 );
    pb->say( "hello" );
    pb->func();
}
