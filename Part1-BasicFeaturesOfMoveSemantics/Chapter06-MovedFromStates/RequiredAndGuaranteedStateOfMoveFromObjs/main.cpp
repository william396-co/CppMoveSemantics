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
 * 6.1.3 Broken Invariants(破坏不变量)
 *
 * The C++ standard library defines what all moved-from objects being in a "valid but unspecified state " means as follow:
 *
 * The value of an object is not specified except that the object's invariants are met and operations on the object
 * behave as specified for its type
 *
 * Invariant are the guarantees that apply to all of the objcets that can be created, With this guarantee, you can assume that
 * a moved-from object is in a state that means that its invariants are not broken. You can use the object like a non-const
 * reference parameter without knowing anything about the arguments passed:
 *
 */

/*
 * Restricted Invariants(受限不变量)
 * Ideally, a moved-form state that does not support all operations should be detectable. The object should know this state
 * and provide a member function to check for this state. Moved-from objects might also refuse to execute operations not supported
 * in this state, However , corresponding checks might const performnce in the general case.
 *
 * In the C++ standard library, some types provide APIs to check whether objects are in a moved-from state.
 * For example, std::future have a memeber function valid() that returns flase for moved-form objects. But the interfaces
 * to check for moved-from states vary(不同)
 *
 * Pretty often the moved-from state is the default constructed state. which means that the moved-from state is parts
 * of the invariants anyway.In any case, make sure users fo your types know about whati si well-defined and what is not.
 */
int main()
{
    requied_states_of_moved_from_objects();
    guaranteed_states_of_moved_from_objs();

    return 0;
}
