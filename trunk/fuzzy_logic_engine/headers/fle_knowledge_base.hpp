#ifndef _FUZZY_LOGIC_ENGINE__KNOWLEDGE_BASE_
#define _FUZZY_LOGIC_ENGINE__KNOWLEDGE_BASE_

/*------      ------      ------      ------      ------      ------      ------      ------*/

#include "fuzzy_logic_engine/headers/fle_export.hpp"
#include "fuzzy_logic_engine/headers/fle_input_cube.hpp"
#include "fuzzy_logic_engine/headers/fle_output_term.hpp"
#include "fuzzy_logic_engine/headers/fle_typedefs.hpp"

/*------      ------      ------      ------      ------      ------      ------      ------*/

namespace FuzzyLogicEngine
{

/*------      ------      ------      ------      ------      ------      ------      ------*/

class KnowledgeBase
	: public boost::noncopyable
{

	/*-----     -----     -----     -----      -----     -----*/

public:

	/*-----     -----     -----     -----      -----     -----*/

	virtual ~KnowledgeBase() {}

	/*-----     -----     -----     -----      -----     -----*/

	virtual const unsigned int getProductionRulesCount() const = 0;

	virtual const unsigned int getProductionRulesCount( OutputTerm::Enum _term ) const = 0;

	virtual InputCube const& getInputCube( OutputTerm::Enum _term, const unsigned int _index ) const = 0;

	/*-----     -----     -----     -----      -----     -----*/

	// NOTE: _inputs will be cleared after the call!
	virtual void addProductionRule(
			InputTermsVectorNonConstRef _inputs
		,	OutputTerm::Enum _outTerm
	) = 0;

	/*-----     -----     -----     -----      -----     -----*/

	virtual void removeProductionRule( OutputTerm::Enum _term, const unsigned int _index ) = 0;

	virtual void clear() = 0;

	/*-----     -----     -----     -----      -----     -----*/

	virtual const unsigned int calculateConjunctionsCount() const = 0;

	virtual const unsigned int calculateConjunctionsCount( OutputTerm::Enum _term ) const = 0;

	virtual const unsigned int calculateConditionsCount() const = 0;

	/*-----     -----     -----     -----      -----     -----*/

	virtual boost::shared_ptr< KnowledgeBase > createCompactAndMinimizedKnowledgeBase() = 0;

	/*-----     -----     -----     -----      -----     -----*/

}; // class KnowledgeBase

/*------      ------      ------      ------      ------      ------      ------      ------*/

} // FuzzyLogicEngine

/*------      ------      ------      ------      ------      ------      ------      ------*/

#endif // _FUZZY_LOGIC_ENGINE__KNOWLEDGE_BASE_