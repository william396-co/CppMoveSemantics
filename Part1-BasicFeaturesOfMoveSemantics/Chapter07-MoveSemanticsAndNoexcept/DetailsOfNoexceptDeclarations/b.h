#pragma once
#include <ios>
#include <iostream>
#include <type_traits>
#include <string>
#include <iomanip>

#include "../../../util/print.h"

class B
{
    std::string s;

public:
    B() = default; // noexcept  condition automatically generated

    B( B const & ) = default; // noexcept condition automatically generated(disable default constructor)
    B( B && ) = default;      // noexcept condition automatically generated(disable default constructor)

    B & operator=( B const & ) = default; // noexcept condition automatically generated

    B & operator=( B && ) = default; // noexcept condition automatically generated

    ~B() {} // automatically always declared as ~() noexcept
};

class C
{
public:
    C( C const & )
    noexcept = default; // guarantees not to throw(Ok since C++20)
    C( C && )
    noexcept( false ) = default; // specifies that it might throw(Ok since C++20)
};

inline void test_b()
{
    println( __PRETTY_FUNCTION__ );

    println( std::boolalpha,
        std::is_nothrow_default_constructible<B>::value, //true
        "\n",
        std::is_nothrow_copy_assignable<B>::value, //false
        "\n",
        std::is_nothrow_move_constructible<B>::value, //true
        "\n",
        std::is_nothrow_copy_assignable<B>::value, //false
        "\n",
        std::is_nothrow_move_assignable<B>::value,
        "\n",
        std::is_nothrow_destructible<B>::value // true
    );                                         //true
}
