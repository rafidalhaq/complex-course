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

}


/*------------------------------------------------------------------------------*/


bool
ProjectSetup::commitChanges(EngineController & _engine)
{

	QList<QListWidgetItem*> variables =
		m_ui.m_inputVariablesList->findItems(
			"*input - *"
		,	Qt::MatchWildcard
		);

	if(variables.isEmpty())
	{
		showError("Add at list one input variable!");
		return false ;
	}

	QList<QListWidgetItem*>::iterator beginIt = variables.begin();
	QList<QListWidgetItem*>::iterator endIt = variables.end();
	while(beginIt!=endIt)
	{
		QString text = (*beginIt)->text();

		_engine.addInputVariable(text.section(" - ",1));

		beginIt++;
	}
	variables =
		m_ui.m_inputVariablesList->findItems(
			"*output - *"
		,	Qt::MatchWildcard
		);

	if(variables.isEmpty())
	{
		showError("Add an output variable!");
		return false;
	}

	beginIt = variables.begin();
	endIt = variables.end();
	while(beginIt!=endIt)
	{
		QString text = (*beginIt)->text();
		_engine.addOutpuVariable(text.section(" - ",1));
		beginIt++;
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
