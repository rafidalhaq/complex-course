#include "ph/fle_ph.hpp"

#include "fuzzy_logic_engine/sources/fle_input_cube_impl.hpp"

#include <algorithm>

/*------      ------      ------      ------      ------      ------      ------      ------*/

namespace FuzzyLogicEngine
{

/*------      ------      ------      ------      ------      ------      ------      ------*/


const unsigned int
InputCubeImpl::getTermsCount() const
{
	return m_terms.size();
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


const CubeTerm::Enum
InputCubeImpl::getCubeTerm( unsigned int _index ) const
{
	return m_terms.at( _index );
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


const unsigned int
InputCubeImpl::getRank() const
{
	return termsCount( CubeTerm::X );
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


const unsigned int
InputCubeImpl::getUndefinedValuesCount() const
{
	return termsCount( CubeTerm::U );
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


const unsigned int
InputCubeImpl::calculateCodeDistance( InputCube const& _other ) const
{
	if ( _other.getTermsCount() != getTermsCount() )
		FLE_INTERNAL_ERROR_WITH_DESCRIPTION( "operation applied on cubes of different sizes" );

	InputCubeImpl const& otherImpl = static_cast< InputCubeImpl const& >( _other );
	unsigned int result = 0;
	permuteToGetBestMatching( otherImpl, &result );

	return result;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


void
InputCubeImpl::swap( InputTermsVectorNonConstRef _terms )
{
	m_terms.swap( _terms );
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


std::auto_ptr< const InputCube >
InputCubeImpl::intersect( InputCube const& _other ) const
{
	return makeNewCube( _other, &CubeTerm::intersection, true );
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


std::auto_ptr< const InputCube >
InputCubeImpl::join( InputCube const& _other ) const
{
	return makeNewCube( _other, &CubeTerm::conjunction, false );
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


std::auto_ptr< const InputCube >
InputCubeImpl::complement() const
{
	InputTermsVector result( getTermsCount() );
	for( unsigned int i = 0; i < getTermsCount(); ++i )
		result[ i ] = CubeTerm::complement( getCubeTerm( i ) ); 

	std::auto_ptr< InputCubeImpl > resultCube( new InputCubeImpl );
	resultCube->swap( result );
	return resultCube;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


std::auto_ptr< const InputCube >
InputCubeImpl::summ( InputCube const& _other ) const
{
	return makeNewCube( _other, &CubeTerm::summation, false );
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


std::auto_ptr< const InputCube >
InputCubeImpl::makeNewCube(
		InputCube const& _other
	,	InputCubeImpl::CubeTermTableMethod _method
	,	bool _returnNullIfTriggeredEmptyCube
) const
{
	if ( _other.getTermsCount() != getTermsCount() )
		FLE_INTERNAL_ERROR;

	InputCubeImpl const& otherImpl = static_cast< InputCubeImpl const& >( _other );
	InputTermsVector permuttedVector = permuteToGetBestMatching( otherImpl );

	InputTermsVector result( getTermsCount() );
	for( unsigned int i = 0; i < getTermsCount(); ++i )
	{
		result[ i ] = _method( permuttedVector[ i ], otherImpl.m_terms[ i ] );
		if ( result[ i ] == CubeTerm::U && _returnNullIfTriggeredEmptyCube )
			return std::auto_ptr< const InputCube >();
	}

	std::auto_ptr< InputCubeImpl > resultCube( new InputCubeImpl );
	resultCube->swap( result );
	return resultCube;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


const unsigned int
InputCubeImpl::termsCount( CubeTerm::Enum _term ) const
{
	struct Predicate
	{
		Predicate( CubeTerm::Enum _term )
			:	m_term( _term ) {}

		bool operator() ( CubeTerm::Enum _enum )
		{
			return _enum == m_term;
		}

		CubeTerm::Enum m_term;
	};

	return std::count_if( m_terms.begin(), m_terms.end(), Predicate( _term ) );
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


InputTermsVector
InputCubeImpl::permuteToGetBestMatching(
		InputCubeImpl const& _other
	,	unsigned int * _numberOfMatchingElements
) const
{
	InputTermsVector bestVariant( m_terms );
	unsigned int numberOfMatchingElements = 0;
	std::sort( bestVariant.begin(), bestVariant.end() );

	InputTermsVector currentVariant( bestVariant );
	unsigned int currentNumberOfMatchingElements;
	
	do
	{
		currentNumberOfMatchingElements = 0;
		for( unsigned int i = 0; i < m_terms.size(); ++i )
		{
			if ( currentVariant[ i ] == _other.m_terms[ i ] )
				++currentNumberOfMatchingElements;
		}
		if ( currentNumberOfMatchingElements > numberOfMatchingElements )
		{
			bestVariant = currentVariant;
			numberOfMatchingElements = currentNumberOfMatchingElements;
		}
	} while ( std::next_permutation( currentVariant.begin(), currentVariant.end() ) );

	if ( _numberOfMatchingElements )
		*_numberOfMatchingElements = numberOfMatchingElements;

	return bestVariant;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


std::auto_ptr< const InputCube >
InputCubeImpl::bond( InputCube const& _other ) const
{
	if ( _other.getTermsCount() != getTermsCount() )
		FLE_INTERNAL_ERROR;

	InputCubeImpl const& otherImpl = static_cast< InputCubeImpl const& >( _other );
	unsigned int equalTermsCount = 0;
	InputTermsVector permuttedVector = permuteToGetBestMatching( otherImpl, &equalTermsCount );

	if ( equalTermsCount != ( getTermsCount() - 1 ) )
		return std::auto_ptr< const InputCube >();

	InputTermsVector result( getTermsCount() );
	for( unsigned int i = 0; i < getTermsCount(); ++i )
	{
		result[ i ] = CubeTerm::conjunction( permuttedVector[ i ], otherImpl.m_terms[ i ] );
	}

	std::auto_ptr< InputCubeImpl > resultCube( new InputCubeImpl );
	resultCube->swap( result );
	return resultCube;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


std::auto_ptr< const InputCubeImpl >
InputCubeImpl::clone() const
{
	InputCubeImpl * newCube = new InputCubeImpl;
	newCube->m_terms.resize( m_terms.size() );
	std::copy( m_terms.begin(), m_terms.end(), newCube->m_terms.begin() );

	return std::auto_ptr< const InputCubeImpl >( newCube );
}


/*------      ------      ------      ------      ------      ------      ------      ------*/

} // FuzzyLogicEngine

/*------      ------      ------      ------      ------      ------      ------      ------*/
