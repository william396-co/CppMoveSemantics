#pragma once


#include "../../../util/print.h"

class Y{};

#define USE_REF

#ifndef USE_REF
inline void f(Y ){ // call-by-value
     println(__PRETTY_FUNCTION__);
}

#else
inline void f( Y const & )
{ // read-only access
    println( __PRETTY_FUNCTION__ );
}

inline void f( Y & )
{ // OUT parameter( usually long-living object)
    println( __PRETTY_FUNCTION__ );
}


inline void f( Y && )
{ // can steal value(object usually about to die)
    println( __PRETTY_FUNCTION__ );
}

inline void f( Y const && )
{ // no clear semantics meaning
    println( __PRETTY_FUNCTION__ );
}
#endif
/*
 *  In principle, declaring all these overloads is allowed, However, there is no specific priority between call-by-value
 *  and call-by-reference, If you have a function declared to take an argument by value(which can take any argument
 *  of any value category). any matching declaration taking the argument by reference creates an ambiguity.
 *
 *  Therefore, you should usually only take an argument either by value or by reference(with as many reference
 *  overloads as you think are useful) but never both.
 */
inline void overloading_by_ref_val(){
    println(__PRETTY_FUNCTION__);

    Y y{};
    f(y);//

    const Y cy{};
    f(cy);

    f(std::move(y));
    f(Y{});
    f(std::move(cy));
}
