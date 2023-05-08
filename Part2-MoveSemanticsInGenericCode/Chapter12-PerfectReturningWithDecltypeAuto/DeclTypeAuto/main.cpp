#include "../../../util/print.h"
#include <string>
#include <iostream>
#include <utility>
#include <type_traits>
/*
 * 12.2 delctype(auto)
 * Just like the other placeholder type auto, delctype(auto) is a placeholder type that lets the compiler
 * deduce the type at initialization time, However, in this case ,the type is deduced according to the rules
 * of decltype:
 * .If you initialize it with or return a plain name, the return type is the type of the object with that name.
 * .If you initialize it with or return an expression, the return type is the type and value category of the
 *   evaluated expression as follows with the following encoding:
 *  - For a prvalue, it just yields its value type: type
 *  - For an lvalue, it yields its type as an lvalue reference: type&
 *  - For an xvalue, it yields its type as an rvalue reference: type&&
 */

void decltype_auto()
{
    println(__PRETTY_FUNCTION__);
    std::string s ="hello";
    std::string& r = s;

    // initialize with name:
    decltype(auto) da1 = s; //std::string
    decltype(auto) da2(s);//same
    decltype(auto) da3{s};//same
    decltype(auto) da4=r; //std::string&

        // initialize with expression:
        decltype(auto) da5 = std::move(s); //std::string&&  std::move(s) is xvalue, so da5 is an rvalue reference
        decltype(auto) da6 = s+s;// std::string operator+ for string returns a new temporary string by value(so it is prvalue), da6 is plain value type
        decltype(auto) da7 = s[0]; // char& s[0] returns an lvalue reference to the first character, it is an lvalue and forces da7 also to be an lvalue reference.
        decltype(auto) da8 = (s); //std::string& (s) is an lvalue, da8 is an lvalue reference, yes ,the parentheses make a difference here.


        // Note that decltype(auto) cannot have additional qualifiers:
        decltype(auto) da{s};//OK
       // const delctype(auto)& cda{s};//ERROR
       // decltype(auto)* pda{&s}; //ERROR
}

/*
 * 12.2.1 Return Type decltype(auto)
 *
 * When using decltype(auto) as a return type, we use the rules of decltype as follows:
 * .If the expression returns/yeilds a plain value, then the value category is a prvalue and decltype(auto)
 *   deduce a value type.
 * .If the expression returns/yeilds an lvalue reference, then the value category is an lvalue and decltype(auto)
 *   deduces an lvalue reference.
 * .If the expression returns/yeilds an rvalue reference, then the value category is an xvalue and decltype(auto)
 *   deduces an rvalue reference.
 *
 *  That is exactly what we need for perfect returning: for a plain value, we deduce a value, and for a reference,
 *  we deduce a reference of the same type and value category.
 */

/*
 * The function declares args as variadic number of universal references(also called forwarding references).
 * with std::forward<>(), it perfectly forwards these given arguments to the function f passed as first argument,
 * Because we use decltype(auto) as the return type, we perfectly return the return value of f() to the caller of call()
 *
 */
template<typename Func, typename...Args>
decltype(auto) call(Func f, Args&&...args)
{
    return f(std::forward<Args>(args)...);
}

std::string nextString(){
    return "Let's dance";
}
std::ostream& print_str(std::ostream&os, std::string const& val){
    return os<<"value:" <<val;
}
std::string&& returnArg(std::string&& arg){
    return std::move(arg);
}

void return_type_decltype_auto(){
    println(__PRETTY_FUNCTION__,"\n");

    auto s = call(nextString); // call() returns temporary object

    // When calling
    auto&& ref = call(returnArg, std::move(s)); //call returns rvalue reference to s
    // the function call() calls the function returnArg() with s makred with std::move(), returnArg()
    // return back the passed argument an rvalue reference, which then call() perfectly returns to
    // the caller to initialize ref, s still has its value and ref refers to it:
    println("s: ",s); // Let's dance
    println("ref: ", ref);// Let's dance

    println("===============");
    auto str = std::move(ref); // move value from s and ref to str
    println("s: ",s); // s:
    println("ref: ",ref);//ref:
    println("str: ",str);// str: Let's dance


    call(print_str,std::cout,str) << "\n"; // call() returns reference to std::cout
}


/*
 * 12.2.2 Deferred Perfect Returning
 * To perfectly return a value that was computed earlier, we have to declare a local object with decltype(auto)
 * and return it with std::move() if and only if it is an rvalue reference,For example:
 */
template<typename Func, typename...Args>
decltype(auto) call2(Func f, Args&&...args){
    decltype(auto) ret{f(std::forward<Args>(args)...)};

    if constexpr (std::is_rvalue_reference_v<decltype(ret)>){
        return std::move(ret); // move xvalue returned by f() to the caller
    }
    else{
        return ret; // return the plain value or the lvalue reference
      //  return (ret); //FATAL RUNTIME ERROR: always returns an lvalue reference
    }
}

void deferred_perfect_returning(){
    println(__PRETTY_FUNCTION__, "\n");

    auto s = call2(nextString); // call() returns temporary object


    auto&& ref = call2(returnArg, std::move(s)); //call returns rvalue reference to s
    println("s: ",s);
    println("ref: ", ref);

    println("===============");
    auto str = std::move(ref); // move value from s and ref to str
    println("s: ",s);
    println("ref: ",ref);
    println("str: ",str);


    call2(print_str,std::cout,str) << "\n"; // call() returns reference to std::cout
}

/*
 * 12.2.3 Perfect Forwarding and Returning with Lambdas
 *
 */

void perfect_forwarding_and_returning_with_lambdas(){
    println(__PRETTY_FUNCTION__,"\n");
    // explicitly declaring the lambda with the return type decltype(auto)
    auto lambda_call = [](auto f, auto&&...args) -> decltype(auto){
        return f(std::forward<decltype(args)>(args)...);
    };
    std::string str{"how are you doing"};

    lambda_call(print_str,std::cout,str)<<"\n";

    auto ll = [](auto f, auto&&...args) -> decltype(auto){
        decltype(auto) ret{f(std::forward<decltype(args)>(args)...)};

        if constexpr( std::is_rvalue_reference_v<decltype(ret)>){
            return std::move(ret);
        }else{
            return ret;
        }
    };

    auto s = ll(nextString);
    auto&& ref = ll(returnArg, std::move(s));
    println("s:",s);
    println("ref:",ref);
}
int main(){

    decltype_auto();
    return_type_decltype_auto();
    deferred_perfect_returning();
    perfect_forwarding_and_returning_with_lambdas();
    return 0;
}
