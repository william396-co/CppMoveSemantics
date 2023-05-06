#include "../../../util/print.h"


template<typename T>
void foo(T const&){
    println(__PRETTY_FUNCTION__);
}

template<typename T>
void foo(T& ){
    println(__PRETTY_FUNCTION__);
}

template<typename T>
void foo(T&&){
    println(__PRETTY_FUNCTION__);
}


int main(){

    auto callFoo = [](auto&& arg){ // arg is a universal/forwarding reference
        foo(std::forward<decltype(arg)>(arg)); // perfectly forward arg
    };

    std::string s{"BLM"};
    callFoo(s); // foo(std::string&)
    callFoo(std::move(s));//foo(std::string&&)
    callFoo(std::string{"tmp"}); // foo(std::string&&)
    callFoo("tmp"); // string literals is lvalue, const char[], foo(const char(&)[])

    return 0;
}
