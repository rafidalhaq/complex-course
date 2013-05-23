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

	virtual ~LinguaVariablesDictionary() {}

	/*-----     -----     -----     -----      -----     -----*/

	virtual const unsigned int getInputLinguaVariablesCount() const = 0;

	virtual LinguaVariable const& getInputLinguaVariable(
		const unsigned int _index
	) const = 0;

	/*-----     -----     -----     -----      -----     -----*/

	virtual const unsigned int getOutputLinguaVariablesCount() const = 0;

	virtual LinguaVariable const& getOutputLinguaVariable(
		const unsigned int _index
	) const = 0;

	/*-----     -----     -----     -----      -----     -----*/

	virtual void addInputLinguaVariable( const QString& _name ) = 0;

	virtual void addOutputLinguaVariable( const QString& _name ) = 0;

	/*-----     -----     -----     -----      -----     -----*/

	virtual void removeInputVariable( const unsigned int _index ) = 0;

	virtual void removeOutputVariable( const unsigned int _index ) = 0;

	virtual void clear() = 0;

	/*-----     -----     -----     -----      -----     -----*/

}; // class LinguaVariablesDictionary

/*------      ------      ------      ------      ------      ------      ------      ------*/

} // FuzzyLogicEngine

/*------      ------      ------      ------      ------      ------      ------      ------*/

#endif // _FUZZY_LOGIC_ENGINE__LINGUA_VARIABLES_DICTIONARY_