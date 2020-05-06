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
