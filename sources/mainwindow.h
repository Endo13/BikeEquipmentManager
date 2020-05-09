#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include "Equipments/GearsDialog.h"
#include "Equipments/GearsView.h"
#include "Bikes/BikeDialog.h"
#include "Bikes/BikesView.h"

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
	void on_actionShowBike_triggered();
    void on_actionShowGear_triggered();
	void on_actionConfigBike_triggered();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
};

#endif // MAINWINDOW_H
