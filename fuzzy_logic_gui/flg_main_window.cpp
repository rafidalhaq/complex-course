
#include "stdafx.h"
#include "flg_main_window.hpp"
#include "flg_analysis_page.hpp"

/*------------------------------------------------------------------------------*/

namespace FuzzyLogic{
namespace Gui{

/*------------------------------------------------------------------------------*/


MainWindow::MainWindow(QApplication* _mainApp)
	:	QMainWindow()
	,	m_compactRulesPage(NULL)
{
	m_ui.setupUi(this);

	m_projectSetupPage = new Pages::ProjectSetup;

	QObject::connect(m_ui.actionNew_Project, SIGNAL(triggered()),
                      this, SLOT(newProject()));

	QObject::connect(m_ui.actionSave, SIGNAL(triggered()),
		this, SLOT(saveProject()));

	QObject::connect(m_ui.actionLoad, SIGNAL(triggered()),
		this, SLOT(loadProject()));

	QObject::connect(m_ui.actionExit, SIGNAL(triggered()),
                      _mainApp, SLOT(quit() ));

	QObject::connect(m_projectSetupPage->getNextButton(), SIGNAL(clicked()),
                      this, SLOT(toCompactFormPage()));

}


/*------------------------------------------------------------------------------*/


MainWindow::~MainWindow()
{

}


/*------------------------------------------------------------------------------*/

void
MainWindow::newProject()
{
	if(m_compactRulesPage)
		m_compactRulesPage->closeDocks();

	setCentralWidget(NULL);
	m_projectSetupPage = new Pages::ProjectSetup;

	QObject::connect(m_projectSetupPage->getNextButton(), SIGNAL(clicked()),
		this, SLOT(toCompactFormPage()));

	setCentralWidget(m_projectSetupPage);
}


/*------------------------------------------------------------------------------*/

void
MainWindow::toCompactFormPage()
{
	if(!m_projectSetupPage->commitChanges(m_engine))
		return;

	setCentralWidget(NULL);
	m_compactRulesPage = new Pages::CompactRules(m_engine,*this);

	setCentralWidget(m_compactRulesPage);

} // MainWindow::toCompactFormPage


/*------------------------------------------------------------------------------*/


void
MainWindow::saveProject()
{
	QString fileName =
		QFileDialog::getSaveFileName(
			NULL
		,	"Save As"
		,	QString()
		,	"*.flp"
	);

} // MainWindow::saveProject


/*------------------------------------------------------------------------------*/


void
MainWindow::loadProject()
{
	QString fileName =
		QFileDialog::getOpenFileName(
			NULL
		,	"Load Project"
		,	QString()
		,	"*.flp"
	);

} // MainWindow::loadProject


/*------------------------------------------------------------------------------*/

} // namespace Gui
} // namespace FuzzyLogic

/*------------------------------------------------------------------------------*/
