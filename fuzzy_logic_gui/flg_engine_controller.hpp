#ifndef __FUZZY_LOGIC_GUI_MAIN_WINDOW_HPP__
#define __FUZZY_LOGIC_GUI_MAIN_WINDOW_HPP__

#include <QtCore/QStringList>

/*------------------------------------------------------------------------------*/

namespace FuzzyLogic{
namespace Gui{

/*------------------------------------------------------------------------------*/

class EngineController
{
/*------------------------------------------------------------------------------*/

public:

/*------------------------------------------------------------------------------*/

	EngineController();

	~EngineController();

/*------------------------------------------------------------------------------*/

public:

/*------------------------------------------------------------------------------*/

	void addInputVariable( const QString & _name );

	void addOutpuVariable( const QString & _name );

	void addRule( const QString & input, const QString & _output );

	int getInputVariablesCount() const;

	int getOutputVariablesCount() const;

	void makeFullRulesForm( QStringList & _destination );


/*------------------------------------------------------------------------------*/

};

/*------------------------------------------------------------------------------*/

} // namespace Gui
} // namespace FuzzyLogic

/*------------------------------------------------------------------------------*/

#endif // __FUZZY_LOGIC_GUI_MAIN_WINDOW_HPP__
