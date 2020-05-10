#ifndef WorkoutView_H
#define WorkoutView_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QSqlError>
#include "workoutSqlModel.h"


namespace Ui {
class WorkoutView;
}

class WorkoutView : public QDialog
{
    Q_OBJECT

public:
    explicit WorkoutView(QSqlDatabase *database, QWidget *parent = 0);
    ~WorkoutView();
private slots:
	void on_pbQuit_clicked();
	void on_tableClicked(const QModelIndex &);
	void on_tableDoubleClicked(const QModelIndex &);
	void on_delete();
	void on_edit();
	void on_add();

private:
    Ui::WorkoutView *ui;
    QSqlDatabase *db;
	workoutSqlModel *_model;
};

#endif // WorkoutView_H
