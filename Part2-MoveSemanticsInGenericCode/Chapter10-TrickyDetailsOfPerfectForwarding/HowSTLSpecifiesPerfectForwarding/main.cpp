#include <string>
#include <type_traits>
#include <utility>
#include <vector>
#include "../../../util/print.h"

/*
 * 10.3 How the Standard Specifies Perfect Forwarding
 * To finally understand all rules of perfect forwarding , let us see how the rules are formally
 * specified in the C++ standard
 *
 */

template<typename T>
void g( T & )
{
    println( __PRETTY_FUNCTION__ );
}

template<typename T>
void g( T const & )
{
    println( __PRETTY_FUNCTION__ );
}
template<typename T>
void g( T && )
{
    println( __PRETTY_FUNCTION__ );
}
template<typename T>
void g( T const && )
{
    println( __PRETTY_FUNCTION__ );
}

// references to functions are awalys lvalues, therefor T is always deduced as an lvalue reference if
// we pass a reference to a function to a universal reference
void func( int )
{
}

#if __cplusplus > 201703L
void f( auto && arg )
{
    g( std::forward<decltype( arg )>( arg ) );
}
#else

template<typename T>
void f( T && arg ) // arg is universal/forwarding reference
{
    g( std::forward<T>( arg ) ); // perfectly forward(move() only for passed rvalues)
}
#endif

class MyType
{};


/*
 * 10.3.2 Conflicting Template Parameter Deduction with Universal References
 */
template<typename T>
void insert(std::vector<T>&vec, T&& elem)
{
    println(__PRETTY_FUNCTION__);
    vec.push_back(std::forward<T>(elem));
}

// you can use the type trait std::remove_reference_t<>
template<typename T>
void insert1(std::vector<std::remove_reference_t<T>>&vec, T&& elem)
{
    println(__PRETTY_FUNCTION__);
    vec.push_back(std::forward<T>(elem));
}

// you can use two template parameter instead
template<typename T1, typename T2>
void insert2(std::vector<T1>&vec, T2&&elem){
    println(__PRETTY_FUNCTION__);
    vec.push_back(std::forward<T2>(elem));
}

// or just
template<typename Coll, typename T>
void insert3(Coll& coll, T&& elem){
    println(__PRETTY_FUNCTION__);
    coll.push_back(std::forward<T>(elem));
}

/*
 * 10.3.3 Pure Rvalue Reference of Generic Types
 * With the special rule for deducting template parameters of universal references(deducing the types as an
 * lvalue reference when lvalue are passed), we can constrain generic reference parameters to only bind to
 * rvalues:
 */
template<typename T>
void foo(T&& arg){
    println(__PRETTY_FUNCTION__);
}

#if __cplusplus > 201703L
template<typename T>
requires( !std::is_lvalue_reference_v<T> ) void callFoo( T && arg )
{
    foo( std::forward<T>( arg ) );
}
#else
template<typename T,
    typename = typename std::enable_if<!std::is_lvalue_reference<T>::value>::type>
void callFoo( T && arg )
{
    foo( std::forward<T>( arg ) );
}
#endif

int main()
{

    MyType v;
    const MyType c;
    f( MyType {} );      // T is deduced as MyType, so arg is declared as MyType&&
    f( std::move( v ) ); // T is deduced as MyType, so arg is declared as MyType&&

    /*
     * If the parameter type is an rvalue reference to a cv-unqualified template parameter and the
     * argument is an lvalue, the type "lvalue reference to T" is used in place of T for type deduction.
     */
    f( v ); // T is deduced as MyType& and arg has this type
    f( c ); // T is deduced as const MyType& and arg has this type

    /*  引用折叠
     * However , we have arg declared as T&&,so if T is T& instead, what does that mean? Here , the reference
     * collapsing rule of C++ gives an answer:
     * .Type& & becomes Type&
     * .Type& && becomes Type&
     * .Type&& & becomes Type&
     * .Type&& && becomes Type&&
     */

    /*
     * Now consider how std::forward<>() is defined in contrast to std::move():
     *
     * .std::move() always convert any type to an rvalue reference:
     *   static_cast<remove_reference_t<T>&&>(t) 删除引用 再增加&&
     *   It removes any referenceness and converts to the corresponding rvalue reference type(removes any&
     *   and add &&)
     *
     * .std::forward<>() only adds rvalue referenceness to the passed type parameter:
     *  static_cast<T&&>(t) // 仅增加&&
     *
     *  Here, the reference collapsing rules aplly agian:
     *  - If type T is lvalue reference,T&& is still an lvalue reference(&& has no effect). Therefor, we cast
     *   arg to an lvalue reference,which means that arg has no move semantics.
     *  - However, if T is an rvalue reference(or not a refernce at all),T&& is (still) an rvalue reference.
     *    Therefor, we cast arg to an rvalue reference and that waay we change the value category to an xvalue,
     *    which is the effect of std::move()
     *
     * In total, therefor, we get:
     */

    f( v );              // T and arg are MyType&, forward() has no effect in this case
    f( c );              // T and arg are const MyType&, forward() has no effect in this case
    f( MyType {} );      //T is MyType, arg is MyType&&, forward() is equivalent to move()
    f( std::move( v ) ); //T is MyType, arg is MyType&&, forward() is equivalent to move()

    // Not that [string literals are lvalues] , so that we deduce T and arg for them as follows:
    f( "hi" );                 // lvalue passed, so T and arg have type const char(&)[3]
    f( std::move( "hello" ) ); // xvalue passed, so T is deduced as const char[6] and arg has type const char(&&)[6]

    // Remember also that [reference to function are always lvalues]
    println( "===========================" );
    f( func );              // lvalue passed to f(), so T and arg have type void(&)(int)
    f( std::move( func ) ); // lvalue passed to f(), so T and arg have type void(&)(int)

    /*
     * 10.3.1 Explicit Specification of Types for Universal References
     *
     */
    println( "=================================" );
    std::string s { "hello" };
    const std::string cs { "hi" };
    //f<std::string>( s );              // ERROR , cannot bind rvalue reference to lvalue
    f<std::string &>( s );            // Ok, does not move and forward s
    f<std::string>( std::move( s ) ); // OK , does move and forwad s
    f<std::string &&>( std::move( s ) );
    f<std::string const &>( cs );

    // 10.3.2
    {
        std::vector<std::string> coll;
        std::string s { "hi" };
        //        insert(coll,s); // ERROR, no matching function call
        // Using the parameter coll, T it is deduced as std::string.
        // However, according to the special rule for universal references,
        // parameter forces to deduce T as std::string&(s is std::string&)
        insert1( coll, s ); // Now, with T deducedd as std::string& vec now bind to coll

        insert2( coll, s );
        insert3( coll, s );
    }

    // 10.3.3
    {
        println("================================");
        MyType x{};
        callFoo(MyType{});
//        callFoo(x); //ERROR, no matching function
    callFoo(std::move(x));

    }
    return 0;
}
