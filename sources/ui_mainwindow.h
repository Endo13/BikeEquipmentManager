/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAddGear;
    QAction *actionShowGear;
    QWidget *centralWidget;
    QLabel *status;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QPushButton *pbConfigBike;
    QPushButton *pbStatistics;
    QPushButton *pbShowGear;
    QPushButton *pbWorkout;
    QPushButton *pbShowBike;
    QPushButton *pbAddGear;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(443, 780);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(443, 780));
        MainWindow->setMaximumSize(QSize(443, 780));
        QIcon icon;
        icon.addFile(QStringLiteral(":/bike/BikeEquipmentManager.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setToolButtonStyle(Qt::ToolButtonIconOnly);
        actionAddGear = new QAction(MainWindow);
        actionAddGear->setObjectName(QStringLiteral("actionAddGear"));
        actionShowGear = new QAction(MainWindow);
        actionShowGear->setObjectName(QStringLiteral("actionShowGear"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        status = new QLabel(centralWidget);
        status->setObjectName(QStringLiteral("status"));
        status->setGeometry(QRect(10, 710, 400, 21));
        status->setStyleSheet(QStringLiteral("color:green;font-size:16px;"));
        formLayoutWidget = new QWidget(centralWidget);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(0, 0, 442, 691));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setSizeConstraint(QLayout::SetMaximumSize);
        formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        formLayout->setLabelAlignment(Qt::AlignCenter);
        formLayout->setFormAlignment(Qt::AlignCenter);
        formLayout->setContentsMargins(6, 6, 6, 6);
        pbConfigBike = new QPushButton(formLayoutWidget);
        pbConfigBike->setObjectName(QStringLiteral("pbConfigBike"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/bike/AddGear.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        pbConfigBike->setIcon(icon1);
        pbConfigBike->setIconSize(QSize(200, 200));
        pbConfigBike->setFlat(true);

        formLayout->setWidget(3, QFormLayout::LabelRole, pbConfigBike);

        pbStatistics = new QPushButton(formLayoutWidget);
        pbStatistics->setObjectName(QStringLiteral("pbStatistics"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/bike/Statistics.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        pbStatistics->setIcon(icon2);
        pbStatistics->setIconSize(QSize(200, 200));
        pbStatistics->setFlat(true);

        formLayout->setWidget(4, QFormLayout::FieldRole, pbStatistics);

        pbShowGear = new QPushButton(formLayoutWidget);
        pbShowGear->setObjectName(QStringLiteral("pbShowGear"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/bike/ShowGear.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        pbShowGear->setIcon(icon3);
        pbShowGear->setIconSize(QSize(200, 200));
        pbShowGear->setFlat(true);

        formLayout->setWidget(1, QFormLayout::FieldRole, pbShowGear);

        pbWorkout = new QPushButton(formLayoutWidget);
        pbWorkout->setObjectName(QStringLiteral("pbWorkout"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/bike/workout.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        pbWorkout->setIcon(icon4);
        pbWorkout->setIconSize(QSize(200, 200));
        pbWorkout->setFlat(true);

        formLayout->setWidget(4, QFormLayout::LabelRole, pbWorkout);

        pbShowBike = new QPushButton(formLayoutWidget);
        pbShowBike->setObjectName(QStringLiteral("pbShowBike"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/bike/ShowBike.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        pbShowBike->setIcon(icon5);
        pbShowBike->setIconSize(QSize(200, 200));
        pbShowBike->setFlat(true);

        formLayout->setWidget(3, QFormLayout::FieldRole, pbShowBike);

        pbAddGear = new QPushButton(formLayoutWidget);
        pbAddGear->setObjectName(QStringLiteral("pbAddGear"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/bike/gear.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        pbAddGear->setIcon(icon6);
        pbAddGear->setIconSize(QSize(200, 200));
        pbAddGear->setFlat(true);

        formLayout->setWidget(1, QFormLayout::LabelRole, pbAddGear);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 443, 21));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        pbConfigBike->setDefault(false);
        pbStatistics->setDefault(false);
        pbShowGear->setDefault(false);
        pbWorkout->setDefault(false);
        pbShowBike->setDefault(false);
        pbAddGear->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Bike Equipment Manager", Q_NULLPTR));
        actionAddGear->setText(QApplication::translate("MainWindow", "Ajout \303\251quipement", Q_NULLPTR));
        actionShowGear->setText(QApplication::translate("MainWindow", "Voir mes \303\251quipements", Q_NULLPTR));
        status->setText(QApplication::translate("MainWindow", "(Status of Database)", Q_NULLPTR));
        pbConfigBike->setText(QString());
        pbStatistics->setText(QString());
        pbShowGear->setText(QString());
        pbWorkout->setText(QString());
        pbShowBike->setText(QString());
        pbAddGear->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
