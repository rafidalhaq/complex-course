#include "stdafx.h"
#include "flg_project_setup_page.hpp"
/*------------------------------------------------------------------------------*/

namespace FuzzyLogic{
namespace Gui{
namespace Pages{

/*------------------------------------------------------------------------------*/


ProjectSetup::ProjectSetup(QWidget *parent)
	:	QWidget(parent)
{
	m_ui.setupUi(this);

	m_ui.m_typeCombo->addItem("input");
	m_ui.m_typeCombo->addItem("output");

	connect(m_ui.m_inputVariablesList, SIGNAL(itemDoubleClicked ( QListWidgetItem * )),
	 this, SLOT(onItemDoubleClicked(QListWidgetItem*)));

	connect(m_ui.m_addButton, SIGNAL(clicked()),
	 this, SLOT(onAddButton()));

	QString validationRegex("\\w+");
	m_ui.m_variableName->setValidator(
		new QRegExpValidator(QRegExp(validationRegex)));

}


/*------------------------------------------------------------------------------*/


ProjectSetup::~ProjectSetup()
{


}


/*------------------------------------------------------------------------------*/

QObject *
ProjectSetup::getNextButton()
{
	return m_ui.m_nextButton;
}


/*------------------------------------------------------------------------------*/


void
ProjectSetup::onItemDoubleClicked(QListWidgetItem * _item)
{
	QListWidgetItem* targetItem =
		m_ui.m_inputVariablesList->takeItem(
			m_ui.m_inputVariablesList->row(_item));

	if(_item->text().contains( "output - "))
		m_ui.m_typeCombo->addItem("output");

	updateNumbers();

	delete targetItem;

}


/*------------------------------------------------------------------------------*/


void
ProjectSetup::onAddButton()
{
	if(m_ui.m_variableName->text().isEmpty())
	{
		showError("Input variable name!");
		return;
	}

	int lineNumber = m_ui.m_inputVariablesList->count();

	m_ui.m_inputVariablesList->addItem(
			QString::number(lineNumber+1)
		+	". "
		+	m_ui.m_typeCombo->currentText()
		+	" - "
		+	m_ui.m_variableName->text()
	);

	if(m_ui.m_typeCombo->currentText() == "output")
		m_ui.m_typeCombo->removeItem(1);

	updateNumbers();

}


/*------------------------------------------------------------------------------*/


bool
ProjectSetup::commitChanges(EngineController & _engine)
{

	QList<QListWidgetItem*> inputVariables =
		m_ui.m_inputVariablesList->findItems(
			"*input - *"
		,	Qt::MatchWildcard
		);

	QList<QListWidgetItem*> outputVariables =
		m_ui.m_inputVariablesList->findItems(
		"*output - *"
		,	Qt::MatchWildcard
		);

	if(inputVariables.isEmpty())
	{
		showError("Add at least one input variable!");
		return false;
	}
	if(outputVariables.isEmpty())
	{
		showError("Add an output variable!");
		return false;
	}

	QList<QListWidgetItem*>::iterator ibeginIt = inputVariables.begin();
	QList<QListWidgetItem*>::iterator iendIt = inputVariables.end();
	while(ibeginIt!=iendIt)
	{
		QString text = (*ibeginIt)->text();

		_engine.addInputVariable(text.section(" - ",1));

		ibeginIt++;
	}

	QList<QListWidgetItem*>::iterator obeginIt = outputVariables.begin();
	QList<QListWidgetItem*>::iterator oendIt = outputVariables.end();
	while(obeginIt!=oendIt)
	{
		QString text = (*obeginIt)->text();
		_engine.addOutpuVariable(text.section(" - ",1));
		obeginIt++;
	}

	return true;

}


/*------------------------------------------------------------------------------*/

void
ProjectSetup::updateNumbers()
{
	for(int row = 0; row < m_ui.m_inputVariablesList->count(); row++)
	{
		QListWidgetItem * item =
			m_ui.m_inputVariablesList->item(row);

		QString currentText = item->text();

		item->setText(QString::number(row+1)+". "+currentText.section(" ",1) );
	}

	QList<QListWidgetItem*> variables =
		m_ui.m_inputVariablesList->findItems(
		"*input - *"
		,	Qt::MatchWildcard
		);

	QString text = m_ui.m_rulesCountLabel->text();

	int rulesCount = pow(3,(long double)variables.size());

	m_ui.m_rulesCountLabel->setText(text.section(":",0,0) + ":" + QString::number(rulesCount));


}


/*------------------------------------------------------------------------------*/

void
ProjectSetup::showError(QString const & _text)
{
	QMessageBox::warning(this, "Error", _text);
}

/*------------------------------------------------------------------------------*/

} // namespace Pages
} // namespace Gui
} // namespace FuzzyLogic

/*------------------------------------------------------------------------------*/
