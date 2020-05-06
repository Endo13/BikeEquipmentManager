#ifndef GearsView_H
#define GearsView_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QSqlError>

namespace Ui {
class GearsView;
}

class GearsView : public QDialog
{
    Q_OBJECT

public:
    explicit GearsView(QSqlDatabase *database, QWidget *parent = 0);
    ~GearsView();




private:
    Ui::GearsView *ui;
    QSqlDatabase *db;
};

#endif // GearsView_H
