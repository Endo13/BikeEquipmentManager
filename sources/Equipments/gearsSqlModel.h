#include "QSqlTableModel.h"
#include "../Common/tableUtilities.h"

class gearsSqlModel :
	public QSqlTableModel
{
	Q_OBJECT
public:
	explicit gearsSqlModel(QObject *parent, QSqlDatabase *database);
	~gearsSqlModel();

	

private:
	QVariant data(const QModelIndex & index, int role) const;

	QSqlDatabase *db;
	TableUtilities tableUtilities;
};

