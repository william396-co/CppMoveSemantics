#pragma once

#include <vector>
#include <initializer_list>

#include "geoobj.h"
#include "coord.h"

class Polygon : public GeoObj
{
public:
    Polygon( std::string s, std::initializer_list<Coord> coords = {} );

    virtual void draw() const override;

 //   virtual ~Polygon() = default; // OOPS: don't do that because it disables move semantics

protected:
    std::vector<Coord> points;
};
