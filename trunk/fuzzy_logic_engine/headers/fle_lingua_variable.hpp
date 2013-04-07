#ifndef _FUZZY_LOGIC_ENGINE__LINGUA_VARIABLE_
#define _FUZZY_LOGIC_ENGINE__LINGUA_VARIABLE_

/*------      ------      ------      ------      ------      ------      ------      ------*/

namespace FuzzyLogicEngine
{

/*------      ------      ------      ------      ------      ------      ------      ------*/

class LinguaVariable
	: public boost::noncopyable
{

	/*-----     -----     -----     -----      -----     -----*/

public:

	/*-----     -----     -----     -----      -----     -----*/

	struct Kind
	{
		enum Enum
		{
			Input, Output
		};
	};

	/*-----     -----     -----     -----      -----     -----*/

	virtual Kind::Enum getKind() const = 0;

	virtual QString const& getName() const = 0;

	virtual const unsigned int getAlphabetTermsCount() const = 0;

	/*-----     -----     -----     -----      -----     -----*/

}; // class LinguaVariable

/*------      ------      ------      ------      ------      ------      ------      ------*/

} // FuzzyLogicEngine

/*------      ------      ------      ------      ------      ------      ------      ------*/

#endif // _FUZZY_LOGIC_ENGINE__LINGUA_VARIABLE_