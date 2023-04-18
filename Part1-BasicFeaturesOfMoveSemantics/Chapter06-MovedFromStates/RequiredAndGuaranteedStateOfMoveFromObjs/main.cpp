#include "../../../util/print.h"

/*
 * we clarify the definition of an "invalid" state according to the guarantee of the C++
 * standard library that moved-from object are a valid but unspecified state
 */

#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <stack>
#include <cassert>

class Obj
{
public:
    Obj( std::string name )
        : name { std::move( name ) }
    {
    }
    void clear()
    {
        println( __PRETTY_FUNCTION__ );
        name = "";
    }
    const std::string & getName() const &
    {
        return name;
    }
    std::string getName() &&
    {
        return std::move( name );
    }

private:
    std::string name;
};

void draw( std::unique_ptr<int> up )
{
    println( __PRETTY_FUNCTION__, " ", *up );
}

void foo( Obj && obj )
{
    println( __PRETTY_FUNCTION__, " ", obj.getName() );
}

void foo( std::stack<int> && stk )
{
    println( __PRETTY_FUNCTION__, "  stk size: ", stk.size() );
    while ( !stk.empty() ) {
        println( " pop ", stk.top() );
        stk.pop();
    }
}

/*
 *
 *  6.1.1 Required States of Moved-From objects
 *
 * So, for moved-from objects we have the same basic requirements that usually apply to all objects:
    . We have to able to destroy moved-form objects
    . We have to be able to assign a new value to moved-from objects
    . We should be able to copy, move, or assign a moved-from objects to another object.

    For all objects and types you use in the C++ standard library you should ensure that moved-from objects
    also support all requirements of the funcitons called
*/

void requied_states_of_moved_from_objects()
{
    println( __PRETTY_FUNCTION__ );
    std::string a = "hello";
    std::string b = "world";

    std::string tmp = std::move( a );
    a = std::move( b );
    b = std::move( tmp );

    println( "a = [", a, "] b = [", b, "] tmp=[", tmp, "]" );
}

/*
 *  6.1.2 Guaranteed State of Moved-From objects
 *
 *  Becuase we always destroy an object at the end of its lifetime. The minimum guarantee you always have to give for
 *  moved-form states is taht calling the destructor is well-defined.
 *
 *  Usually, more guarantees are given, For the requirements of the C++ standard library, supporting basic operations
 *  such as copying, assigning objects of the same type are often enough.
 *
 */

void guaranteed_states_of_moved_from_objs()
{
    println( __PRETTY_FUNCTION__ );
    std::string s = "hello"; // assign "hello";
    std::string s2 = "good";
    s.assign( s2 ); // assign the state of s2
    s.clear();      // assign the empty state
                    /*   std::cin >> s;               // assign the next word from std::cin
    std::getline( std::cin, s ); // assign the next line from std::cin

    std::string row;
    std::vector<std::string> coll;
    while ( std::getline( std::cin, row ) ) { //
        coll.push_back( std::move( row ) );   // move the line into the vector
    }*/

    Obj obj { "Obj" };
    foo( std::move( obj ) ); // pass obj to foo
    obj.clear();             // ensure the object is mepty afterwards

    std::unique_ptr<int> up = std::make_unique<int>( 42 );
    draw( std::move( up ) ); // the unique pointer might or might not give up ownership
    up.reset();              // ensure we give up ownership and release any resource

    std::stack<int> stk;
    stk.push( 100 );
    foo( std::move( stk ) );
    stk.push( 42 );

    int i = stk.top();
    assert( i == 42 ); // should neve fail
}

/*
 * 6.1.3 Broken Invariants
 *
 */
int main()
{
    requied_states_of_moved_from_objects();
    guaranteed_states_of_moved_from_objs();

    return 0;
}
