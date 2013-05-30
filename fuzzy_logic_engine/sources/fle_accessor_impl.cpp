#include "ph/fle_ph.hpp"

#include "fuzzy_logic_engine/sources/fle_accessor_impl.hpp"

#include "fuzzy_logic_engine/headers/fle_knowledge_base.hpp"

#include "fuzzy_logic_engine/sources/fle_all_cubes_generator.hpp"

#include "fuzzy_logic_engine/sources/fle_input_cube_impl.hpp"

/*------      ------      ------      ------      ------      ------      ------      ------*/

namespace FuzzyLogicEngine
{

/*------      ------      ------      ------      ------      ------      ------      ------*/


KnowledgeBase const&
AccessorImpl::getKnowledgeBase() const
{
	return m_knowledgeBase;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


LinguaVariablesDictionary const&
AccessorImpl::getLinguaVariablesDictionary() const
{
	return m_linguaVariablesDictionary;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


KnowledgeBase &
AccessorImpl::getKnowledgeBaseModifying()
{
	return m_knowledgeBase;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


LinguaVariablesDictionary &
AccessorImpl::getLinguaVariablesDictionaryModifying()
{
	return m_linguaVariablesDictionary;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


bool
AccessorImpl::isCompleteKB( KnowledgeBase const& _knowledgeBase ) const
{
	std::auto_ptr< const InputCube > intersection;

	std::vector< InputTermsVector > allGeneratedCubes;
	InputTermsVector cubes;

	AllCubesGenerator generator( getLinguaVariablesDictionary().getInputLinguaVariablesCount() );

	for ( OutputTerm::Enum outTerm = OutputTerm::OH; outTerm != OutputTerm::Last; )
	{
		for( unsigned int i = 0; i < _knowledgeBase.getProductionRulesCount( outTerm ); ++i )
		{
			generator.reset();
			bool triggeredNonEmptyIntersect = false;
			for ( ; generator.isValid(); generator.next() )
			{
				intersection = generator.getNextCube().intersect( _knowledgeBase.getInputCube( outTerm, i ) );
				if ( intersection->getUndefinedValuesCount() == 0 )
				{
					triggeredNonEmptyIntersect = true;
					break;
				}
			}
			if ( !triggeredNonEmptyIntersect )
				return false;
		}
		outTerm = OutputTerm::next( outTerm );
	}

	return true;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


bool
AccessorImpl::isConsistentKB( KnowledgeBase const& _knowledgeBase ) const
{
	std::auto_ptr< const InputCube > intersection;

	for ( OutputTerm::Enum firstOutTerm = OutputTerm::OH; firstOutTerm != OutputTerm::B; )
	{
		for ( OutputTerm::Enum secondOutTerm = OutputTerm::next( firstOutTerm ); secondOutTerm != OutputTerm::Last; )
		{
			for( unsigned int i = 0; i < _knowledgeBase.getProductionRulesCount( firstOutTerm ); ++i )
			{
				for( unsigned int j = 0; j < _knowledgeBase.getProductionRulesCount( secondOutTerm ); ++j )
				{
					intersection = _knowledgeBase.getInputCube( firstOutTerm, i )
						.intersect( _knowledgeBase.getInputCube( secondOutTerm, j ) );
					if ( intersection->getUndefinedValuesCount() == 0 )
						return false;
				}
			}
			secondOutTerm = OutputTerm::next( secondOutTerm );
		}
		firstOutTerm = OutputTerm::next( firstOutTerm );
	}

	return true;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


bool
AccessorImpl::isMinimalKB( KnowledgeBase const& _knowledgeBase ) const
{
	std::auto_ptr< const InputCube > intersection;

	for ( OutputTerm::Enum outTerm = OutputTerm::OH; outTerm != OutputTerm::Last; )
	{
		const unsigned int rulesCount = _knowledgeBase.getProductionRulesCount( outTerm );
		for( unsigned int i = 0; i < rulesCount; ++i )
		{
			for( unsigned int j = 0; ( j < rulesCount ) && ( i != j ); ++j )
			{
				intersection = _knowledgeBase.getInputCube( outTerm, i ).intersect( _knowledgeBase.getInputCube( outTerm, j ) );
				if ( intersection->getUndefinedValuesCount() == 0 )
					return false;
			}
		}
		outTerm = OutputTerm::next( outTerm );
	}

	return true;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


bool
AccessorImpl::isCoherentKB( KnowledgeBase const& _knowledgeBase ) const
{
	std::auto_ptr< const InputCube > summ;
	const unsigned int cubesCount = m_linguaVariablesDictionary.getInputLinguaVariablesCount();
	std::set< unsigned int > significantVariables;

	for ( OutputTerm::Enum firstOutTerm = OutputTerm::OH; firstOutTerm != OutputTerm::B; )
	{
		for ( OutputTerm::Enum secondOutTerm = OutputTerm::next( firstOutTerm ); secondOutTerm != OutputTerm::Last; )
		{
			for( unsigned int i = 0; i < _knowledgeBase.getProductionRulesCount( firstOutTerm ); ++i )
			{
				for( unsigned int j = 0; j < _knowledgeBase.getProductionRulesCount( secondOutTerm ); ++j )
				{
					summ = _knowledgeBase.getInputCube( firstOutTerm, i )
						.summ( _knowledgeBase.getInputCube( secondOutTerm, j ) );
					if ( summ->getUndefinedValuesCount() == ( cubesCount - 1 ) )
					{
						unsigned int significantVariablePosition = 0;
						for( ; significantVariablePosition < cubesCount; ++significantVariablePosition )
							if ( summ->getCubeTerm( significantVariablePosition ) != CubeTerm::U )
								break;
						if ( significantVariables.count( significantVariablePosition ) == 0 )
							significantVariables.insert( significantVariablePosition );
					}
				}
			}
			secondOutTerm = OutputTerm::next( secondOutTerm );
		}
		firstOutTerm = OutputTerm::next( firstOutTerm );
	}

	return significantVariables.size() == cubesCount;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


namespace
{
	AccessorImpl s_Accessor;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


FUZZY_LOGIC_ENGINE_API
Accessor const&
getAccessor()
{
	return s_Accessor;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


FUZZY_LOGIC_ENGINE_API
Accessor &
getAccessorModifying()
{
	return s_Accessor;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/

} // FuzzyLogicEngine

/*------      ------      ------      ------      ------      ------      ------      ------*/
