#include "savedialog.h"
#include "ui_savedialog.h"
#include <QDebug>
#include <QFileDialog>


SaveDialog::SaveDialog(QSqlDatabase *database, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveDialog)
{
    ui->setupUi(this);
    db = database;
    //setup models
   
}

void SaveDialog::on_pbExport_clicked()
{
	QString format = qApp->translate("Data", "data") + " (*.db);;";
	QString _dataDir;
	QString file = QFileDialog::getSaveFileName(this, tr("Exporter fichier"),
		_dataDir, format);

	if (QFile::exists(file))
	{
		QFile::remove(file);
	}
	QString path = qApp->applicationDirPath() + "/records/data.db";
	if (!QFile::copy(path,file)) {
		QMessageBox::warning(this, "Echec", QString::fromLatin1("Export impossible"));
	}
	else {
		QMessageBox::information(this, "Succes", "Export reussi");
		this->close();
	}
}

void SaveDialog::on_pbImport_clicked()
{
	QString format = qApp->translate("Data", "data") + " (*.db);;";
	QString _dataDir;
	QString file = QFileDialog::getOpenFileName(this, tr("Importer fichier"),
		_dataDir, format);
	
	if (QFile::exists(file)) {
		QString path = qApp->applicationDirPath() + "/records/data.db";
		db->close();
		if (QFile::exists(path))
		{
			QFile::remove(path);
		}
		if (!QFile::copy(file, path)) {
			QMessageBox::warning(this, "Echec", QString::fromLatin1("Import impossible"));
		}
		else {
			QMessageBox::information(this, "Succes", "Import reussi");
			db->setDatabaseName(path.toLatin1());
			if (db->open())
				qDebug() << "connected";
			else
				qDebug() << "not connected";
			this->close();
		}		
	}
	else {
		QMessageBox::warning(this, "Echec", QString::fromLatin1("Fichier introuvable"));
	}
}


void SaveDialog::on_pbQuit_clicked()
{
	this->close();
}

SaveDialog::~SaveDialog()
{
    delete ui;
}


