#include "dondialog.h"
#include "ui_dondialog.h"
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>


donDialog::donDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::donDialog)
{
    ui->setupUi(this);
    //setup models
   
}

void donDialog::on_pbQuit_clicked()
{
	this->close();
}

void donDialog::on_pbDon_clicked()
{
	QDesktopServices::openUrl(QUrl("https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=JGVRY4TJ2NN5U&source=url", QUrl::TolerantMode));
}

donDialog::~donDialog()
{
	delete ui;
}


