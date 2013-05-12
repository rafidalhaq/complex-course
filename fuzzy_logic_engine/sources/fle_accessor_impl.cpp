#include "ph/fle_ph.hpp"

#include "fuzzy_logic_engine/sources/fle_accessor_impl.hpp"

#include "fuzzy_logic_engine/headers/fle_knowledge_base.hpp"

#include "fuzzy_logic_engine/sources/fle_all_cubes_generator.hpp"

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
	for ( OutputTerm::Enum outTerm = OutputTerm::OH; outTerm != OutputTerm::Last; )
	{
		for( unsigned int i = 0; i < _knowledgeBase.getProductionRulesCount( outTerm ); ++i )
		{
			AllCubesGenerator generator( getLinguaVariablesDictionary().getInputLinguaVariablesCount() );
			bool triggeredNonEmptyIntersect = false;
			for ( ; generator.isValid(); generator.next() )
			{
				if ( generator.getNextCube().intersect( _knowledgeBase.getInputCube( outTerm, i ) ).get() )
				{
					triggeredNonEmptyIntersect = true;
					break;
				}
			}
			if ( !triggeredNonEmptyIntersect )
				return false;
		}
		outTerm = static_cast< OutputTerm::Enum >( outTerm + 1 );
	}

	return true;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


bool
AccessorImpl::isConsistentKB( KnowledgeBase const& _knowledgeBase ) const
{
	for ( OutputTerm::Enum firstOutTerm = OutputTerm::OH; firstOutTerm != OutputTerm::B; )
	{
		for ( OutputTerm::Enum secondOutTerm = OutputTerm::H; secondOutTerm != OutputTerm::Last; )
		{
			for( unsigned int i = 0; i < _knowledgeBase.getProductionRulesCount( firstOutTerm ); ++i )
			{
				for( unsigned int j = 0; j < _knowledgeBase.getProductionRulesCount( secondOutTerm ); ++j )
				{
					if ( _knowledgeBase.getInputCube( firstOutTerm, i )
						.intersect( _knowledgeBase.getInputCube( secondOutTerm, j ) )
						.get()
					)
						return false;
				}
			}
			secondOutTerm = static_cast< OutputTerm::Enum >( secondOutTerm + 1 );
		}
		firstOutTerm = static_cast< OutputTerm::Enum >( firstOutTerm + 1 );
	}

	return true;
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
