#include "polygon.h"

#include "../../../util/print.h"

Polygon::Polygon( std::string s, std::initializer_list<Coord> coords )
    : GeoObj( std::move( s ) ), points { std::move( coords ) }
{
}

void Polygon::draw() const
{
    print( "Polygon '", name, "' over " );
    for ( auto const & pt : points ) {
        print( pt, " " );
    }
    println();
}
