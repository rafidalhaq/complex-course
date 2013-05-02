#ifndef _FUZZY_LOGIC_ENGINE__OUTPUT_LINGUA_VARIABLE_IMPL_
#define _FUZZY_LOGIC_ENGINE__OUTPUT_LINGUA_VARIABLE_IMPL_

/*------      ------      ------      ------      ------      ------      ------      ------*/

#include "fuzzy_logic_engine/sources/fle_lingua_variable_impl.hpp"

/*------      ------      ------      ------      ------      ------      ------      ------*/

namespace FuzzyLogicEngine
{

/*------      ------      ------      ------      ------      ------      ------      ------*/

class OutputLinguaVariableImpl
	: public LinguaVariableImpl
{

	/*-----     -----     -----     -----      -----     -----*/

public:

	/*-----     -----     -----     -----      -----     -----*/

	OutputLinguaVariableImpl( QString const& _name )
		:	LinguaVariableImpl( _name )
	{
	}

	/*-----     -----     -----     -----      -----     -----*/

	/*virtual*/ const Kind::Enum getKind() const
	{
		return Kind::Output;
	}

	/*virtual*/ const unsigned int getAlphabetTermsCount() const
	{
		return 5;
	}

	/*-----     -----     -----     -----      -----     -----*/

}; // class OutputLinguaVariableImpl

/*------      ------      ------      ------      ------      ------      ------      ------*/

} // FuzzyLogicEngine

/*------      ------      ------      ------      ------      ------      ------      ------*/

#endif // _FUZZY_LOGIC_ENGINE__OUTPUT_LINGUA_VARIABLE_IMPL_