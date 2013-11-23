
#include "stdafx.h"
#include "flg_main_window.hpp"
#include "flg_analysis_page.hpp"

#include <QtCore/QFile>

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

	QObject::connect(m_ui.actionAbout, SIGNAL(triggered()),
                      this, SLOT(about() ));

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

	m_engine.clearModels();

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

	QStringList rules;
	if(m_compactRulesPage)
		m_compactRulesPage->collectRules(rules);
	QStringList variables;
	m_engine.collectVariables(variables);

	QFile file(fileName);
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream out(&file);
	out << "----variables----\n";
	out << variables.join("\n");
	out << "\n------rules------\n";
	out << rules.join("\n");
	
	file.close();

} // MainWindow::saveProject


/*------------------------------------------------------------------------------*/


void
MainWindow::loadProject()
{
	setCentralWidget(NULL);

	if(m_compactRulesPage)
		m_compactRulesPage->closeDocks();

	m_engine.clearModels();

	QString fileName =
		QFileDialog::getOpenFileName(
			NULL
		,	"Load Project"
		,	QString()
		,	"*.flp"
	);

	QFile file(fileName);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QTextStream in(&file);

	QStringList rules;
	
	bool readVariables = false;
	bool outputAdded = false;

	while (!in.atEnd())
	{
		QString line = in.readLine();
		if(line == "----variables----")
		{
			readVariables = true;
			continue;
		}
		if(line == "------rules------")
		{
			readVariables = false;
			continue;
		}
		if (line.isEmpty())
			continue;

		QString first = line.section("-",0,0);
		QString second = line.section("-",1,1);

		if(readVariables)	
		{
			if(first == "o")
			{
				if( outputAdded )
				{
					QMessageBox::critical(NULL,"LoadError","More than one output variable!");
					m_engine.clearModels();
					return;
				}
				else
					m_engine.addOutpuVariable(second);
			}
			else
				m_engine.addInputVariable(second);
		}
		else
			rules.push_back(first+"-"+second);
	}

	m_compactRulesPage = new Pages::CompactRules(m_engine,*this);
	setCentralWidget(m_compactRulesPage);
	m_compactRulesPage->applyRules(rules);

} // MainWindow::loadProject


/*------------------------------------------------------------------------------*/


void
MainWindow::about()
{
	QMessageBox::about( this, "About FuzzyLogic",
		"FuzzyLogic is a simple program that helps to check fuzzy logic rules correctness.\n"
		"\n"
		"It was made as a term paper when studying in KhNURE (Ukraine)\n"
		"\n"
		"Developers:\n"
		"\t- Vasiliy Belous: model and core algorithms implementation\n"
		"\t- Ivan Zyenovich: GUI and project save/load implementation\n"
		"\n"
		"This program is distributed under the terms of the GNU GPL v3.\n"
		"\n"
		"\tCopyright (c) 2013 Ivan Zyenovich and Vasiliy Belous"
	);

} // MainWindow::about


/*------------------------------------------------------------------------------*/

} // namespace Gui
} // namespace FuzzyLogic

/*------------------------------------------------------------------------------*/
