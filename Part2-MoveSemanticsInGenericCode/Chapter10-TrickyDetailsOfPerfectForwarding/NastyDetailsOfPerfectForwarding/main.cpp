#include "../../../util/print.h"
#include <vector>
#include <string>

/*
 * "Universal" Versus "Forwarding" Reference
 *
 * In 2023, Scott Meyers introduced the term "universal reference" fot them
 *
 * C++ standard committee decided to introduce a different term with C++17: forwarding reference.
 */

/*
 * 10.4.2 Why && for Both Ordinary Rvalues and Universal References?
 */
using Coll = std::vector<std::string>;

// Use two ampersands for ordinary rvalue references:
void foo(Coll&&arg){ // arg is an ordnary rvalue reference
    println(__PRETTY_FUNCTION__);
}

// Use three ampersands for universal/forwarding reference
template<typename T>
void foo(T&&& arg){ // can not declare T&&&
    println(__PRETTY_FUNCTION__);
}

int main(){

    Coll coll;
    foo(std::move(coll));
    return 0;
}
