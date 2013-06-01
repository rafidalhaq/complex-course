#ifndef _FUZZY_LOGIC_ENGINE__INPUT_CUBE_IMPL_
#define _FUZZY_LOGIC_ENGINE__INPUT_CUBE_IMPL_

/*------      ------      ------      ------      ------      ------      ------      ------*/

#include "fuzzy_logic_engine/headers/fle_input_cube.hpp"
#include "fuzzy_logic_engine/headers/fle_typedefs.hpp"

/*------      ------      ------      ------      ------      ------      ------      ------*/

namespace FuzzyLogicEngine
{

/*------      ------      ------      ------      ------      ------      ------      ------*/

class InputCubeImpl
	: public InputCube
{

	/*-----     -----     -----     -----      -----     -----*/

public:

	/*virtual*/ const unsigned int getTermsCount() const;

	/*virtual*/ const CubeTerm::Enum getCubeTerm( unsigned int _index ) const;

	/*virtual*/ const unsigned int getRank() const;

	/*virtual*/ const unsigned int getUndefinedValuesCount() const;

	/*virtual*/ const unsigned int calculateCodeDistance( InputCube const& _other ) const;

	/*-----     -----     -----     -----      -----     -----*/

	// TODO: maybe, this ones should be moved to another place?

	/*virtual*/ std::auto_ptr< const InputCube > intersect( InputCube const& _other ) const;

	/*virtual*/ std::auto_ptr< const InputCube > join( InputCube const& _other ) const;

	/*virtual*/ std::auto_ptr< const InputCube > complement() const;

	/*virtual*/ std::auto_ptr< const InputCube > summ( InputCube const& _other ) const;

	/*virtual*/ std::auto_ptr< const InputCube > bond( InputCube const& _other ) const;

	// TODO: should be added 'absorbs'?

	/*-----     -----     -----     -----      -----     -----*/

	std::auto_ptr< const InputCubeImpl > clone() const;

	void swap( InputTermsVectorNonConstRef _terms );

	InputTermsVector permuteToGetBestMatching(
			InputCubeImpl const& _other
		,	unsigned int * _numberOfMatchingElements = NULL
	) const;

	/*-----     -----     -----     -----      -----     -----*/

private:

	/*-----     -----     -----     -----      -----     -----*/

	typedef CubeTerm::Enum ( *CubeTermTableMethod ) ( CubeTerm::Enum, CubeTerm::Enum );

	/*-----     -----     -----     -----      -----     -----*/

	std::auto_ptr< const InputCube > makeNewCube(
			InputCube const& _other
		,	CubeTermTableMethod _method
		,	bool _returnNullIfTriggeredEmptyCube
	) const;

	const unsigned int termsCount( CubeTerm::Enum _term ) const;

	/*-----     -----     -----     -----      -----     -----*/

	InputTermsVector m_terms;

	/*-----     -----     -----     -----      -----     -----*/

}; // class InputCubeImpl

/*------      ------      ------      ------      ------      ------      ------      ------*/

} // FuzzyLogicEngine

/*------      ------      ------      ------      ------      ------      ------      ------*/

#endif // _FUZZY_LOGIC_ENGINE__INPUT_CUBE_IMPL_