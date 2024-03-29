#ifndef __FUZZY_LOGIC_GUI_ANALYSIS_PAGE_HPP__
#define __FUZZY_LOGIC_GUI_ANALYSIS_PAGE_HPP__

#include <QtGui/QMainWindow>

#include "ui_flg_analysis_page.h"
#include "flg_engine_controller.hpp"

/*------------------------------------------------------------------------------*/

namespace FuzzyLogic{
namespace Gui{
namespace Pages{

/*------------------------------------------------------------------------------*/

class Analysis
	:	public QWidget
{
	Q_OBJECT

/*------------------------------------------------------------------------------*/

public:

/*------------------------------------------------------------------------------*/

	Analysis(EngineController & _engine, QWidget *parent = 0);

	~Analysis();

/*------------------------------------------------------------------------------*/

public:

/*------------------------------------------------------------------------------*/

	void initialize();

/*------------------------------------------------------------------------------*/

public slots:

/*------------------------------------------------------------------------------*/

	void completeness();

	void minimality();

	void coherence();

	void consistency();


	void closeTab(int _index);

/*------------------------------------------------------------------------------*/

private:

/*------------------------------------------------------------------------------*/

	void showError(QString const & _text);

	void addTab(QString const & _title, QString const & _text);

/*------------------------------------------------------------------------------*/

private:

/*------------------------------------------------------------------------------*/

	Ui::AnalysisUi m_ui;

	EngineController & m_engine;

/*------------------------------------------------------------------------------*/

};

/*------------------------------------------------------------------------------*/

} // namespace Pages
} // namespace Gui
} // namespace FuzzyLogic

/*------------------------------------------------------------------------------*/

#endif // __FUZZY_LOGIC_GUI_ANALYSIS_PAGE_HPP__
