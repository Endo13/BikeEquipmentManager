#include "GearsView.h"
#include "ui_GearsView.h"
#include "QSqlTableModel.h"

GearsView::GearsView(QSqlDatabase *database, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GearsView)
{
    ui->setupUi(this);
    db = database;

	QSqlTableModel *model = new QSqlTableModel(this, *db);
	model->setTable("gears");
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
	model->select();
	model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
	model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
	model->setHeaderData(2, Qt::Horizontal, QObject::tr("Marque"));
	model->setHeaderData(3, Qt::Horizontal, QObject::tr("Modele"));
	model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date d'achat"));
	model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date 1ere utilisation"));
	model->setHeaderData(6, Qt::Horizontal, QObject::tr("KM initial"));
	model->setHeaderData(7, Qt::Horizontal, QObject::tr("KM cumules"));
	model->setHeaderData(8, Qt::Horizontal, QObject::tr("Poids"));
	model->setHeaderData(9, Qt::Horizontal, QObject::tr("Prix"));
	model->setHeaderData(10, Qt::Horizontal, QObject::tr("Commander"));
	ui->twGears->setModel(model);
	ui->twGears->show();
}

GearsView::~GearsView()
{
    delete ui;
}
