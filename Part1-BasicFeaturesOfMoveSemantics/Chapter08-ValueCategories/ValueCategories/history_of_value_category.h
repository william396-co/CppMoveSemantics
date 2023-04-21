#pragma once
#include "../../../util/print.h"

/*
 * 8.1.1 History of Value Categories
 *
 * . An lvalue could occur on the  left-hand side of an assignment
 * . An rvalue could occur only on the right-hand side of an assignment
 */

#include <string>
#include <functional>

inline void history_value_categories()
{
    println( __PRETTY_FUNCTION__ );

    int x; // x is an lvalue when used in an expression

    x = 42; // Ok, because x is an lvalue and the type matches
    //    42= x;//EROR; 42 is an rvalue and can bo only on the right-hand side of an assignment

    int * p1 = &x;
    println(*p1);
    //    int* p2 = &42; // ERROR: &is not allowed for rvalues(object has no specified location)

    {
        const int c = 42;
        //c = 43; // now an ERROR(so that c should no longer be an lvalue)
        const int * p1 = &c; // still Ok(so that c should still be an lvalue)
        println(*p1);
    }
    {
        std::string s;

        std::move( s ) = "hello"; // OK(behaves like an lvalue)
       //        auto ps = &std::move(s); // ERROR(behaves like an rvalue)
       println(s);
    }

    {
        int i ;
//        std::move(i) = 42;// ERROR
  //      auto pi= &std::move(i);// ERROR
    }
}
