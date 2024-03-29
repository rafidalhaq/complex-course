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
	m_vectorValidator.reset( new UppercaseRegExpValidator(QRegExp(validationRegex)) );

	m_ui.m_inputVector->setValidator(m_vectorValidator.data());

	m_analysisView.reset( new Analysis( m_engine ) );

}


/*------------------------------------------------------------------------------*/


CompactRules::~CompactRules()
{
	m_mainWindow.removeDockWidget(m_extensiveDock.data());
	m_mainWindow.removeDockWidget(m_analysisDock.data());
}


/*------------------------------------------------------------------------------*/

void
CompactRules::onAddPress()
{
	if(m_ui.m_inputVector->text().size()< m_engine.getInputVariablesCount())
	{
		showError("Too short input vector!");
		return;
	}

	int lineNumber = m_ui.m_rulesList->count();

	unsigned int concatenations =
		m_engine.addRule(m_ui.m_inputVector->text(),m_ui.m_outputCombo->currentText());

	if(concatenations)
	{
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
	else
	{
		showError("This cube is already covered!");
		return;
	}

	updateViews();
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

	updateViews();

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
		m_extensiveDock.reset( new QDockWidget(tr("Extensive Form"), this) );
		m_extensiveDock->setAllowedAreas(Qt::LeftDockWidgetArea |
			Qt::RightDockWidgetArea);
		m_extensiveDock->setWidget(m_extensiveView);

		m_extensiveView->setMinimumSize(370,100);

		m_mainWindow.addDockWidget(Qt::RightDockWidgetArea, m_extensiveDock.data());
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

		QString cubesCount = QString::number( m_engine.addRule(
					rule.section("->", 0,0)	// input
				,	rule.section("->", 1).section(" (",0,0)	// output
			)
		);

		item->setText(
				QString::number(row+1)
			+	". "
			+	rule.section(" (",0,0) // rule itself
			+	" (" + cubesCount + ")" ) 
		;
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

		m_analysisDock.reset( new QDockWidget("Analysis", this) );
		m_analysisDock->setAllowedAreas(Qt::LeftDockWidgetArea |
			Qt::RightDockWidgetArea);
		m_analysisDock->setWidget(m_analysisView.data());
		m_mainWindow.addDockWidget(Qt::LeftDockWidgetArea, m_analysisDock.data());
	}

}

/*------------------------------------------------------------------------------*/

void CompactRules::collectRules( QStringList & _rules )
{
	for(int row = 0; row < m_ui.m_rulesList->count(); row++)
	{
		QListWidgetItem * item =
			m_ui.m_rulesList->item(row);
		QString currentText = item->text();

		QString rule = currentText.section(". ",1);
		
		_rules.push_back(
				rule.section("->", 0,0)	// input
			+	"-"
			+	rule.section("->", 1).section(" (",0,0)	// output
		);
	}
}


/*------------------------------------------------------------------------------*/


void CompactRules::applyRules( QStringList const & _rules )
{
	for(int rule = 0; rule < _rules.size(); rule++)
	{
		QString input = _rules[rule].section("-",0,0);
		QString output = _rules[rule].section("-",1,1);

		unsigned int concatenations =
			m_engine.addRule(input,output);

		if(concatenations)
		{
			m_ui.m_rulesList->addItem(
				QString::number(rule+1)
				+	". "
				+	input
				+	"->"
				+	output
				+	" ("
				+	QString::number(concatenations)
				+	")"
				);
		}
	}
}

/*------------------------------------------------------------------------------*/

void
CompactRules::updateViews()
{
	if(m_analysisDock)
		m_analysisView->initialize();
	if(m_extensiveDock)
		showExtensiveView();
}

/*------------------------------------------------------------------------------*/

void
CompactRules::showError(QString const & _text)
{
	QMessageBox::warning(this, "Error", _text);
}


/*------------------------------------------------------------------------------*/

} // namespace Pages
} // namespace Gui
} // namespace FuzzyLogic

/*------------------------------------------------------------------------------*/
