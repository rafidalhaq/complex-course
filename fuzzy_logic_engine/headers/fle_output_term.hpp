#ifndef _FUZZY_LOGIC_ENGINE__OUTPUT_TERM_
#define _FUZZY_LOGIC_ENGINE__OUTPUT_TERM_

/*------      ------      ------      ------      ------      ------      ------      ------*/

namespace FuzzyLogicEngine
{

/*------      ------      ------      ------      ------      ------      ------      ------*/

struct OutputTerm
{

	/*-----     -----     -----     -----      -----     -----*/

	enum Enum
	{
			OH	= 1
		,	H	= 2
		,	C	= 3
		,	D	= 4
		,	B	= 5

		,	Last
	};

	/*-----     -----     -----     -----      -----     -----*/

	static Enum fromShortString( QString const& _str )
	{
		static QHash< QString, Enum > table;
		if ( table.empty() )
		{
			table[ "OH" ] = OH;
			table[ "H" ] = H;
			table[ "C" ] = C;
			table[ "D" ] = D;
			table[ "B" ] = B;
		}

		if ( !table.contains( _str ) )
			throw std::exception();

		return table.value( _str );
	}

	/*-----     -----     -----     -----      -----     -----*/

	static QString toShortString( Enum _enum )
	{
		static QHash< Enum, QString > table;
		if ( table.empty() )
		{
			table[ OH ] = "OH";
			table[ H ] = "H";
			table[ C ] = "C";
			table[ D ] = "D";
			table[ B ] = "B";
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

}; // struct OutputTerm

/*------      ------      ------      ------      ------      ------      ------      ------*/

} // FuzzyLogicEngine

/*------      ------      ------      ------      ------      ------      ------      ------*/

#endif // _FUZZY_LOGIC_ENGINE__OUTPUT_TERM_