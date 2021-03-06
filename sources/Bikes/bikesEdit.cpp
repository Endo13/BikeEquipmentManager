#include "bikesEdit.h"
#include "ui_bikedialog.h"
#include <QDebug>
#include <QSqlRecord>
#include <QComboBox>

BikesEdit::BikesEdit(QSqlDatabase *database, int ID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BikeDialog)
{
    ui->setupUi(this);
    db = database;
	_idToEdit = ID;
    //setup models
    setupModels();

	//setup ui
	ui->leNom->setFocus();
	//Signal Slot

}

void BikesEdit::initializeModels()
{
    /// initializes all models
	//prepare the query
	QSqlQuery q(*db);
	QString queryPrep = "select nom";
	
	for (int i = 0; i < NB_GEARS; i++) {
		queryPrep += ", eq" + QString::number(i + 1);
	}
	queryPrep += " from bikes where ID = ? ";
	q.prepare(queryPrep);
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
		qint8	nomIndex = q.record().indexOf("nom"); 
		ui->leNom->setText(q.value(nomIndex).toString());
		QVector <int> eq;
		for (int i = 0; i < NB_GEARS; i++) {
			qint8 eqIndex = q.record().indexOf("eq" + QString::number(i + 1));
			eq.push_back(q.value(eqIndex).toInt());
		}
		
		for (int i = 0; i < NB_GEARS/2; i++) {
			QComboBox *cb = (QComboBox*)ui->gridLayout->itemAtPosition(i, 1)->widget();
			int index = cb->findData(eq.first());
			eq.removeFirst();
			if (index > 0) { // -1 for not found
				cb->setCurrentIndex(index);
			}
		}
		for (int i = 0; i < NB_GEARS/2; i++) {
			QComboBox *cb = (QComboBox*)ui->gridLayout->itemAtPosition(i, 3)->widget();
			int index = cb->findData(eq.first());
			eq.removeFirst();
			if (index > 0) { // -1 for not found
				cb->setCurrentIndex(index);
			}
		}	
	}
}

void BikesEdit::setupModels()
{
    /// sets up all models
	setupUnitsComboBoxModel();
    initializeModels();
}

void BikesEdit::setupUnitsComboBoxModel()
{
    /// sets up the model for combo box
	int row = 0;
	int column = 0;
	for (int i = 0; i<NB_GEARS; i++) {
		QComboBox *cb = new QComboBox();
		QSqlQuery q(*db);
		q.prepare("select gear_code,marque,modele from gears where type=?");
		q.bindValue(0, i + 1);

		//execute the query
		if (!q.exec()) {
		}
		QVariant Qid = 0;
		cb->addItem(QObject::tr("Aucun equipement selectionne"), Qid);
		while (q.next()) {//if the result exists then load the description					 
			qint8 marqueRec = q.record().indexOf("marque");
			qint8 modeleRec = q.record().indexOf("modele");
			qint8 codegearRec = q.record().indexOf("gear_code");
			QString id = q.value(marqueRec).toString();
			QString marque;
			QString mod = q.value(modeleRec).toString();
			QSqlQuery q2(*db);
			QString table = tableUtilities.getTableMarque(i + 1);
			q2.prepare("select nom from " + table + " where ID=?");
			q2.bindValue(0, id);
			if (!q2.exec()) {//if the query has some error then return
				QString err = q2.lastError().text();
			}
			if (q2.next()) {
				qint8 nomRec = q2.record().indexOf("nom");
				marque = q2.value(nomRec).toString();
			}
			Qid = q.value(codegearRec);
			cb->addItem(marque + " - " + mod, Qid);
		}
		QLabel *lab = new QLabel();
		lab->setText(tableUtilities.getNomEquipement(i + 1));
		ui->gridLayout->addWidget(lab, row, column);
		ui->gridLayout->addWidget(cb, row, column + 1);
		ui->gridLayout->setColumnStretch(1, 1);
		ui->gridLayout->setColumnStretch(3, 1);
		row++;
		if (row == (NB_GEARS/2)) {
			row = 0;
			column = 2;
		}
	}
	
}

bool BikesEdit::validateForm()
{
    /// validates the form fields and checks if they are empty


    return true;
}

bool BikesEdit::addItem()
{
    /// takes care of the query preperation and execution
    /// to add item to database items table
	QVector <int> eq;
	for (int i = 0; i < NB_GEARS/2; i++) {
		QComboBox *cb = (QComboBox*)ui->gridLayout->itemAtPosition(i, 1)->widget();
		eq.push_back(cb->itemData(cb->currentIndex()).toInt());
	}
	for (int i = 0; i < NB_GEARS/2; i++) {
		QComboBox *cb = (QComboBox*)ui->gridLayout->itemAtPosition(i, 3)->widget();
		eq.push_back(cb->itemData(cb->currentIndex()).toInt());
	}

	QString nom = ui->leNom->text();

	//prepare the query
	QSqlQuery q(*db);
	QString queryPrep = "update bikes set nom=?";
	for (int i = 0; i < NB_GEARS; i++) {
		queryPrep += ", eq" + QString::number(i + 1) + "=?";
	}
	queryPrep += " where ID = ? ";
	q.prepare(queryPrep);
	q.bindValue(0, nom);
	for (int i = 0; i < NB_GEARS; i++) {
		q.bindValue(i+1, eq[i]);
	}
	q.bindValue(NB_GEARS+1, _idToEdit);

	//execute the query
	if (!q.exec()) {
		QMessageBox::critical(this, "Error", q.lastError().text()
			+ "\n" + q.lastQuery());
		return false;
	}
	return true;
}

void BikesEdit::resetForm()
{
    /// resets the form fields

}

void BikesEdit::on_pbQuit_clicked()
{
	this->close();
}

BikesEdit::~BikesEdit()
{
    delete ui;
}

void BikesEdit::on_add_pushButton_clicked()
{
    //// Validates the form
    /// Adds the item to the database items table
    /// and resets the form
    //validate form
        if(!validateForm()){
        QMessageBox::warning(this, QObject::tr("Remplir les champs"), QObject::tr("Remplir le champ nom du velo"));
        return;
    }

    //confirms from the user
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, QObject::tr("Confirmation"),
			QObject::tr("Confirmez vous la modification de ce velo?"),
                                  QMessageBox::Yes | QMessageBox::Cancel);
    //if the user accepts the dialog
    if (reply == QMessageBox::Yes){
        if(addItem()){
            QMessageBox::information(this, QObject::tr("Succes"), QObject::tr("Velo modifie"));
            resetForm();
        }
    }
	this->close();
}
