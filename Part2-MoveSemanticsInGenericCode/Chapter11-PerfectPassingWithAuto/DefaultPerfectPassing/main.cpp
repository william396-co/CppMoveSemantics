#include "../../../util/print.h"
#include <string>

/*
 * 11.1 Default Perfect Passing
 *
 * if you pass a return value to another function directly, the value is passed perfectly.
 * keeping its type and value category.
 */


void process(std::string const&){
    println(__PRETTY_FUNCTION__);
}
void process(std::string&){
    println(__PRETTY_FUNCTION__);
}
void process(std::string&&){
    println(__PRETTY_FUNCTION__);
}
/*
void process(std::string const&&){
    println(__PRETTY_FUNCTION__);
}
*/
const std::string& computeConstLRef(std::string const& str){
    return str;
}
std::string& computeLRef(std::string& str){
    return str;
}
std::string&& computeRRef(std::string&&str){
    return std::move(str);
}
std::string computeVal(std::string const& str){
    return str;
}
const std::string computeConstVal(std::string const& str){
    return str;
}
const std::string&& computeConstRRef(std::string&&str){
    return std::move(str);
}

int main(){

    println("========================================");
    process(computeConstLRef("tmp")); // calls process(std::string const&) return const lvalue reference

    std::string str{"lvalue"};
    process(computeLRef(str)); // calls process(std::string&) return a non-const lvalue reference

    process(computeRRef("tmp")); // calls process(std::string&&) return an rvalue reference
    process(computeRRef(std::move(str))); // calls process(std::string&&) return an rvalue reference

    process(computeVal("tmp")); // calls process(std::string&&) return value is a prvalue

    process(computeConstVal("tmp")); // calls process(std::string const&) return a const value
    process(computeConstRRef("tmp"));// calls process(std::string const&) return a const rvalue reference
    // if declare for const&&, that overload would be taken.
    return 0;
}
