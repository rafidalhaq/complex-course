#ifndef _FUZZY_LOGIC_ENGINE__INPUT_CUBE_
#define _FUZZY_LOGIC_ENGINE__INPUT_CUBE_

/*------      ------      ------      ------      ------      ------      ------      ------*/

#include "fuzzy_logic_engine/headers/fle_cube_term.hpp"

/*------      ------      ------      ------      ------      ------      ------      ------*/

namespace FuzzyLogicEngine
{

/*------      ------      ------      ------      ------      ------      ------      ------*/

class InputCube
	: public boost::noncopyable
{

	/*-----     -----     -----     -----      -----     -----*/

public:

	/*-----     -----     -----     -----      -----     -----*/

	virtual const unsigned int getTermsCount() const = 0;

	virtual const CubeTerm::Enum getCubeTerm( unsigned int _index ) const = 0;

	/*-----     -----     -----     -----      -----     -----*/

	virtual const unsigned int getRank() const = 0;

	/*-----     -----     -----     -----      -----     -----*/

	virtual const unsigned int calculateCodeDistance( InputCube const& _other ) const = 0;

	/*-----     -----     -----     -----      -----     -----*/

	// TODO: maybe, this ones should be moved to another place?

	virtual std::auto_ptr< const InputCube > intersect( InputCube const& _other ) const = 0;

	virtual std::auto_ptr< const InputCube > join( InputCube const& _other ) const = 0;

	virtual std::auto_ptr< const InputCube > complement( InputCube const& _other ) const = 0;

	virtual std::auto_ptr< const InputCube > summ( InputCube const& _other ) const = 0;

	// TODO: should be added 'absorbs' and 'bonds'?

	/*-----     -----     -----     -----      -----     -----*/

}; // class InputCube

/*------      ------      ------      ------      ------      ------      ------      ------*/

} // FuzzyLogicEngine

/*------      ------      ------      ------      ------      ------      ------      ------*/

#endif // _FUZZY_LOGIC_ENGINE__INPUT_CUBE_