#ifndef GEARSDIALOG_H
#define GEARSDIALOG_H

#include <QDialog>
#include <QStringListModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QString>

namespace Ui {
class GearsDialog;
}

class GearsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GearsDialog(QSqlDatabase* database, QWidget *parent = 0);

    ~GearsDialog();

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

private:
    Ui::GearsDialog *ui;
    QSqlDatabase* db;
    QSqlQueryModel *unitsComboBoxModel;
};

#endif // ITEMCODEDIALOG_H
