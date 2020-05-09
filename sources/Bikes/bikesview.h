#ifndef BikesView_H
#define BikesView_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QSqlError>
#include "bikesSqlModel.h"


namespace Ui {
class BikesView;
}

class BikesView : public QDialog
{
    Q_OBJECT

public:
    explicit BikesView(QSqlDatabase *database, QWidget *parent = 0);
    ~BikesView();
private slots:
	void on_pbQuit_clicked();
	void on_tableClicked(const QModelIndex &);
	void on_tableDoubleClicked(const QModelIndex &);
	void on_delete();
	void on_edit();


private:
    Ui::BikesView *ui;
    QSqlDatabase *db;
	bikesSqlModel *_model;
};

#endif // BikesView_H
