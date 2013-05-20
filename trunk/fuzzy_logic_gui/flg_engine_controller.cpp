
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
{return 1;}


/*------------------------------------------------------------------------------*/


void
EngineController::addRule(const QString & input, const QString & _output)
{
	FuzzyLogicEngine::InputTermsVector inputs;

	for(int currChar = 0; currChar<input.size(); currChar++)
		inputs.push_back(FuzzyLogicEngine::CubeTerm::fromShortString(input[currChar]));
	

	FuzzyLogicEngine::getAccessorModifying()
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

	for (int outputTerm = FuzzyLogicEngine::OutputTerm::OH; outputTerm<FuzzyLogicEngine::OutputTerm::Last; outputTerm++ )
	{
		for (int ruleId = 0; ruleId < kBase.getProductionRulesCount((FuzzyLogicEngine::OutputTerm::Enum)outputTerm);ruleId++)
		{
			FuzzyLogicEngine::InputCube const & currentCube =
				kBase.getInputCube((FuzzyLogicEngine::OutputTerm::Enum)outputTerm,ruleId);

			QString line;
			line+="If ";

			for(int variableId = 0; variableId< currentCube.getTermsCount(); )
			{
				FuzzyLogicEngine::LinguaVariable const& currVar =
					lvDict.getInputLinguaVariable(variableId);

				line += currVar.getName();
				line += " equals ";

				line += FuzzyLogicEngine::CubeTerm::toShortString(
					currentCube.getCubeTerm(variableId));

				variableId++;

				if(variableId<currentCube.getTermsCount())
					line+=" and ";
			}

			line+=" then ";
			line+=lvDict.getOutputLinguaVariable(0).getName();
			line+=" equals ";
			line+= FuzzyLogicEngine::OutputTerm::toShortString(
				(FuzzyLogicEngine::OutputTerm::Enum)outputTerm);

			_destination.push_back(line);
		}

		

		
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

} // namespace Gui
} // namespace FuzzyLogic

/*------------------------------------------------------------------------------*/
