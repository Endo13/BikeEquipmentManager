#ifndef SERVICEBOOK_H
#define SERVICEBOOK_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QSqlError>



namespace Ui {
class ServiceBook;
}

class ServiceBook : public QDialog
{
    Q_OBJECT

public:
    explicit ServiceBook(QSqlDatabase *database, int ID, QWidget *parent = 0);
    ~ServiceBook();
private slots:
	void on_pbQuit_clicked();
	void on_add();


private:
    Ui::ServiceBook *ui;
    QSqlDatabase *db;
	int _idToEdit;
};

#endif // ServiceBook_H
