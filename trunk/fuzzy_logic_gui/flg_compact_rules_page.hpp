#ifndef __FUZZY_LOGIC_GUI_COMPACT_RULES_PAGE_HPP__
#define __FUZZY_LOGIC_GUI_COMPACT_RULES_PAGE_HPP__

#include <QtGui/QMainWindow>
#include "ui_flg_compact_rules_page.h"
#include "flg_engine_controller.hpp"
#include "flg_analysis_page.hpp"

/*------------------------------------------------------------------------------*/

namespace FuzzyLogic{
namespace Gui{
namespace Pages{

/*------------------------------------------------------------------------------*/

class UppercaseRegExpValidator
	:	public QRegExpValidator
{
	Q_OBJECT

public:

	UppercaseRegExpValidator( const QRegExp & _rx )
		:	QRegExpValidator(_rx)
	{}

	/*virtual*/ QValidator::State validate ( QString & input, int & pos ) const
	{
		input = input.toUpper();
		return QRegExpValidator::validate( input, pos );
	}

};

/*------------------------------------------------------------------------------*/

class CompactRules
	:	public QWidget
{
	Q_OBJECT

/*------------------------------------------------------------------------------*/

public:

/*------------------------------------------------------------------------------*/

	CompactRules(
			EngineController & _engine
		,	QMainWindow & _mainWindow
		,	QWidget *parent = 0
		);

	~CompactRules();

/*------------------------------------------------------------------------------*/

public:

/*------------------------------------------------------------------------------*/

	void closeDocks();

	void collectRules( QStringList & _rules );

	void applyRules( QStringList const & _rules );

/*------------------------------------------------------------------------------*/

protected slots:

/*------------------------------------------------------------------------------*/

	void onAddPress();

	void onItemDoubleClicked ( QListWidgetItem * item );

	void showExtensiveView();

	void showAnalysisView();

/*------------------------------------------------------------------------------*/

private:

/*------------------------------------------------------------------------------*/

	void refillRules();

	void showError(QString const & _text);

	void updateViews();

/*------------------------------------------------------------------------------*/

private:

/*------------------------------------------------------------------------------*/

	Ui::CompactRulesUi m_ui;

	QRegExpValidator* m_vectorValidator;

	EngineController & m_engine;

	QTextEdit* m_extensiveView;

	QMainWindow & m_mainWindow;

	QDockWidget * m_extensiveDock;

	QDockWidget * m_analysisDock;

	Analysis * m_analysisView;


/*------------------------------------------------------------------------------*/

};

/*------------------------------------------------------------------------------*/

} // namespace Pages
} // namespace Gui
} // namespace FuzzyLogic

/*------------------------------------------------------------------------------*/

#endif // __FUZZY_LOGIC_GUI_COMPACT_RULES_PAGE_HPP__
