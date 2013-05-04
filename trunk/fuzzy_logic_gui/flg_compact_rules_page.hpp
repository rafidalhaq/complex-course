#ifndef __FUZZY_LOGIC_GUI_COMPACT_RULES_PAGE_HPP__
#define __FUZZY_LOGIC_GUI_COMPACT_RULES_PAGE_HPP__

#include <QtGui/QMainWindow>
#include "ui_flg_compact_rules_page.h"

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

	CompactRules(QWidget *parent = 0);

	~CompactRules();


/*------------------------------------------------------------------------------*/

private:

/*------------------------------------------------------------------------------*/

	Ui::CompactRulesUi m_ui;

/*------------------------------------------------------------------------------*/

};

/*------------------------------------------------------------------------------*/

} // namespace Pages
} // namespace Gui
} // namespace FuzzyLogic

/*------------------------------------------------------------------------------*/

#endif // __FUZZY_LOGIC_GUI_COMPACT_RULES_PAGE_HPP__
