#include "workoutSqlModel.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDate>

workoutSqlModel::workoutSqlModel(QObject * parent, QSqlDatabase * database) :
	QSqlTableModel(parent,*database)
{
	db = database;
}


workoutSqlModel::~workoutSqlModel()
{
}

QVariant workoutSqlModel::data(const QModelIndex &index, int role) const
{

	if (role == Qt::TextAlignmentRole)
		return Qt::AlignCenter;
	if ((role == Qt::DisplayRole) && (index.column() == 2)) {
		//prepare the query
		QSqlQuery q(*db);
		q.prepare("select nom from bikes where ID=?");
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
	else if ((role == Qt::DisplayRole) && (index.column() == 3)) {
		return tableUtilities.getTypeVelo(QSqlTableModel::data(index, role).toInt());
	}
	else if ((role == Qt::DisplayRole) && (index.column() == 4)) {
		QDate Date = QDate::fromString(QSqlTableModel::data(index, role).toString(), Qt::DateFormat::ISODate);
		return Date.toString(Qt::DateFormat::LocalDate);
	}
	else if ((role == Qt::DisplayRole) && (index.column() == 5)) {
		return tableUtilities.getMeteo(QSqlTableModel::data(index, role).toInt());
	}
	else {
		return QSqlTableModel::data(index, role);
	}
}
