#include "stdafx.h"
#include "flg_compact_rules_page.hpp"

/*------------------------------------------------------------------------------*/

namespace FuzzyLogic{
namespace Gui{
namespace Pages{

/*------------------------------------------------------------------------------*/


CompactRules::CompactRules(QWidget *parent)
	:	QWidget(parent)
{
	m_ui.setupUi(this);

	m_ui.m_outputCombo->addItem("OH");
	m_ui.m_outputCombo->addItem("H");
	m_ui.m_outputCombo->addItem("C");
	m_ui.m_outputCombo->addItem("D");
	m_ui.m_outputCombo->addItem("B");
}


/*------------------------------------------------------------------------------*/


CompactRules::~CompactRules()
{

}


/*------------------------------------------------------------------------------*/

} // namespace Pages
} // namespace Gui
} // namespace FuzzyLogic

/*------------------------------------------------------------------------------*/
