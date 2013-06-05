#ifndef __FUZZY_LOGIC_GUI_ENGINE_CONTROLLER_HPP__
#define __FUZZY_LOGIC_GUI_ENGINE_CONTROLLER_HPP__

#include <QtCore/QStringList>

#include "fuzzy_logic_engine/headers/fle_checks_listener.hpp"

/*------------------------------------------------------------------------------*/

namespace FuzzyLogic{
namespace Gui{

/*------------------------------------------------------------------------------*/

class EngineController
	:	private FuzzyLogicEngine::ChecksListener
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

	bool checkForCompleteness( QString & _detailed );

	bool checkForConsistency( QString & _detailed );

	bool checkForMinimality( QString & _detailed );

	bool checkForCoherence( QString & _detailed );

	void clearModels();

	void collectVariables(QStringList & _variables);

	void addVariables(QStringList const & _variables);

/*------------------------------------------------------------------------------*/

private:

/*------------------------------------------------------------------------------*/

	/*virtual*/ void onUncoveredCube( FuzzyLogicEngine::InputCube const& _cube );

	/*virtual*/ void onInconsistentCubes(
			FuzzyLogicEngine::InputCube const& _cube1, FuzzyLogicEngine::OutputTerm::Enum _outTerm1
		,	FuzzyLogicEngine::InputCube const& _cube2, FuzzyLogicEngine::OutputTerm::Enum _outTerm2
	);

	/*virtual*/ void onRedundantCubes(
			FuzzyLogicEngine::InputCube const& _cube1
		,	FuzzyLogicEngine::InputCube const& _cube2
		,	FuzzyLogicEngine::OutputTerm::Enum _outTerm
	);

	/*virtual*/ void onInconsistentTerm( FuzzyLogicEngine::OutputTerm::Enum _outTerm );

/*------------------------------------------------------------------------------*/

	QString cubeToString( FuzzyLogicEngine::InputCube const& _cube );

	QString ruleToString(
			FuzzyLogicEngine::InputCube const& _cube
		,	FuzzyLogicEngine::OutputTerm::Enum _outTerm
	);

/*------------------------------------------------------------------------------*/

	QString m_currentDetailedText;

/*------------------------------------------------------------------------------*/

};

/*------------------------------------------------------------------------------*/

} // namespace Gui
} // namespace FuzzyLogic

/*------------------------------------------------------------------------------*/

#endif // __FUZZY_LOGIC_GUI_ENGINE_CONTROLLER_HPP__
