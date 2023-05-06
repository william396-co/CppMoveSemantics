#include "../../../util/print.h"
#include <vector>
#include <string>
#include <iomanip>

// Using the Range-Based for Loop
template<typename Coll,typename T>
void assign(Coll& coll, T const& value){
    for(auto&& elem:coll){ // note: universal reference support proxy element types
        elem = value;
    }
}

int main()
{

    std::vector<int> vi{1,2,3};
    print_con(vi);
    assign(vi,42);
    print_con(vi);

    std::vector<std::string> coll2{"hell", "world"};
    assign(coll2,"ok");
    print_con(coll2);

    std::vector<bool> collB{true,false,true};
    assign(collB,true); // ERROR: cannot bind non-const lvalue reference to an rvalue
    print(std::boolalpha);
    print_con( collB);

    return 0;
}
