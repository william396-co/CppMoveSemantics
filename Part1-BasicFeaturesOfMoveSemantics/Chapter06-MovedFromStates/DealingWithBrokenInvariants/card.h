#pragma once

#include <ostream>
#include <string>
#include <iostream>
#include <vector>

#include "../../../util/print.h"

// 6.3.1 Breaking Invariants Due to a Moved Value Member
class Card
{
public:
    Card( std::string v )
        : value { std::move( v ) }
    {
        assertValidCard( value ); // ensure the value is always valid
    }

    const std::string & getValue() const
    {
        return value;
    }

    // disable move semantics
    Card( Card const & ) = default;
    Card & operator=( Card const & ) = default;

    // disable copy/move semantics
    /*    Card( Card const & ) = delete;
    Card & operator=( Card const & ) = delete;*/

    friend std::ostream & operator<<( std::ostream & os, Card const & card );

private:
    void assertValidCard( std::string const & val )
    {
    }

private:
    std::string value; // rank + "-of-" + suit
};

inline std::ostream & operator<<( std::ostream & os, Card const & card )
{
    std::string val = card.getValue();

    auto pos = val.find( "-of-" );
    if ( pos != std::string::npos ) {
        return os << val.substr( 0, pos ) << ' ' << val.substr( pos + 4 );
    }
    return os << "no value";
}

inline void test_card()
{
    println( __PRETTY_FUNCTION__ );

    std::vector<Card> deck;
    deck.emplace_back( "ace-of-hearts" );
    deck.emplace_back( "jack-of-black" );

    Card c { std::move( deck[0] ) }; // deck[0] has invalid state

    println( deck[0] ); // passing an object with broken invariant

    deck[0] = Card { "one-of-hearts" }; // deck[0] is valid again
}
