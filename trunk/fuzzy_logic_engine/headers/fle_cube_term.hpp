#ifndef _FUZZY_LOGIC_ENGINE__CUBE_TERM_
#define _FUZZY_LOGIC_ENGINE__CUBE_TERM_

/*------      ------      ------      ------      ------      ------      ------      ------*/

namespace FuzzyLogicEngine
{

/*------      ------      ------      ------      ------      ------      ------      ------*/

struct CubeTerm
{

	/*-----     -----     -----     -----      -----     -----*/

	enum Enum
	{
			H
		,	C
		,	B
		,	K
		,	L
		,	M
		,	X
		,	U
	};

	/*-----     -----     -----     -----      -----     -----*/

	static bool isValidInputTerm( Enum _e )
	{
		return _e == H || _e == C || _e == B;
	}

	/*-----     -----     -----     -----      -----     -----*/

	static Enum fromShortString( QString const& _str )
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

	/*-----     -----     -----     -----      -----     -----*/

	static QString toShortString( Enum _enum )
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

	/*-----     -----     -----     -----      -----     -----*/

	static Enum concat( Enum _e1, Enum _e2 )
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

	/*-----     -----     -----     -----      -----     -----*/

	// the same will be for 'intersection', 'conjunction', 'complement', 'summation'
	// TODO: move implementation - consumes many place

	/*-----     -----     -----     -----      -----     -----*/

}; // struct CubeTerm

/*------      ------      ------      ------      ------      ------      ------      ------*/

} // FuzzyLogicEngine

/*------      ------      ------      ------      ------      ------      ------      ------*/

#endif // _FUZZY_LOGIC_ENGINE__CUBE_TERM_