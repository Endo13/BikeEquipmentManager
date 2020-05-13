#ifndef STATISTICSDIALOG_H
#define STATISTICSDIALOG_H

#include <QDialog>
#include <QStringListModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QString>
#include <QtCharts>

#include "../Common/tableUtilities.h"

namespace Ui {
class StatisticsDialog;
}

class StatisticsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StatisticsDialog(QSqlDatabase* database, QWidget *parent = 0);

    ~StatisticsDialog();

private:
    //models



    //helper
	void showDistanceByMonth();
	void showBikesThisYear();
	void showDistanceByYear();
	void showPersonalRecords();

	QChartView * getMoyChartView();
	QChartView * getMaxChartView();
	
private slots:
	void on_pbQuit_clicked();

private:
    Ui::StatisticsDialog *ui;
	QSqlDatabase* db;
};

#endif // ITEMCODEDIALOG_H
