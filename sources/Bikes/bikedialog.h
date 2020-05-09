#ifndef BIKEDIALOG_H
#define BIKEDIALOG_H

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
class BikeDialog;
}

class BikeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BikeDialog(QSqlDatabase* database, QWidget *parent = 0);

    ~BikeDialog();

private:
    //models
    void initializeModels();
    void setupModels();
    void setupUnitsComboBoxModel();


    //helper
    bool validateForm();
    bool addItem();
    void resetForm();

	
private slots:
    void on_add_pushButton_clicked();
	void on_pbQuit_clicked();

private:
    Ui::BikeDialog *ui;
    QSqlDatabase* db;
    QSqlQueryModel *unitsComboBoxModel;
	TableUtilities tableUtilities;
};

#endif // ITEMCODEDIALOG_H
