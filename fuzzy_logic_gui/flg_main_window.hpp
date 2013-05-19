#ifndef __FUZZY_LOGIC_GUI_MAIN_WINDOW_HPP__
#define __FUZZY_LOGIC_GUI_MAIN_WINDOW_HPP__

#include <QtGui/QMainWindow>
#include "ui_flg_main_window.h"

#include "flg_project_setup_page.hpp"
#include "flg_compact_rules_page.hpp"

/*------------------------------------------------------------------------------*/

namespace FuzzyLogic{
namespace Gui{

/*------------------------------------------------------------------------------*/

class MainWindow
	:	public QMainWindow
{	
	Q_OBJECT

/*------------------------------------------------------------------------------*/

public:

/*------------------------------------------------------------------------------*/

	MainWindow( QApplication* _mainApp = NULL );
	~MainWindow();

/*------------------------------------------------------------------------------*/

public slots:

/*------------------------------------------------------------------------------*/

	void newProject();

	void toCompactFormPage();

/*------------------------------------------------------------------------------*/

private:

/*------------------------------------------------------------------------------*/

	Ui::Form_MainWindow m_ui;

	Pages::ProjectSetup* m_projectSetupPage;

	Pages::CompactRules* m_compactRulesPage;

/*------------------------------------------------------------------------------*/

};

/*------------------------------------------------------------------------------*/

} // namespace Gui
} // namespace FuzzyLogic

/*------------------------------------------------------------------------------*/

#endif // __FUZZY_LOGIC_GUI_MAIN_WINDOW_HPP__