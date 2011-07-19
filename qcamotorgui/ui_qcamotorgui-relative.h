/********************************************************************************
** Form generated from reading UI file 'qcamotorgui-relative.ui'
**
** Created: Mon Jul 18 16:50:52 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QCAMOTORGUI_2D_RELATIVE_H
#define UI_QCAMOTORGUI_2D_RELATIVE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <qtpvwidgets.h>

QT_BEGIN_NAMESPACE

class Ui_GoRelative
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QMDoubleSpinBox *goRelative;

    void setupUi(QDialog *GoRelative)
    {
        if (GoRelative->objectName().isEmpty())
            GoRelative->setObjectName(QString::fromUtf8("GoRelative"));
        GoRelative->resize(201, 101);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GoRelative->sizePolicy().hasHeightForWidth());
        GoRelative->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(GoRelative);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
        widget = new QWidget(GoRelative);
        widget->setObjectName(QString::fromUtf8("widget"));
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        verticalLayout_2->addWidget(label);

        goRelative = new QMDoubleSpinBox(widget);
        goRelative->setObjectName(QString::fromUtf8("goRelative"));
        sizePolicy.setHeightForWidth(goRelative->sizePolicy().hasHeightForWidth());
        goRelative->setSizePolicy(sizePolicy);
        goRelative->setKeyboardTracking(false);
        goRelative->setMinimum(-2.14748e+09);
        goRelative->setMaximum(2.14748e+09);
        goRelative->setValue(0);

        verticalLayout_2->addWidget(goRelative);


        verticalLayout->addWidget(widget);


        retranslateUi(GoRelative);
        QObject::connect(goRelative, SIGNAL(escaped()), GoRelative, SLOT(reject()));
        QObject::connect(goRelative, SIGNAL(valueEdited(double)), GoRelative, SLOT(accept()));

        QMetaObject::connectSlotsByName(GoRelative);
    } // setupUi

    void retranslateUi(QDialog *GoRelative)
    {
        GoRelative->setWindowTitle(QApplication::translate("GoRelative", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("GoRelative", "Move relatively:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        goRelative->setToolTip(QApplication::translate("GoRelative", "Go relatively by the step", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class GoRelative: public Ui_GoRelative {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCAMOTORGUI_2D_RELATIVE_H
