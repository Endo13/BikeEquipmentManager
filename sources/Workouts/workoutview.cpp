#include "WorkoutView.h"
#include "ui_WorkoutView.h"
#include "ui_WorkoutDialog.h"
#include "workoutEdit.h"
#include "workoutDialog.h"
#include <QSqlRecord>

WorkoutView::WorkoutView(QSqlDatabase *database, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WorkoutView)
{
    ui->setupUi(this);
    db = database;

	_model = new workoutSqlModel(this, db);
	_model->setTable("workouts");
	_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
	_model->select();
	_model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
	_model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
	_model->setHeaderData(2, Qt::Horizontal, QObject::tr(QString::fromLatin1("Vélo utilisé").toStdString().c_str()));	
	_model->setHeaderData(5, Qt::Horizontal, QObject::tr(QString::fromLatin1("Type de sortie").toStdString().c_str()));
	_model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date"));
	_model->setHeaderData(3, Qt::Horizontal, QObject::tr(QString::fromLatin1("Météo").toStdString().c_str()));
	_model->setHeaderData(6, Qt::Horizontal, QObject::tr("Distance (km)"));
	_model->setHeaderData(7, Qt::Horizontal, QObject::tr(QString::fromLatin1("Durée").toStdString().c_str()));
	_model->setHeaderData(8, Qt::Horizontal, QObject::tr(QString::fromLatin1("Dénivelé (m)").toStdString().c_str()));
	_model->setHeaderData(9, Qt::Horizontal, QObject::tr("Puissance moyenne (w)"));
	_model->setHeaderData(10, Qt::Horizontal, QObject::tr("Puissance max (w)"));
	_model->setHeaderData(11, Qt::Horizontal, QObject::tr("Energie (kJ)"));
	_model->setHeaderData(12, Qt::Horizontal, QObject::tr("Vitesse moyenne (km/h)"));
	_model->setHeaderData(13, Qt::Horizontal, QObject::tr("Vitesse max (km/h)"));
	_model->setHeaderData(14, Qt::Horizontal, QObject::tr(QString::fromLatin1("Fréquence moyenne").toStdString().c_str()));
	_model->setHeaderData(15, Qt::Horizontal, QObject::tr(QString::fromLatin1("Fréquence max").toStdString().c_str()));
	_model->setHeaderData(16, Qt::Horizontal, QObject::tr(QString::fromLatin1("Cadence moyenne").toStdString().c_str()));
	_model->setHeaderData(17, Qt::Horizontal, QObject::tr(QString::fromLatin1("Cadence max").toStdString().c_str())); 
	//_model->sort(4,Qt::SortOrder::DescendingOrder);
	ui->twGears->setModel(_model);
	ui->twGears->sortByColumn(4, Qt::SortOrder::DescendingOrder);
	ui->twGears->setSortingEnabled(true);
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
	connect(ui->pbAdd, SIGNAL(clicked()), SLOT(on_add()));
}


WorkoutView::~WorkoutView()
{
    delete ui;
}

void WorkoutView::on_tableClicked(const QModelIndex &)
{
	ui->pbEdit->setEnabled(true);
	ui->pbDelete->setEnabled(true);
}

void WorkoutView::on_tableDoubleClicked(const QModelIndex &)
{
	on_edit();
}

void WorkoutView::on_delete()
{
	//confirms from the user
	QMessageBox::StandardButton reply;
	reply = QMessageBox::question(this, "Confirmation",
		"Confirmez vous la suppression de cette sortie?",
		QMessageBox::Yes | QMessageBox::Cancel);
	//if the user accepts the dialog
	if (reply == QMessageBox::Yes) {
		int rowidx = ui->twGears->selectionModel()->currentIndex().row();
		int ID = _model->index(rowidx, 0).data().toInt();
		int bikeID = 0;
		double distance = _model->index(rowidx, 6).data().toDouble();
		QSqlQuery query(*db);
		query.prepare("select bikeID from workouts where ID=?");
		query.bindValue(0, ID);
		if (!query.exec()) {
		}
		if (query.next()) {
			qint8 bikeIndex = query.record().indexOf("bikeID");
			bikeID = query.value(bikeIndex).toInt();
		}

		QSqlQuery q(*db);
		q.prepare("DELETE FROM workouts where ID=?");
		q.bindValue(0,ID);

		//execute the query
		if (!q.exec()) {//if the query has some error then return
			QMessageBox::critical(this, "Echec", "Suppression impossible");
			QMessageBox::critical(this, "Error", q.lastError().text()
				+ "\n" + q.lastQuery());
		}
		else {
			TableUtilities tableutility;
			tableutility.updateKMEquipments(db, this, bikeID, -distance);
			_model->select();
			ui->pbEdit->setEnabled(false);
			ui->pbDelete->setEnabled(false);
			QMessageBox::information(this, "Succes", "Sortie supprimee");			
		}
	}
	ui->pbEdit->setEnabled(false);
	ui->pbDelete->setEnabled(false);

}

void WorkoutView::on_edit()
{
	int rowidx = ui->twGears->selectionModel()->currentIndex().row();
	int ID = _model->index(rowidx, 0).data().toInt();
	WorkoutEdit* wEdit = new WorkoutEdit(db, ID,this);
	wEdit->setAttribute(Qt::WA_DeleteOnClose);
	wEdit->setModal(true);
	wEdit->exec();
	_model->select();
	ui->pbEdit->setEnabled(false);
	ui->pbDelete->setEnabled(false);
}

void WorkoutView::on_add()
{
	WorkoutDialog* w = new WorkoutDialog(db, this);
	w->setAttribute(Qt::WA_DeleteOnClose);
	w->setModal(true);
	w->exec();
	_model->select();
	ui->twGears->resizeColumnsToContents();
}

void WorkoutView::on_pbQuit_clicked()
{
	this->close();
}
