#pragma once

#include "../../../util/print.h"
#include <ostream>
#include <string>

//#define RETURN_BY_VALUE
//#define RETURN_BY_REFERENCE

#define BEST_PERFORM

class Person
{
public:
    Person( std::string n )
        : name { std::move( n ) } {}

#ifdef RETURN_BY_VALUE
    // return by value
    std::string getName() const
    {
        return name; //
    }
#endif
#ifdef RETURN_BY_REFERENCE
    // return by reference
    const std::string & getName() const
    {
        return name;
    }
#endif

#ifdef BEST_PERFORM
    const std::string & getName() const & // in all other cases
    {
        println( __PRETTY_FUNCTION__, " ", name );
        return name; // we give acces to the member
    }

    // return rvalue reference(by std::move())
    std::string getName() && // when we no longer need the value

    {
        println( __PRETTY_FUNCTION__, " ", name );
        return std::move( name ); // we steal and return by value
    }
#endif

    friend std::ostream & operator<<( std::ostream & os, Person const & p );

private:
    std::string name;
};
inline std::ostream & operator<<( std::ostream & os, Person const & p )
{
    return os << p.name;
}
