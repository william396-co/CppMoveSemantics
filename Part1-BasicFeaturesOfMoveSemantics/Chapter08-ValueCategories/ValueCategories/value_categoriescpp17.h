#pragma once

#include "../../../util/print.h"
/*
 * 8.1.3  Value Categories Since C++17
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
 *                   \            /
 *                    \          /
 *                  materialization
 *
 * glvalue: expressions for locations for long-living objects or functions
 * prvalue: expressions for short-living values for initializations
 * An xvalue is then considered a special location, representing a (long-living) object
 * whose resources/values are no longer needed
 *
 */

class C
{
public:
    C()=default;
    C(C const&)=delete; // this class is neither copyable...
    C(C&&)=delete;// ...nor movable
};


inline C createC(){
    return C{}; // Always creates a conceptual temporary prior to C++17
                // In C++17, no temporary object is created at this point.
}

inline void takeC(C val){
    println(__PRETTY_FUNCTION__);
}

/*
 * Materialization
 * C++17 then introduces a new term, called materialization(of an unnamed temporary), for the moment a
 * prvalue becomes a temporary object, Thus, a temporary materialization conversion is a(usually implicit)
 * prvalue-to-xvalue conversion.
 */
class Y{};
inline void f(const Y& p){ // accepts an expression of any value category but expects a glvalue
    println(__PRETTY_FUNCTION__);
}

inline void value_categories_cpp17()
{
    println( __PRETTY_FUNCTION__ );
    takeC( createC() );
    f( Y {} ); // creates a temporary prvalue and passes it materialized as an xvalue
}
