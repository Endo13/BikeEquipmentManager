#ifndef WORKOUTEDIT_H
#define WORKOUTEDIT_H

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

class WorkoutEdit : public QDialog
{
    Q_OBJECT

public:
    explicit WorkoutEdit(QSqlDatabase* database, int ID, QWidget *parent = 0);

    ~WorkoutEdit();

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
    Ui::WorkoutDialog *ui;
    QSqlDatabase* db;
    QSqlQueryModel *unitsComboBoxModel;
	TableUtilities tableUtilities;
	int	_idToEdit;
	double _oldDistance;
};

#endif // ITEMCODEDIALOG_H
