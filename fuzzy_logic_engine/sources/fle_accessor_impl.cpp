#include "ph/fle_ph.hpp"

#include "fuzzy_logic_engine/sources/fle_accessor_impl.hpp"

#include "fuzzy_logic_engine/headers/fle_knowledge_base.hpp"

#include "fuzzy_logic_engine/sources/fle_all_cubes_generator.hpp"

#include "fuzzy_logic_engine/sources/fle_input_cube_impl.hpp"

#include "fuzzy_logic_engine/headers/fle_checks_listener.hpp"

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
AccessorImpl::isCompleteKB(
		KnowledgeBase const& _knowledgeBase 
	,	boost::optional< ChecksListener & > _listener
) const
{
	AllCubesGenerator generator( getLinguaVariablesDictionary().getInputLinguaVariablesCount() );

	for ( OutputTerm::Enum outTerm = OutputTerm::OH; outTerm != OutputTerm::Last; )
	{
		for( unsigned int i = 0; i < _knowledgeBase.getProductionRulesCount( outTerm ); ++i )
		{
			generator.reset();
			while ( generator.isValid() )
			{
				if ( generator.getNextCube().intersect( _knowledgeBase.getInputCube( outTerm, i ) ).get() )
					generator.removeCurrentCube();
				else
					generator.next();
			}
		}
		outTerm = OutputTerm::next( outTerm );
	}

	generator.reset();
	bool result = !generator.isValid();

	if ( _listener )
	{
		for ( ; generator.isValid(); generator.next() )
		{
			_listener->onUncoveredCube( generator.getNextCube() );
		}
	}

	return result;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


bool
AccessorImpl::isConsistentKB(
		KnowledgeBase const& _knowledgeBase 
	,	boost::optional< ChecksListener & > _listener
) const
{
	bool result = true;

	for ( OutputTerm::Enum firstOutTerm = OutputTerm::OH; firstOutTerm != OutputTerm::B; )
	{
		for ( OutputTerm::Enum secondOutTerm = OutputTerm::next( firstOutTerm ); secondOutTerm != OutputTerm::Last; )
		{
			for( unsigned int i = 0; i < _knowledgeBase.getProductionRulesCount( firstOutTerm ); ++i )
			{
				for( unsigned int j = 0; j < _knowledgeBase.getProductionRulesCount( secondOutTerm ); ++j )
				{
					if ( _knowledgeBase.getInputCube( firstOutTerm, i )
						.intersect( _knowledgeBase.getInputCube( secondOutTerm, j ) ).get()
					)
					{
						if ( _listener )
							_listener->onInconsistentCubes(
									_knowledgeBase.getInputCube( firstOutTerm, i ), firstOutTerm
								,	_knowledgeBase.getInputCube( secondOutTerm, j ), secondOutTerm
							);

						result = false;
					}
				}
			}
			secondOutTerm = OutputTerm::next( secondOutTerm );
		}
		firstOutTerm = OutputTerm::next( firstOutTerm );
	}

	return result;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


bool
AccessorImpl::isMinimalKB(
		KnowledgeBase const& _knowledgeBase 
	,	boost::optional< ChecksListener & > _listener
) const
{
	bool result = true;

	for ( OutputTerm::Enum outTerm = OutputTerm::OH; outTerm != OutputTerm::Last; )
	{
		const unsigned int rulesCount = _knowledgeBase.getProductionRulesCount( outTerm );
		for( unsigned int i = 0; i < rulesCount; ++i )
		{
			for( unsigned int j = 0; ( j < rulesCount ) && ( i != j ); ++j )
			{
				if ( _knowledgeBase.getInputCube( outTerm, i ).intersect( _knowledgeBase.getInputCube( outTerm, j ) ).get() )
				{
					if ( _listener )
						_listener->onRedundantCubes(
								_knowledgeBase.getInputCube( outTerm, i )
							,	_knowledgeBase.getInputCube( outTerm, j )
							,	outTerm
						);

					result = false;
				}
			}
		}
		outTerm = OutputTerm::next( outTerm );
	}

	return result;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


bool
AccessorImpl::isCoherentKB(
		KnowledgeBase const& _knowledgeBase 
	,	boost::optional< ChecksListener & > _listener
) const
{
	std::auto_ptr< const InputCube > summ;
	const unsigned int variablesCount = m_linguaVariablesDictionary.getInputLinguaVariablesCount();
	std::set< OutputTerm::Enum > coherents;

	for ( OutputTerm::Enum firstOutTerm = OutputTerm::OH; firstOutTerm != OutputTerm::B; )
	{
		for ( OutputTerm::Enum secondOutTerm = OutputTerm::next( firstOutTerm ); secondOutTerm != OutputTerm::Last; )
		{
			for( unsigned int i = 0; i < _knowledgeBase.getProductionRulesCount( firstOutTerm ); ++i )
			{
				for( unsigned int j = 0; j < _knowledgeBase.getProductionRulesCount( secondOutTerm ); ++j )
				{
					InputCube const& firstInCube = _knowledgeBase.getInputCube( firstOutTerm, i );
					InputCube const& secondInCube = _knowledgeBase.getInputCube( secondOutTerm, j );
					summ = firstInCube.summ( secondInCube );
					if ( summ->getUndefinedValuesCount() == ( variablesCount - 1 ) )
					{
						coherents.insert( firstOutTerm );
						coherents.insert( secondOutTerm );
						if ( _listener )
							_listener->onAdjacentCubes( firstInCube, firstOutTerm, secondInCube, secondOutTerm );
					}
				}
			}
			secondOutTerm = OutputTerm::next( secondOutTerm );
		}
		firstOutTerm = OutputTerm::next( firstOutTerm );
	}

	const bool result = coherents.size() == OutputTerm::Count;

	if ( !result && _listener )
	{
		for ( OutputTerm::Enum outTerm = OutputTerm::OH; outTerm != OutputTerm::Last; )
		{
			if ( !coherents.count( outTerm ) )
				_listener->onInconsistentTerm( outTerm );
			outTerm = OutputTerm::next( outTerm );
		}
	}

	return result;
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
