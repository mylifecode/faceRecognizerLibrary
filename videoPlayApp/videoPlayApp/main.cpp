#include "videoPlayApp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	videoPlayApp w;
	w.setFixedSize(QSize(1000, 800));
	w.show();
	return a.exec();
}
