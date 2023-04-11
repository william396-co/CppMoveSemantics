#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> createAndInsert()
{

    std::vector<std::string> coll;
    coll.reserve( 3 );

    std::string s = "data";

    coll.push_back( s );              // copy string
    coll.push_back( s + s );          // temporary value user universe reference (T&&),  std::move
    coll.push_back( std::move( s ) ); // s will no longer need use

    return coll;
}

int main()
{
    std::vector<std::string> v;
    v = createAndInsert();

    for ( auto const & it : v ) {
        std::cout << it << "\t";
    }
    std::cout << "\n";
    return 0;
}
