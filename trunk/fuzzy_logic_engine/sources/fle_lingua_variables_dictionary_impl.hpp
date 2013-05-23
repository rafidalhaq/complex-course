#ifndef _FUZZY_LOGIC_ENGINE__LINGUA_VARIABLES_DICTIONARY_IMPL_
#define _FUZZY_LOGIC_ENGINE__LINGUA_VARIABLES_DICTIONARY_IMPL_

/*------      ------      ------      ------      ------      ------      ------      ------*/

#include "fuzzy_logic_engine/headers/fle_lingua_variables_dictionary.hpp"

/*------      ------      ------      ------      ------      ------      ------      ------*/

namespace FuzzyLogicEngine
{

/*------      ------      ------      ------      ------      ------      ------      ------*/

class LinguaVariablesDictionaryImpl
	: public LinguaVariablesDictionary
{

	/*-----     -----     -----     -----      -----     -----*/

public:

	/*-----     -----     -----     -----      -----     -----*/

	/*virtual*/ const unsigned int getInputLinguaVariablesCount() const;

	/*virtual*/ LinguaVariable const& getInputLinguaVariable(
		const unsigned int _index
	) const;

	/*-----     -----     -----     -----      -----     -----*/

	/*virtual*/ const unsigned int getOutputLinguaVariablesCount() const;

	/*virtual*/ LinguaVariable const& getOutputLinguaVariable(
		const unsigned int _index
	) const;

	/*-----     -----     -----     -----      -----     -----*/

	/*virtual*/ void addInputLinguaVariable( const QString& _name );

	/*virtual*/ void addOutputLinguaVariable( const QString& _name );

	/*-----     -----     -----     -----      -----     -----*/

	/*virtual*/ void removeInputVariable( const unsigned int _index );

	/*virtual*/ void removeOutputVariable( const unsigned int _index );

	/*virtual*/ void clear();

	/*-----     -----     -----     -----      -----     -----*/

private:

	/*-----     -----     -----     -----      -----     -----*/

	typedef
		std::vector< boost::shared_ptr< const LinguaVariable > >
		VariablesVector;

	VariablesVector m_inputVariables, m_outputVariables;

	/*-----     -----     -----     -----      -----     -----*/

}; // class LinguaVariablesDictionaryImpl

/*------      ------      ------      ------      ------      ------      ------      ------*/

} // FuzzyLogicEngine

/*------      ------      ------      ------      ------      ------      ------      ------*/

#endif // _FUZZY_LOGIC_ENGINE__LINGUA_VARIABLES_DICTIONARY_IMPL_