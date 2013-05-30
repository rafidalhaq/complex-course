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
			H	= 1
		,	C	= 2
		,	B	= 3
		,	K	= 4
		,	L	= 5
		,	M	= 6
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
			table[ "h" ] = H;
			table[ "C" ] = C;
			table[ "c" ] = C;
			table[ "B" ] = B;
			table[ "b" ] = B;
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

	static Enum next( Enum const _val )
	{
		return static_cast< Enum >( _val + 1 );
	}

	/*-----     -----     -----     -----      -----     -----*/

	static Enum concat( Enum _e1, Enum _e2 );

	/*-----     -----     -----     -----      -----     -----*/

	static Enum intersection( Enum _e1, Enum _e2 );

	static Enum conjunction( Enum _e1, Enum _e2 );

	static Enum complement( Enum _e );

	static Enum summation( Enum _e1, Enum _e2 );

	/*-----     -----     -----     -----      -----     -----*/

}; // struct CubeTerm


/*------      ------      ------      ------      ------      ------      ------      ------*/

} // FuzzyLogicEngine

/*------      ------      ------      ------      ------      ------      ------      ------*/

#endif // _FUZZY_LOGIC_ENGINE__CUBE_TERM_