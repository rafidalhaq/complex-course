
#include "stdafx.h"

#include "flg_engine_controller.hpp"
#include "fuzzy_logic_engine/headers/fle_accessor.hpp"
#include "fuzzy_logic_engine/headers/fle_lingua_variables_dictionary.hpp"
#include "fuzzy_logic_engine/headers/fle_knowledge_base.hpp"

#include "boost/foreach.hpp"

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
EngineController::getInputVariablesCount() const
{
	return FuzzyLogicEngine::getAccessor().getLinguaVariablesDictionary()
		.getInputLinguaVariablesCount();
}


/*------------------------------------------------------------------------------*/


int
EngineController::getOutputVariablesCount() const
{
	return FuzzyLogicEngine::getAccessor().getLinguaVariablesDictionary()
		.getOutputLinguaVariablesCount();
}


/*------------------------------------------------------------------------------*/


unsigned int
EngineController::addRule(const QString & input, const QString & _output)
{
	FuzzyLogicEngine::InputTermsVector inputs;

	for(int currChar = 0; currChar<input.size(); currChar++)
		inputs.push_back(FuzzyLogicEngine::CubeTerm::fromShortString(input[currChar]));
	

	return FuzzyLogicEngine::getAccessorModifying()
		.getKnowledgeBaseModifying().addProductionRule(
				inputs
			,	FuzzyLogicEngine::OutputTerm::fromShortString(_output)
		);

}


/*------------------------------------------------------------------------------*/


void
EngineController::makeFullRulesForm( QStringList & _destination )
{
	FuzzyLogicEngine::KnowledgeBase const & kBase =
		FuzzyLogicEngine::getAccessor().getKnowledgeBase();

	FuzzyLogicEngine::LinguaVariablesDictionary const & lvDict =
		FuzzyLogicEngine::getAccessor().getLinguaVariablesDictionary();

	FuzzyLogicEngine::KnowledgeBase::RulesVector rulesVector
		= kBase.getAllRulesConsideringPermutations();

	for ( unsigned int ruleId = 0; ruleId < rulesVector.size(); ruleId++ )
	{
		std::pair< FuzzyLogicEngine::InputTermsVector, FuzzyLogicEngine::OutputTerm::Enum > const& currentRule =
			rulesVector[ ruleId ];
		FuzzyLogicEngine::InputTermsVector const& currentCube = currentRule.first;

		QString line;
		line+="If ";

		for(unsigned int variableId = 0; variableId< currentCube.size(); )
		{
			FuzzyLogicEngine::LinguaVariable const& currVar =
				lvDict.getInputLinguaVariable(variableId);

			line += currVar.getName();
			line += " is ";

			line += FuzzyLogicEngine::CubeTerm::toShortString(currentCube[variableId]);

			variableId++;

			if(variableId<currentCube.size())
				line+=" and ";
		}

		line+=" then ";
		line+=lvDict.getOutputLinguaVariable(0).getName();
		line+=" is ";
		line+= FuzzyLogicEngine::OutputTerm::toShortString( currentRule.second );

		_destination.push_back(line);
	}

}


/*------------------------------------------------------------------------------*/


void
EngineController::makeCMRulesForm( QStringList & _destination )
{
	using namespace FuzzyLogicEngine;

	KnowledgeBase const& minimizedKB = getAccessor().getKnowledgeBase().getMinimizedKnowledgeBase();

	for (int outputTerm = OutputTerm::OH; outputTerm<OutputTerm::Last; outputTerm++ )
	{
		QString line(
				OutputTerm::toShortString((OutputTerm::Enum)outputTerm)
			+	"->{"
		);

		int rulesCount = minimizedKB.getProductionRulesCount((FuzzyLogicEngine::OutputTerm::Enum)outputTerm);

		for (int ruleId = 0; ruleId < rulesCount;ruleId++)
		{
			FuzzyLogicEngine::InputCube const & currentCube =
				minimizedKB.getInputCube((FuzzyLogicEngine::OutputTerm::Enum)outputTerm,ruleId);

			line += cubeToString( currentCube );

			if(ruleId<rulesCount-1)
				line+=", ";
		}

		line+="}";
		_destination.push_back(line);
	}
}


/*------------------------------------------------------------------------------*/


void EngineController::addInputVariable( const QString & _name )
{
	FuzzyLogicEngine::getAccessorModifying().getLinguaVariablesDictionaryModifying()
		.addInputLinguaVariable(_name);
}


/*------------------------------------------------------------------------------*/


void EngineController::addOutpuVariable( const QString & _name )
{
	FuzzyLogicEngine::getAccessorModifying().getLinguaVariablesDictionaryModifying()
		.addOutputLinguaVariable(_name);
}


/*------------------------------------------------------------------------------*/


bool
EngineController::checkForCompleteness( QString & _detailed )
{
	FuzzyLogicEngine::Accessor const & accessor =
		FuzzyLogicEngine::getAccessor();

	m_currentDetailedText.clear();

	const bool result = accessor.isCompleteKB(
			accessor.getKnowledgeBase().getMinimizedKnowledgeBase()
		,	*this
	);

	if ( !m_currentDetailedText.isEmpty() )
		_detailed += m_currentDetailedText + ".";

	return result;
}


/*------------------------------------------------------------------------------*/


bool
EngineController::checkForConsistency( QString & _detailed )
{	
	FuzzyLogicEngine::Accessor const & accessor =
		FuzzyLogicEngine::getAccessor();

	m_currentDetailedText.clear();

	const bool result = accessor.isConsistentKB(
			accessor.getKnowledgeBase().getMinimizedKnowledgeBase()
		,	*this
	);

	if ( !m_currentDetailedText.isEmpty() )
		_detailed += m_currentDetailedText + ".";

	return result;
}


/*------------------------------------------------------------------------------*/


bool
EngineController::checkForMinimality( QString & _detailed )
{	
	FuzzyLogicEngine::Accessor const & accessor =
		FuzzyLogicEngine::getAccessor();

	m_currentDetailedText.clear();

	const bool result = accessor.isMinimalKB(
			accessor.getKnowledgeBase().getMinimizedKnowledgeBase()
		,	*this
	);

	if ( !m_currentDetailedText.isEmpty() )
		_detailed += m_currentDetailedText + ".";

	return result;
}


/*------------------------------------------------------------------------------*/


bool
EngineController::checkForCoherence( QString & _detailed )
{	
	FuzzyLogicEngine::Accessor const & accessor =
		FuzzyLogicEngine::getAccessor();

	m_currentDetailedText.clear();
	m_anotherCurrentDetailedText.clear();

	const bool result = accessor.isCoherentKB(
			accessor.getKnowledgeBase().getMinimizedKnowledgeBase()
		,	*this
	);

	QString newLine( '\n' );

	if ( !m_anotherCurrentDetailedText.isEmpty() )
		_detailed += newLine + "The following rules are adjacent:" + newLine + m_anotherCurrentDetailedText + '.';

	if ( !m_currentDetailedText.isEmpty() )
		_detailed += newLine + "The following cube sets are not coherent with any other:" + newLine + m_currentDetailedText + ".";

	return result;
}


/*------------------------------------------------------------------------------*/

void
EngineController::removeAllRules( )
{
	FuzzyLogicEngine::Accessor & accessor =
		FuzzyLogicEngine::getAccessorModifying();

	accessor.getKnowledgeBaseModifying().clear();

}


/*------------------------------------------------------------------------------*/


void
EngineController::clearModels()
{
	FuzzyLogicEngine::Accessor & accessor =
		FuzzyLogicEngine::getAccessorModifying();

	accessor.getKnowledgeBaseModifying().clear();
	accessor.getLinguaVariablesDictionaryModifying().clear();

}


/*------------------------------------------------------------------------------*/


void
EngineController::onUncoveredCube( FuzzyLogicEngine::InputCube const& _cube )
{
	if ( !m_currentDetailedText.isEmpty() )
		m_currentDetailedText += ", ";

	m_currentDetailedText += cubeToString( _cube );
}


/*------------------------------------------------------------------------------*/


void
EngineController::onInconsistentCubes(
		FuzzyLogicEngine::InputCube const& _cube1, FuzzyLogicEngine::OutputTerm::Enum _outTerm1
	,	FuzzyLogicEngine::InputCube const& _cube2, FuzzyLogicEngine::OutputTerm::Enum _outTerm2
)
{
	if ( !m_currentDetailedText.isEmpty() )
		m_currentDetailedText += ";\n";

	m_currentDetailedText +=
			ruleToString( _cube1, _outTerm1 )
		+	" and "
		+	ruleToString( _cube2, _outTerm2 )
	;
}


/*------------------------------------------------------------------------------*/


void
EngineController::onRedundantCubes(
		FuzzyLogicEngine::InputCube const& _cube1
	,	FuzzyLogicEngine::InputCube const& _cube2
	,	FuzzyLogicEngine::OutputTerm::Enum _outTerm
)
{
	if ( !m_currentDetailedText.isEmpty() )
		m_currentDetailedText += ";\n";

	m_currentDetailedText +=
			FuzzyLogicEngine::OutputTerm::toShortString( _outTerm )
		+	": "
		+	cubeToString( _cube1 )
		+	" and "
		+	cubeToString( _cube2 )
	;
}


/*------------------------------------------------------------------------------*/


void
EngineController::onInconsistentTerm( FuzzyLogicEngine::OutputTerm::Enum _outTerm )
{
	if ( !m_currentDetailedText.isEmpty() )
		m_currentDetailedText += ", ";

	m_currentDetailedText += FuzzyLogicEngine::OutputTerm::toShortString( _outTerm );
}


/*------------------------------------------------------------------------------*/


void
EngineController::onAdjacentCubes(
		FuzzyLogicEngine::InputCube const& _cube1, FuzzyLogicEngine::OutputTerm::Enum _outTerm1
	,	FuzzyLogicEngine::InputCube const& _cube2, FuzzyLogicEngine::OutputTerm::Enum _outTerm2
)
{
	if ( !m_anotherCurrentDetailedText.isEmpty() )
		m_anotherCurrentDetailedText += ";\n";

	m_anotherCurrentDetailedText +=
			ruleToString( _cube1, _outTerm1 )
		+	" and "
		+	ruleToString( _cube2, _outTerm2 )
	;
}


/*------------------------------------------------------------------------------*/


QString
EngineController::cubeToString( FuzzyLogicEngine::InputCube const& _cube )
{
	QString result;

	for( unsigned int variableId = 0; variableId< _cube.getTermsCount(); ++variableId )
	{
		result += FuzzyLogicEngine::CubeTerm::toShortString(
			_cube.getCubeTerm( variableId )
		);
	}

	return result;
}


/*------------------------------------------------------------------------------*/


QString
EngineController::ruleToString(
		FuzzyLogicEngine::InputCube const& _cube
	,	FuzzyLogicEngine::OutputTerm::Enum _outTerm
)
{
	QString result( '{' + cubeToString( _cube ) + '}' );
	result += "->";
	result += FuzzyLogicEngine::OutputTerm::toShortString( _outTerm );
	return result;
}


/*------------------------------------------------------------------------------*/


void
EngineController::collectVariables(QStringList & _variables)
{
	FuzzyLogicEngine::Accessor const & accessor =
		FuzzyLogicEngine::getAccessor();

	int inCount = accessor.getLinguaVariablesDictionary().getInputLinguaVariablesCount();
	int outCount = accessor.getLinguaVariablesDictionary().getOutputLinguaVariablesCount();

	for(int i = 0; i<inCount; i++)
	{
		_variables.push_back(
				"i-"
			+	accessor.getLinguaVariablesDictionary().getInputLinguaVariable(i).getName()
		);
	}
	for(int o = 0; o<outCount; o++)
	{
		_variables.push_back(
			"o-"
			+	accessor.getLinguaVariablesDictionary().getOutputLinguaVariable(o).getName()
		);
	}

}


/*------------------------------------------------------------------------------*/


void
EngineController::addVariables(QStringList const & _variables)
{
	BOOST_FOREACH(QString current, _variables)
	{
		QString prefix = current.section("-",0,0);
		QString name = current.section("-",1,1);

		if(prefix == "i")
			addInputVariable(name);
		else
			addOutpuVariable(name);
	}
}


/*------------------------------------------------------------------------------*/

} // namespace Gui
} // namespace FuzzyLogic

/*------------------------------------------------------------------------------*/
