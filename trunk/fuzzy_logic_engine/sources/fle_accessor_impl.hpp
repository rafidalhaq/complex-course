#ifndef _FUZZY_LOGIC_ENGINE__ACCESSOR_IMPL_
#define _FUZZY_LOGIC_ENGINE__ACCESSOR_IMPL_

/*------      ------      ------      ------      ------      ------      ------      ------*/

#include "fuzzy_logic_engine/headers/fle_accessor.hpp"

#include "fuzzy_logic_engine/sources/fle_knowledge_base_impl.hpp"
#include "fuzzy_logic_engine/sources/fle_lingua_variables_dictionary_impl.hpp"

/*------      ------      ------      ------      ------      ------      ------      ------*/

namespace FuzzyLogicEngine
{

/*------      ------      ------      ------      ------      ------      ------      ------*/

class AccessorImpl
	: public Accessor
{

	/*-----     -----     -----     -----      -----     -----*/

public:

	/*-----     -----     -----     -----      -----     -----*/

	/*virtual*/ KnowledgeBase const& getKnowledgeBase() const;

	/*virtual*/ LinguaVariablesDictionary const& getLinguaVariablesDictionary() const;

	/*-----     -----     -----     -----      -----     -----*/

	/*virtual*/ KnowledgeBase& getKnowledgeBaseModifying();

	/*virtual*/ LinguaVariablesDictionary & getLinguaVariablesDictionaryModifying();

	/*-----     -----     -----     -----      -----     -----*/

	// TODO: here will be the methods to do the production rules analysis

	/*-----     -----     -----     -----      -----     -----*/

private:

	/*-----     -----     -----     -----      -----     -----*/

	KnowledgeBaseImpl m_knowledgeBase;

	LinguaVariablesDictionaryImpl m_linguaVariablesDictionary;

	/*-----     -----     -----     -----      -----     -----*/

}; // class AccessorImpl

/*------      ------      ------      ------      ------      ------      ------      ------*/

} // FuzzyLogicEngine

/*------      ------      ------      ------      ------      ------      ------      ------*/

#endif // _FUZZY_LOGIC_ENGINE__ACCESSOR_IMPL_