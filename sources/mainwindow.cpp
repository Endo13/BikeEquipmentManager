#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QDebug>
#include <QStyleFactory>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	// set style
	qApp->setStyle(QStyleFactory::create("Fusion"));
	// increase font size for better reading
	QFont defaultFont = QApplication::font();
	defaultFont.setPointSize(defaultFont.pointSize() + 2);
	qApp->setFont(defaultFont);
	// modify palette to dark
	QPalette darkPalette;
	darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
	darkPalette.setColor(QPalette::WindowText, Qt::white);
	darkPalette.setColor(QPalette::Disabled, QPalette::WindowText, QColor(127, 127, 127));
	darkPalette.setColor(QPalette::Base, QColor(42, 42, 42));
	darkPalette.setColor(QPalette::AlternateBase, QColor(66, 66, 66));
	darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
	darkPalette.setColor(QPalette::ToolTipText, Qt::white);
	darkPalette.setColor(QPalette::Text, Qt::white);
	darkPalette.setColor(QPalette::Disabled, QPalette::Text, QColor(127, 127, 127));
	darkPalette.setColor(QPalette::Dark, QColor(35, 35, 35));
	darkPalette.setColor(QPalette::Shadow, QColor(20, 20, 20));
	darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
	darkPalette.setColor(QPalette::ButtonText, Qt::white);
	darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, QColor(127, 127, 127));
	darkPalette.setColor(QPalette::BrightText, Qt::red);
	darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
	darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
	darkPalette.setColor(QPalette::Disabled, QPalette::Highlight, QColor(80, 80, 80));
	darkPalette.setColor(QPalette::HighlightedText, Qt::white);
	darkPalette.setColor(QPalette::Disabled, QPalette::HighlightedText, QColor(127, 127, 127));
	qApp->setPalette(darkPalette);

	connect(ui->pbAddGear, SIGNAL(clicked()), SLOT(on_actionAddGear_triggered()));
	connect(ui->pbConfigBike, SIGNAL(clicked()), SLOT(on_actionConfigBike_triggered()));
	connect(ui->pbWorkout, SIGNAL(clicked()), SLOT(on_actionWorkout_triggered()));
	connect(ui->pbSave, SIGNAL(clicked()), SLOT(on_actionSave_triggered()));
	connect(ui->pbDon, SIGNAL(clicked()), SLOT(on_actionDon_triggered()));
	connect(ui->pbStatistics, SIGNAL(clicked()), SLOT(on_actionStatistics_triggered()));

    setupDatabase();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupDatabase()
{
    /// searches for the database file
    /// if it finds it then connect to it
    /// otherwise open a file dialog and ask the user to locate the file
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString path = qApp->applicationDirPath()+"/records/data.db";
    QFile dbFile(path);
    if(!dbFile.exists()){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"Database","No database Exists."
                                              "Do you want to open your own database?",
                              QMessageBox::Yes | QMessageBox::No);
        if(reply==QMessageBox::Yes)
            path = QFileDialog::getOpenFileName(this,"Database",QDir::currentPath());
        else{
            qApp->closeAllWindows();
            qApp->exit(0);
        }
    }
    db.setDatabaseName(path.toLatin1());
	qDebug() << path;
	if (db.open())
		qDebug() << "connected";
	else
		qDebug() << "not connected";
}

void MainWindow::on_actionAddGear_triggered()
{
	GearsView* gearsView = new GearsView(&db, this);
	gearsView->setAttribute(Qt::WA_DeleteOnClose);
	gearsView->setModal(true);
	gearsView->exec();
}


void MainWindow::on_actionConfigBike_triggered()
{
	BikesView* bike = new BikesView(&db, this);
	bike->setAttribute(Qt::WA_DeleteOnClose);
	bike->setModal(true);
	bike->exec();
}

void MainWindow::on_actionWorkout_triggered()
{
	WorkoutView* w = new WorkoutView(&db, this);
	w->setAttribute(Qt::WA_DeleteOnClose);
	w->setModal(true);
	w->exec();
}

void MainWindow::on_actionSave_triggered()
{
	SaveDialog *w = new SaveDialog(&db, this);
	w->setAttribute(Qt::WA_DeleteOnClose);
	w->setModal(true);
	w->exec();
}

void MainWindow::on_actionDon_triggered()
{
	donDialog *w = new donDialog(this);
	w->setAttribute(Qt::WA_DeleteOnClose);
	w->setModal(true);
	w->exec();
}

void MainWindow::on_actionStatistics_triggered()
{
	StatisticsDialog *w = new StatisticsDialog(&db, this);
	w->setAttribute(Qt::WA_DeleteOnClose);
	w->setModal(true);
	w->exec();
}

