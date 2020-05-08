/********************************************************************************
** Form generated from reading UI file 'gearsview.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GEARSVIEW_H
#define UI_GEARSVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GearsView
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QTableView *twGears;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pbDelete;
    QPushButton *pbEdit;
    QPushButton *pbQuit;

    void setupUi(QDialog *GearsView)
    {
        if (GearsView->objectName().isEmpty())
            GearsView->setObjectName(QStringLiteral("GearsView"));
        GearsView->resize(1370, 824);
        horizontalLayoutWidget = new QWidget(GearsView);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 1341, 721));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        twGears = new QTableView(horizontalLayoutWidget);
        twGears->setObjectName(QStringLiteral("twGears"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(twGears->sizePolicy().hasHeightForWidth());
        twGears->setSizePolicy(sizePolicy);
        twGears->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        twGears->setEditTriggers(QAbstractItemView::NoEditTriggers);
        twGears->setAlternatingRowColors(true);
        twGears->setSelectionBehavior(QAbstractItemView::SelectRows);
        twGears->horizontalHeader()->setCascadingSectionResizes(true);
        twGears->horizontalHeader()->setMinimumSectionSize(50);
        twGears->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        twGears->horizontalHeader()->setStretchLastSection(false);
        twGears->verticalHeader()->setCascadingSectionResizes(true);
        twGears->verticalHeader()->setStretchLastSection(false);

        horizontalLayout->addWidget(twGears);

        horizontalLayoutWidget_2 = new QWidget(GearsView);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(530, 740, 331, 80));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        pbDelete = new QPushButton(horizontalLayoutWidget_2);
        pbDelete->setObjectName(QStringLiteral("pbDelete"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/bike/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbDelete->setIcon(icon);
        pbDelete->setIconSize(QSize(24, 24));
        pbDelete->setFlat(true);

        horizontalLayout_2->addWidget(pbDelete);

        pbEdit = new QPushButton(horizontalLayoutWidget_2);
        pbEdit->setObjectName(QStringLiteral("pbEdit"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/bike/edit.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbEdit->setIcon(icon1);
        pbEdit->setIconSize(QSize(24, 24));
        pbEdit->setFlat(true);

        horizontalLayout_2->addWidget(pbEdit);

        pbQuit = new QPushButton(horizontalLayoutWidget_2);
        pbQuit->setObjectName(QStringLiteral("pbQuit"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/bike/cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbQuit->setIcon(icon2);
        pbQuit->setIconSize(QSize(24, 24));
        pbQuit->setFlat(true);

        horizontalLayout_2->addWidget(pbQuit);


        retranslateUi(GearsView);

        QMetaObject::connectSlotsByName(GearsView);
    } // setupUi

    void retranslateUi(QDialog *GearsView)
    {
        GearsView->setWindowTitle(QApplication::translate("GearsView", "Mes \303\251quipements", Q_NULLPTR));
        pbDelete->setText(QApplication::translate("GearsView", " Supprimer", Q_NULLPTR));
        pbEdit->setText(QApplication::translate("GearsView", " Modifier", Q_NULLPTR));
        pbQuit->setText(QApplication::translate("GearsView", " Annuler", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class GearsView: public Ui_GearsView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GEARSVIEW_H
