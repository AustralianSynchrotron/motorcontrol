/********************************************************************************
** Form generated from reading UI file 'qcamotorgui-pv.ui'
**
** Created: Mon Jul 18 16:50:52 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QCAMOTORGUI_2D_PV_H
#define UI_QCAMOTORGUI_2D_PV_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "qcamotorgui-additional.h"

QT_BEGIN_NAMESPACE

class Ui_PVtable
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    LineEdit *search;
    QTableView *pvTable;

    void setupUi(QDialog *PVtable)
    {
        if (PVtable->objectName().isEmpty())
            PVtable->setObjectName(QString::fromUtf8("PVtable"));
        PVtable->resize(713, 306);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PVtable->sizePolicy().hasHeightForWidth());
        PVtable->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(PVtable);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new QWidget(PVtable);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        search = new LineEdit(widget);
        search->setObjectName(QString::fromUtf8("search"));

        horizontalLayout->addWidget(search);


        verticalLayout->addWidget(widget);

        pvTable = new QTableView(PVtable);
        pvTable->setObjectName(QString::fromUtf8("pvTable"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pvTable->sizePolicy().hasHeightForWidth());
        pvTable->setSizePolicy(sizePolicy1);
        pvTable->setFocusPolicy(Qt::NoFocus);
        pvTable->setAlternatingRowColors(true);
        pvTable->setSelectionMode(QAbstractItemView::SingleSelection);
        pvTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        pvTable->setSortingEnabled(true);
        pvTable->horizontalHeader()->setCascadingSectionResizes(true);
        pvTable->horizontalHeader()->setStretchLastSection(true);

        verticalLayout->addWidget(pvTable);


        retranslateUi(PVtable);

        QMetaObject::connectSlotsByName(PVtable);
    } // setupUi

    void retranslateUi(QDialog *PVtable)
    {
        PVtable->setWindowTitle(QApplication::translate("PVtable", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("PVtable", "Filter or PV:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        search->setToolTip(QApplication::translate("PVtable", "Enter the search creteria to filter the list or give the PV name and hit Return.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class PVtable: public Ui_PVtable {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCAMOTORGUI_2D_PV_H
