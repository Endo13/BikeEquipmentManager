#ifndef BIKESEDIT_H
#define BIKESEDIT_H

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

class BikesEdit : public QDialog
{
    Q_OBJECT

public:
    explicit BikesEdit(QSqlDatabase* database, int ID, QWidget *parent = 0);

    ~BikesEdit();

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
	int	_idToEdit;
};

#endif // ITEMCODEDIALOG_H
