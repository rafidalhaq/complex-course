#ifndef _FUZZY_LOGIC_ENGINE__KNOWLEDGE_BASE_IMPL_
#define _FUZZY_LOGIC_ENGINE__KNOWLEDGE_BASE_IMPL_

/*------      ------      ------      ------      ------      ------      ------      ------*/

#include "fuzzy_logic_engine/headers/fle_knowledge_base.hpp"

#include "fuzzy_logic_engine/sources/fle_input_cube_impl.hpp"

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

	/*virtual*/ RulesVector getAllRulesConsideringPermutations() const;

	/*-----     -----     -----     -----      -----     -----*/

	// attention: _inputs will be cleared after the call!
	/*virtual*/ unsigned int addProductionRule(
			InputTermsVectorNonConstRef _inputs
		,	OutputTerm::Enum _outTerm
	);

	/*-----     -----     -----     -----      -----     -----*/

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
		std::multimap< OutputTerm::Enum, boost::shared_ptr< const InputCubeImpl > >
		ProductionRulesMap;

	ProductionRulesMap m_rules;

	/*-----     -----     -----     -----      -----     -----*/

	typedef
		std::map< OutputTerm::Enum, std::set< InputTermsVector > >
		CoveredTermsMap;

	CoveredTermsMap m_coveredTerms;

	/*-----     -----     -----     -----      -----     -----*/

}; // class KnowledgeBaseImpl

/*------      ------      ------      ------      ------      ------      ------      ------*/

} // FuzzyLogicEngine

/*------      ------      ------      ------      ------      ------      ------      ------*/

#endif // _FUZZY_LOGIC_ENGINE__KNOWLEDGE_BASE_IMPL_