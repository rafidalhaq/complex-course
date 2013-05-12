#ifndef _FUZZY_LOGIC_ENGINE__ALL_CUBES_GENERATOR_
#define _FUZZY_LOGIC_ENGINE__ALL_CUBES_GENERATOR_

/*------      ------      ------      ------      ------      ------      ------      ------*/

#include "fuzzy_logic_engine/headers/fle_input_cube.hpp"
#include "fuzzy_logic_engine/headers/fle_typedefs.hpp"

/*------      ------      ------      ------      ------      ------      ------      ------*/

namespace FuzzyLogicEngine
{

/*------      ------      ------      ------      ------      ------      ------      ------*/

class AllCubesGenerator
{

	/*-----     -----     -----     -----      -----     -----*/

public:

	/*-----     -----     -----     -----      -----     -----*/

	AllCubesGenerator( const unsigned int _cubeLength );

	/*-----     -----     -----     -----      -----     -----*/

	InputCube const& getNextCube() const;

	void next();

	bool isValid() const;

	/*-----     -----     -----     -----      -----     -----*/

private:

	/*-----     -----     -----     -----      -----     -----*/

	boost::scoped_ptr< InputCube > m_lastCube;

	InputTermsVector m_terms;

	const unsigned int m_cubeLength;

	unsigned int m_currentHoldingValueIndex, m_currentIncrementingValueIndex;

	/*-----     -----     -----     -----      -----     -----*/

}; // class AccessorImpl

/*------      ------      ------      ------      ------      ------      ------      ------*/

} // FuzzyLogicEngine

/*------      ------      ------      ------      ------      ------      ------      ------*/

#endif // _FUZZY_LOGIC_ENGINE__ALL_CUBES_GENERATOR_