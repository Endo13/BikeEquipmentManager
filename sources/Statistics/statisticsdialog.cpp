#include "statisticsdialog.h"
#include "ui_statisticsdialog.h"
#include <QDebug>

#include <QSqlRecord>
#include <sstream>
#include <iomanip>
#include <QtGlobal>

using namespace QtCharts;

StatisticsDialog::StatisticsDialog(QSqlDatabase *database, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StatisticsDialog)
{
    ui->setupUi(this);
    db = database;
    //setup models
	showDistanceByMonth();
	showDistanceByYear();
	showBikesThisYear();
	showPersonalRecords();
}

void StatisticsDialog::on_pbQuit_clicked()
{
	this->close();
}

StatisticsDialog::~StatisticsDialog()
{
    delete ui;
}

void StatisticsDialog::showDistanceByYear()
{
	qreal max = 1;
	qreal maxDen = 1;
	QDate d;
	int year = d.currentDate().year();
	QBarSeries *series = new QBarSeries();
	QLineSeries *lineseries = new QLineSeries();
	QStringList categories;
	QBarSet *set = new QBarSet(QObject::tr("Annees"));
	lineseries->setName(QObject::tr("Denivele"));
	int denCount = 0;
	for (int y = year - 4; y <= year; y++) {		
		categories << QString::number(y);
			
		QSqlQuery q(*db);
		QString query = "select sum(distance), sum(denivele) from workouts WHERE date like '%" + QString::number(y) + "-%' ";
		q.prepare(query);
		//execute the query
		if (!q.exec()) {//if the query has some error then return

		}
		if (q.next()) {//if the result exists then load the description					 
			qint8 dist = q.record().indexOf("sum(distance)");
			qint8 den = q.record().indexOf("sum(denivele)");
			if (q.value(dist).toDouble() > max)
				max = q.value(dist).toDouble();
			*set << q.value(dist).toDouble();
			if (q.value(den).toDouble() > maxDen)
				maxDen = q.value(den).toDouble();
			lineseries->append(QPointF(denCount++, q.value(den).toDouble() / 1000.0));
		}
		else {
			*set << 0;
			lineseries->append(QPointF(denCount++, 0));
		}
		
				
	}
	series->append(set);
	QChart *chart = new QChart();
	chart->addSeries(series);
	chart->addSeries(lineseries);
	chart->setTitle(QObject::tr("Distance (km) et denivele (km) parcourue par annee"));
	chart->setAnimationOptions(QChart::SeriesAnimations);

	
	QBarCategoryAxis *axisX = new QBarCategoryAxis();
	axisX->append(categories);
	chart->addAxis(axisX, Qt::AlignBottom);
	series->attachAxis(axisX);

	QValueAxis *axisY = new QValueAxis();
	axisY->setRange(0, max);
	chart->addAxis(axisY, Qt::AlignLeft);
	series->attachAxis(axisY);

	QValueAxis *axisY2 = new QValueAxis();
	axisY2->setRange(0, maxDen/1000.0);
	chart->addAxis(axisY2, Qt::AlignRight);
	lineseries->attachAxis(axisY2);

	chart->legend()->setVisible(true);
	chart->legend()->setAlignment(Qt::AlignBottom);

	chart->setTheme(QtCharts::QChart::ChartThemeDark);

	QChartView *chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);

	ui->gridLayout->addWidget(chartView, 0, 0);
}

void StatisticsDialog::showPersonalRecords()
{
	QChartView *chartViewMoy = getMoyChartView();
	QChartView *chartViewMax = getMaxChartView();
	QHBoxLayout *hlay = new QHBoxLayout();
	hlay->addWidget(chartViewMoy);
	hlay->addWidget(chartViewMax);
	ui->gridLayout->addLayout(hlay, 1, 1);
}

QChartView * StatisticsDialog::getMoyChartView()
{
	QDate d;
	int year = d.currentDate().year();
	QBarSet *moy = new QBarSet(QObject::tr("FC, Cadence et Puissance"));
	int maxMoy = 1;
	QSqlQuery q(*db);
	QString query = "select Max(FCMoyenne), Max(CadenceMoyenne), Max(PuissanceMoyenne) from workouts WHERE date like '%" + QString::number(year) + "-%'";
	q.prepare(query);
	//execute the query
	if (!q.exec()) {//if the query has some error then return

	}
	if (q.next()) {//if the result exists then load the description					 
		qint8 fcMIndex = q.record().indexOf("Max(FCMoyenne)");
		qint8 cadMIndex = q.record().indexOf("Max(CadenceMoyenne)");
		qint8 powMIndex = q.record().indexOf("Max(PuissanceMoyenne)");
		*moy << q.value(fcMIndex).toInt() << q.value(cadMIndex).toInt() << q.value(powMIndex).toInt();
		maxMoy = qMax(q.value(fcMIndex).toInt(), qMax(q.value(cadMIndex).toInt(), q.value(powMIndex).toInt()));
	}

	QStackedBarSeries *series = new QStackedBarSeries();
	series->append(moy);
	QChart *chart = new QChart();
	chart->addSeries(series);
	chart->setTitle(QObject::tr("Mes meilleures moyennes en ") + QString::number(year));
	chart->setAnimationOptions(QChart::SeriesAnimations);

	QStringList categories = {
		QObject::tr("F"), QObject::tr("C"), QObject::tr("P")
	};

	QBarCategoryAxis *axisX = new QBarCategoryAxis();
	axisX->append(categories);
	chart->addAxis(axisX, Qt::AlignBottom);
	QValueAxis *axisY = new QValueAxis();
	if (maxMoy == 0)
		maxMoy = 1;
	axisY->setRange(0, maxMoy);
	chart->addAxis(axisY, Qt::AlignLeft);
	series->attachAxis(axisX);
	series->attachAxis(axisY);
	chart->legend()->setVisible(true);
	chart->legend()->setAlignment(Qt::AlignBottom);
	chart->setTheme(QtCharts::QChart::ChartThemeDark);
	QChartView *chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);
	return chartView;
}

QChartView * StatisticsDialog::getMaxChartView()
{
	QDate d;
	int year = d.currentDate().year();
	QBarSet *max = new QBarSet(QObject::tr("FC, Cadence et Puissance Max"));
	int maxMax = 1;
	QSqlQuery q(*db);
	QString query = "select Max(FCMax), Max(CadenceMax), Max(PuissanceMax) from workouts WHERE date like '%" + QString::number(year) + "-%'";
	q.prepare(query);
	//execute the query
	if (!q.exec()) {//if the query has some error then return

	}
	if (q.next()) {//if the result exists then load the description					 
		qint8 fcMaxIndex = q.record().indexOf("Max(FCMax)");
		qint8 cadMaxIndex = q.record().indexOf("Max(CadenceMax)");
		qint8 powMaxIndex = q.record().indexOf("Max(PuissanceMax)");
		*max << q.value(fcMaxIndex).toInt() << q.value(cadMaxIndex).toInt() << q.value(powMaxIndex).toInt();
		maxMax = qMax(q.value(fcMaxIndex).toInt(), qMax(q.value(cadMaxIndex).toInt(), q.value(powMaxIndex).toInt()));
	}

	QStackedBarSeries *series = new QStackedBarSeries();
	series->append(max);
	QChart *chart = new QChart();
	chart->addSeries(series);
	chart->setTitle(QObject::tr("Mes records personels en ") + QString::number(year));
	chart->setAnimationOptions(QChart::SeriesAnimations);

	QStringList categories = {
		QObject::tr("F"), QObject::tr("C"), QObject::tr("P")
	};

	QBarCategoryAxis *axisX = new QBarCategoryAxis();
	axisX->append(categories);
	chart->addAxis(axisX, Qt::AlignBottom);
	QValueAxis *axisY = new QValueAxis();
	if (maxMax == 0)
		maxMax = 1;
	axisY->setRange(0, maxMax);
	chart->addAxis(axisY, Qt::AlignLeft);
	series->attachAxis(axisX);
	series->attachAxis(axisY);
	chart->legend()->setVisible(true);
	chart->legend()->setAlignment(Qt::AlignBottom);
	chart->setTheme(QtCharts::QChart::ChartThemeDark);
	QChartView *chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);
	return chartView;
}

void StatisticsDialog::showDistanceByMonth()
{
	qreal max = 1;
	QDate d;
	int year = d.currentDate().year();
	QBarSeries *series = new QBarSeries();

	for (int y = year - 4; y <= year; y++) {
		QBarSet *set = new QBarSet(QString::number(y));
		for (int i = 0; i < 13; i++) {
			std::stringstream ss;
			ss << std::setw(2) << std::setfill('0') << (i + 1);
			QString mois = QString::fromStdString(ss.str());
			QSqlQuery q(*db);
			QString query = "select sum(distance) from workouts WHERE date like '%" + QString::number(y) + "-" + mois + "-%' ";
			q.prepare(query);
			//execute the query
			if (!q.exec()) {//if the query has some error then return

			}
			if (q.next()) {//if the result exists then load the description					 
				qint8 dist = q.record().indexOf("sum(distance)");
				if (q.value(dist).toDouble() > max)
					max = q.value(dist).toDouble();
				*set << q.value(dist).toDouble();
			}
			else {
				*set << 0;
			}
			series->append(set);
		}
	}

	QChart *chart = new QChart();
	chart->addSeries(series);
	chart->setTitle(QObject::tr("Distance (km) parcourue par mois et annee"));
	chart->setAnimationOptions(QChart::SeriesAnimations);

	QStringList categories;
	categories << QObject::tr("Jan") << QObject::tr("Fev") << QObject::tr("Mar") << QObject::tr("Avr") << QObject::tr("Mai") << QObject::tr("Jun") << QObject::tr("Jui") << QObject::tr("Aou") << QObject::tr("Sep") << QObject::tr("Oct") << QObject::tr("Nov") << QObject::tr("Dec");
	QBarCategoryAxis *axisX = new QBarCategoryAxis();
	axisX->append(categories);
	chart->addAxis(axisX, Qt::AlignBottom);
	series->attachAxis(axisX);

	QValueAxis *axisY = new QValueAxis();
	axisY->setRange(0, max);
	chart->addAxis(axisY, Qt::AlignLeft);
	series->attachAxis(axisY);

	chart->legend()->setVisible(true);
	chart->legend()->setAlignment(Qt::AlignBottom);

	QChartView *chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);
	chart->setTheme(QtCharts::QChart::ChartThemeDark);
	ui->gridLayout->addWidget(chartView, 0, 1);
}

void StatisticsDialog::showBikesThisYear() {
	QDate d;
	int year = d.currentDate().year();
	// 
	int count = 0;
	QPieSeries *series = new QPieSeries();
	QSqlQuery q(*db);
	QString query = "select bikeID, sum(DISTINCT distance) from workouts WHERE date like '%" + QString::number(year) + "-%' group by bikeID; ";
	q.prepare(query);
	//execute the query
	if (!q.exec()) {//if the query has some error then return

	}
	while (q.next()) {//if the result exists then load the description					 
		qint8 dist = q.record().indexOf("sum(DISTINCT distance)");
		qint8 id = q.record().indexOf("bikeID");

		QSqlQuery q2(*db);
		q2.prepare("select nom from bikes where ID="+ q.value(id).toString());
		if (!q2.exec()) {//if the query has some error then return

		}
		if (q2.next()) {
			qint8 nom = q2.record().indexOf("nom");
			series->append(q2.value(nom).toString() + " - " + q.value(dist).toString() + " km", q.value(dist).toInt());
			QPieSlice *slice = series->slices().at(count++);
			slice->setExploded();
			slice->setLabelVisible();
			slice->setPen(QPen(Qt::black, 2));
			slice->setBrush(Qt::GlobalColor(count+12));
		}		
	}

	QChart *chart = new QChart();
	chart->addSeries(series);
	chart->setTitle(QObject::tr("Distance par velo en ")+QString::number(year));
	chart->setAnimationOptions(QChart::SeriesAnimations);
	chart->legend()->hide();

	QChartView *chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);
	chart->setTheme(QtCharts::QChart::ChartThemeDark);
	ui->gridLayout->addWidget(chartView, 1, 0);
}

