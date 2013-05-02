#include "ph/fle_ph.hpp"

#include "fuzzy_logic_engine/sources/fle_lingua_variable_impl.hpp"

/*------      ------      ------      ------      ------      ------      ------      ------*/

namespace FuzzyLogicEngine
{

/*------      ------      ------      ------      ------      ------      ------      ------*/


LinguaVariableImpl::LinguaVariableImpl( QString const& _name )
	:	m_name( _name )
{
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


QString const&
LinguaVariableImpl::getName() const
{
	return m_name;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/

} // FuzzyLogicEngine

/*------      ------      ------      ------      ------      ------      ------      ------*/
