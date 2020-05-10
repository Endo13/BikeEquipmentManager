#include "gearsSqlModel.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

gearsSqlModel::gearsSqlModel(QObject * parent, QSqlDatabase * database) :
	QSqlTableModel(parent,*database)
{
	db = database;
}


gearsSqlModel::~gearsSqlModel()
{
}

QVariant gearsSqlModel::data(const QModelIndex &index, int role) const
{

	if (role == Qt::TextAlignmentRole)
		return Qt::AlignCenter;
	if ((role == Qt::DisplayRole) && (index.column() == 1)) {
		//prepare the query
		QSqlQuery q(*db);
		q.prepare("select nom from typeEquipement where ID=?");
		q.bindValue(0, QSqlTableModel::data(index, role));
		//execute the query
		if (!q.exec()) {//if the query has some error then return
			return "N/C";
		}
		// if the query executes
		// check for the result
		if (q.next()) {//if the result exists then load the description					 
			qint8 nom = q.record().indexOf("nom");
			return q.value(nom).toString();
		}
		else {
			return "N/C";
		}
	}
	else if ((role == Qt::DisplayRole) && (index.column() == 2)) {
		const QModelIndex ind = index.sibling(index.row(), 1);
		QVariant m = QSqlTableModel::data(ind, role);
		QString marque = tableUtilities.getTableMarque(m.toInt());
		//prepare the query
		QSqlQuery q(*db);
		q.prepare("select nom from " + marque + " where ID=?");
		q.bindValue(0, QSqlTableModel::data(index, role));

		//execute the query
		if (!q.exec()) {//if the query has some error then return
			return "N/C";
		}
		// if the query executes
		// check for the result
		if (q.next()) {//if the result exists then load the description					 
			qint8 nom = q.record().indexOf("nom");
			return q.value(nom).toString();
		}
		else {
			return "N/C";
		}
	}
	else if ((role == Qt::DisplayRole) && (index.column() == 7)) {
		const QModelIndex ind = index.sibling(index.row(), 6);
		return QSqlTableModel::data(ind, role).toDouble() + QSqlTableModel::data(index, role).toDouble();
	}
	else {
		return QSqlTableModel::data(index, role);
	}
}
