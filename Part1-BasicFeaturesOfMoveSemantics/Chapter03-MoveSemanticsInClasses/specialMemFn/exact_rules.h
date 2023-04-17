#pragma once

#include "../../../util/print.h"
#include <ctime>

namespace exact_rules_for_gen_special_mem_fn {

class MyType
{
};

class Base
{
};

class MyClass : public Base
{
public:
    // Copy constructor
    // The generated copy constructor is declared as noexcept if all copy operations (the copy constructors of
    // all base classes and the copy constructors of all members) give this guarantee.
    MyClass( MyClass const & obj ) noexcept
        : Base( obj ), value( obj.value )
    {
    }

    // Move constructor
    // The generated move constructor is declared as noexcept if all called move/copy operations (the copy or
    // move constructors of all base classes and the copy or move constructors of all members) give this guarantee.
    MyClass( MyClass && obj ) noexcept
        : Base( std::move( obj ) ), value( std::move( obj.value ) )
    {
    }

    // Copy Assignment Operator
    // In addition, the generated copy assignment operator is declared as noexcept if all assignment operations
    // (the assignment of the base class members and the assignment of the new members) give this guarantee.
    MyClass & operator=( MyClass const & obj ) noexcept
    {
        Base::operator=( obj ); // perform assignment for base class members
        value = obj.value;      // assign new members
        return *this;
    }

    // Move assignment Operator
    MyClass & operator=( MyClass && obj ) noexcept
    {
        Base::operator=( std::move( obj ) ); // perform move assignment for base class members
        value = std::move( obj.value );      // move assign new members
        return *this;
    }

private:
    MyType value;
};

inline void execute()
{
    println( __PRETTY_FUNCTION__ );
}
} // namespace exact_rules_for_gen_special_mem_fn
