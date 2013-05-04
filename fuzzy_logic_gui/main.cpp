#include "stdafx.h"
#include "flg_main_window.hpp"

#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication mainApp(argc, argv);
	FuzzyLogic::Gui::MainWindow window(&mainApp);
	window.show();
	return mainApp.exec();
}
