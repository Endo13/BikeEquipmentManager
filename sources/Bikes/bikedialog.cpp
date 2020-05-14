#include "bikedialog.h"
#include "ui_bikedialog.h"
#include <QDebug>
#include <QSqlRecord>
#include <QComboBox>

BikeDialog::BikeDialog(QSqlDatabase *database, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BikeDialog)
{
    ui->setupUi(this);
    db = database;

    //setup models
    setupModels();

	//setup ui
	ui->leNom->setFocus();
	//Signal Slot

}

void BikeDialog::initializeModels()
{
    /// initializes all models
}

void BikeDialog::setupModels()
{
    /// sets up all models

    initializeModels();
    setupUnitsComboBoxModel();
    qDebug() << "setupModels called";
}

void BikeDialog::setupUnitsComboBoxModel()
{
    /// sets up the model for combo box	
	int row = 0;
	int column = 0;
	for (int i = 0; i<NB_GEARS;i++){
		QComboBox *cb = new QComboBox();
		QSqlQuery q(*db);
		q.prepare("select gear_code,marque,modele from gears where type=?");
		q.bindValue(0, i+1);
		
		//execute the query
		if (!q.exec()) {
		}
		QVariant Qid = 0;
		cb->addItem(QString::fromLatin1("Aucun équipement sélectionné"), Qid);
		while (q.next()) {//if the result exists then load the description					 
			qint8 marqueRec = q.record().indexOf("marque");
			qint8 modeleRec = q.record().indexOf("modele");
			qint8 codegearRec = q.record().indexOf("gear_code");
			QString id = q.value(marqueRec).toString();
			QString marque;
			QString mod = q.value(modeleRec).toString();
			QSqlQuery q2(*db);
			QString table = tableUtilities.getTableMarque(i+1);
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
		lab->setText(tableUtilities.getNomEquipement(i+1));
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

bool BikeDialog::validateForm()
{
    /// validates the form fields and checks if they are empty
	if (ui->leNom->text() == "") {
		return false;
	}

    return true;
}

bool BikeDialog::addItem()
{
    /// takes care of the query preperation and execution
    /// to add item to database items table
	QVector <int> eq;
	for (int i = 0; i < (NB_GEARS/2); i++) {
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
	QString queryPrep = "insert into bikes (nom";   
	QString queryPrepfin = ") values (:nom";
	for (int i = 0; i < NB_GEARS; i++) {
		queryPrep += ", eq" + QString::number( i + 1);
		queryPrepfin += ", :eq" + QString::number(i + 1);
	}
	queryPrepfin += " );";
	q.prepare(queryPrep + queryPrepfin);
	q.bindValue(":nom", nom);
	for (int i = 0; i < NB_GEARS; i++) {
		QString query = ":eq" + QString::number(i + 1);
		q.bindValue(query, eq[i]);
	}

    //execute the query
    if(!q.exec()){
        QMessageBox::critical(this, "Error", q.lastError().text()
                              + "\n" + q.lastQuery());
        return false;
    }
    return true;
}

void BikeDialog::resetForm()
{
    /// resets the form fields

}

void BikeDialog::on_pbQuit_clicked()
{
	this->close();
}

BikeDialog::~BikeDialog()
{
    delete ui;
}

void BikeDialog::on_add_pushButton_clicked()
{
    //// Validates the form
    /// Adds the item to the database items table
    /// and resets the form
    //validate form
    if(!validateForm()){
        QMessageBox::warning(this,"Remplir les champs", QString::fromLatin1("Remplir le champ nom du vélo"));
        return;
    }

    //confirms from the user
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"Etes vous sur?",
                                  "Confirmez vous la creation de cet equipement?",
                                  QMessageBox::Yes | QMessageBox::Cancel);
    //if the user accepts the dialog
    if (reply == QMessageBox::Yes){
        if(addItem()){
            QMessageBox::information(this, "Succes", "Equipement ajoute");
            resetForm();
			this->close();
        }
    }
	this->close();
}
