#include "gearsdialog.h"
#include "ui_gearsdialog.h"
#include <QDebug>
#include "QDateTime.h"


GearsDialog::GearsDialog(QSqlDatabase *database, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GearsDialog)
{
    ui->setupUi(this);
    db = database;

    //setup models
    setupModels();

	//setup ui
	ui->leKMInitial->setValidator(new QIntValidator(0, 2147483647, this));
	ui->lePoids->setValidator(new QDoubleValidator(0.0, 2147483647.0,2, this));
	ui->lePrix->setValidator(new QDoubleValidator(0.0, 2147483647.0, 2, this));
	ui->deAchat->setDate(QDate::currentDate());
	ui->deAchat->setDisplayFormat("dd.MM.yyyy");
	ui->deUtilisation->setDate(QDate::currentDate());
	ui->deUtilisation->setDisplayFormat("dd.MM.yyyy");

	//Signal Slot
	connect(ui->cbType, SIGNAL(currentIndexChanged(int)), SLOT(changeMarque(int)));
}

void GearsDialog::initializeModels()
{
    /// initializes all models
}

void GearsDialog::setupModels()
{
    /// sets up all models

    initializeModels();
    setupUnitsComboBoxModel();
    qDebug() << "setupModels called";
}

void GearsDialog::setupUnitsComboBoxModel()
{
    /// sets up the model for combo box
	QSqlQueryModel *model = new QSqlQueryModel(ui->cbType);
	model->setQuery("SELECT nom FROM typeEquipement");
	ui->cbType->setModel(model);

	QSqlQueryModel *modeMarquel = new QSqlQueryModel(ui->cbMarque);
	modeMarquel->setQuery("SELECT nom FROM MarqueAmortisseurAR");
	ui->cbMarque->setModel(modeMarquel);
}

bool GearsDialog::validateForm()
{
    /// validates the form fields and checks if they are empty


    return true;
}

bool GearsDialog::addItem()
{
    /// takes care of the query preperation and execution
    /// to add item to database items table

    //gather arguments
	qint8	type = ui->cbType->currentIndex()+1;
	qint8   marque = ui->cbMarque->currentIndex()+1;
	QString modele = ui->leModele->text();
	QString dateAchat = ui->deAchat->text();
	QString dateUtilisation = ui->deUtilisation->text();
	int  kmInit = ui->leKMInitial->text().toInt();
	double  poids = ui->lePoids->text().toDouble();
	double prix = ui->lePrix->text().toDouble();
	
    //prepare the query
    QSqlQuery q(*db);
    q.prepare("insert into gears (type, marque, modele, date_achat, date_utilisation, km_initial, km_cumul, poids, prix) values "
              "(:type, :marque, :modele, :date_achat, :date_utilisation, :km_initial, :km_cumul, :poids, :prix );");
    q.bindValue(":type", type);
    q.bindValue(":marque", marque);
    q.bindValue(":modele", modele);
	q.bindValue(":date_achat", dateAchat);
	q.bindValue(":date_utilisation", dateUtilisation);
	q.bindValue(":km_initial", kmInit);
	q.bindValue(":km_cumul", 0);
	q.bindValue(":poids", poids);
	q.bindValue(":prix", prix);


    //execute the query
    if(!q.exec()){
        QMessageBox::critical(this, "Error", q.lastError().text()
                              + "\n" + q.lastQuery());
        return false;
    }
    return true;
}

void GearsDialog::resetForm()
{
    /// resets the form fields
    ui->leModele->clear();
    ui->cbType->setFocus();//focus on it
}

void GearsDialog::on_pbQuit_clicked()
{
	this->close();
}

void GearsDialog::changeMarque(int index)
{
	QSqlQueryModel *modeMarquel = new QSqlQueryModel(ui->cbMarque);
	QString table = tableUtilities.getTableMarque(index + 1);
	modeMarquel->setQuery("SELECT nom FROM "+table);
	ui->cbMarque->setModel(modeMarquel);
}

GearsDialog::~GearsDialog()
{
    delete ui;
}

void GearsDialog::on_add_pushButton_clicked()
{
    //// Validates the form
    /// Adds the item to the database items table
    /// and resets the form
    //validate form
    if(!validateForm()){
        QMessageBox::warning(this,"Fill Form", "Please Fill the form completely.");
        return;
    }

    //confirms from the user
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"Etes vous sur?",
                                  "Confirmer vous la creation de cet equipement?",
                                  QMessageBox::Yes | QMessageBox::Cancel);
    //if the user accepts the dialog
    if (reply == QMessageBox::Yes){
        if(addItem()){
            QMessageBox::information(this, "Succes", "Equipement ajoute!");
            resetForm();
        }
    }
	this->close();
}
