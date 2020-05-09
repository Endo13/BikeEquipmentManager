#include "BikesView.h"
#include "ui_BikesView.h"
#include "ui_BikeDialog.h"
#include "bikesEdit.h"

BikesView::BikesView(QSqlDatabase *database, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BikesView)
{
    ui->setupUi(this);
    db = database;

	_model = new bikesSqlModel(this, db);
	_model->setTable("bikes");
	_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
	_model->select();
	_model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
	_model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
	_model->setHeaderData(2, Qt::Horizontal, QObject::tr("Marque cadre"));
	TableUtilities tableUtilities;
	for (int i = 0; i < NB_GEARS; i++) {
		_model->setHeaderData(i+3, Qt::Horizontal, QObject::tr(tableUtilities.getNomEquipement(i+1).toStdString().c_str()));
	}
	_model->sort(1,Qt::SortOrder::AscendingOrder);
	ui->twGears->setModel(_model);
	ui->twGears->resizeColumnsToContents();
	ui->twGears->setColumnHidden(0, true);
	ui->twGears->verticalHeader()->hide();
	ui->twGears->show();
	

	ui->pbEdit->setEnabled(false);
	ui->pbDelete->setEnabled(false);

	connect(ui->twGears, SIGNAL(clicked(const QModelIndex &)), SLOT(on_tableClicked(const QModelIndex &)));
	connect(ui->twGears, SIGNAL(doubleClicked(const QModelIndex & )), SLOT(on_tableDoubleClicked(const QModelIndex &)));
	connect(ui->pbDelete, SIGNAL(clicked()), SLOT(on_delete()));
	connect(ui->pbEdit, SIGNAL(clicked()), SLOT(on_edit()));
}


BikesView::~BikesView()
{
    delete ui;
}

void BikesView::on_tableClicked(const QModelIndex &)
{
	ui->pbEdit->setEnabled(true);
	ui->pbDelete->setEnabled(true);
}

void BikesView::on_tableDoubleClicked(const QModelIndex &)
{
	on_edit();
}

void BikesView::on_delete()
{
	//confirms from the user
	QMessageBox::StandardButton reply;
	reply = QMessageBox::question(this, QString::fromLatin1("Confirmation"),
		QString::fromLatin1("Confirmez vous la suppression de ce velo?"),
		QMessageBox::Yes | QMessageBox::Cancel);
	//if the user accepts the dialog
	if (reply == QMessageBox::Yes) {
		int rowidx = ui->twGears->selectionModel()->currentIndex().row();
		int ID = _model->index(rowidx, 0).data().toInt();
		QSqlQuery q(*db);
		q.prepare("DELETE FROM bikes where ID=?");
		q.bindValue(0,ID);

		//execute the query
		if (!q.exec()) {//if the query has some error then return
			QMessageBox::critical(this, "Echec", "Suppression impossible");
			QMessageBox::critical(this, "Error", q.lastError().text()
				+ "\n" + q.lastQuery());
		}
		else {
			_model->select();
			ui->pbEdit->setEnabled(false);
			ui->pbDelete->setEnabled(false);
			QMessageBox::information(this, "Succes", QString::fromLatin1("Velo supprime"));
		}
	}
	ui->pbEdit->setEnabled(false);
	ui->pbDelete->setEnabled(false);

}

void BikesView::on_edit()
{
	int rowidx = ui->twGears->selectionModel()->currentIndex().row();
	int ID = _model->index(rowidx, 0).data().toInt();
	BikesEdit* bikesEdit = new BikesEdit(db, ID,this);
	bikesEdit->setAttribute(Qt::WA_DeleteOnClose);
	bikesEdit->setModal(true);
	bikesEdit->exec();
	_model->select();
	ui->twGears->resizeColumnsToContents();
	ui->pbEdit->setEnabled(false);
	ui->pbDelete->setEnabled(false);
}

void BikesView::on_pbQuit_clicked()
{
	this->close();
}
