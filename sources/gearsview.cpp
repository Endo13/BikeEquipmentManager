#include "GearsView.h"
#include "ui_GearsView.h"
#include "ui_GearsDialog.h"
#include "gearsEdit.h"

GearsView::GearsView(QSqlDatabase *database, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GearsView)
{
    ui->setupUi(this);
    db = database;

	_model = new gearsSqlModel(this, db);
	_model->setTable("gears");
	_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
	_model->select();
	_model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
	_model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
	_model->setHeaderData(2, Qt::Horizontal, QObject::tr("Marque"));
	_model->setHeaderData(3, Qt::Horizontal, QObject::tr("Modele"));
	_model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date d'achat"));
	_model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date 1ere utilisation"));
	_model->setHeaderData(6, Qt::Horizontal, QObject::tr("KM initial"));
	_model->setHeaderData(7, Qt::Horizontal, QObject::tr("KM cumules"));
	_model->setHeaderData(8, Qt::Horizontal, QObject::tr("Poids"));
	_model->setHeaderData(9, Qt::Horizontal, QObject::tr("Prix"));
	_model->setHeaderData(10, Qt::Horizontal, QObject::tr("Commander"));
	_model->sort(1,Qt::SortOrder::AscendingOrder);
	ui->twGears->setModel(_model);

	ui->twGears->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui->twGears->setColumnHidden(0, true);
	ui->twGears->setColumnHidden(10, true);
	ui->twGears->verticalHeader()->hide();
	ui->twGears->show();
	

	ui->pbEdit->setEnabled(false);
	ui->pbDelete->setEnabled(false);

	connect(ui->twGears, SIGNAL(clicked(const QModelIndex &)), SLOT(on_tableClicked(const QModelIndex &)));
	connect(ui->twGears, SIGNAL(doubleClicked(const QModelIndex & )), SLOT(on_tableDoubleClicked(const QModelIndex &)));
	connect(ui->pbDelete, SIGNAL(clicked()), SLOT(on_delete()));
	connect(ui->pbEdit, SIGNAL(clicked()), SLOT(on_edit()));
}


GearsView::~GearsView()
{
    delete ui;
}

void GearsView::on_tableClicked(const QModelIndex &)
{
	ui->pbEdit->setEnabled(true);
	ui->pbDelete->setEnabled(true);
}

void GearsView::on_tableDoubleClicked(const QModelIndex &)
{
	on_edit();
}

void GearsView::on_delete()
{
	//confirms from the user
	QMessageBox::StandardButton reply;
	reply = QMessageBox::question(this, "Etes vous sur?",
		"Confirmer vous la suppression de cet equipement?",
		QMessageBox::Yes | QMessageBox::Cancel);
	//if the user accepts the dialog
	if (reply == QMessageBox::Yes) {
		int rowidx = ui->twGears->selectionModel()->currentIndex().row();
		int ID = _model->index(rowidx, 0).data().toInt();
		QSqlQuery q(*db);
		q.prepare("DELETE FROM gears where gear_code=?");
		q.bindValue(0,ID);

		//execute the query
		if (!q.exec()) {//if the query has some error then return
			QMessageBox::critical(this, "Echec", "Suppression imposible");
			QMessageBox::critical(this, "Error", q.lastError().text()
				+ "\n" + q.lastQuery());
		}
		else {
			_model->select();
			ui->pbEdit->setEnabled(false);
			ui->pbDelete->setEnabled(false);
			QMessageBox::information(this, "Succes", "Equipement supprime");
		}
	}
	ui->pbEdit->setEnabled(false);
	ui->pbDelete->setEnabled(false);

}

void GearsView::on_edit()
{
	int rowidx = ui->twGears->selectionModel()->currentIndex().row();
	int ID = _model->index(rowidx, 0).data().toInt();
	GearsEdit* gearsEdit = new GearsEdit(db, ID,this);
	gearsEdit->setAttribute(Qt::WA_DeleteOnClose);
	gearsEdit->setModal(true);
	gearsEdit->exec();
	_model->select();
	ui->pbEdit->setEnabled(false);
	ui->pbDelete->setEnabled(false);
}

void GearsView::on_pbQuit_clicked()
{
	this->close();
}
