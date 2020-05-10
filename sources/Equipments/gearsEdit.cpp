#include "gearsEdit.h"
#include "ui_gearsdialog.h"
#include <QDebug>
#include "QDateTime.h"
#include <QSqlRecord>

GearsEdit::GearsEdit(QSqlDatabase *database, int ID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GearsDialog)
{
    ui->setupUi(this);
    db = database;
	_idToEdit = ID;
    //setup models
    setupModels();

	//setup ui
	ui->deAchat->setDisplayFormat("dd.MM.yyyy");
	ui->deUtilisation->setDisplayFormat("dd.MM.yyyy");
	//Signal Slot
	connect(ui->cbType, SIGNAL(currentIndexChanged(int)), SLOT(changeMarque(int)));
}

void GearsEdit::initializeModels()
{


    /// initializes all models
	//prepare the query
	QSqlQuery q(*db);
	q.prepare("select type,marque,modele,date_achat, date_utilisation, km_initial, poids, prix from gears where gear_code=?");
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
		qint8	typeIndex = q.record().indexOf("type"); 
		qint8	marqueIndex = q.record().indexOf("marque");
		qint8	modeleIndex = q.record().indexOf("modele");
		qint8	dateAchatIndex = q.record().indexOf("date_achat");
		qint8	dateUtilisationIndex = q.record().indexOf("date_utilisation");
		qint8	kmIndex = q.record().indexOf("km_initial");
		qint8	poidsIndex = q.record().indexOf("poids");
		qint8	prixIndex = q.record().indexOf("prix");

		ui->cbType->setCurrentIndex(q.value(typeIndex).toInt() - 1);
		changeMarque((q.value(typeIndex).toInt() - 1));
		ui->cbMarque->setCurrentIndex(q.value(marqueIndex).toInt() - 1);
		ui->leModele->setText(q.value(modeleIndex).toString());
		QString dateAchat = q.value(dateAchatIndex).toString();
		QDate DateAchat = QDate::fromString(dateAchat, "dd.MM.yyyy");
		ui->deAchat->setDate(DateAchat);
		QString dateUtilisation= q.value(dateUtilisationIndex).toString();
		QDate DateUtilisation = QDate::fromString(dateUtilisation, "dd.MM.yyyy");
		ui->deUtilisation->setDate(DateUtilisation);
		ui->spkm->setValue(q.value(kmIndex).toDouble());
		ui->lePoids->setValue(q.value(poidsIndex).toInt());
		ui->lePrix->setValue(q.value(prixIndex).toDouble());

	}
}

void GearsEdit::setupModels()
{
    /// sets up all models
	setupUnitsComboBoxModel();
    initializeModels();
}

void GearsEdit::setupUnitsComboBoxModel()
{
    /// sets up the model for combo box
	QSqlQueryModel *model = new QSqlQueryModel(ui->cbType);
	model->setQuery("SELECT nom FROM typeEquipement");
	ui->cbType->setModel(model);

	QSqlQueryModel *modeMarquel = new QSqlQueryModel(ui->cbMarque);
	modeMarquel->setQuery("SELECT nom FROM MarqueAmortisseurAR");
	ui->cbMarque->setModel(modeMarquel);
}

bool GearsEdit::validateForm()
{
    /// validates the form fields and checks if they are empty


    return true;
}

bool GearsEdit::addItem()
{
    /// takes care of the query preperation and execution
    /// to add item to database items table

    //gather arguments
	qint8	type = ui->cbType->currentIndex()+1;
	qint8   marque = ui->cbMarque->currentIndex()+1;
	QString modele = ui->leModele->text();
	QString dateAchat = ui->deAchat->text();
	QString dateUtilisation = ui->deUtilisation->text();
	double  kmInit = ui->spkm->value();
	double  poids = ui->lePoids->text().toDouble();
	double prix = ui->lePrix->text().toDouble();

	//prepare the query
	QSqlQuery q(*db);
	q.prepare("update gears set type=?, marque=?, modele=?, date_achat=? , date_utilisation=? , km_initial=? , poids=?, prix=?   where gear_code=?");
	q.bindValue(0, type);
	q.bindValue(1, marque);
	q.bindValue(2, modele);
	q.bindValue(3, dateAchat);
	q.bindValue(4, dateUtilisation);
	q.bindValue(5, kmInit);
	q.bindValue(6, poids);
	q.bindValue(7, prix);
	q.bindValue(8, _idToEdit);
   
    //execute the query
    if(!q.exec()){
        QMessageBox::critical(this, "Error", q.lastError().text()
                              + "\n" + q.lastQuery());
        return false;
    }
    return true;
}

void GearsEdit::resetForm()
{
    /// resets the form fields
    ui->leModele->clear();
    ui->cbType->setFocus();//focus on it
}

void GearsEdit::on_pbQuit_clicked()
{
	this->close();
}

void GearsEdit::changeMarque(int index)
{
	QSqlQueryModel *modeMarquel = new QSqlQueryModel(ui->cbMarque);
	QString table = tableUtilities.getTableMarque(index + 1);
	modeMarquel->setQuery("SELECT nom FROM "+table);
	ui->cbMarque->setModel(modeMarquel);
}

GearsEdit::~GearsEdit()
{
    delete ui;
}

void GearsEdit::on_add_pushButton_clicked()
{
    //// Validates the form
    /// Adds the item to the database items table
    /// and resets the form
    //validate form
    if(!validateForm()){
        QMessageBox::warning(this,"Fill Form", "Please Fill the form completely.");
        return;
    }

    //confirms from the user
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"Confirmation",
                                  "Confirmez vous la modification de cet equipement?",
                                  QMessageBox::Yes | QMessageBox::Cancel);
    //if the user accepts the dialog
    if (reply == QMessageBox::Yes){
        if(addItem()){
            QMessageBox::information(this, "Succes", "Equipement modifie");
            resetForm();
			this->close();
        }
    }
}
