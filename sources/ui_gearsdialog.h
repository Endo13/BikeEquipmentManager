/********************************************************************************
** Form generated from reading UI file 'gearsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GEARSDIALOG_H
#define UI_GEARSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_GearsDialog
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *add_pushButton;
    QPushButton *pbQuit;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QComboBox *cbType;
    QLabel *label_3;
    QComboBox *cbMarque;
    QLabel *label_4;
    QLineEdit *leModele;
    QLabel *label_5;
    QDateEdit *deAchat;
    QLabel *label_6;
    QDateEdit *deUtilisation;
    QLabel *label_7;
    QLineEdit *leKMInitial;
    QLabel *label_9;
    QLineEdit *lePoids;
    QLabel *label_10;
    QLineEdit *lePrix;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *GearsDialog)
    {
        if (GearsDialog->objectName().isEmpty())
            GearsDialog->setObjectName(QStringLiteral("GearsDialog"));
        GearsDialog->resize(256, 495);
        gridLayout = new QGridLayout(GearsDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        add_pushButton = new QPushButton(GearsDialog);
        add_pushButton->setObjectName(QStringLiteral("add_pushButton"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/bike/edit.png"), QSize(), QIcon::Normal, QIcon::Off);
        add_pushButton->setIcon(icon);
        add_pushButton->setIconSize(QSize(24, 24));
        add_pushButton->setFlat(true);

        horizontalLayout_2->addWidget(add_pushButton);

        pbQuit = new QPushButton(GearsDialog);
        pbQuit->setObjectName(QStringLiteral("pbQuit"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/bike/cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbQuit->setIcon(icon1);
        pbQuit->setIconSize(QSize(24, 24));
        pbQuit->setFlat(true);

        horizontalLayout_2->addWidget(pbQuit);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_2 = new QLabel(GearsDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setStyleSheet(QStringLiteral(""));

        verticalLayout->addWidget(label_2);

        cbType = new QComboBox(GearsDialog);
        cbType->setObjectName(QStringLiteral("cbType"));
        cbType->setFrame(true);

        verticalLayout->addWidget(cbType);

        label_3 = new QLabel(GearsDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setStyleSheet(QStringLiteral(""));

        verticalLayout->addWidget(label_3);

        cbMarque = new QComboBox(GearsDialog);
        cbMarque->setObjectName(QStringLiteral("cbMarque"));

        verticalLayout->addWidget(cbMarque);

        label_4 = new QLabel(GearsDialog);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout->addWidget(label_4);

        leModele = new QLineEdit(GearsDialog);
        leModele->setObjectName(QStringLiteral("leModele"));

        verticalLayout->addWidget(leModele);

        label_5 = new QLabel(GearsDialog);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout->addWidget(label_5);

        deAchat = new QDateEdit(GearsDialog);
        deAchat->setObjectName(QStringLiteral("deAchat"));
        deAchat->setCalendarPopup(true);

        verticalLayout->addWidget(deAchat);

        label_6 = new QLabel(GearsDialog);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout->addWidget(label_6);

        deUtilisation = new QDateEdit(GearsDialog);
        deUtilisation->setObjectName(QStringLiteral("deUtilisation"));
        deUtilisation->setCalendarPopup(true);

        verticalLayout->addWidget(deUtilisation);

        label_7 = new QLabel(GearsDialog);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout->addWidget(label_7);

        leKMInitial = new QLineEdit(GearsDialog);
        leKMInitial->setObjectName(QStringLiteral("leKMInitial"));
        leKMInitial->setInputMethodHints(Qt::ImhDigitsOnly|Qt::ImhFormattedNumbersOnly);

        verticalLayout->addWidget(leKMInitial);

        label_9 = new QLabel(GearsDialog);
        label_9->setObjectName(QStringLiteral("label_9"));

        verticalLayout->addWidget(label_9);

        lePoids = new QLineEdit(GearsDialog);
        lePoids->setObjectName(QStringLiteral("lePoids"));
        lePoids->setInputMethodHints(Qt::ImhDigitsOnly|Qt::ImhFormattedNumbersOnly);

        verticalLayout->addWidget(lePoids);

        label_10 = new QLabel(GearsDialog);
        label_10->setObjectName(QStringLiteral("label_10"));

        verticalLayout->addWidget(label_10);

        lePrix = new QLineEdit(GearsDialog);
        lePrix->setObjectName(QStringLiteral("lePrix"));
        lePrix->setInputMethodHints(Qt::ImhFormattedNumbersOnly);

        verticalLayout->addWidget(lePrix);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_4->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout_4, 0, 0, 1, 1);


        retranslateUi(GearsDialog);

        QMetaObject::connectSlotsByName(GearsDialog);
    } // setupUi

    void retranslateUi(QDialog *GearsDialog)
    {
        GearsDialog->setWindowTitle(QApplication::translate("GearsDialog", "Nouvel \303\251quipement", Q_NULLPTR));
        add_pushButton->setText(QApplication::translate("GearsDialog", " Ajouter \303\251quipement", Q_NULLPTR));
        pbQuit->setText(QApplication::translate("GearsDialog", " Annuler", Q_NULLPTR));
        label_2->setText(QApplication::translate("GearsDialog", "Type", Q_NULLPTR));
        label_3->setText(QApplication::translate("GearsDialog", "Marque", Q_NULLPTR));
        label_4->setText(QApplication::translate("GearsDialog", "Mod\303\250le", Q_NULLPTR));
        label_5->setText(QApplication::translate("GearsDialog", "Date d'achat", Q_NULLPTR));
        label_6->setText(QApplication::translate("GearsDialog", "Date de 1\303\250re utilisation", Q_NULLPTR));
        label_7->setText(QApplication::translate("GearsDialog", "KM initial", Q_NULLPTR));
        label_9->setText(QApplication::translate("GearsDialog", "Poids", Q_NULLPTR));
        label_10->setText(QApplication::translate("GearsDialog", "Prix", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class GearsDialog: public Ui_GearsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GEARSDIALOG_H
