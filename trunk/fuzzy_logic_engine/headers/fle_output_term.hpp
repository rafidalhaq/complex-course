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
			OH
		,	H
		,	C
		,	D
		,	B
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

}; // struct OutputTerm

/*------      ------      ------      ------      ------      ------      ------      ------*/

} // FuzzyLogicEngine

/*------      ------      ------      ------      ------      ------      ------      ------*/

#endif // _FUZZY_LOGIC_ENGINE__OUTPUT_TERM_