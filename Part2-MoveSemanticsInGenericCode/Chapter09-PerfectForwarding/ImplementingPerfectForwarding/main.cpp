#include <utility>
#include <string>
/*
 * To avoid overloading functions for parameters with different value categories, C++ introduced a special
 * mechanism for perfect forwarding ,You need three things:
 * 1. Take the call parameter as a pure rvalue reference(declared with && but without const or volatile).
 * 2. The type of parameter has to be a template parameter of function.
 * 3.When forwarding the parameter to another function. use a helper function called std::forward<>(), which declared in <utility>
 */

#include "../../../util/print.h"
class X{};

void foo(X& ){
    println(__PRETTY_FUNCTION__);
}

void foo(X const&){
    println(__PRETTY_FUNCTION__);
}

void foo(X&&){
    println(__PRETTY_FUNCTION__);
}

void foo(X const&&){
    println(__PRETTY_FUNCTION__);
}
template<typename T>
void callFoo( T && arg ) // arg is universal/forwarding reference
{
    foo( std::forward<T>( arg ) );
}
// std::forward<>() is effectively a conditional std::move() so that we get the same behavior
// as three(or four) overloads of callFoo above
// .If we pass an rvalue to arg, we have the same effect as calling foo(std::move(arg))
// .If we pass an lvalue to arg, we have the same effect as calling foo(arg)

template<typename T1, typename T2>
void callFoo( T1 && arg1, T2 && arg2 )
{
    foo( std::forward<T1>( arg1 ), std::forward<T2>( arg2 ) );
}

// we can also apply std::forward<>() to each argument of a variadic number of parameters to perfectly forward them all.
template<typename... Ts>
void callFoo( Ts &&... args )
{
    foo( std::forward<Ts>( args )... );
}


/*
 * 9.2.1 Universal(or Forwarding) References
 * Two Terms: Universal and Forwarding Reference
 *
 * Both terms describe basic aspects of universal/forwarding references:
 *.They can universally bind to objects of all types(const and non-const) and value categories.
 *.They are usually used to forward arguments; but note that this is not the only use(one reason for me to prefer
 * the term universal references
 */

// Note that a generic rvalue reference that is qualified with const(or volatile) is not a universal reference.
// You can only rvalue:
template<typename T>
void callFoo2(T const && arg){ // arg is not a universal/forwarding reference
    foo(std::forward<T const>(arg));
}

/*
 * 9.2.2 std::forward<>()
 *
 * like std::move(), std::forward<>() is also defined as a function template in the header file <utility>
 *  the expression std::forward<T>(arg) is essentially implemented as follows:
 * .If an rvalue of type T is passed to the function, the expression is equivalent to std::move(arg).
 * .If an lvalue of type T is passed to the function, the expression is equivalent to arg
 *
 * that is ,std::forward<>() is a std::move() only for passed rvalue.
 *
 * Just like for std::move(), the  semantic meaning of std::forward<>() is I no longer need this value here, with
 * the additional benefit that we preserve the type(including constness) and the value category of the object
 * the passed universal reference binds to.
 *
 * all you should assume is that after using std::forward<>(), the object is usuall valide but you do not know its value.
 */

// std::forward<>() for Calling Member Functions

class Person
{
public:
    Person(std::string name):name{std::move(name)}{}

    void print()const{
        println("print(", name, ")");
    }

    std::string getName()&&{ // when we no longer need the value we steal and return by value
        return std::move(name);
    }
    const std::string getName() const&{// in all other cases we give acces to the member
        return name;
    }
private:
    std::string name;
};

template<typename T>
void foo(T&&x){
    x.print();// ok, no need to forward the passed value category

    x.getName();// call getName()const&
    std::forward<T>(x).getName();// calls getName()&& for rvalue(ok, no longer need x)
}

int main()
{
/*
 *  In addition, they preserve the constness and value category(whether we have rvalue or an lavalue) of the object
 *  they are bound to:
 */
    X v;
    const X c;
    callFoo(v); // foo(X&)
    callFoo(c);// foo(X const&)
    callFoo(X{});// foo(X&&)
    callFoo(std::move(v));// foo(X&&)
    callFoo(std::move(c));// foo(X const&&)
// By rule, they type T&&, which is the type of arg, is
// .An lvalue reference if we refer to an lvalue
// .An rvalue reference if we refer to an rvalue


    const X c1;
//    callFoo2(c1);// ERROR: c1 is not an rvalue
    callFoo2(std::move(c1)); // Ok, arg is const X&&

    Person peter{"peter"};
//    foo(std::move(peter));
    foo(peter);

    println(peter.getName());


    return 0;
}

/*
 * 9.2.3 The Effect of Perfect Forwarding
 * Whatever we pass to callFoo() becomes an lvalue(because the parameter arg is an object with a name). However,
 * the type of arg depends on what we pass:
 * .If we pass an lvalue, arg is an lvalue reference(X&, when we pass a non-const X, or const X&, when we pass
 * a const X).
 * .If we pass an rvalue(an unnamed temporary object or an object marked with std::move()), arg is an rvalue
 *  reference (X&& or const X&&)
 */
