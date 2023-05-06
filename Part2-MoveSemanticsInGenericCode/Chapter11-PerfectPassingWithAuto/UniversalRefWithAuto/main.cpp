#include "../../../util/print.h"

#include <string>

void process(std::string const&){
    println(__PRETTY_FUNCTION__);
}
void process(std::string&){
    println(__PRETTY_FUNCTION__);
}
void process(std::string&&){
    println(__PRETTY_FUNCTION__);
}
void process(std::string const&&){
    println(__PRETTY_FUNCTION__);
}

const std::string& computeConstLRef(std::string const& str){
    return str;
}
std::string& computeLRef(std::string& str){
    return str;
}
std::string&& computeRRef(std::string&&str){
    return std::move(str);
}
std::string computeVal(std::string const&str){
    return str;
}

std::string ret{"ret"};

std::string retByValue(){
    return "retByValue";
}
std::string& retByRef(){
    return ret;
}
std::string&& retByRRef(){
    return std::move(ret);
}
const std::string& retByConstRef(){
    return  ret;
}
const std::string&& retByConstRRef(){
    return std::move(ret);
}

std::string foo(int){
    return "foo";
}
int main()
{
    {
        /*
         * in generic code, how can you program passing a return value but still keeping its type
         * and value category?
         *
         * the answer is that again,  you need a universal/forwarding reference,
         */
        auto&& r1 = computeConstLRef("tmp"); // initialize a universal reference with the return value
        process(std::forward<decltype(r1)>(r1)); // calls process(std::string const&)

        std::string str{"lvalue"};
        auto&&r2 = computeLRef(str);
        process(std::forward<decltype(r2)>(r2));// calls process(std::string&)

        auto&& r3 = computeRRef("tmp");
        process(std::forward<decltype(r3)>(r3)); // calls process(std::string&&)
        auto&& r4 = computeRRef(std::move(str));
        process(std::forward<decltype(r4)>(r4));// calls process(std::string&&)

        auto&& r5{computeVal("tmp")};// initialize a universal reference with the return value
        process(std::forward<decltype(r5)>(r5));// calls process(std::string&&)

    }

    /*
     * 11.2.1 Type Deduction of auto&&
     * If you declare something with auto&&, you also declare a universal reference.
     */

    // deduced auto&& types:
    {
        println("=================================================");
        std::string s;

        auto&& r1{s}; // std::string&
        auto&& r2{std::move(s)}; // std::string&&

        process(std::forward<decltype(r1)>(r1));
        process(std::forward<decltype(r2)>(r2));

        auto&& r3{retByValue()}; // std::string&&
        auto&& r4{retByRef()};// std::string&
        auto&& r5{retByRRef()};// std::string&&
        auto&& r6{retByConstRef()};// std::string const&
        auto&& r7{retByConstRRef()}; //std::string const&&

        process(std::forward<decltype(r3)>(r3));
        process(std::forward<decltype(r4)>(r4));
        process(std::forward<decltype(r5)>(r5));
        process(std::forward<decltype(r6)>(r6));
        process(std::forward<decltype(r7)>(r7));

        auto&& r8{"hello"}; //const char(&)[6]  string literals is lvalue

        process(std::forward<decltype(r8)>(r8)); // implicitly conversion to std::string form const char*
        // refrence to functions are always lvalues
        auto&& r9{foo};//lvalue type std::string(&)(int)
        auto&& r10{std::move(foo)};//lvalue type std::string(&)(int)
    }
    return 0;
}
