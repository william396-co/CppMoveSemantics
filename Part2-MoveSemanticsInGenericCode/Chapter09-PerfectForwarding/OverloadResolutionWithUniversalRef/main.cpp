#include <string>
#include <type_traits>

#include "../../../util/print.h"

//--------------------------------------------------------------------------------------------------
//            |          |               |              |                   | template<typename T> |
//  Call      |  f(X&)   |  f(X const&)  |   f(X&&)     |   f(X const&&)    |  f(T&&)              |
//=================================================================================================|
//  f(v)      |    1     |     2         |    no        |       no          |       2              |
//  f(c)      |    no    |     1         |    no        |       no          |       2              |
// f(X{})     |    no    |     3         |    1         |       2           |       2              |
// f(move(v)) |    no    |     3         |    1         |       2           |       2              |
// f(move(c)) |    no    |     2         |    no        |       1           |       2              |
//--------------------------------------------------------------------------------------------------


class X{

public:
    X()=default;
    X(X const&){
        println("copy constructor");
    }
    X(X&&){
        println("move constructor");
    }

/*    template<typename T>
    X(T&&){
        println("universal constructor");
    }*/

    // Fixed Overload Resolution with Universal References
    template<typename T,
            typename = typename std::enable_if<!std::is_same<typename std::decay<T>::type,X>::value>::type>
    X(T&&){
        println("universal constructor");
    }

};

void f(X const&){ // read-only acces
    println(__PRETTY_FUNCTION__);
}

void f(X&){// OUt parameter(usually long-living object)
    println(__PRETTY_FUNCTION__);
}

void f(X&&){// can steal value(object usually about to die)
    println(__PRETTY_FUNCTION__);
}

void f(X const&&){// contradicting semantic meaning
    println(__PRETTY_FUNCTION__);
}

template<typename T>
void f(T&& arg){ // to use perfect forwarding
    println(__PRETTY_FUNCTION__);
    f(std::forward<T>(arg));
}


class Y
{
public:
    Y( std::string const & name = "defaultY" )
        : name { name } {}

    std::string getName()&&{
        return std::move(name);
    }
    const std::string getName()const&{
        return name;
    }
private:
    std::string name;
};

Y * create()
{
    return new Y();
}

Y * create( std::string const & name )
{
    return new Y { name };
}

template<typename T, typename... Args>
T * create( Args &&... args )
{
    return new T( std::forward<Args>( args )... );
}


int main()
{
   auto y1 = create();
   auto y2 = create("Y2");

   println(y1->getName());
   println(y2->getName());

   delete y1;
   delete y2;

    println("=========================================");
    X x;
    const X c;
    f(x);
    f(c);
    f(X{});
    f(std::move(x));
    f(std::move(c));

    println("========================");
    X xv;
    const X xc;
    X xcc{xc}; // copy constructor
    X xvc{xv};// OOPS: calls universal constructor
    X xvm{std::move(xv)}; // move constructor
    X xcm{std::move(xc)}; //OOPs: call universal constructor


    f(X{});
    return 0;
}
