#include "../../../util/print.h"

/*
 * Since C++20, you can also declare ordinary function with auto&&, which is then handled in the same way:
 * it declares a function template with a universal reference.
 */

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

#if _cplusplus > 201703L
void callFoo(auto&& val){
    foo(std::forward<decltype(val)>(val));
}
#else
template<typename T>
void callFoo(T&& val){
    foo(std::forward<decltype(val)>(val));
}
#endif

int main()
{
    //This is means that you can also explicitly specify the type of the parameter here, However, in the same way
    //as for ordinary function template, you have to qualify the template parameter with at type that fits the value
    //category of your passed argument

    std::string s;

//    callFoo<std::string>(s); //ERROR; cannot bind rvalue reference to lvalue
    callFoo<std::string&>(s); // foo(std::string&)
    callFoo<std::string>(std::move(s)); // foo(std::string&&)
    callFoo<std::string&&>(std::move(s));// foo(std::string&&)
    callFoo<std::string&&>(std::string{"tmp"});// foo(std::string&&)
    callFoo<std::string const&>(std::string{"tmp"});// foo(std::string const&)

    return 0;
}
