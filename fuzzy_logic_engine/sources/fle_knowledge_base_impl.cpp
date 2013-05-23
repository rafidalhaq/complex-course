#include "ph/fle_ph.hpp"

#include "fuzzy_logic_engine/sources/fle_knowledge_base_impl.hpp"
#include "fuzzy_logic_engine/sources/fle_input_cube_impl.hpp"

/*------      ------      ------      ------      ------      ------      ------      ------*/

namespace FuzzyLogicEngine
{

/*------      ------      ------      ------      ------      ------      ------      ------*/


const unsigned int
KnowledgeBaseImpl::getProductionRulesCount() const
{
	return m_rules.size();
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


const unsigned int
KnowledgeBaseImpl::getProductionRulesCount( OutputTerm::Enum _term ) const
{
	std::pair< ProductionRulesMap::const_iterator, ProductionRulesMap::const_iterator > rules
		= m_rules.equal_range( _term );
	return std::distance( rules.first, rules.second );
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


InputCube const&
KnowledgeBaseImpl::getInputCube( OutputTerm::Enum _term, const unsigned int _index ) const
{
	std::pair< ProductionRulesMap::const_iterator, ProductionRulesMap::const_iterator > rules
		= m_rules.equal_range( _term );
	std::advance( rules.first, _index );

	if ( rules.first == m_rules.end() )
		throw std::exception();

	return * rules.first->second;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


void
KnowledgeBaseImpl::addProductionRule( InputTermsVectorNonConstRef _inputs, OutputTerm::Enum _outTerm )
{
	std::auto_ptr< InputCubeImpl > newCube( new InputCubeImpl );
	newCube->swap( _inputs );
	m_rules.insert( std::make_pair( _outTerm, newCube.release() ) );
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


void
KnowledgeBaseImpl::removeProductionRule( OutputTerm::Enum _term, const unsigned int _index )
{
	std::pair< ProductionRulesMap::const_iterator, ProductionRulesMap::const_iterator > rules
		= m_rules.equal_range( _term );

	std::advance( rules.first, _index );

	if ( rules.first == m_rules.end() )
		throw std::exception();

	m_rules.erase( rules.first );
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


void
KnowledgeBaseImpl::clear()
{
	m_rules.clear();
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


const unsigned int
KnowledgeBaseImpl::calculateConjunctionsCount() const
{
	unsigned int result = 0;
	for ( ProductionRulesMap::const_iterator it = m_rules.begin(); it != m_rules.end(); ++it )
	{
		result += calculateConjunctionsCount( it->first );
	}
	return result;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


const unsigned int
KnowledgeBaseImpl::calculateConjunctionsCount( OutputTerm::Enum _term ) const
{
	// TODO
	return 0;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


const unsigned int
KnowledgeBaseImpl::calculateConditionsCount() const
{
	// CHECKME: calculation doesn't consider conjunctions count
	unsigned int result = 0;
	for ( ProductionRulesMap::const_iterator it = m_rules.begin(); it != m_rules.end(); ++it )
	{
		InputCube const& cube = * it->second;
		for( unsigned int i = 0; i < cube.getTermsCount(); ++i )
		{
			CubeTerm::Enum term = cube.getCubeTerm( i );
			if ( term != CubeTerm::X && term != CubeTerm::U )
				++result;
		}
	}
	return result;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


boost::shared_ptr< KnowledgeBase >
KnowledgeBaseImpl::createCompactAndMinimizedKnowledgeBase()
{
	// TODO
	return boost::shared_ptr< KnowledgeBase >();
}


/*------      ------      ------      ------      ------      ------      ------      ------*/

} // FuzzyLogicEngine

/*------      ------      ------      ------      ------      ------      ------      ------*/
