#pragma once

/*
 * 8.1.2  Value Categories Since C++11
 *
 *                expression
 *                  /   \
 *                 /     \
 *                /       \
 *          glvalue      rvalue
 *           /   \       /   \
 *          /     \     /     \
 *         /       \   /       \
 *      lvalue      xvalue    prvalue
 *
 *  we have the following primary categories:
 *
 *  lvalue("lcator value")
 *  prvalue("pure readable value")
 *  xvalue("eXpiring value")
 *
 *  The composite categories are:
 *  gvalue("generalize lvalue") as a comment term for "lvalue or xvalue"
 *  rvalue as a common term for "xvalue or prvalue"
 */


#include "../../../util/print.h"

class X{};

inline void f(X x){
    println(__PRETTY_FUNCTION__);
}

void inline value_categories(){
    println(__PRETTY_FUNCTION__);

    X v;
    const X c;

    f(v);
    f(c);
    f(X());
    f(X{});
    f(std::move(v));

}
