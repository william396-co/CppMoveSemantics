#include "../../../util/print.h"

/*
 * 9.5 Pefect Forwarding in Lambdas
 * If you want to perfectly forward parameters of lambdas, you also have to use universal references
 * and std::forward<>(), However, in that case, you usually declare the universal with auto&& as
 * explained in the chapter about auto&&
 */

class X{};

void foo(X&){
    println(__PRETTY_FUNCTION__);
}
void foo(X const&){
    println(__PRETTY_FUNCTION__);
}
void foo(X&&){
    println(__PRETTY_FUNCTION__);
}

void foo(X const&&){
    println(__PRETTY_FUNCTION__);
}

int main()
{
    println(__cplusplus);
#if __cplusplus > 201703L
    auto callFoo = []<typename T>(T&& arg){
        foo(std::forward<T>(arg);
    };
#else
    auto callFoo =[](auto&& arg){
        foo(std::forward< decltype(arg)>(arg));
    };
#endif

    X x;
    const X c;

    callFoo(x); // foo(X&)
    callFoo(c); // foo(X const&)
    callFoo(X{}); // foo(X&&)
    callFoo(std::move(x)); // foo(X&&)
    callFoo(std::move(c));// foo(X const&&)

    return 0;
}
