#ifndef _FUZZY_LOGIC_ENGINE__CHECKS_LISTENER_
#define _FUZZY_LOGIC_ENGINE__CHECKS_LISTENER_

/*------      ------      ------      ------      ------      ------      ------      ------*/

#include "fuzzy_logic_engine/headers/fle_input_cube.hpp"
#include "fuzzy_logic_engine/headers/fle_output_term.hpp"

/*------      ------      ------      ------      ------      ------      ------      ------*/

namespace FuzzyLogicEngine
{

/*------      ------      ------      ------      ------      ------      ------      ------*/

class ChecksListener
	: public boost::noncopyable
{

	/*-----     -----     -----     -----      -----     -----*/

public:

	/*-----     -----     -----     -----      -----     -----*/

	virtual void onUncoveredCube( InputCube const& _cube ) = 0;

	virtual void onInconsistentCubes(
			InputCube const& _cube1, OutputTerm::Enum _outTerm1
		,	InputCube const& _cube2, OutputTerm::Enum _outTerm2
	) = 0;

	virtual void onRedundantCubes(
			InputCube const& _cube1
		,	InputCube const& _cube2
		,	OutputTerm::Enum _outTerm
	) = 0;

	virtual void onInconsistentTerm( OutputTerm::Enum _outTerm ) = 0;

	/*-----     -----     -----     -----      -----     -----*/

	// for consisnency analysis:

	virtual void onAdjacentCubes(
			InputCube const& _cube1, OutputTerm::Enum _outTerm1
		,	InputCube const& _cube2, OutputTerm::Enum _outTerm2
	) = 0;

	/*-----     -----     -----     -----      -----     -----*/

}; // class ChecksListener

/*------      ------      ------      ------      ------      ------      ------      ------*/

} // FuzzyLogicEngine

/*------      ------      ------      ------      ------      ------      ------      ------*/

#endif // _FUZZY_LOGIC_ENGINE__CHECKS_LISTENER_