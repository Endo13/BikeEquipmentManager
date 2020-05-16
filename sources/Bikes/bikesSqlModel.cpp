#include "bikesSqlModel.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

bikesSqlModel::bikesSqlModel(QObject * parent, QSqlDatabase * database) :
	QSqlTableModel(parent,*database)
{
	db = database;
}


bikesSqlModel::~bikesSqlModel()
{
}

QVariant bikesSqlModel::data(const QModelIndex &index, int role) const
{

	if (role == Qt::TextAlignmentRole)
		return Qt::AlignCenter;
	else if ((role == Qt::DisplayRole) && (index.column() > 1)) {
		const QModelIndex ind = index.sibling(index.row(), 1);
		//prepare the query
		QSqlQuery q(*db);
		q.prepare("select type, marque, modele from gears where gear_code=?");
		q.bindValue(0, QSqlTableModel::data(index, role));

		//execute the query
		if (!q.exec()) {//if the query has some error then return
			return QObject::tr("non equipe");
		}
		// if the query executes
		// check for the result
		if (q.next()) {//if the result exists then load the description		
			qint8 type = q.record().indexOf("type");
			qint8 marque = q.record().indexOf("marque");		
			qint8 modeleIndex = q.record().indexOf("modele");
			QString modele = q.value(modeleIndex).toString(); 
			if (q.value(marque).toInt() > 0) {
				QString m = tableUtilities.getTableMarque(q.value(type).toInt());
				QSqlQuery q2(*db);
				q2.prepare("select nom from " + m + " where ID=?");
				q2.bindValue(0, q.value(marque).toInt());
				if (!q2.exec()) {//if the query has some error then return
					return QObject::tr("non equipe");
				}
				if (q2.next()) {
					qint8 nom = q2.record().indexOf("nom");	
					return q2.value(nom).toString() + " - " + modele;
				}	
				return QObject::tr("non equipe");
			}
			else {
				return QObject::tr("non equipe");
			}
		}
		else {
			return QObject::tr("non equipe");
		}
	}
	else {
		return QSqlTableModel::data(index, role);
	}
}
