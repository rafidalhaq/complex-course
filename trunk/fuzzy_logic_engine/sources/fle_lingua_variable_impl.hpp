#ifndef _FUZZY_LOGIC_ENGINE__LINGUA_VARIABLE_IMPL_
#define _FUZZY_LOGIC_ENGINE__LINGUA_VARIABLE_IMPL_

/*------      ------      ------      ------      ------      ------      ------      ------*/

#include "fuzzy_logic_engine/headers/fle_lingua_variable.hpp"

/*------      ------      ------      ------      ------      ------      ------      ------*/

namespace FuzzyLogicEngine
{

/*------      ------      ------      ------      ------      ------      ------      ------*/

class LinguaVariableImpl
	: public LinguaVariable
{

	/*-----     -----     -----     -----      -----     -----*/

public:

	/*-----     -----     -----     -----      -----     -----*/

	LinguaVariableImpl( QString const& _name );

	/*-----     -----     -----     -----      -----     -----*/

	/*virtual*/ QString const& getName() const;

	/*-----     -----     -----     -----      -----     -----*/

private:

	/*-----     -----     -----     -----      -----     -----*/

	const QString m_name;

	/*-----     -----     -----     -----      -----     -----*/

}; // class LinguaVariableImpl

/*------      ------      ------      ------      ------      ------      ------      ------*/

} // FuzzyLogicEngine

/*------      ------      ------      ------      ------      ------      ------      ------*/

#endif // _FUZZY_LOGIC_ENGINE__LINGUA_VARIABLE_IMPL_