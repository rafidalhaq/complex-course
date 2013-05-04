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

	connect(m_ui.m_inputVariablesList, SIGNAL(customContextMenuRequested(const QPoint&)),
	 this, SLOT(showContextMenu(const QPoint&)));
	connect(m_ui.m_inputVariablesList, SIGNAL(itemDoubleClicked ( QListWidgetItem * )),
	 this, SLOT(onItemDoubleClicked(QListWidgetItem*)));
	connect(m_ui.m_inputVariablesList, SIGNAL(itemDoubleClicked ( QListWidgetItem * )),
	 this, SLOT(onItemDoubleClicked(QListWidgetItem*)));

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
ProjectSetup::showContextMenu(const QPoint& pos) // this is a slot
{
    QPoint globalPos =
		m_ui.m_inputVariablesList->viewport()->mapToGlobal(pos);
   
    QMenu contextMenu;
	contextMenu.addAction(QString("Add"));

    QAction* selectedItem = contextMenu.exec(globalPos);
    if (selectedItem)
    {
		m_ui.m_inputVariablesList->addItem("variable_name");
    }
}


/*------------------------------------------------------------------------------*/


void
ProjectSetup::onItemDoubleClicked(QListWidgetItem * _item)
{
	_item->setFlags(_item->flags() | Qt::ItemIsEditable);

	m_ui.m_inputVariablesList->editItem(_item);

	_item->setFlags(_item->flags() & ~Qt::ItemIsEditable);

}


/*------------------------------------------------------------------------------*/

} // namespace Pages
} // namespace Gui
} // namespace FuzzyLogic

/*------------------------------------------------------------------------------*/
