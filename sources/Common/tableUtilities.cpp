#include "tableUtilities.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlRecord>

TableUtilities::TableUtilities()
{
}

TableUtilities::~TableUtilities()
{
}

QString TableUtilities::getTableMarque(int index)
{
	switch (index) {
	case 1:
		return QString("MarqueAmortisseurAR");
	case 2:
		return QString("MarqueBoitierDePedalier");
	case 3:
		return QString("MarqueVelo");
	case 4:
		return QString("MarqueCameraAR");
	case 5:
		return QString("MarqueCameraAV");
	case 6:
		return QString("MarqueCapteurCadence");
	case 7:
		return QString("MarqueCapteurPuissance");
	case 8:
		return QString("MarqueCapteurFrequence");
	case 9:
		return QString("MarqueCapteurVitesse");
	case 10:
		return QString("MarqueCassette");
	case 11:
		return QString("MarqueChaine");
	case 12:
		return QString("MarqueCintre");
	case 13:
		return QString("MarqueCollier");
	case 14:
		return QString("MarqueCollierDeSelle");
	case 15:
		return QString("MarqueCompteur");
	case 16:
		return QString("MarqueDerailleurAR");
	case 17:
		return QString("MarqueDerailleurAV");
	case 18:
		return QString("MarqueEclairageAR");
	case 19:
		return QString("MarqueEclairageAV");
	case 20:
		return QString("MarqueFourche");
	case 21:
		return QString("MarqueFreinAR");
	case 22:
		return QString("MarqueFreinAV");
	case 23:
		return QString("MarqueJeuDeDirection");
	case 24:
		return QString("MarqueLeviersDeCommande");
	case 25:
		return QString("MarquePatinsAR");
	case 26:
		return QString("MarquePatinsAV");
	case 27:
		return QString("MarquePatteAntiDeraillement");
	case 28:
		return QString("MarquePedales");
	case 29:
		return QString("MarquePedalier");
	case 30:
		return QString("MarquePlaquettesAR");
	case 31:
		return QString("MarquePlaquettesAV");
	case 32:
		return QString("MarquePlateaux");
	case 33:
		return QString("MarquePlateaux");
	case 34:
		return QString("MarquePlateaux");
	case 35:
		return QString("MarquePneuAR");
	case 36:
		return QString("MarquePneuAV");
	case 37:
		return QString("MarquePotence");
	case 38:
		return QString("MarqueRadar");
	case 39:
		return QString("MarqueRoueAR");
	case 40:
		return QString("MarqueRoueAV");
	case 41:
		return QString("MarqueSacoche");
	case 42:
		return QString("MarqueSelle");
	case 43:
		return QString("MarqueSupportCompteur");
	case 44:
		return QString("MarqueTigeDeSelle");
}
	return QString();
}


QString TableUtilities::getNomEquipement(int index)
{
	
	switch (index) {
	case 1:
		return QString(QObject::tr("Amortisseur arriere"));
	case 2:
		return QString(QObject::tr("Boitier de pedalier"));
	case 3:
		return QString(QObject::tr("Cadre"));
	case 4:
		return QString(QObject::tr("Camera arriere"));
	case 5:
		return QString(QObject::tr("Camera avant"));
	case 6:
		return QString(QObject::tr("Capteur cadence"));
	case 7:
		return QString(QObject::tr("Capteur de puissance"));
	case 8:
		return QString(QObject::tr("Capteur frequence cardiaque"));
	case 9:
		return QString(QObject::tr("Capteur vitesse"));
	case 10:
		return QString(QObject::tr("Cassette"));
	case 11:
		return QString(QObject::tr("Chaine"));
	case 12:
		return QString(QObject::tr("Cintre"));
	case 13:
		return QString(QObject::tr("Collier de derailleur avant"));
	case 14:
		return QString(QObject::tr("Collier de selle"));
	case 15:
		return QString(QObject::tr("Compteur"));
	case 16:
		return QString(QObject::tr("Derailleur arriere"));
	case 17:
		return QString(QObject::tr("Derailleur avant"));
	case 18:
		return QString(QObject::tr("Eclairage arriere"));
	case 19:
		return QString(QObject::tr("Eclairage avant"));
	case 20:
		return QString(QObject::tr("Fourche"));
	case 21:
		return QString(QObject::tr("Frein arriere"));
	case 22:
		return QString(QObject::tr("Frein avant"));
	case 23:
		return QString(QObject::tr("Jeu de direction"));
	case 24:
		return QString(QObject::tr("Leviers de commande"));
	case 25:
		return QString(QObject::tr("Patins arrieres"));
	case 26:
		return QString(QObject::tr("Patins avants"));
	case 27:
		return QString(QObject::tr("Patte anti-deraillement"));
	case 28:
		return QString(QObject::tr("Pedales"));
	case 29:
		return QString(QObject::tr("Pedalier"));
	case 30:
		return QString(QObject::tr("Plaquettes arrieres"));
	case 31:
		return QString(QObject::tr("Plaquettes avant"));
	case 32:
		return QString(QObject::tr("Plateau 1"));
	case 33:
		return QString(QObject::tr("Plateau 2"));
	case 34:
		return QString(QObject::tr("Plateau 3"));
	case 35:
		return QString(QObject::tr("Pneu/boyau arriere"));
	case 36:
		return QString(QObject::tr("Pneu/boyau avant"));
	case 37:
		return QString(QObject::tr("Potence"));
	case 38:
		return QString(QObject::tr("Radar"));
	case 39:
		return QString(QObject::tr("Roue arriere"));
	case 40:
		return QString(QObject::tr("Roue avant"));
	case 41:
		return QString(QObject::tr("Sacoche"));
	case 42:
		return QString(QObject::tr("Selle"));
	case 43:
		return QString(QObject::tr("Support compteur"));
	case 44:
		return QString(QObject::tr("Tige de selle"));
	}
	return QString();
}

QString TableUtilities::getTypeVelo(int index)
{
	switch (index) {
	case SUN:
		return QString(QObject::tr("Soleil"));
	case RAIN:
		return QString(QObject::tr("Pluie"));
	case WIND:
		return QString(QObject::tr("Vent"));
	default:
		return QString(QObject::tr("Soleil"));
	}
}

QString TableUtilities::getMeteo(int index)
{
	switch (index) {
	case ROUTE:
		return QString(QObject::tr("Route"));
	case VTT:
		return QString(QObject::tr("VTT"));
	case PISTE:
		return QString(QObject::tr("Piste"));
	case DESCENTE:
		return QString(QObject::tr("Descente"));
	default:
		return QString(QObject::tr("Route"));
	}
}

void TableUtilities::updateKMEquipments(QSqlDatabase* db,QWidget *parent,int bikeID, double kmToUpdate)
{
	QSqlQuery q(*db);
	QString queryPrep = "select nom";

	for (int i = 0; i < NB_GEARS; i++) {
		queryPrep += ", eq" + QString::number(i + 1);
	}
	queryPrep += " from bikes where ID = ? ";
	q.prepare(queryPrep);
	q.bindValue(0, bikeID);

	//execute the query
	if (!q.exec()) {//if the query has some error then return
		QMessageBox::critical(parent, QObject::tr("Echec"), QObject::tr("Mise a jour des km impossible"));
		QMessageBox::critical(parent, "Error", q.lastError().text()
			+ "\n" + q.lastQuery());
		return;
	}

	// if the query executes
	// check for the result
	if (q.next()) {//if the result exists then load the description
		for (int i = 0; i < NB_GEARS; i++) {
			qint8 eqIndex = q.record().indexOf("eq" + QString::number(i + 1));
			int eqID = q.value(eqIndex).toInt();
			if (eqID > 0) {
				QSqlQuery q2(*db);
				q2.prepare("select km_cumul from gears where gear_code=?");
				q2.bindValue(0, eqID);
				if (!q2.exec()) {
				}
				if (q2.next()) {
					qint8 kmIndex = q2.record().indexOf("km_cumul");
					double km = q2.value(kmIndex).toDouble();
					km += kmToUpdate;
					QSqlQuery q3(*db);
					q3.prepare("update gears set km_cumul=? where gear_code=?");
					q3.bindValue(0, km);
					q3.bindValue(1, eqID);
					if (!q3.exec()) {
						QMessageBox::critical(parent, "Error", q3.lastError().text()
							+ "\n" + q3.lastQuery());
					}
				}
			}
		}
	}
}
