#include "stdafx.h"
#include "flg_analysis_page.hpp"
/*------------------------------------------------------------------------------*/

namespace FuzzyLogic{
namespace Gui{
namespace Pages{

/*------------------------------------------------------------------------------*/


Analysis::Analysis(EngineController & _engine , QWidget *parent)
	:	QWidget(parent)
	,	m_engine(_engine)
{
	m_ui.setupUi(this);

	connect(m_ui.m_completButt, SIGNAL(clicked()),
		this, SLOT(completeness()));

	connect(m_ui.m_consistButt, SIGNAL(clicked()),
		this, SLOT(consistency()));

	connect(m_ui.m_minimalButt, SIGNAL(clicked()),
		this, SLOT(minimality()));

	connect(m_ui.m_coherenButt, SIGNAL(clicked()),
		this, SLOT(coherence()));

	connect(m_ui.m_resultsTabber, SIGNAL(tabCloseRequested(int)),
		this, SLOT(closeTab(int)));
}


/*------------------------------------------------------------------------------*/


Analysis::~Analysis()
{
}


/*------------------------------------------------------------------------------*/


void
Analysis::initialize()
{
	m_ui.m_rulesList->clear();

	QStringList rules;

	m_engine.makeCMRulesForm(rules);

	for (int i = 0;i<rules.size(); i++)
	{
		rules[i].prepend(QString::number(i+1) + ". ");
	}

	m_ui.m_rulesList->addItems(rules);
}


/*------------------------------------------------------------------------------*/

void Analysis::completeness()
{
	QString details;

	bool isComplete = m_engine.checkForCompleteness( details );

	QString text("Completeness analysis finished. The rules are ");
	if ( !isComplete )
		text += "not ";
	text += "complete.";

	if ( !isComplete )
		text += "\nThe following cubes are not covered:\n" + details;

	QTextEdit* result = new QTextEdit;

	result->setText( text );

	m_ui.m_resultsTabber->addTab(result,"Completeness");

}


/*------------------------------------------------------------------------------*/


void Analysis::consistency()
{
	QString details;

	bool isConsistent = m_engine.checkForConsistency( details );

	QString text("Consistency analysis finished. The rules are ");
	if ( !isConsistent )
		text += "not ";
	text += "consistent.";

	if ( !isConsistent )
		text += "\nThe following rules are not consistent:\n" + details;

	QTextEdit* result = new QTextEdit;

	result->setText( text );

	m_ui.m_resultsTabber->addTab(result,"Consistency");

}

/*------------------------------------------------------------------------------*/


void Analysis::minimality()
{
	QString details;

	bool isMinimal = m_engine.checkForMinimality( details );

	QString text("Minimality analysis finished. The rules are ");
	if ( !isMinimal )
		text += "not ";
	text += "minimal.";

	if ( !isMinimal )
		text += "\nThe following cubes are redundant:\n" + details;

	QTextEdit* result = new QTextEdit;

	result->setText( text );

	m_ui.m_resultsTabber->addTab(result,"Minimality");

}

/*------------------------------------------------------------------------------*/


void Analysis::coherence()
{
	QString details;

	bool isCoherent = m_engine.checkForCoherence( details );

	QString text("Coherence analysis finished. The rules are ");
	if ( !isCoherent )
		text += "not ";
	text += "coherent.";

	if ( !isCoherent )
		text += "\nThe following cube sets are not coherent with any other:\n" + details;

	QTextEdit* result = new QTextEdit;

	result->setText( text );

	m_ui.m_resultsTabber->addTab(result,"Coherence");

}

/*------------------------------------------------------------------------------*/


void
Analysis::closeTab(int _index)
{
	QWidget* tab = m_ui.m_resultsTabber->widget(_index);

	m_ui.m_resultsTabber->removeTab(_index);

	delete tab;
}


/*------------------------------------------------------------------------------*/


void
Analysis::showError(QString const & _text)
{
	QMessageBox::warning(this, "Error", _text);
}


/*------------------------------------------------------------------------------*/

} // namespace Pages
} // namespace Gui
} // namespace FuzzyLogic

/*------------------------------------------------------------------------------*/
