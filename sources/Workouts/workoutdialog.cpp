#include "workoutdialog.h"
#include "ui_workoutdialog.h"
#include <QDebug>
#include <QSqlRecord>

WorkoutDialog::WorkoutDialog(QSqlDatabase *database, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WorkoutDialog)
{
    ui->setupUi(this);
    db = database;

    //setup models
    setupModels();

	//setup ui
	ui->deSortie->setDate(QDate::currentDate());
	ui->deSortie->setDisplayFormat("dd.MM.yyyy");
	
	//Signal Slot

}

void WorkoutDialog::initializeModels()
{
    /// initializes all models
}

void WorkoutDialog::setupModels()
{
    /// sets up all models

    initializeModels();
    setupUnitsComboBoxModel();
    qDebug() << "setupModels called";
}

void WorkoutDialog::setupUnitsComboBoxModel()
{
    /// sets up the model for combo box
	QSqlQueryModel *modeMarquel = new QSqlQueryModel(ui->cbBike);
	modeMarquel->setQuery("SELECT nom FROM bikes");
	ui->cbBike->setModel(modeMarquel);	
}

bool WorkoutDialog::validateForm()
{
    /// validates the form fields and checks if they are empty
    return true;
}

bool WorkoutDialog::addItem()
{
    /// takes care of the query preperation and execution
    /// to add item to database items table
	QString	bikeName = ui->cbBike->currentText();
	int bikeID = 0;
	QSqlQuery q(*db);
	q.prepare("select ID from bikes where nom=?");
	q.bindValue(0, bikeName);
	//execute the query
	if (!q.exec()) {
	}
	if (q.next()) {
		qint8 index = q.record().indexOf("ID");
		bikeID = q.value(index).toInt();
	}

	QString nom = ui->leNom->text();
	qint8	type = ui->cbType->currentIndex();
	QString date = ui->deSortie->text();
	double  distance = ui->spDistance->value();
	QString  duree = ui->teSortie->text();
	int denivele = ui->spDenivele->value();
	int puissanceMoyenne = ui->spPuissanceMoyenne->value();
	int puissanceMax = ui->spPuissanceMax->value();
	int energie = ui->spEnergie->value();
	double vitesseMoyenne = ui->spVitesseMoyenne->value();
	double vitesseMax = ui->spVitesseMax->value();
	int FCMoyenne = ui->spFCMoyenne->value();
	int FCMax = ui->spFCMax->value();
	int CadenceMoyenne = ui->spCadenceMoyenne->value();
	int CadenceMax = ui->spCadenceMax->value();
	int meteo = 0;
	if (ui->rbSun->isChecked()) {
		meteo = SUN;
	}
	else if (ui->rbRain->isChecked()) {
		meteo = RAIN;
	}
	else if (ui->rbWind->isChecked()) {
		meteo = WIND;
	}

	//prepare the query
	QSqlQuery q2(*db);
	q2.prepare("insert into workouts (bikeID, nom, type, date, distance, duree, denivele, puissanceMoyenne, puissanceMax, energie, vitesseMoyenne, vitesseMax, FCMoyenne, FCMax, CadenceMoyenne, CadenceMax, meteo) values "
		"(:bikeID, :nom, :type, :date, :distance, :duree, :denivele, :puissanceMoyenne, :puissanceMax, :energie, :vitesseMoyenne, :vitesseMax, :FCMoyenne, :FCMax, :CadenceMoyenne, :CadenceMax, :meteo );");
	
	q2.bindValue(":bikeID", bikeID);
	q2.bindValue(":nom", nom);
	q2.bindValue(":type", type);
	q2.bindValue(":date", date);
	q2.bindValue(":distance", distance);
	q2.bindValue(":duree", duree);
	q2.bindValue(":denivele", denivele);
	q2.bindValue(":puissanceMoyenne", puissanceMoyenne);
	q2.bindValue(":puissanceMax", puissanceMax);
	q2.bindValue(":energie", energie);
	q2.bindValue(":vitesseMoyenne", vitesseMoyenne);
	q2.bindValue(":vitesseMax", vitesseMax);
	q2.bindValue(":FCMoyenne", FCMoyenne);
	q2.bindValue(":FCMax", FCMax);
	q2.bindValue(":CadenceMoyenne", CadenceMoyenne);
	q2.bindValue(":CadenceMax", CadenceMax);
	q2.bindValue(":meteo", meteo);

	//execute the query
	if (!q2.exec()) {
		QMessageBox::critical(this, "Error", q2.lastError().text()
			+ "\n" + q2.lastQuery());
		return false;
	}

	tableUtilities.updateKMEquipments(db,this,bikeID, distance);

	return true;
}

void WorkoutDialog::resetForm()
{
    /// resets the form fields

}



void WorkoutDialog::on_pbQuit_clicked()
{
	this->close();
}

WorkoutDialog::~WorkoutDialog()
{
    delete ui;
}

void WorkoutDialog::on_add_pushButton_clicked()
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
                                  "Confirmez vous la creation de cette sortie?",
                                  QMessageBox::Yes | QMessageBox::Cancel);
    //if the user accepts the dialog
    if (reply == QMessageBox::Yes){
        if(addItem()){
            QMessageBox::information(this, "Succes", "Sortie ajoutee");
            resetForm();
			this->close();
        }
    }
	else {
		return;
	}
	this->close();
}
