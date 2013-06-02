#include "ph/fle_ph.hpp"

#include "fuzzy_logic_engine/headers/fle_exceptions.hpp"

/*------      ------      ------      ------      ------      ------      ------      ------*/

namespace FuzzyLogicEngine {
namespace Exceptions {

/*------      ------      ------      ------      ------      ------      ------      ------*/


InternalError::InternalError( const char * _file, int _line, QString _description )
	:	m_file( _file )
	,	m_line( QString::number( _line ) )
	,	m_errorMessage( _description )
{
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


QString const&
InternalError::getErrorMessage() const
{
	return m_errorMessage;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


QString const&
InternalError::getFile() const
{
	return m_file;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


QString const&
InternalError::getLine() const
{
	return m_line;
}


/*------      ------      ------      ------      ------      ------      ------      ------*/

} // Exceptions
} // FuzzyLogicEngine

/*------      ------      ------      ------      ------      ------      ------      ------*/
