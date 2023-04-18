#include "../../../util/print.h"

#include "refqual.h"

int main()
{
    C x;
    x.foo();              // call foo()&
    C {}.foo();           // call foo()&&
    std::move( x ).foo(); // call foo()&&

    const C cx;
    cx.foo();              // call foo()const&
    std::move( cx ).foo(); // call foo()const&&
    return 0;
}
