#ifndef GearsView_H
#define GearsView_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QSqlError>
#include "gearsSqlModel.h"


namespace Ui {
class GearsView;
}

class GearsView : public QDialog
{
    Q_OBJECT

public:
    explicit GearsView(QSqlDatabase *database, QWidget *parent = 0);
    ~GearsView();
private slots:
	void on_pbQuit_clicked();
	void on_tableClicked(const QModelIndex &);
	void on_tableDoubleClicked(const QModelIndex &);
	void on_delete();
	void on_edit();


private:
    Ui::GearsView *ui;
    QSqlDatabase *db;
	gearsSqlModel *_model;
};

#endif // GearsView_H
