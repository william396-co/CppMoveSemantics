#include <string>
#include <vector>
#include <iostream>

/*
 * SSO small string optimization(the string might store its whole value on the stack provided the is not too long)
 */

std::vector<std::string> createAndInsert()
{
    std::vector<std::string> coll;
    coll.reserve( 3 );

    std::string s = "data";

    coll.push_back( s );
    coll.push_back( s + s );
    coll.push_back( s );

    return coll;
}

int main()
{
    std::vector<std::string> v;
    v = createAndInsert();

    for ( std::vector<std::string>::iterator it = v.begin(); it != v.end(); ++it ) {
        std::cout << *it << "\t";
    }
    std::cout << "\n";

    return 0;
}
