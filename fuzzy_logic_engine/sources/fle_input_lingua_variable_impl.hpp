#ifndef _FUZZY_LOGIC_ENGINE__INPUT_LINGUA_VARIABLE_IMPL_
#define _FUZZY_LOGIC_ENGINE__INPUT_LINGUA_VARIABLE_IMPL_

/*------      ------      ------      ------      ------      ------      ------      ------*/

#include "fuzzy_logic_engine/sources/fle_lingua_variable_impl.hpp"

/*------      ------      ------      ------      ------      ------      ------      ------*/

namespace FuzzyLogicEngine
{

/*------      ------      ------      ------      ------      ------      ------      ------*/

class InputLinguaVariableImpl
	: public LinguaVariableImpl
{

	/*-----     -----     -----     -----      -----     -----*/

public:

	/*-----     -----     -----     -----      -----     -----*/

	InputLinguaVariableImpl( QString const& _name )
		:	LinguaVariableImpl( _name )
	{
	}

	/*-----     -----     -----     -----      -----     -----*/

	/*virtual*/ const Kind::Enum getKind() const
	{
		return Kind::Input;
	}

	/*virtual*/ const unsigned int getAlphabetTermsCount() const
	{
		return 3;
	}

	/*-----     -----     -----     -----      -----     -----*/

}; // class InputLinguaVariableImpl

/*------      ------      ------      ------      ------      ------      ------      ------*/

} // FuzzyLogicEngine

/*------      ------      ------      ------      ------      ------      ------      ------*/

#endif // _FUZZY_LOGIC_ENGINE__INPUT_LINGUA_VARIABLE_IMPL_