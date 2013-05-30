#include "ph/fle_ph.hpp"

#include "fuzzy_logic_engine/sources/fle_knowledge_base_impl.hpp"
#include "fuzzy_logic_engine/sources/fle_input_cube_impl.hpp"

#include <algorithm>

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


unsigned int
KnowledgeBaseImpl::addProductionRule( InputTermsVectorNonConstRef _inputs, OutputTerm::Enum _outTerm )
{
	InputTermsVector inputTerms( _inputs );

	unsigned int insertedCount = 0;

	std::sort( inputTerms.begin(), inputTerms.end() );

	if ( m_coveredTerms[ _outTerm ].count( inputTerms ) == 0 )
	{
		m_coveredTerms[ _outTerm ].insert( inputTerms );
		++insertedCount;
	}
	else
		return 0;

	while( std::next_permutation( inputTerms.begin(), inputTerms.end() ) )
	{
		if ( m_coveredTerms[ _outTerm ].count( inputTerms ) == 0 )
		{
			m_coveredTerms[ _outTerm ].insert( inputTerms );
			++insertedCount;
		}
	}

	if ( insertedCount != 0 )
	{
		std::auto_ptr< InputCubeImpl > newCube( new InputCubeImpl );
		newCube->swap( _inputs );
		m_rules.insert( std::make_pair( _outTerm, newCube.release() ) );
	}

	return insertedCount;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


void
KnowledgeBaseImpl::clear()
{
	m_rules.clear();
	m_coveredTerms.clear();
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


KnowledgeBase::RulesVector
KnowledgeBaseImpl::getAllRulesConsideringPermutations() const
{
	KnowledgeBase::RulesVector rulesVector;

	for(
			CoveredTermsMap::const_iterator outTermsIt = m_coveredTerms.begin()
		;	outTermsIt != m_coveredTerms.end()
		;	++outTermsIt
	)
	{
		for (
				CoveredTermsMap::mapped_type::const_iterator vectorsIt = outTermsIt->second.begin()
			;	vectorsIt != outTermsIt->second.end()
			;	++vectorsIt
		)
		{
			rulesVector.push_back( std::make_pair( *vectorsIt, outTermsIt->first ) );
		}
	}

	return rulesVector;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/

} // FuzzyLogicEngine

/*------      ------      ------      ------      ------      ------      ------      ------*/
