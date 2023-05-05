#include <string>
#include <vector>


#include "../../../util/print.h"

using Coll = std::vector<std::string>;


void bar(Coll&){
    println(__PRETTY_FUNCTION__);
}
void bar(Coll const&){
    println(__PRETTY_FUNCTION__);
}
void bar(Coll &&){
    println(__PRETTY_FUNCTION__);
}
void bar(Coll const&&){
    println(__PRETTY_FUNCTION__);
}

/*
 * 9.3.1 Rvalue Reference of Actual Types
 */
void foo(Coll&& arg){ // arg is an ordinary rvalue reference

    Coll coll; // coll can't be const

    bar(std::move(arg)); // perfectly forward to bar()(no need to use std::forward<>() here)
}
// Inside foo():
// .We know that the type of arg, Coll is never const.
// .It does not make sense to use std::forward<>(),It only makes sense to use std::move() when we no
// longer need the value and want to forward it to another function(using std::forward<>() is possible
// here because it is equivalent to std::move() when called for rvalue references).



/*
 * 9.3.2 Rvalue References of Function Template Parameters
 *
 * If we heve a non-const/volatile rvalue reference to a function template parameter, we pass objects
 * of all value categories. the passed argument may or may not be const:
 */
template<typename Coll>
void foo(Coll&& arg){// arg is universal/forwarding reference
//    Coll coll{}; // coll may be const

    bar(std::forward<Coll>(arg));// perfectly forward to bar()(don't use std::move()here)
}
// Inside foo()
// .The type or arg may or may not be const now.
// .In this case, it usually does not make sense to use std::move(). It only make sense to use std::forward<>()
//  When we no longer need the value and want to forward it to another function(using std::move() is
//  possible but would pass all arguments to foo() with  move semantics, passing the non-const lvalue
//  as an xvalue)

int main()
{
    Coll v;
    const Coll c;

//    foo(v); //ERROR, can't bind rvalue reference to lvalue
  //  foo(c);// ERROR, can't bind rvalue reference to lvalue
    foo(Coll{});//OK, arg binds to a non-const prvalue
    foo(std::move(v));// Ok, arg binds to a non-const xvalue
   // foo(std::move(c));//ERROR, can't bind non-const rvalue reference to const xvalue

    println("==================universal/forwarding referece===============");
    std::vector<std::string> v1;
    const std::vector<std::string> c1;
    foo(v1); // Ok, arg binds to a non-const lvalue
    foo(c1);// Ok, arg binds to a const lvalue
    foo(Coll{});// Ok, arg binds to a non-const prvalue
    foo(std::move(v1));// Ok, arg binds to a non-const xvalue
    foo(std::move(c1));// Ok , arg binds to const xvalue

    return 0;
}
