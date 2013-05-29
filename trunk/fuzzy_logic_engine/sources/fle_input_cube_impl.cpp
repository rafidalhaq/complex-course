#include "ph/fle_ph.hpp"

#include "fuzzy_logic_engine/sources/fle_input_cube_impl.hpp"

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
		throw std::exception();

	unsigned int result = 0;
	for( unsigned int i = 0; i < getTermsCount(); ++i )
		if ( getCubeTerm( i ) != _other.getCubeTerm( i ) )
			++ result;

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
	return makeNewCube( _other, &CubeTerm::intersection );
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


std::auto_ptr< const InputCube >
InputCubeImpl::join( InputCube const& _other ) const
{
	return makeNewCube( _other, &CubeTerm::conjunction );
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
	return makeNewCube( _other, &CubeTerm::summation );
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


std::auto_ptr< const InputCube >
InputCubeImpl::makeNewCube( InputCube const& _other, InputCubeImpl::CubeTermTableMethod _method ) const
{
	if ( _other.getTermsCount() != getTermsCount() )
		throw std::exception();

	InputTermsVector result( getTermsCount() );
	for( unsigned int i = 0; i < getTermsCount(); ++i )
	{
		result[ i ] = _method( getCubeTerm( i ), _other.getCubeTerm( i ) );
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

} // FuzzyLogicEngine

/*------      ------      ------      ------      ------      ------      ------      ------*/
