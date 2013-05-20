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

	if(_item->text().startsWith( "output"))
		m_ui.m_typeCombo->addItem("output");

	delete targetItem;

}


/*------------------------------------------------------------------------------*/


void
ProjectSetup::onAddButton()
{
	m_ui.m_inputVariablesList->addItem(
			m_ui.m_typeCombo->currentText()
		+	" - "
		+	m_ui.m_variableName->text()
	);

	if(m_ui.m_typeCombo->currentText() == "output")
		m_ui.m_typeCombo->removeItem(1);

}


/*------------------------------------------------------------------------------*/


void
ProjectSetup::commitChanges(EngineController & _engine)
{
	QList<QListWidgetItem*> variables =
		m_ui.m_inputVariablesList->findItems(
			"input*"
		,	Qt::MatchWildcard
		);
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
			"output*"
		,	Qt::MatchWildcard
		);
	beginIt = variables.begin();
	endIt = variables.end();
	while(beginIt!=endIt)
	{
		QString text = (*beginIt)->text();
		_engine.addOutpuVariable(text.section(" - ",1));
		beginIt++;
	}

}


/*------------------------------------------------------------------------------*/

} // namespace Pages
} // namespace Gui
} // namespace FuzzyLogic

/*------------------------------------------------------------------------------*/
