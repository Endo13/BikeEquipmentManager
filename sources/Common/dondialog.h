#ifndef DONDIALOG_H
#define DONDIALOG_H

#include <QDialog>
#include <QString>


namespace Ui {
class donDialog;
}

class donDialog : public QDialog
{
    Q_OBJECT

public:
    explicit donDialog(QWidget *parent = 0);

    ~donDialog();

private:
    //models



    //helper


	
private slots:
    void on_pbDon_clicked();
	void on_pbQuit_clicked();

private:
    Ui::donDialog *ui;
};

#endif // ITEMCODEDIALOG_H
