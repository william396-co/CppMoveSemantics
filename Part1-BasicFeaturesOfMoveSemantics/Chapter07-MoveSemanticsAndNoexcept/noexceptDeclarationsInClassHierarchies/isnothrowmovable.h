#pragma once

#include <type_traits>

/*
 * 7.3.1 Checking for noexcept Move Constructors in Abstract Base Classes
 */

template<typename Base>
struct Wrapper : Base
{
    using Base::Base;
    // implement all possibly wrapped pure virtual functions
    void print() const {}
    void test(){}
};

// type trait to check whether a base class guarantees not to throw
// in move constructor(even if the constructor is not callable)
template<typename T>
static constexpr inline bool is_nothrow_movable_v = std::is_nothrow_move_constructible<Wrapper<T>>::value;
