
#include "flg_engine_controller.hpp"

/*------------------------------------------------------------------------------*/

namespace FuzzyLogic{
namespace Gui{

/*------------------------------------------------------------------------------*/


EngineController::EngineController()
{}


/*------------------------------------------------------------------------------*/


EngineController::~EngineController()
{}


/*------------------------------------------------------------------------------*/


int
EngineController::getInputVariablesCount()
{return 4;}


/*------------------------------------------------------------------------------*/


int
EngineController::getOutputVariablesCount()
{return 1;}


/*------------------------------------------------------------------------------*/


void
EngineController::addRule(const QString & input, const QString & _output)
{}


/*------------------------------------------------------------------------------*/


void
EngineController::makeFullRulesForm( QStringList & _destination )
{
	_destination.insert("Some Full Rule");
	_destination.insert("Some Full Rule2");
	_destination.insert("Some Full Rule3");
}


/*------------------------------------------------------------------------------*/


void EngineController::addInputVariable( const QString & _name )
{

}


/*------------------------------------------------------------------------------*/


void EngineController::addOutpuVariable( const QString & _name )
{

}


/*------------------------------------------------------------------------------*/

} // namespace Gui
} // namespace FuzzyLogic

/*------------------------------------------------------------------------------*/
