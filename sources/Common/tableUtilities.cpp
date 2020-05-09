#include "tableUtilities.h"

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
		return QString("MarqueCameraAR");
	case 4:
		return QString("MarqueCameraAV");
	case 5:
		return QString("MarqueCapteurCadence");
	case 6:
		return QString("MarqueCapteurPuissance");
	case 7:
		return QString("MarqueCapteurFrequence");
	case 8:
		return QString("MarqueCapteurVitesse");
	case 9:
		return QString("MarqueCassette");
	case 10:
		return QString("MarqueChaine");
	case 11:
		return QString("MarqueCintre");
	case 12:
		return QString("MarqueCollier");
	case 13:
		return QString("MarqueCompteur");
	case 14:
		return QString("MarqueDerailleurAR");
	case 15:
		return QString("MarqueDerailleurAV");
	case 16:
		return QString("MarqueEclairageAR");
	case 17:
		return QString("MarqueEclairageAV");
	case 18:
		return QString("MarqueFourche");
	case 19:
		return QString("MarqueFreinAR");
	case 20:
		return QString("MarqueFreinAV");
	case 21:
		return QString("MarqueJeuDeDirection");
	case 22:
		return QString("MarqueLeviersDeCommande");
	case 23:
		return QString("MarquePatinsAR");
	case 24:
		return QString("MarquePatinsAV");
	case 25:
		return QString("MarquePatteAntiDeraillement");
	case 26:
		return QString("MarquePedales");
	case 27:
		return QString("MarquePedalier");
	case 28:
		return QString("MarquePlaquettesAR");
	case 29:
		return QString("MarquePlaquettesAV");
	case 30:
		return QString("MarquePlateaux");
	case 31:
		return QString("MarquePneuAR");
	case 32:
		return QString("MarquePneuAV");
	case 33:
		return QString("MarquePotence");
	case 34:
		return QString("MarqueRadar");
	case 35:
		return QString("MarqueRoueAR");
	case 36:
		return QString("MarqueRoueAV");
	case 37:
		return QString("MarqueSacoche");
	case 38:
		return QString("MarqueSupportCompteur");
	case 39:
		return QString("MarqueTigeDeSelle");
}
	return QString();
}


QString TableUtilities::getNomEquipement(int index)
{
	switch (index) {
	case 1:
		return QString(QString::fromLatin1("Amortisseur arrière"));
	case 2:
		return QString(QString::fromLatin1("Boîtier de pédalier"));
	case 3:
		return QString(QString::fromLatin1("Caméra arrière"));
	case 4:
		return QString(QString::fromLatin1("Caméra avant"));
	case 5:
		return QString(QString::fromLatin1("Capteur cadence"));
	case 6:
		return QString(QString::fromLatin1("Capteur de puissance"));
	case 7:
		return QString(QString::fromLatin1("Capteur fréquence cardiaque"));
	case 8:
		return QString(QString::fromLatin1("Capteur vitesse"));
	case 9:
		return QString(QString::fromLatin1("Cassette"));
	case 10:
		return QString(QString::fromLatin1("Chaîne"));
	case 11:
		return QString(QString::fromLatin1("Cintre"));
	case 12:
		return QString(QString::fromLatin1("Collier de dérailleur avant"));
	case 13:
		return QString(QString::fromLatin1("Compteur"));
	case 14:
		return QString(QString::fromLatin1("Dérailleur arrière"));
	case 15:
		return QString(QString::fromLatin1("Dérailleur avant"));
	case 16:
		return QString(QString::fromLatin1("Eclairage arrière"));
	case 17:
		return QString(QString::fromLatin1("Eclairage avant"));
	case 18:
		return QString(QString::fromLatin1("Fourche"));
	case 19:
		return QString(QString::fromLatin1("Frein arrière"));
	case 20:
		return QString(QString::fromLatin1("Frein avant"));
	case 21:
		return QString(QString::fromLatin1("Jeu de direction"));
	case 22:
		return QString(QString::fromLatin1("Leviers de commande"));
	case 23:
		return QString(QString::fromLatin1("Patins arrières"));
	case 24:
		return QString(QString::fromLatin1("Patins avants"));
	case 25:
		return QString(QString::fromLatin1("Patte anti-déraillement"));
	case 26:
		return QString(QString::fromLatin1("Pédales"));
	case 27:
		return QString(QString::fromLatin1("Pédalier"));
	case 28:
		return QString(QString::fromLatin1("Plaquettes arrières"));
	case 29:
		return QString(QString::fromLatin1("Plaquettes avant"));
	case 30:
		return QString(QString::fromLatin1("Plateaux"));
	case 31:
		return QString(QString::fromLatin1("Pneu/boyau arrière"));
	case 32:
		return QString(QString::fromLatin1("Pneu/boyau avant"));
	case 33:
		return QString(QString::fromLatin1("Potence"));
	case 34:
		return QString(QString::fromLatin1("Radar"));
	case 35:
		return QString(QString::fromLatin1("Roue arrière"));
	case 36:
		return QString(QString::fromLatin1("Roue avant"));
	case 37:
		return QString(QString::fromLatin1("Sacoche"));
	case 38:
		return QString(QString::fromLatin1("Support compteur"));
	case 39:
		return QString(QString::fromLatin1("Tige de selle"));
	}
	return QString();
}