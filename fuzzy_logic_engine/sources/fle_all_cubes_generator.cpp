#include "ph/fle_ph.hpp"

#include "fuzzy_logic_engine/sources/fle_all_cubes_generator.hpp"

#include "fuzzy_logic_engine/sources/fle_input_cube_impl.hpp"

#include <cmath>

/*------      ------      ------      ------      ------      ------      ------      ------*/

namespace FuzzyLogicEngine
{

/*------      ------      ------      ------      ------      ------      ------      ------*/


AllCubesGenerator::AllCubesGenerator( const unsigned int _cubeLength )
	:	m_lastCube( new InputCubeImpl )
{
	m_currentCubeIt = m_allCombinations.begin();

	intializeCubesSequence( _cubeLength );
	reset();
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


InputCube const&
AllCubesGenerator::getNextCube() const
{
	if ( !isValid() )
		FLE_INTERNAL_ERROR;

	return *m_lastCube;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


void
AllCubesGenerator::next()
{
	++m_currentCubeIt;

	if ( !isValid() )
		return;

	updateCurrentCube();
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


bool
AllCubesGenerator::isValid() const
{
	return m_currentCubeIt != m_allCombinations.end();

}


/*------      ------      ------      ------      ------      ------      ------      ------*/


void
AllCubesGenerator::reset()
{
	m_currentCubeIt = m_allCombinations.begin();

	updateCurrentCube();
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


void
AllCubesGenerator::intializeCubesSequence( const unsigned int _cubeLength )
{
	std::vector< CubeTerm::Enum > alphabet( 3 );
	alphabet[ 0 ] = CubeTerm::H;
	alphabet[ 1 ] = CubeTerm::C;
	alphabet[ 2 ] = CubeTerm::B;

	InputTermsVector currentCombination( _cubeLength, alphabet.front() );

	InputTermsVector::iterator it = currentCombination.begin();

	while ( it != currentCombination.end() )
	{
		m_allCombinations.push_back( currentCombination );

		if ( *it != alphabet.back() )
			*it = CubeTerm::next( *it );
		else
		{
			do
			{
				++it;
			} while ( ( it != currentCombination.end() ) && ( *it == alphabet.back() ) );

			if ( it == currentCombination.end() )
				break;

			*it = CubeTerm::next( *it );

			std::fill( currentCombination.begin(), it, alphabet.front() );
			it = currentCombination.begin();
		}
	}

	if ( m_allCombinations.size() != std::pow( (long double)alphabet.size(), (int)_cubeLength ) )
		FLE_INTERNAL_ERROR;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


void
AllCubesGenerator::removeCurrentCube()
{
	m_currentCubeIt = m_allCombinations.erase( m_currentCubeIt );
	updateCurrentCube();
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


void
AllCubesGenerator::updateCurrentCube()
{
	if ( m_allCombinations.empty() || m_currentCubeIt == m_allCombinations.end() )
		return;

	InputTermsVector termsCopy( *m_currentCubeIt );
	static_cast< InputCubeImpl * >( m_lastCube.get() )->swap( termsCopy );
}


/*------      ------      ------      ------      ------      ------      ------      ------*/

} // FuzzyLogicEngine

/*------      ------      ------      ------      ------      ------      ------      ------*/
