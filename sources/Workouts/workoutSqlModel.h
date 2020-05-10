#include "QSqlTableModel.h"
#include "../Common/tableUtilities.h"

class workoutSqlModel :
	public QSqlTableModel
{
	Q_OBJECT
public:
	explicit workoutSqlModel(QObject *parent, QSqlDatabase *database);
	~workoutSqlModel();

	

private:
	QVariant data(const QModelIndex & index, int role) const;

	QSqlDatabase *db;
	TableUtilities tableUtilities;
};

