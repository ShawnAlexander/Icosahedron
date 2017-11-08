#include "SJWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SJWindow w;
	w.show();
	return a.exec();
}
