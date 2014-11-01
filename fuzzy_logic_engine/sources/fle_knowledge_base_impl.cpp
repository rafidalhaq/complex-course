#include "ph/fle_ph.hpp"

#include "fuzzy_logic_engine/sources/fle_knowledge_base_impl.hpp"

#include <algorithm>

#include <boost/unordered_map.hpp> 

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
		FLE_INTERNAL_ERROR;

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

	m_minimizedKB.reset();

	return insertedCount;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


void
KnowledgeBaseImpl::clear()
{
	m_rules.clear();
	m_coveredTerms.clear();
	m_minimizedKB.reset();
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

	struct CubeInfo
	{
		int m_countH, m_countC, m_countB;

		CubeInfo()
			:	m_countH( 0 )
			,	m_countC( 0 )
			,	m_countB( 0 )
		{}

		static CubeInfo create( const InputCube& _ic )
		{
			CubeInfo info;
			for( unsigned int i = 0; i < _ic.getTermsCount(); ++i )
			{
				switch ( _ic.getCubeTerm( i ) )
				{
				case CubeTerm::H:
					++info.m_countH;
					break;
				case CubeTerm::C:
					++info.m_countC;
					break;
				case CubeTerm::B:
					++info.m_countB;
					break;
				default:
					break;
				}
			}
			return info;
		}
	};


/*------      ------      ------      ------      ------      ------      ------      ------*/


KnowledgeBase const&
KnowledgeBaseImpl::getMinimizedKnowledgeBase() const
{
	if ( m_minimizedKB )
		return *m_minimizedKB;

	m_minimizedKB.reset( new KnowledgeBaseImpl );

	struct CubeBondPossibilityChecker
	{
		// bond is possible if cubes differ by one place
		// that is, for input terms (three possible), when
		// count of one is equal, and count of another twos' differs by one
		bool operator () ( const CubeInfo& _ic1, const CubeInfo& _ic2 ) const
		{
			return	( _ic1.m_countH == _ic2.m_countH ) && ( _ic1.m_countC == _ic2.m_countC ) && ( _ic1.m_countB == _ic2.m_countB )
				||	( _ic1.m_countH == _ic2.m_countH ) && ( abs( _ic1.m_countC - _ic2.m_countC ) == 1 ) && ( abs( _ic1.m_countB - _ic2.m_countB ) == 1 )
				||	( _ic1.m_countC == _ic2.m_countC ) && ( abs( _ic1.m_countH - _ic2.m_countH ) == 1 ) && ( abs( _ic1.m_countB - _ic2.m_countB ) == 1 )
				||	( _ic1.m_countB == _ic2.m_countB ) && ( abs( _ic1.m_countC - _ic2.m_countC ) == 1 ) && ( abs( _ic1.m_countH - _ic2.m_countH ) == 1 )
			;

		}
	};

	struct CubeInfoHasher
	{
		// it is really necessary to return the same hash value all the times
		// to get necessary behavior
		std::size_t operator () ( const CubeInfo& _ic ) const
		{
			return 0;
		}
	};

	typedef
		boost::unordered_multimap< CubeInfo, boost::shared_ptr< const InputCubeImpl >, CubeInfoHasher, CubeBondPossibilityChecker >
		MultimapToBond;

	struct MultimapToBondDebugPrinter
	{
		static QString print ( MultimapToBond const& _map )
		{
			QString result;
			for( MultimapToBond::const_iterator itint = _map.begin(); itint != _map.end(); )
			{
				std::pair< MultimapToBond::const_iterator, MultimapToBond::const_iterator > boundCubesInt
					= _map.equal_range( itint->first );
				for( ; boundCubesInt.first != boundCubesInt.second; ++boundCubesInt.first )
				{
					for( unsigned int i = 0; i < boundCubesInt.first->second->getTermsCount(); ++i )
						result += FuzzyLogicEngine::CubeTerm::toShortString(
							boundCubesInt.first->second->getCubeTerm( i )
						);
					result += ", ";
				}
				if ( itint != boundCubesInt.second )
					itint = boundCubesInt.second;
				else
					++itint;
				result += " :::: ";
			}
			return result;
		}
	};

	MultimapToBond m_bondsMultimap;

	for ( OutputTerm::Enum outTerm = OutputTerm::OH; outTerm != OutputTerm::Last; )
	{
		{
			std::pair< ProductionRulesMap::const_iterator, ProductionRulesMap::const_iterator > rules
				= m_rules.equal_range( outTerm );
			for( ProductionRulesMap::const_iterator it = rules.first; it != rules.second; ++it )
			{
				m_bondsMultimap.insert(
					std::make_pair( CubeInfo::create( *it->second ), it->second )
				);
			}
		}

		// now, m_bondsMultimap holds cubes sorted by the bond possibility
		// they're accessible by equal_range

		// for debugging purposes - boost::unordered doesn't have visualizer
#ifdef _DEBUG
		{
			QString result = MultimapToBondDebugPrinter::print( m_bondsMultimap );
			result.isEmpty();
		}
#endif

		for( MultimapToBond::const_iterator it = m_bondsMultimap.begin(); it != m_bondsMultimap.end(); )
		{
			std::pair< MultimapToBond::iterator, MultimapToBond::iterator > boundCubes
				= m_bondsMultimap.equal_range( it->first );
			MultimapToBond::iterator it1 = boundCubes.first, it2 = boundCubes.first;
			std::auto_ptr< const InputCube > cube;
			bool triggeredReplacement = false;
			while( it1 != boundCubes.second )
			{
				for( ; it2 != boundCubes.second; ++it2 )
				{
					if ( it1 == it2 )
						continue;
					cube = it1->second->bond( * it2->second );
					if( cube.get() && ( cube->getRank() == 1 ) )
					{
						CubeInfo info = it->first;
						m_bondsMultimap.erase( it1 );
						m_bondsMultimap.erase( it2 );
						m_bondsMultimap.insert(
							std::make_pair( info, static_cast< const InputCubeImpl * >( cube.release() ) )
						);
						boundCubes = m_bondsMultimap.equal_range( info );
						it1 = boundCubes.first;
						it2 = boundCubes.first;
						triggeredReplacement = true;

						// for debugging purposes - boost::unordered doesn't have visualizer
#ifdef _DEBUG
						QString result = MultimapToBondDebugPrinter::print( m_bondsMultimap );
#endif


						break;
					}
				}
				if ( !triggeredReplacement )
					++it1;
				else
					triggeredReplacement = false;
			}
			if ( it != boundCubes.second )
				it = boundCubes.second;
			else
				++it;
		}
	
		// for debugging purposes - boost::unordered doesn't have visualizer
#ifdef _DEBUG
		{
			QString result = MultimapToBondDebugPrinter::print( m_bondsMultimap );
			result.isEmpty();
		}
#endif

		for( MultimapToBond::const_iterator it = m_bondsMultimap.begin(); it != m_bondsMultimap.end(); ++it )
		{
			m_minimizedKB->m_rules.insert( std::make_pair( outTerm, it->second ) );
		}

		outTerm = OutputTerm::next( outTerm );
		m_bondsMultimap.clear();
	}

	return *m_minimizedKB;
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
