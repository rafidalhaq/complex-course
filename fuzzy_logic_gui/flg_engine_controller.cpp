
#include "stdafx.h"

#include "flg_engine_controller.hpp"
#include "fuzzy_logic_engine/headers/fle_accessor.hpp"
#include "fuzzy_logic_engine/headers/fle_lingua_variables_dictionary.hpp"
#include "fuzzy_logic_engine/headers/fle_knowledge_base.hpp"

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
			line += " equals ";

			line += FuzzyLogicEngine::CubeTerm::toShortString(currentCube[variableId]);

			variableId++;

			if(variableId<currentCube.size())
				line+=" and ";
		}

		line+=" then ";
		line+=lvDict.getOutputLinguaVariable(0).getName();
		line+=" equals ";
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

			for(int variableId = 0; variableId< currentCube.getTermsCount(); variableId++ )
			{
				line += FuzzyLogicEngine::CubeTerm::toShortString(
					currentCube.getCubeTerm(variableId));
			}

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
EngineController::checkForCompleteness()
{
	FuzzyLogicEngine::Accessor const & accessor =
		FuzzyLogicEngine::getAccessor();

	return accessor.isCompleteKB(accessor.getKnowledgeBase().getMinimizedKnowledgeBase());
}


/*------------------------------------------------------------------------------*/


bool
EngineController::checkForConsistency()
{	
	FuzzyLogicEngine::Accessor const & accessor =
		FuzzyLogicEngine::getAccessor();

	return accessor.isConsistentKB(accessor.getKnowledgeBase().getMinimizedKnowledgeBase());
}


/*------------------------------------------------------------------------------*/


bool
EngineController::checkForMinimality()
{	
	FuzzyLogicEngine::Accessor const & accessor =
		FuzzyLogicEngine::getAccessor();

	return accessor.isMinimalKB(accessor.getKnowledgeBase().getMinimizedKnowledgeBase());
}


/*------------------------------------------------------------------------------*/


bool
EngineController::checkForCoherence()
{	
	FuzzyLogicEngine::Accessor const & accessor =
		FuzzyLogicEngine::getAccessor();

	return accessor.isCoherentKB(accessor.getKnowledgeBase().getMinimizedKnowledgeBase());
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

} // namespace Gui
} // namespace FuzzyLogic

/*------------------------------------------------------------------------------*/
