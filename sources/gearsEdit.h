#ifndef GEARSEDIT_H
#define GEARSEDIT_H

#include <QDialog>
#include <QStringListModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QString>

#include "tableUtilities.h"

namespace Ui {
class GearsDialog;
}

class GearsEdit : public QDialog
{
    Q_OBJECT

public:
    explicit GearsEdit(QSqlDatabase* database, int ID, QWidget *parent = 0);

    ~GearsEdit();

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
	void changeMarque(int);

private:
    Ui::GearsDialog *ui;
    QSqlDatabase* db;
    QSqlQueryModel *unitsComboBoxModel;
	TableUtilities tableUtilities;
	int	_id;
};

#endif // ITEMCODEDIALOG_H
