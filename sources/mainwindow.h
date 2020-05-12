#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include "Equipments/GearsView.h"
#include "Bikes/BikesView.h"
#include "Workouts/WorkoutView.h"
#include "Common/savedialog.h"
#include "Common/dondialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    void setupDatabase();

private slots:
    void on_actionAddGear_triggered();
	void on_actionConfigBike_triggered();
	void on_actionWorkout_triggered();
	void on_actionSave_triggered();
	void on_actionDon_triggered();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
};

#endif // MAINWINDOW_H
