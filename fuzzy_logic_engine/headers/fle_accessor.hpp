#ifndef _FUZZY_LOGIC_ENGINE__ACCESSOR_
#define _FUZZY_LOGIC_ENGINE__ACCESSOR_

/*------      ------      ------      ------      ------      ------      ------      ------*/

#include "fuzzy_logic_engine/headers/fle_export.hpp"

/*------      ------      ------      ------      ------      ------      ------      ------*/

namespace FuzzyLogicEngine
{

	class KnowledgeBase;
	class LinguaVariablesDictionary;

/*------      ------      ------      ------      ------      ------      ------      ------*/

class Accessor
	: public boost::noncopyable
{

	/*-----     -----     -----     -----      -----     -----*/

public:

	/*-----     -----     -----     -----      -----     -----*/

	virtual KnowledgeBase const& getKnowledgeBase() const = 0;

	virtual LinguaVariablesDictionary const& getLinguaVariablesDictionary() const = 0;

	/*-----     -----     -----     -----      -----     -----*/

	virtual KnowledgeBase& getKnowledgeBaseModifying() = 0;

	virtual LinguaVariablesDictionary & getLinguaVariablesDictionaryModifying() = 0;

	/*-----     -----     -----     -----      -----     -----*/

	virtual bool isCompleteKB( KnowledgeBase const& _knowledgeBase ) const = 0;

	virtual bool isConsistentKB( KnowledgeBase const& _knowledgeBase ) const = 0;

	virtual bool isMinimalKB( KnowledgeBase const& _knowledgeBase ) const = 0;

	virtual bool isCoherentKB( KnowledgeBase const& _knowledgeBase ) const = 0;

	/*-----     -----     -----     -----      -----     -----*/

}; // class Accessor

/*------      ------      ------      ------      ------      ------      ------      ------*/

// yep, not very good solution to differentiate modifying interfaces
// on the other hand, we don't have factory and writable interfaces pattern

FUZZY_LOGIC_ENGINE_API Accessor const& getAccessor();

FUZZY_LOGIC_ENGINE_API Accessor & getAccessorModifying();

/*------      ------      ------      ------      ------      ------      ------      ------*/

} // FuzzyLogicEngine

/*------      ------      ------      ------      ------      ------      ------      ------*/

#endif // _FUZZY_LOGIC_ENGINE__ACCESSOR_