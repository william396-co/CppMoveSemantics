#pragma once

#include <iostream>
#include <ostream>

class Coord
{
public:
    Coord( int x, int y )
        : x { x }, y { y } {}

    friend std::ostream & operator<<( std::ostream & os, Coord const & coord );

private:
    int x;
    int y;
};
inline std::ostream & operator<<( std::ostream & os, Coord const & coord )
{
    return os << "(" << coord.x << "," << coord.y << ")";
}
