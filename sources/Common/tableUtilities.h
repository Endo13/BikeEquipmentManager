#ifndef TABLEUTILITIES_H
#define TABLEUTILITIES_H

#include <QString>
#include <QSqlDatabase>
#include <QWidget>

#define NB_GEARS 44

#define SUN 0
#define RAIN 1
#define WIND 2

#define ROUTE 0
#define VTT 1
#define PISTE 2
#define DESCENTE 3

class TableUtilities
{
public:
	TableUtilities();
	~TableUtilities();

	static QString getTableMarque(int index);
	static QString getNomEquipement(int index);
	static QString getMeteo(int index);
	static void updateKMEquipments(QSqlDatabase* db, QWidget *parent, int bikeID, double kmToUpdate);
	static QString getTypeVelo(int index);

};
#endif 
