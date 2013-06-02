#include "stdafx.h"
#include "flg_main_window.hpp"

#include "fuzzy_logic_engine/headers/fle_exceptions.hpp"

#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication mainApp(argc, argv);
	FuzzyLogic::Gui::MainWindow window(&mainApp);
	try
	{
		window.show();
		return mainApp.exec();
	}
	catch ( FuzzyLogicEngine::Exceptions::InternalError const& _e )
	{
		QString errorMessage( "An unknown internal error occured, the application will be closed.\n" );
		errorMessage += QString( "Error throw point: " ) + _e.getFile() + "(" + _e.getLine() + ")\n";
		if ( !_e.getErrorMessage().isEmpty() )
			errorMessage += QString( "Error description: " ) + _e.getErrorMessage() + ".\n";
		errorMessage += QString( "Please, contact the developers and provide this info with steps to reproduce." );
		QMessageBox::critical( &window, "Internal error", errorMessage );
		return -1;
	}
	catch ( std::exception const& /*_e*/ )
	{
		QMessageBox::critical(
				&window
			,	"Unhandled error"
			,	"An unknown internal error occured, the application will be closed.\nPlease, contact the developers."
		);
		return -1;
	}
}
