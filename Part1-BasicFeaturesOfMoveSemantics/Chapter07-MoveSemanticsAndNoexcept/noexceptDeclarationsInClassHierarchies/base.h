#pragma once

#include "../../../util/print.h"
#include "isnothrowmovable.h"
#include <string>

class Base
{
protected:
    std::string id;

public:
    virtual void print() const = 0; // pure virtual function(force abstract base class)

    virtual void test() = 0;
    virtual ~Base() = default;

protected:
    Base( std::string && id )
        : id { std::move( id ) } {}

    // procted copy and move semantics(also forces abstract base class)
    Base( Base const & ) = default;
    Base( Base && ) = default;

    // disable assignment operator(due to the problem of slicing)
    Base & operator=( Base const & ) = delete;
    Base & operator=( Base && ) = delete;
};

class Drv : public Base
{
    std::string member;

public:
    // You can now check even for abstract base classes whether the move constructor is noexcept.
    // just use is_nothrow_movable_v<T> to check wheterh Base and MemberType is throw
    Drv( Drv && ) noexcept( is_nothrow_movable_v<Base> && is_nothrow_movable_v<std::string> ) = default;

    Drv( std::string id, std::string member )
        : Base { std::move( id ) }, member { std::move( member ) } {}

    virtual void print() const override
    {
        println( __PRETTY_FUNCTION__, " id:", id, " member:", member );
    }
    virtual void test() override
    {
        println( __PRETTY_FUNCTION__ );
    }
};
