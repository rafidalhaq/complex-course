#include "stdafx.h"
#include "flg_compact_rules_page.hpp"

/*------------------------------------------------------------------------------*/

namespace FuzzyLogic{
namespace Gui{
namespace Pages{

/*------------------------------------------------------------------------------*/


CompactRules::CompactRules(EngineController & _engine, QWidget *parent )
	:	QWidget(parent)
	,	m_engine(_engine)
{
	m_ui.setupUi(this);

	connect(m_ui.m_addButton, SIGNAL(pressed()),
	 this, SLOT(onAddPress()));

	connect(m_ui.m_extensiveButton, SIGNAL(pressed()),
		this, SLOT(showExtensiveView()));

	m_ui.m_outputCombo->addItem("OH");
	m_ui.m_outputCombo->addItem("H");
	m_ui.m_outputCombo->addItem("C");
	m_ui.m_outputCombo->addItem("D");
	m_ui.m_outputCombo->addItem("B");

	QString validationRegex("[HCBhcb]");
	validationRegex+="{";
	validationRegex+=QString::number(m_engine.getInputVariablesCount());
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

	m_engine.addRule(m_ui.m_inputVector->text(),m_ui.m_outputCombo->currentText());

}

/*------------------------------------------------------------------------------*/

void
CompactRules::onItemDoubleClicked(QListWidgetItem * _item)
{
	QListWidgetItem* targetItem =
		m_ui.m_rulesList->takeItem(
		m_ui.m_rulesList->row(_item));

	delete targetItem;

}

/*------------------------------------------------------------------------------*/

void
CompactRules::showExtensiveView()
{
	QTextEdit* textView = new QTextEdit;

	QStringList rules;

	m_engine.makeFullRulesForm(rules);

	textView->setText(
		rules.join("\n")
		);

	textView->setReadOnly(true);

	textView->show();
}



/*------------------------------------------------------------------------------*/

} // namespace Pages
} // namespace Gui
} // namespace FuzzyLogic

/*------------------------------------------------------------------------------*/
