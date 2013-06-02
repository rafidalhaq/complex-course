#ifndef __FUZZY_LOGIC_GUI_ENGINE_CONTROLLER_HPP__
#define __FUZZY_LOGIC_GUI_ENGINE_CONTROLLER_HPP__

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

	unsigned int addRule( const QString & input, const QString & _output );

	void removeAllRules();

	int getInputVariablesCount() const;

	int getOutputVariablesCount() const;

	void makeFullRulesForm( QStringList & _destination );

	void makeCMRulesForm( QStringList & _destination );

	bool checkForCompleteness();

	bool checkForConsistency();

	bool checkForMinimality();

	bool checkForCoherence();

	void clearModels();

/*------------------------------------------------------------------------------*/

private:

/*------------------------------------------------------------------------------*/

};

/*------------------------------------------------------------------------------*/

} // namespace Gui
} // namespace FuzzyLogic

/*------------------------------------------------------------------------------*/

#endif // __FUZZY_LOGIC_GUI_ENGINE_CONTROLLER_HPP__
