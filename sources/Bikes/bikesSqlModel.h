#include "QSqlTableModel.h"
#include "../Common/tableUtilities.h"

class bikesSqlModel :
	public QSqlTableModel
{
	Q_OBJECT
public:
	explicit bikesSqlModel(QObject *parent, QSqlDatabase *database);
	~bikesSqlModel();

	

private:
	QVariant data(const QModelIndex & index, int role) const;

	QSqlDatabase *db;
	TableUtilities tableUtilities;
};

