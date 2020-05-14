#include "ServiceBook.h"
#include "ui_ServiceBook.h"
#include <QSqlRecord>

ServiceBook::ServiceBook(QSqlDatabase *database, int ID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServiceBook)
{
    ui->setupUi(this);
    db = database;
	_idToEdit = ID;

	QSqlQuery q(*db);
	q.prepare("select serviceBook from bikes where ID=?");
	q.bindValue(0, _idToEdit);

	//execute the query
	if (!q.exec()) {//if the query has some error then return
		QMessageBox::critical(this, "Echec", "Modification imposible");
		QMessageBox::critical(this, "Error", q.lastError().text()
			+ "\n" + q.lastQuery());
		return;
	}

	// if the query executes
	// check for the result
	if (q.next()) {//if the result exists then load the description
		qint8	serviceBookIndex = q.record().indexOf("serviceBook");
		QString str = q.value(serviceBookIndex).toString();
		ui->plainTextEdit->setPlainText(str);
	}

	connect(ui->pbAdd, SIGNAL(clicked()), SLOT(on_add()));
}


ServiceBook::~ServiceBook()
{
    delete ui;
}



void ServiceBook::on_pbQuit_clicked()
{
	this->close();
}

void ServiceBook::on_add()
{
	QString str = ui->plainTextEdit->toPlainText();
	QSqlQuery q(*db);
	q.prepare("update bikes set serviceBook=? where ID=?");
	q.bindValue(0, str);
	q.bindValue(1, _idToEdit);

	//execute the query
	if (!q.exec()) {
		QMessageBox::critical(this, "Error", q.lastError().text()
			+ "\n" + q.lastQuery());
	}
}
