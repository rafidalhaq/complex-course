#ifndef __FUZZY_LOGIC_GUI_COMPACT_RULES_PAGE_HPP__
#define __FUZZY_LOGIC_GUI_COMPACT_RULES_PAGE_HPP__

#include <QtGui/QMainWindow>
#include "ui_flg_compact_rules_page.h"
#include "flg_engine_controller.hpp"

/*------------------------------------------------------------------------------*/

namespace FuzzyLogic{
namespace Gui{
namespace Pages{

/*------------------------------------------------------------------------------*/

class CompactRules
	:	public QWidget
{
	Q_OBJECT

/*------------------------------------------------------------------------------*/

public:

/*------------------------------------------------------------------------------*/

	CompactRules(EngineController & _engine, QWidget *parent = 0);

	~CompactRules();


/*------------------------------------------------------------------------------*/

protected slots:

/*------------------------------------------------------------------------------*/

	void onAddPress();

	void onItemDoubleClicked ( QListWidgetItem * item );

	void showExtensiveView();

/*------------------------------------------------------------------------------*/

private:

/*------------------------------------------------------------------------------*/

	Ui::CompactRulesUi m_ui;

	QRegExpValidator* m_vectorValidator;

	EngineController & m_engine;

/*------------------------------------------------------------------------------*/

};

/*------------------------------------------------------------------------------*/

} // namespace Pages
} // namespace Gui
} // namespace FuzzyLogic

/*------------------------------------------------------------------------------*/

#endif // __FUZZY_LOGIC_GUI_COMPACT_RULES_PAGE_HPP__
