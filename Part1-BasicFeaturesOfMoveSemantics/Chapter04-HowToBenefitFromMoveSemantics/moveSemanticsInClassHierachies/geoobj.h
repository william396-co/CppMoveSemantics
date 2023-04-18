#pragma once

#include <string>

class GeoObj
{
protected:
    std::string name;
    GeoObj( std::string n )
        : name { std::move( n ) } {}

public:
    virtual void draw() const = 0;

    virtual ~GeoObj() = default; // let delete call the right destructor(disabled move semantics for name)
protected:
    // enabled copy and move semantics(callable only for derived classes)
    GeoObj( GeoObj && ) = default;
    GeoObj( GeoObj const & ) = default;
    // disable assignment operator(due to the problem of slicing)
    GeoObj & operator=( GeoObj && ) = delete;
    GeoObj & operator=( GeoObj const & ) = delete;
};
