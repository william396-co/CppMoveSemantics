#include "base.h"

#include <iomanip>
#include <ios>
#include "../../../util/print.h"

int main()
{

    println( std::boolalpha,
        "std::is_nothrow_move_constructible_v<Base>: ",
        std::is_nothrow_move_constructible<Base>::value, //false
        "\n is_nothrow_movable_v<Base>: ",
        is_nothrow_movable_v<Base> ); // true

    println( std::boolalpha,
        "std::is_nothrow_move_constructible_v<Drv>:",
        std::is_nothrow_move_constructible<Drv>::value, //false
        "\nis_nothrow_movable_v<Drv>:",
        is_nothrow_movable_v<Drv> ); //true

    Base * pb = new Drv( "1001", "This is my Member" );
    pb->print();

    return 0;
}
