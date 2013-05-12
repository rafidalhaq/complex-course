#include "ph/fle_ph.hpp"

#include "fuzzy_logic_engine/sources/fle_all_cubes_generator.hpp"

#include "fuzzy_logic_engine/sources/fle_input_cube_impl.hpp"

/*------      ------      ------      ------      ------      ------      ------      ------*/

namespace FuzzyLogicEngine
{

/*------      ------      ------      ------      ------      ------      ------      ------*/


AllCubesGenerator::AllCubesGenerator( const unsigned int _cubeLength )
	:	m_cubeLength( _cubeLength )
	,	m_terms( _cubeLength, CubeTerm::H )
	,	m_currentHoldingValueIndex( 0 )
	,	m_currentIncrementingValueIndex( 1 )
{
	m_lastCube.reset( new InputCubeImpl );

	InputTermsVector termsCopy( m_terms );
	static_cast< InputCubeImpl * >( m_lastCube.get() )->swap( termsCopy );

}


/*------      ------      ------      ------      ------      ------      ------      ------*/


InputCube const&
AllCubesGenerator::getNextCube() const
{
	if ( !isValid() )
		throw std::exception();

	return *m_lastCube;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


void
AllCubesGenerator::next()
{
	if ( !isValid() )
		return;

	// if next value at current idx is not valid - go to next
	if ( !CubeTerm::isValidInputTerm(
		static_cast< CubeTerm::Enum >( m_terms[ m_currentIncrementingValueIndex ] + 1 )
		)
	)
		// if that was the last - reset to the next holding one
		if ( ( m_currentIncrementingValueIndex + 1 ) == m_cubeLength )
			// if holding value index was the last - mark as finished
			if ( ( m_currentHoldingValueIndex + 1 ) == m_cubeLength )
			{
				m_currentHoldingValueIndex = m_currentIncrementingValueIndex = 0;
				return;
			}
			else
			{
				m_currentIncrementingValueIndex = 0;
				++m_currentHoldingValueIndex;
			}

	m_terms[ m_currentIncrementingValueIndex ]
		= static_cast< CubeTerm::Enum >( m_terms[ m_currentIncrementingValueIndex ] + 1 );
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


bool
AllCubesGenerator::isValid() const
{
	return m_currentHoldingValueIndex == m_currentIncrementingValueIndex;

}


/*------      ------      ------      ------      ------      ------      ------      ------*/

} // FuzzyLogicEngine

/*------      ------      ------      ------      ------      ------      ------      ------*/
