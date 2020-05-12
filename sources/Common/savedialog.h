#ifndef SAVEDIALOG_H
#define SAVEDIALOG_H

#include <QDialog>
#include <QStringListModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QString>

#include "../Common/tableUtilities.h"

namespace Ui {
class SaveDialog;
}

class SaveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaveDialog(QSqlDatabase* database, QWidget *parent = 0);

    ~SaveDialog();

private:
    //models



    //helper


	
private slots:
    void on_pbImport_clicked();
	void on_pbExport_clicked();
	void on_pbQuit_clicked();

private:
    Ui::SaveDialog *ui;
	QSqlDatabase* db;
};

#endif // ITEMCODEDIALOG_H
