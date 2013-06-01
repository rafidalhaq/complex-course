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
	,	m_analysisDock(NULL)
	,	m_analysisView(NULL)
{
	m_ui.setupUi(this);

	connect(m_ui.m_addButton, SIGNAL(clicked()),
		this, SLOT(onAddPress()));

	connect(m_ui.m_inputVector, SIGNAL(returnPressed()),
		this, SLOT(onAddPress()));

	connect(m_ui.m_extensiveButton, SIGNAL(clicked()),
		this, SLOT(showExtensiveView()));

	connect(m_ui.m_analysisButton, SIGNAL(clicked()),
		this, SLOT(showAnalysisView()));

	connect(m_ui.m_rulesList, SIGNAL(itemDoubleClicked ( QListWidgetItem * )),
		this, SLOT(onItemDoubleClicked(QListWidgetItem*)));

	m_ui.m_outputCombo->addItem("OH");
	m_ui.m_outputCombo->addItem("H");
	m_ui.m_outputCombo->addItem("C");
	m_ui.m_outputCombo->addItem("D");
	m_ui.m_outputCombo->addItem("B");

	QString validationRegex("[HCB]");
	validationRegex+="{";
	validationRegex+=QString::number(m_engine.getInputVariablesCount());
	validationRegex+="}";
	m_vectorValidator = new UppercaseRegExpValidator(QRegExp(validationRegex));

	m_ui.m_inputVector->setValidator(m_vectorValidator);

	m_analysisView = new Analysis( m_engine );

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

	unsigned int concatenations =
		m_engine.addRule(m_ui.m_inputVector->text(),m_ui.m_outputCombo->currentText());

	m_ui.m_rulesList->addItem(
			QString::number(lineNumber+1)
		+	". "
		+	m_ui.m_inputVector->text()
		+	"->"
		+	m_ui.m_outputCombo->currentText()
		+	" ("
		+	QString::number(concatenations)
		+	")"
	);
}

/*------------------------------------------------------------------------------*/

void
CompactRules::onItemDoubleClicked(QListWidgetItem * _item)
{
	QListWidgetItem* targetItem =
		m_ui.m_rulesList->takeItem(
		m_ui.m_rulesList->row(_item));

	delete targetItem;

	refillRules();

}

/*------------------------------------------------------------------------------*/

void
CompactRules::showExtensiveView()
{
	if(!m_extensiveView)
		m_extensiveView = new QTextEdit;

	QStringList rules;

	m_engine.makeFullRulesForm(rules);

	for (int i = 0;i<rules.size(); i++)
	{
		rules[i].prepend(QString::number(i+1) + ". ");
	}

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
		m_extensiveDock = new QDockWidget(tr("Extensive Form"), this);
		m_extensiveDock->setAllowedAreas(Qt::LeftDockWidgetArea |
			Qt::RightDockWidgetArea);
		m_extensiveDock->setWidget(m_extensiveView);

		m_extensiveView->setMinimumSize(370,100);

		m_mainWindow.addDockWidget(Qt::RightDockWidgetArea, m_extensiveDock);
	}
}

/*------------------------------------------------------------------------------*/

void
CompactRules::refillRules()
{
	m_engine.removeAllRules();

	for(int row = 0; row < m_ui.m_rulesList->count(); row++)
	{
		QListWidgetItem * item =
			m_ui.m_rulesList->item(row);
		QString currentText = item->text();

		QString rule = currentText.section(". ",1);

		m_engine.addRule(
				rule.section("->", 0,0)	// input
			,	rule.section("->", 1).section(" (",0,0)	// output
		);

		item->setText(QString::number(row+1)+". "+ rule);
	}
}


/*------------------------------------------------------------------------------*/

void
CompactRules::showAnalysisView()
{
	if(m_analysisDock )
	{
		if( m_analysisDock->isHidden())
		{
			m_analysisView->initialize();
			m_analysisView->update();
			m_analysisDock->show();
		}
		else
		{
			return;
		}
	}
	else // no dock was created yet
	{
		m_analysisView->initialize();

		m_analysisDock = new QDockWidget("Analysis", this);
		m_analysisDock->setAllowedAreas(Qt::LeftDockWidgetArea |
			Qt::RightDockWidgetArea);
		m_analysisDock->setWidget(m_analysisView);
		m_mainWindow.addDockWidget(Qt::LeftDockWidgetArea, m_analysisDock);
	}

}

/*------------------------------------------------------------------------------*/

} // namespace Pages
} // namespace Gui
} // namespace FuzzyLogic

/*------------------------------------------------------------------------------*/
