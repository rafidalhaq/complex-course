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

	void reset();

	void removeCurrentCube();

	/*-----     -----     -----     -----      -----     -----*/

private:

	/*-----     -----     -----     -----      -----     -----*/

	void intializeCubesSequence( const unsigned int _cubeLength );

	void updateCurrentCube();

	/*-----     -----     -----     -----      -----     -----*/

	boost::scoped_ptr< InputCube > m_lastCube;

	std::list< InputTermsVector > m_allCombinations;

	typedef
		std::list< InputTermsVector >::iterator
		CubesIterator;

	CubesIterator m_currentCubeIt;

	/*-----     -----     -----     -----      -----     -----*/

}; // class AccessorImpl

/*------      ------      ------      ------      ------      ------      ------      ------*/

} // FuzzyLogicEngine

/*------      ------      ------      ------      ------      ------      ------      ------*/

#endif // _FUZZY_LOGIC_ENGINE__ALL_CUBES_GENERATOR_