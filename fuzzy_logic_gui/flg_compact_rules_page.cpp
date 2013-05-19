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

	connect(m_ui.m_addButton, SIGNAL(pressed()),
	 this, SLOT(onAddPress()));

	m_ui.m_outputCombo->addItem("OH");
	m_ui.m_outputCombo->addItem("H");
	m_ui.m_outputCombo->addItem("C");
	m_ui.m_outputCombo->addItem("D");
	m_ui.m_outputCombo->addItem("B");

	QString validationRegex("[HCBhcb]");
	validationRegex+="{";
	validationRegex+=QString::number(3);
	validationRegex+="}";
	m_vectorValidator = new QRegExpValidator(QRegExp(validationRegex));

	m_ui.m_inputVector->setValidator(m_vectorValidator);
}


/*------------------------------------------------------------------------------*/


CompactRules::~CompactRules()
{

}


/*------------------------------------------------------------------------------*/

void
CompactRules::onAddPress()
{
	m_ui.m_rulesList->addItem(
			m_ui.m_inputVector->text()
		+	"->"
		+	m_ui.m_outputCombo->currentText()
	);
}

/*------------------------------------------------------------------------------*/



/*------------------------------------------------------------------------------*/

} // namespace Pages
} // namespace Gui
} // namespace FuzzyLogic

/*------------------------------------------------------------------------------*/
