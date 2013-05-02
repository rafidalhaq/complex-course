#include "ph/fle_ph.hpp"

#include "fuzzy_logic_engine/sources/fle_lingua_variables_dictionary_impl.hpp"
#include "fuzzy_logic_engine/sources/fle_input_lingua_variable_impl.hpp"
#include "fuzzy_logic_engine/sources/fle_output_lingua_variable_impl.hpp"

/*------      ------      ------      ------      ------      ------      ------      ------*/

namespace FuzzyLogicEngine
{

/*------      ------      ------      ------      ------      ------      ------      ------*/


const unsigned int
LinguaVariablesDictionaryImpl::getInputLinguaVariablesCount() const
{
	return m_inputVariables.size();
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


const unsigned int
LinguaVariablesDictionaryImpl::getOutputLinguaVariablesCount() const
{
	return m_outputVariables.size();
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


LinguaVariable const&
LinguaVariablesDictionaryImpl::getInputLinguaVariable( const unsigned int _index ) const
{
	return * m_inputVariables.at( _index );
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


LinguaVariable const&
LinguaVariablesDictionaryImpl::getOutputLinguaVariable( const unsigned int _index ) const
{
	return * m_outputVariables.at( _index );
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


void
LinguaVariablesDictionaryImpl::addInputLinguaVariable( const QString& _name )
{
	boost::shared_ptr< LinguaVariable > newVar(
		new InputLinguaVariableImpl( _name )
	);

	return m_inputVariables.push_back( newVar );
}


/*------      ------      ------      ------      ------      ------      ------      ------*/


void
LinguaVariablesDictionaryImpl::addOutputLinguaVariable( const QString& _name )
{
	boost::shared_ptr< LinguaVariable > newVar(
		new OutputLinguaVariableImpl( _name )
	);

	return m_outputVariables.push_back( newVar );
}


/*------      ------      ------      ------      ------      ------      ------      ------*/

} // FuzzyLogicEngine

/*------      ------      ------      ------      ------      ------      ------      ------*/
