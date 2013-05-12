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

	static Enum fromShortString( QString const& _str );

	static QString toShortString( Enum _enum );

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