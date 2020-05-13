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
		return QString("MarqueSupportCompteur");
	case 43:
		return QString("MarqueTigeDeSelle");
}
	return QString();
}


QString TableUtilities::getNomEquipement(int index)
{
	
	switch (index) {
	case 1:
		return QString(QObject::tr(QString::fromLatin1("Amortisseur arrière").toStdString().c_str()));
	case 2:
		return QString(QObject::tr(QString::fromLatin1("Boîtier de pédalier").toStdString().c_str()));
	case 3:
		return QString(QObject::tr(QString::fromLatin1("Cadre").toStdString().c_str()));
	case 4:
		return QString(QObject::tr(QString::fromLatin1("Caméra arrière").toStdString().c_str()));
	case 5:
		return QString(QObject::tr(QString::fromLatin1("Caméra avant").toStdString().c_str()));
	case 6:
		return QString(QObject::tr(QString::fromLatin1("Capteur cadence").toStdString().c_str()));
	case 7:
		return QString(QObject::tr(QString::fromLatin1("Capteur de puissance").toStdString().c_str()));
	case 8:
		return QString(QObject::tr(QString::fromLatin1("Capteur fréquence cardiaque").toStdString().c_str()));
	case 9:
		return QString(QObject::tr(QString::fromLatin1("Capteur vitesse").toStdString().c_str()));
	case 10:
		return QString(QObject::tr(QString::fromLatin1("Cassette").toStdString().c_str()));
	case 11:
		return QString(QObject::tr(QString::fromLatin1("Chaîne").toStdString().c_str()));
	case 12:
		return QString(QObject::tr(QString::fromLatin1("Cintre").toStdString().c_str()));
	case 13:
		return QString(QObject::tr(QString::fromLatin1("Collier de dérailleur avant").toStdString().c_str()));
	case 14:
		return QString(QObject::tr(QString::fromLatin1("Collier de selle").toStdString().c_str()));
	case 15:
		return QString(QObject::tr(QString::fromLatin1("Compteur").toStdString().c_str()));
	case 16:
		return QString(QObject::tr(QString::fromLatin1("Dérailleur arrière").toStdString().c_str()));
	case 17:
		return QString(QObject::tr(QString::fromLatin1("Dérailleur avant").toStdString().c_str()));
	case 18:
		return QString(QObject::tr(QString::fromLatin1("Eclairage arrière").toStdString().c_str()));
	case 19:
		return QString(QObject::tr(QString::fromLatin1("Eclairage avant").toStdString().c_str()));
	case 20:
		return QString(QObject::tr(QString::fromLatin1("Fourche").toStdString().c_str()));
	case 21:
		return QString(QObject::tr(QString::fromLatin1("Frein arrière").toStdString().c_str()));
	case 22:
		return QString(QObject::tr(QString::fromLatin1("Frein avant").toStdString().c_str()));
	case 23:
		return QString(QObject::tr(QString::fromLatin1("Jeu de direction").toStdString().c_str()));
	case 24:
		return QString(QObject::tr(QString::fromLatin1("Leviers de commande").toStdString().c_str()));
	case 25:
		return QString(QObject::tr(QString::fromLatin1("Patins arrières").toStdString().c_str()));
	case 26:
		return QString(QObject::tr(QString::fromLatin1("Patins avants").toStdString().c_str()));
	case 27:
		return QString(QObject::tr(QString::fromLatin1("Patte anti-déraillement").toStdString().c_str()));
	case 28:
		return QString(QObject::tr(QString::fromLatin1("Pédales").toStdString().c_str()));
	case 29:
		return QString(QObject::tr(QString::fromLatin1("Pédalier").toStdString().c_str()));
	case 30:
		return QString(QObject::tr(QString::fromLatin1("Plaquettes arrières").toStdString().c_str()));
	case 31:
		return QString(QObject::tr(QString::fromLatin1("Plaquettes avant").toStdString().c_str()));
	case 32:
		return QString(QObject::tr(QString::fromLatin1("Plateau 1").toStdString().c_str()));
	case 33:
		return QString(QObject::tr(QString::fromLatin1("Plateau 2").toStdString().c_str()));
	case 34:
		return QString(QObject::tr(QString::fromLatin1("Plateau 3").toStdString().c_str()));
	case 35:
		return QString(QObject::tr(QString::fromLatin1("Pneu/boyau arrière").toStdString().c_str()));
	case 36:
		return QString(QObject::tr(QString::fromLatin1("Pneu/boyau avant").toStdString().c_str()));
	case 37:
		return QString(QObject::tr(QString::fromLatin1("Potence").toStdString().c_str()));
	case 38:
		return QString(QObject::tr(QString::fromLatin1("Radar").toStdString().c_str()));
	case 39:
		return QString(QObject::tr(QString::fromLatin1("Roue arrière").toStdString().c_str()));
	case 40:
		return QString(QObject::tr(QString::fromLatin1("Roue avant").toStdString().c_str()));
	case 41:
		return QString(QObject::tr(QString::fromLatin1("Sacoche").toStdString().c_str()));
	case 42:
		return QString(QObject::tr(QString::fromLatin1("Support compteur").toStdString().c_str()));
	case 43:
		return QString(QObject::tr(QString::fromLatin1("Tige de selle").toStdString().c_str()));
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
		QMessageBox::critical(parent, "Echec", "Mise a jour des km impossible");
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
