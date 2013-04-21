#include "ph/fle_ph.hpp"

#include "fuzzy_logic_engine/headers/fle_cube_term.hpp"

#include <boost/assign/list_of.hpp>

/*------      ------      ------      ------      ------      ------      ------      ------*/

namespace FuzzyLogicEngine
{

/*------      ------      ------      ------      ------      ------      ------      ------*/


CubeTerm::Enum
CubeTerm::fromShortString( QString const& _str )
{
	static QHash< QString, Enum > table;
	if ( table.empty() )
	{
		table[ "H" ] = H;
		table[ "C" ] = C;
		table[ "B" ] = B;
		table[ "K" ] = K;
		table[ "L" ] = L;
		table[ "M" ] = M;
		table[ "X" ] = X;
		table[ "U" ] = U;
	}

	if ( !table.contains( _str ) )
		throw std::exception();

	Enum enumVal = table.value( _str );

	// CHECKME: this whole function is made considering it will be called only on the input values
	// and the valid inputs aren't all the alphabet
	if ( !isValidInputTerm( enumVal ) )
		throw std::exception();

	return enumVal;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


QString
CubeTerm::toShortString( CubeTerm::Enum _enum )
{
	static QHash< Enum, QString > table;
	if ( table.empty() )
	{
		table[ H ] = "H";
		table[ C ] = "C";
		table[ B ] = "B";
		table[ K ] = "K";
		table[ L ] = "L";
		table[ M ] = "M";
		table[ X ] = "X";
		table[ U ] = "U";
	}

	if ( !table.contains( _enum ) )
		throw std::exception();

	return table.value( _enum );
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


CubeTerm::Enum
CubeTerm::concat( CubeTerm::Enum _e1, CubeTerm::Enum _e2 )
{
	if ( !isValidInputTerm( _e1 ) || !isValidInputTerm( _e2 ) )
		throw std::exception();

	static std::map< std::pair< Enum, Enum >, Enum > table;
	if ( table.empty() )
	{
		table[ std::make_pair( H, H ) ] = H;
		table[ std::make_pair( C, C ) ] = C;
		table[ std::make_pair( B, B ) ] = B;
		table[ std::make_pair( H, C ) ] = K;
		table[ std::make_pair( C, H ) ] = K;
		table[ std::make_pair( H, B ) ] = M;
		table[ std::make_pair( B, H ) ] = M;
		table[ std::make_pair( B, C ) ] = L;
		table[ std::make_pair( C, B ) ] = L;
	}

	return table.find( std::make_pair( _e1, _e2 ) )->second;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


CubeTerm::Enum
CubeTerm::intersection( CubeTerm::Enum _e1, CubeTerm::Enum _e2 )
{
	static std::map< std::pair< Enum, Enum >, Enum > table = boost::assign::map_list_of
		( std::make_pair( H, H ), H )
		( std::make_pair( H, C ), U )
		( std::make_pair( H, B ), U )
		( std::make_pair( H, K ), H )
		( std::make_pair( H, L ), U )
		( std::make_pair( H, M ), H )
		( std::make_pair( H, X ), H )
		( std::make_pair( H, U ), U )

		( std::make_pair( C, H ), U )
		( std::make_pair( C, C ), C )
		( std::make_pair( C, B ), U )
		( std::make_pair( C, K ), C )
		( std::make_pair( C, L ), C )
		( std::make_pair( C, M ), U )
		( std::make_pair( C, X ), C )
		( std::make_pair( C, U ), U )

		( std::make_pair( B, H ), U )
		( std::make_pair( B, C ), U )
		( std::make_pair( B, B ), B )
		( std::make_pair( B, K ), U )
		( std::make_pair( B, L ), B )
		( std::make_pair( B, M ), B )
		( std::make_pair( B, X ), B )
		( std::make_pair( B, U ), U )

		( std::make_pair( K, H ), H )
		( std::make_pair( K, C ), C )
		( std::make_pair( K, B ), U )
		( std::make_pair( K, K ), K )
		( std::make_pair( K, L ), C )
		( std::make_pair( K, M ), H )
		( std::make_pair( K, X ), K )
		( std::make_pair( K, U ), U )

		( std::make_pair( L, H ), U )
		( std::make_pair( L, C ), C )
		( std::make_pair( L, B ), B )
		( std::make_pair( L, K ), C )
		( std::make_pair( L, L ), L )
		( std::make_pair( L, M ), B )
		( std::make_pair( L, X ), L )
		( std::make_pair( L, U ), U )

		( std::make_pair( M, H ), H )
		( std::make_pair( M, C ), U )
		( std::make_pair( M, B ), B )
		( std::make_pair( M, K ), H )
		( std::make_pair( M, L ), B )
		( std::make_pair( M, M ), M )
		( std::make_pair( M, X ), M )
		( std::make_pair( M, U ), U )

		( std::make_pair( X, H ), H )
		( std::make_pair( X, C ), C )
		( std::make_pair( X, B ), B )
		( std::make_pair( X, K ), K )
		( std::make_pair( X, L ), L )
		( std::make_pair( X, M ), M )
		( std::make_pair( X, X ), X )
		( std::make_pair( X, U ), U )

		( std::make_pair( U, H ), U )
		( std::make_pair( U, C ), U )
		( std::make_pair( U, B ), U )
		( std::make_pair( U, K ), U )
		( std::make_pair( U, L ), U )
		( std::make_pair( U, M ), U )
		( std::make_pair( U, X ), U )
		( std::make_pair( U, U ), U )
	;

	return table.find( std::make_pair( _e1, _e2 ) )->second;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


CubeTerm::Enum
CubeTerm::conjunction( CubeTerm::Enum _e1, CubeTerm::Enum _e2 )
{
	static std::map< std::pair< Enum, Enum >, Enum > table = boost::assign::map_list_of
		( std::make_pair( H, H ), H )
		( std::make_pair( H, C ), K )
		( std::make_pair( H, B ), M )
		( std::make_pair( H, K ), K )
		( std::make_pair( H, L ), X )
		( std::make_pair( H, M ), M )
		( std::make_pair( H, X ), X )
		( std::make_pair( H, U ), H )

		( std::make_pair( C, H ), K )
		( std::make_pair( C, C ), C )
		( std::make_pair( C, B ), L )
		( std::make_pair( C, K ), K )
		( std::make_pair( C, L ), L )
		( std::make_pair( C, M ), X )
		( std::make_pair( C, X ), X )
		( std::make_pair( C, U ), C )

		( std::make_pair( B, H ), M )
		( std::make_pair( B, C ), L )
		( std::make_pair( B, B ), B )
		( std::make_pair( B, K ), X )
		( std::make_pair( B, L ), L )
		( std::make_pair( B, M ), M )
		( std::make_pair( B, X ), X )
		( std::make_pair( B, U ), B )

		( std::make_pair( K, H ), K )
		( std::make_pair( K, C ), K )
		( std::make_pair( K, B ), X )
		( std::make_pair( K, K ), K )
		( std::make_pair( K, L ), X )
		( std::make_pair( K, M ), X )
		( std::make_pair( K, X ), X )
		( std::make_pair( K, U ), K )

		( std::make_pair( L, H ), X )
		( std::make_pair( L, C ), L )
		( std::make_pair( L, B ), L )
		( std::make_pair( L, K ), X )
		( std::make_pair( L, L ), L )
		( std::make_pair( L, M ), X )
		( std::make_pair( L, X ), X )
		( std::make_pair( L, U ), L )

		( std::make_pair( M, H ), M )
		( std::make_pair( M, C ), X )
		( std::make_pair( M, B ), M )
		( std::make_pair( M, K ), X )
		( std::make_pair( M, L ), X )
		( std::make_pair( M, M ), M )
		( std::make_pair( M, X ), X )
		( std::make_pair( M, U ), M )

		( std::make_pair( X, H ), X )
		( std::make_pair( X, C ), X )
		( std::make_pair( X, B ), X )
		( std::make_pair( X, K ), X )
		( std::make_pair( X, L ), X )
		( std::make_pair( X, M ), X )
		( std::make_pair( X, X ), X )
		( std::make_pair( X, U ), X )

		( std::make_pair( U, H ), H )
		( std::make_pair( U, C ), C )
		( std::make_pair( U, B ), B )
		( std::make_pair( U, K ), K )
		( std::make_pair( U, L ), L )
		( std::make_pair( U, M ), M )
		( std::make_pair( U, X ), X )
		( std::make_pair( U, U ), U )
	;

	return table.find( std::make_pair( _e1, _e2 ) )->second;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


CubeTerm::Enum
CubeTerm::complement( CubeTerm::Enum _e )
{
	static std::map< Enum, Enum > table = boost::assign::map_list_of
		( H, L )
		( C, M )
		( B, K )
		( K, B )
		( L, H )
		( M, C )
		( X, U )
		( U, X )
	;

	return table.find( _e )->second;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


CubeTerm::Enum
CubeTerm::summation( CubeTerm::Enum _e1, CubeTerm::Enum _e2 )
{
	static std::map< std::pair< Enum, Enum >, Enum > table = boost::assign::map_list_of
		( std::make_pair( H, H ), U )
		( std::make_pair( H, C ), K )
		( std::make_pair( H, B ), M )
		( std::make_pair( H, K ), C )
		( std::make_pair( H, L ), X )
		( std::make_pair( H, M ), B )
		( std::make_pair( H, X ), L )
		( std::make_pair( H, U ), H )

		( std::make_pair( C, H ), K )
		( std::make_pair( C, C ), U )
		( std::make_pair( C, B ), L )
		( std::make_pair( C, K ), H )
		( std::make_pair( C, L ), B )
		( std::make_pair( C, M ), X )
		( std::make_pair( C, X ), M )
		( std::make_pair( C, U ), C )

		( std::make_pair( B, H ), M )
		( std::make_pair( B, C ), L )
		( std::make_pair( B, B ), U )
		( std::make_pair( B, K ), X )
		( std::make_pair( B, L ), C )
		( std::make_pair( B, M ), H )
		( std::make_pair( B, X ), K )
		( std::make_pair( B, U ), B )

		( std::make_pair( K, H ), C )
		( std::make_pair( K, C ), H )
		( std::make_pair( K, B ), X )
		( std::make_pair( K, K ), U )
		( std::make_pair( K, L ), M )
		( std::make_pair( K, M ), L )
		( std::make_pair( K, X ), B )
		( std::make_pair( K, U ), K )

		( std::make_pair( L, H ), X )
		( std::make_pair( L, C ), B )
		( std::make_pair( L, B ), C )
		( std::make_pair( L, K ), M )
		( std::make_pair( L, L ), U )
		( std::make_pair( L, M ), K )
		( std::make_pair( L, X ), H )
		( std::make_pair( L, U ), L )

		( std::make_pair( M, H ), B )
		( std::make_pair( M, C ), X )
		( std::make_pair( M, B ), H )
		( std::make_pair( M, K ), L )
		( std::make_pair( M, L ), K )
		( std::make_pair( M, M ), U )
		( std::make_pair( M, X ), C )
		( std::make_pair( M, U ), M )

		( std::make_pair( X, H ), L )
		( std::make_pair( X, C ), M )
		( std::make_pair( X, B ), K )
		( std::make_pair( X, K ), B )
		( std::make_pair( X, L ), H )
		( std::make_pair( X, M ), C )
		( std::make_pair( X, X ), U )
		( std::make_pair( X, U ), X )

		( std::make_pair( U, H ), H )
		( std::make_pair( U, C ), C )
		( std::make_pair( U, B ), B )
		( std::make_pair( U, K ), K )
		( std::make_pair( U, L ), L )
		( std::make_pair( U, M ), M )
		( std::make_pair( U, X ), X )
		( std::make_pair( U, U ), U )
	;

	return table.find( std::make_pair( _e1, _e2 ) )->second;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/

} // FuzzyLogicEngine

/*------      ------      ------      ------      ------      ------      ------      ------*/
