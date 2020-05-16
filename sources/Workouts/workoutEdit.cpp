#include "workoutEdit.h"
#include "ui_workoutdialog.h"
#include <QDebug>
#include "QDateTime.h"
#include <QSqlRecord>
#include <QFileDialog>
#include "../Data/data.h"

WorkoutEdit::WorkoutEdit(QSqlDatabase *database, int ID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WorkoutDialog)
{
    ui->setupUi(this);
    db = database;
	_idToEdit = ID;
	_oldDistance = 0;
    //setup models
    setupModels();
	
	//setup ui
	QString locale = QLocale::system().name().section('_', 0, 0);
	if (locale == "fr")
		ui->deSortie->setDisplayFormat("dd/MM/yyyy");
	ui->leNom->setFocus();

	connect(ui->pbImport, SIGNAL(clicked()), SLOT(on_import()));
}

void WorkoutEdit::initializeModels()
{
    /// initializes all models
	//prepare the query
	QSqlQuery q(*db);
	q.prepare("select bikeID, nom, type, date, distance, duree, denivele, puissanceMoyenne, puissanceMax, energie, vitesseMoyenne, vitesseMax, FCMoyenne, FCMax, CadenceMoyenne, CadenceMax, meteo from workouts where ID=?");
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
		qint8	bikeIDIndex = q.record().indexOf("bikeID");
		qint8	nomIndex = q.record().indexOf("nom");
		qint8	typeIndex = q.record().indexOf("type");
		qint8	dateIndex = q.record().indexOf("date");
		qint8	distanceIndex = q.record().indexOf("distance");
		qint8	dureeIndex = q.record().indexOf("duree");
		qint8	deniveleIndex = q.record().indexOf("denivele");
		qint8	puissanceMoyIndex = q.record().indexOf("puissanceMoyenne");
		qint8	puissanceMaxIndex = q.record().indexOf("puissanceMax");
		qint8	enregieIndex = q.record().indexOf("energie");
		qint8	vitesseMoyIndex = q.record().indexOf("vitesseMoyenne");
		qint8	vitesseMaxIndex = q.record().indexOf("vitesseMax");
		qint8	fcMoyIndex = q.record().indexOf("FCMoyenne");
		qint8	fcMaxIndex = q.record().indexOf("FCMax");
		qint8	cadenceMoyIndex = q.record().indexOf("CadenceMoyenne");
		qint8	cadenceMaxIndex = q.record().indexOf("CadenceMax");
		qint8	meteoIndex = q.record().indexOf("meteo");

		ui->cbBike->setCurrentIndex(q.value(bikeIDIndex).toInt() - 1);
		ui->leNom->setText(q.value(nomIndex).toString());
		ui->cbType->setCurrentIndex(q.value(typeIndex).toInt());
		QString date = q.value(dateIndex).toString();
		QDate Date = QDate::fromString(date, Qt::DateFormat::ISODate);
		ui->deSortie->setDate(Date);
		_oldDistance = q.value(distanceIndex).toDouble();
		ui->spDistance->setValue(_oldDistance);
		QString duree = q.value(dureeIndex).toString();
		QTime Time = QTime::fromString(duree, "hh:mm:ss");
		ui->teSortie->setTime(Time);
		ui->spDenivele->setValue(q.value(deniveleIndex).toInt());
		ui->spPuissanceMoyenne->setValue(q.value(puissanceMoyIndex).toInt());
		ui->spPuissanceMax->setValue(q.value(puissanceMaxIndex).toInt());
		ui->spEnergie->setValue(q.value(enregieIndex).toInt());
		ui->spVitesseMoyenne->setValue(q.value(vitesseMoyIndex).toDouble());
		ui->spVitesseMax->setValue(q.value(vitesseMaxIndex).toDouble());
		ui->spFCMoyenne->setValue(q.value(fcMoyIndex).toInt());
		ui->spFCMax->setValue(q.value(fcMaxIndex).toInt());
		ui->spCadenceMoyenne->setValue(q.value(cadenceMoyIndex).toInt());
		ui->spCadenceMax->setValue(q.value(cadenceMaxIndex).toInt());
		if (q.value(meteoIndex).toInt() == SUN)
			ui->rbSun->setChecked(true);
		if (q.value(meteoIndex).toInt() == RAIN)
			ui->rbRain->setChecked(true);
		if (q.value(meteoIndex).toInt() == WIND)
			ui->rbWind->setChecked(true);
	}
}

void WorkoutEdit::setupModels()
{
    /// sets up all models
	setupUnitsComboBoxModel();
    initializeModels();
}

void WorkoutEdit::setupUnitsComboBoxModel()
{
    /// sets up the model for combo box
	QSqlQueryModel *modeMarquel = new QSqlQueryModel(ui->cbBike);
	modeMarquel->setQuery("SELECT nom FROM bikes");
	ui->cbBike->setModel(modeMarquel);
}

bool WorkoutEdit::validateForm()
{
    /// validates the form fields and checks if they are empty


    return true;
}

bool WorkoutEdit::addItem()
{
    /// takes care of the query preperation and execution
    /// to add item to database items table

    //gather arguments
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
	QDate da = ui->deSortie->date();
	QString dstr = da.toString(Qt::DateFormat::ISODate);
	double  distance = ui->spDistance->value();
	int  duree = ui->teSortie->time().hour() + ui->teSortie->time().minute() + ui->teSortie->time().second();
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
	q2.prepare("update workouts set bikeID=?, nom=?, type=?, date=?, distance=?, duree=?, denivele=?, puissanceMoyenne=?, puissanceMax=?, energie=?, vitesseMoyenne=?, vitesseMax=?, FCMoyenne=?, FCMax=?, CadenceMoyenne=?, CadenceMax=?, meteo=? where ID=?");
	q2.bindValue(0, bikeID);
	q2.bindValue(1, nom);
	q2.bindValue(2, type);
	q2.bindValue(3, dstr);
	q2.bindValue(4, distance);
	q2.bindValue(5, duree);
	q2.bindValue(6, denivele);
	q2.bindValue(7, puissanceMoyenne);
	q2.bindValue(8, puissanceMax);
	q2.bindValue(9, energie);
	q2.bindValue(10, vitesseMoyenne);
	q2.bindValue(11, vitesseMax);
	q2.bindValue(12, FCMoyenne);
	q2.bindValue(13, FCMax);
	q2.bindValue(14, CadenceMoyenne);
	q2.bindValue(15, CadenceMax);
	q2.bindValue(16, meteo);
	q2.bindValue(17, _idToEdit);

	double d = distance - _oldDistance;
	tableUtilities.updateKMEquipments(db, this, bikeID, d);

	//execute the query
	if (!q2.exec()) {
		QMessageBox::critical(this, "Error", q2.lastError().text()
			+ "\n" + q2.lastQuery());
		return false;
	}
	return true;
}

void WorkoutEdit::resetForm()
{
    /// resets the form fields
}

void WorkoutEdit::on_pbQuit_clicked()
{
	this->close();
}

WorkoutEdit::~WorkoutEdit()
{
    delete ui;
}

void WorkoutEdit::on_add_pushButton_clicked()
{
    //// Validates the form
    /// Adds the item to the database items table
    /// and resets the form
    //validate form
	if (!validateForm()) {
		QMessageBox::warning(this, QObject::tr("Remplir les champs"), QObject::tr("Remplir le champ nom du velo"));
		return;
	}

	//confirms from the user
	QMessageBox::StandardButton reply;
	reply = QMessageBox::question(this, QObject::tr("Etes vous sur?"),
		QObject::tr("Confirmer vous la modification de cette sortie?"),
		QMessageBox::Yes | QMessageBox::Cancel);
	//if the user accepts the dialog
	if (reply == QMessageBox::Yes) {
		if (addItem()) {
			QMessageBox::information(this, QObject::tr("Succes"), QObject::tr("Sortie modifiee"));
			resetForm();
		}
	}
	else {
		return;
	}
	this->close();
}

void WorkoutEdit::on_import()
{
	QString file = QFileDialog::getOpenFileName(this, tr("Ouvrir fichier"),
		_dataDir, Data::formats());
	Data dataGPX(file);

	if (dataGPX.isValid()) {
		qreal _trackDistance = 0;
		qreal _time = 0;
		qreal _movingTime = 0;
		QString name = "";
		qreal _ascent = 0;
		qreal speedMoy = 0;
		qreal speedMax = 0;
		qreal fcMoy = 0;
		qreal fcMax = 0;
		qreal cadenceMoy = 0;
		qreal cadenceMax = 0;
		QDate Date;

		for (int i = 0; i < dataGPX.tracks().count(); i++) {
			const Track &track = dataGPX.tracks().at(i);
			name = track.name();
			_trackDistance += track.distance();
			_time += track.time();
			_movingTime += track.movingTime();
			const QDate &date = track.date().date();
			Date = date;

			track.elevation(_ascent);
			track.speed(speedMax, speedMoy);
			track.heartRate(fcMax, fcMoy);
			track.cadence(cadenceMax, cadenceMoy);
		}
		unsigned h, m, s;
		h = _movingTime / 3600;
		m = (_movingTime - (h * 3600)) / 60;
		s = _movingTime - (h * 3600) - (m * 60);
		QTime t(h, m, s);
		ui->teSortie->setTime(t);
		ui->spDistance->setValue(_trackDistance / 1000.0);
		ui->deSortie->setDate(Date);
		ui->leNom->setText(name);
		ui->spDenivele->setValue(_ascent);
		ui->spVitesseMoyenne->setValue(speedMoy*3.6);
		ui->spVitesseMax->setValue(speedMax*3.6);
		ui->spFCMoyenne->setValue(fcMoy);
		ui->spFCMax->setValue(fcMax);
		ui->spCadenceMoyenne->setValue(cadenceMoy);
		ui->spCadenceMax->setValue(cadenceMax);
	}
}