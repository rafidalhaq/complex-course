#include "ph/fle_ph.hpp"

#include "fuzzy_logic_engine/sources/fle_accessor_impl.hpp"

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
