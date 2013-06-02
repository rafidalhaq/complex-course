#ifndef _FUZZY_LOGIC_ENGINE__EXCEPTIONS_
#define _FUZZY_LOGIC_ENGINE__EXCEPTIONS_

/*------      ------      ------      ------      ------      ------      ------      ------*/

#include "fuzzy_logic_engine/headers/fle_export.hpp"

/*------      ------      ------      ------      ------      ------      ------      ------*/

namespace FuzzyLogicEngine {
namespace Exceptions {

/*------      ------      ------      ------      ------      ------      ------      ------*/

class FUZZY_LOGIC_ENGINE_API InternalError
{

	/*-----     -----     -----     -----      -----     -----*/

public:

	/*-----     -----     -----     -----      -----     -----*/

	InternalError( const char * _file, int _line, QString _description = QString() );

	/*-----     -----     -----     -----      -----     -----*/

	QString const& getErrorMessage() const;

	QString const& getFile() const;

	QString const& getLine() const;

	/*-----     -----     -----     -----      -----     -----*/

private:

	/*-----     -----     -----     -----      -----     -----*/

	const QString m_errorMessage;

	const QString m_file;

	const QString m_line;

	/*-----     -----     -----     -----      -----     -----*/

}; // class InternalError

/*------      ------      ------      ------      ------      ------      ------      ------*/

#define FLE_INTERNAL_ERROR throw Exceptions::InternalError( __FILE__, __LINE__ );

#define FLE_INTERNAL_ERROR_WITH_DESCRIPTION( _description )			\
	throw Exceptions::InternalError( __FILE__, __LINE__, _description );

/*------      ------      ------      ------      ------      ------      ------      ------*/

} // Exceptions
} // FuzzyLogicEngine

/*------      ------      ------      ------      ------      ------      ------      ------*/

#endif // _FUZZY_LOGIC_ENGINE__EXCEPTIONS_