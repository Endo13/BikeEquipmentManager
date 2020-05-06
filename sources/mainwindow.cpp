#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
    db.setDatabaseName(path);
    qDebug() << path;
    if(db.open())
        ui->status->setText("Database Connected");
    else
        ui->status->setText("Database not connected");
}

void MainWindow::on_actionAddGear_triggered()
{
    GearsDialog* gearsDialog = new GearsDialog(&db, this);
	gearsDialog->setAttribute(Qt::WA_DeleteOnClose);
	gearsDialog->setModal(true);
	gearsDialog->exec();
}

void MainWindow::on_actionShowGear_triggered()
{
	GearsView* gearsView  = new GearsView(&db, this);
	gearsView->setAttribute(Qt::WA_DeleteOnClose);
	gearsView->setModal(true);
	gearsView->exec();
}


