#include "stdafx.h"
#include "flg_compact_rules_page.hpp"

/*------------------------------------------------------------------------------*/

namespace FuzzyLogic{
namespace Gui{
namespace Pages{

/*------------------------------------------------------------------------------*/


CompactRules::CompactRules(
	EngineController & _engine
,	QMainWindow & _mainWindow
,	QWidget *parent
)
	:	QWidget(parent)
	,	m_engine(_engine)
	,	m_mainWindow(_mainWindow)
	,	m_extensiveView(NULL)
	,	m_extensiveDock(NULL)
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
	int lineNumber = m_ui.m_rulesList->count();

	m_ui.m_rulesList->addItem(
			QString::number(lineNumber+1)
		+	". "
		+	m_ui.m_inputVector->text()
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

	updateNumbers();

}

/*------------------------------------------------------------------------------*/

void
CompactRules::showExtensiveView()
{
	if(!m_extensiveView)
		m_extensiveView = new QTextEdit;

	QStringList rules;

	m_engine.makeFullRulesForm(rules);

	m_extensiveView->setText(
		rules.join("\n")
	);

	m_extensiveView->setReadOnly(true);

	if(m_extensiveDock )
	{
		if( m_extensiveDock->isHidden())
		{
			m_extensiveView->update();
			m_extensiveDock->show();
		}
		else
		{
			return;
		}
	}
	else // no dock was created yet
	{
		m_extensiveDock = new QDockWidget(tr("Extencive Form"), this);
		m_extensiveDock->setAllowedAreas(Qt::LeftDockWidgetArea |
			Qt::RightDockWidgetArea);
		m_extensiveDock->setWidget(m_extensiveView);

		m_mainWindow.addDockWidget(Qt::RightDockWidgetArea, m_extensiveDock);
	}
}

/*------------------------------------------------------------------------------*/

void
CompactRules::updateNumbers()
{
	for(int row = 0; row < m_ui.m_rulesList->count(); row++)
	{
		QListWidgetItem * item =
			m_ui.m_rulesList->item(row);
		QString currentText = item->text();
		item->setText(QString::number(row+1)+". "+currentText.section(" ",1) );
	}
}


/*------------------------------------------------------------------------------*/


QObject *
CompactRules::getAnalysisButton()
{
	return m_ui.m_analysisButton;
}


/*------------------------------------------------------------------------------*/

} // namespace Pages
} // namespace Gui
} // namespace FuzzyLogic

/*------------------------------------------------------------------------------*/
