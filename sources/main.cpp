#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	QString locale = QLocale::system().name().section('_', 0, 0);

	
	if (locale == "fr") {
		QTranslator* translator = new QTranslator();
		if (translator->load(QString("BikeEquipmentManager_fr"), QCoreApplication::applicationDirPath()))
			a.installTranslator(translator);
	}
	else {
		QTranslator* translator = new QTranslator();
		if (translator->load(QString("BikeEquipmentManager_en"), QCoreApplication::applicationDirPath()))
			a.installTranslator(translator);
	}


    MainWindow w;
    w.show();

    return a.exec();
}
