#ifndef WORKOUTDIALOG_H
#define WORKOUTDIALOG_H

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
class WorkoutDialog;
}

class WorkoutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WorkoutDialog(QSqlDatabase* database, QWidget *parent = 0);

    ~WorkoutDialog();

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
	void on_import();

private:
    Ui::WorkoutDialog *ui;
    QSqlDatabase* db;
    QSqlQueryModel *unitsComboBoxModel;
	TableUtilities tableUtilities;
	QString _dataDir;
};

#endif // ITEMCODEDIALOG_H
