#include "../../../util/print.h"

#include "gelf.h"
#include "polygon.h"
#include "coord.h"

int main()
{

    Polygon p0 { "Poly1", { Coord { 1, 1 }, Coord { 1, 9 }, Coord { 9, 9 }, Coord { 9, 1 } } };

    Polygon p1 { p0 };              // copy
    Polygon p2 { std::move( p0 ) }; // move

    p0.draw();
    p1.draw();
    p2.draw();

    auto p4 = std::move( p2 ); // move
    p4.draw();
    p2.draw();


    GeoObj& geoRef{p4}; //copy
    geoRef.draw();

 //   geoRef = p1; // ERROR: use GeoObj::operator= and assigns no Polygon members

    return 0;
}
