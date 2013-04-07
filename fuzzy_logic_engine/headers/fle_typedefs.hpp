#ifndef _FUZZY_LOGIC_ENGINE__TYPEDEFS_
#define _FUZZY_LOGIC_ENGINE__TYPEDEFS_

/*------      ------      ------      ------      ------      ------      ------      ------*/

#include "fuzzy_logic_engine/headers/fle_cube_term.hpp"

/*------      ------      ------      ------      ------      ------      ------      ------*/

namespace FuzzyLogicEngine
{

/*------      ------      ------      ------      ------      ------      ------      ------*/

	typedef
		std::vector< CubeTerm >
		InputTermsVector;

	typedef
		InputTermsVector &
		InputTermsVectorNonConstRef;

/*------      ------      ------      ------      ------      ------      ------      ------*/

} // FuzzyLogicEngine

/*------      ------      ------      ------      ------      ------      ------      ------*/

#endif // _FUZZY_LOGIC_ENGINE__TYPEDEFS_