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
	bool isComplete = m_engine.checkForCompleteness();

	QString text("Completeness analysis finished. The rules are ");
	text += isComplete ? "complete." : "not complete.";

	QTextEdit* result = new QTextEdit;

	result->setText( text );

	m_ui.m_resultsTabber->addTab(result,"Completeness");

}


/*------------------------------------------------------------------------------*/


void Analysis::consistency()
{
	bool isConsistent = m_engine.checkForConsistency();

	QString text(isConsistent?"consistent.":"not consistent.");

	QTextEdit* result = new QTextEdit;

	result->setText(
		"Consistency analysis finished. The rules are "
		+	text
		);

	m_ui.m_resultsTabber->addTab(result,"Consistency");

}

/*------------------------------------------------------------------------------*/


void Analysis::minimality()
{
	bool isMinimal = m_engine.checkForMinimality();

	QString text(isMinimal ? "minimal.":"not minimal.");

	QTextEdit* result = new QTextEdit;

	result->setText(
		"Minimality analysis finished. The rules are "
		+	text
		);

	m_ui.m_resultsTabber->addTab(result,"Minimality");

}

/*------------------------------------------------------------------------------*/


void Analysis::coherence()
{
	bool isCoherent = m_engine.checkForCoherence();

	QString text(isCoherent ? "coherent.":"not coherent.");

	QTextEdit* result = new QTextEdit;

	result->setText(
		"Coherence analysis finished. The rules are "
		+	text
		);

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
