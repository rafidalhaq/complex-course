#ifndef _FUZZY_LOGIC_ENGINE__KNOWLEDGE_BASE_IMPL_
#define _FUZZY_LOGIC_ENGINE__KNOWLEDGE_BASE_IMPL_

/*------      ------      ------      ------      ------      ------      ------      ------*/

#include "fuzzy_logic_engine/headers/fle_knowledge_base.hpp"

/*------      ------      ------      ------      ------      ------      ------      ------*/

namespace FuzzyLogicEngine
{

/*------      ------      ------      ------      ------      ------      ------      ------*/

class KnowledgeBaseImpl
	: public KnowledgeBase
{

	/*-----     -----     -----     -----      -----     -----*/

public:

	/*-----     -----     -----     -----      -----     -----*/

	/*virtual*/ const unsigned int getProductionRulesCount() const;

	/*virtual*/ const unsigned int getProductionRulesCount( OutputTerm::Enum _term ) const;

	/*virtual*/ InputCube const& getInputCube( OutputTerm::Enum _term, const unsigned int _index ) const;

	/*-----     -----     -----     -----      -----     -----*/

	// attention: _inputs will be cleared after the call!
	/*virtual*/ void addProductionRule(
			InputTermsVectorNonConstRef _inputs
		,	OutputTerm::Enum _outTerm
	);

	/*-----     -----     -----     -----      -----     -----*/

	/*virtual*/ void removeProductionRule( OutputTerm::Enum _term, const unsigned int _index );

	/*virtual*/ void clear();

	/*-----     -----     -----     -----      -----     -----*/

	/*virtual*/ const unsigned int calculateConjunctionsCount() const;

	/*virtual*/ const unsigned int calculateConjunctionsCount( OutputTerm::Enum _term ) const;

	/*virtual*/ const unsigned int calculateConditionsCount() const;

	/*-----     -----     -----     -----      -----     -----*/

	/*virtual*/ boost::shared_ptr< KnowledgeBase > createCompactAndMinimizedKnowledgeBase();

	/*-----     -----     -----     -----      -----     -----*/

private:

	/*-----     -----     -----     -----      -----     -----*/

	typedef
		std::multimap< OutputTerm::Enum, boost::shared_ptr< const InputCube > >
		ProductionRulesMap;

	ProductionRulesMap m_rules;

	/*-----     -----     -----     -----      -----     -----*/

}; // class KnowledgeBaseImpl

/*------      ------      ------      ------      ------      ------      ------      ------*/

} // FuzzyLogicEngine

/*------      ------      ------      ------      ------      ------      ------      ------*/

#endif // _FUZZY_LOGIC_ENGINE__KNOWLEDGE_BASE_IMPL_