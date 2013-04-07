#ifndef _FUZZY_LOGIC_ENGINE__LINGUA_VARIABLES_DICTIONARY_
#define _FUZZY_LOGIC_ENGINE__LINGUA_VARIABLES_DICTIONARY_

/*------      ------      ------      ------      ------      ------      ------      ------*/

#include "fuzzy_logic_engine/headers/fle_lingua_variable.hpp"

/*------      ------      ------      ------      ------      ------      ------      ------*/

namespace FuzzyLogicEngine
{

/*------      ------      ------      ------      ------      ------      ------      ------*/

class LinguaVariablesDictionary
	: public boost::noncopyable
{

	/*-----     -----     -----     -----      -----     -----*/

public:

	/*-----     -----     -----     -----      -----     -----*/

	// TODO: maybe, better use different named methods (i.e., getInput...)?

	virtual const unsigned int getLinguaVariablesCount( LinguaVariable::Kind::Enum _kind ) const = 0;

	virtual LinguaVariable const& getLinguaVariable(
			LinguaVariable::Kind::Enum _kind
		,	const unsigned int _index
	) const = 0;

	/*-----     -----     -----     -----      -----     -----*/

	virtual void addLinguaVariable(
			LinguaVariable::Kind::Enum _kind
		,	const QString& _name
	) = 0;

	/*-----     -----     -----     -----      -----     -----*/

}; // class LinguaVariablesDictionary

/*------      ------      ------      ------      ------      ------      ------      ------*/

} // FuzzyLogicEngine

/*------      ------      ------      ------      ------      ------      ------      ------*/

#endif // _FUZZY_LOGIC_ENGINE__LINGUA_VARIABLES_DICTIONARY_