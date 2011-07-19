/********************************************************************************
** Form generated from reading UI file 'qcamotorgui.ui'
**
** Created: Mon Jul 18 16:50:52 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QCAMOTORGUI_H
#define UI_QCAMOTORGUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>
#include <qtpvwidgets.h>
#include "qcamotorgui-additional.h"

QT_BEGIN_NAMESPACE

class Ui_MotorControl
{
public:
    QHBoxLayout *horizontalLayout;
    QPushButton *setup;
    QFrame *line_0;
    QMDoubleSpinBox *userPosition;
    QWidget *mButtons;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *goM;
    QToolButton *jogM;
    QToolButton *limitM;
    QMultiComboBox *step;
    QWidget *pButtons;
    QHBoxLayout *horizontalLayout_3;
    QToolButton *limitP;
    QToolButton *jogP;
    QToolButton *goP;
    QFrame *line_2;
    QToolButton *stop;
    QWidget *powerW;
    QHBoxLayout *horizontalLayout_4;
    QToolButton *power;

    void setupUi(QWidget *MotorControl)
    {
        if (MotorControl->objectName().isEmpty())
            MotorControl->setObjectName(QString::fromUtf8("MotorControl"));
        MotorControl->resize(701, 32);
        horizontalLayout = new QHBoxLayout(MotorControl);
        horizontalLayout->setSpacing(1);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        setup = new QPushButton(MotorControl);
        setup->setObjectName(QString::fromUtf8("setup"));
        setup->setMinimumSize(QSize(0, 0));

        horizontalLayout->addWidget(setup);

        line_0 = new QFrame(MotorControl);
        line_0->setObjectName(QString::fromUtf8("line_0"));
        line_0->setFrameShape(QFrame::VLine);
        line_0->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_0);

        userPosition = new QMDoubleSpinBox(MotorControl);
        userPosition->setObjectName(QString::fromUtf8("userPosition"));
        userPosition->setEnabled(false);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(userPosition->sizePolicy().hasHeightForWidth());
        userPosition->setSizePolicy(sizePolicy);
        userPosition->setKeyboardTracking(false);
        userPosition->setMinimum(-2.14748e+09);
        userPosition->setMaximum(2.14748e+09);

        horizontalLayout->addWidget(userPosition);

        mButtons = new QWidget(MotorControl);
        mButtons->setObjectName(QString::fromUtf8("mButtons"));
        horizontalLayout_2 = new QHBoxLayout(mButtons);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        goM = new QToolButton(mButtons);
        goM->setObjectName(QString::fromUtf8("goM"));
        goM->setEnabled(false);
        sizePolicy.setHeightForWidth(goM->sizePolicy().hasHeightForWidth());
        goM->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(goM);

        jogM = new QToolButton(mButtons);
        jogM->setObjectName(QString::fromUtf8("jogM"));
        jogM->setEnabled(false);
        sizePolicy.setHeightForWidth(jogM->sizePolicy().hasHeightForWidth());
        jogM->setSizePolicy(sizePolicy);
        jogM->setCheckable(false);

        horizontalLayout_2->addWidget(jogM);

        limitM = new QToolButton(mButtons);
        limitM->setObjectName(QString::fromUtf8("limitM"));
        limitM->setEnabled(false);
        sizePolicy.setHeightForWidth(limitM->sizePolicy().hasHeightForWidth());
        limitM->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(limitM);


        horizontalLayout->addWidget(mButtons);

        step = new QMultiComboBox(MotorControl);
        step->setObjectName(QString::fromUtf8("step"));
        step->setEnabled(false);
        sizePolicy.setHeightForWidth(step->sizePolicy().hasHeightForWidth());
        step->setSizePolicy(sizePolicy);
        step->setEditable(true);
        step->setInsertPolicy(QComboBox::NoInsert);

        horizontalLayout->addWidget(step);

        pButtons = new QWidget(MotorControl);
        pButtons->setObjectName(QString::fromUtf8("pButtons"));
        horizontalLayout_3 = new QHBoxLayout(pButtons);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        limitP = new QToolButton(pButtons);
        limitP->setObjectName(QString::fromUtf8("limitP"));
        limitP->setEnabled(false);
        sizePolicy.setHeightForWidth(limitP->sizePolicy().hasHeightForWidth());
        limitP->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(limitP);

        jogP = new QToolButton(pButtons);
        jogP->setObjectName(QString::fromUtf8("jogP"));
        jogP->setEnabled(false);
        sizePolicy.setHeightForWidth(jogP->sizePolicy().hasHeightForWidth());
        jogP->setSizePolicy(sizePolicy);
        jogP->setCheckable(false);

        horizontalLayout_3->addWidget(jogP);

        goP = new QToolButton(pButtons);
        goP->setObjectName(QString::fromUtf8("goP"));
        goP->setEnabled(false);
        sizePolicy.setHeightForWidth(goP->sizePolicy().hasHeightForWidth());
        goP->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(goP);


        horizontalLayout->addWidget(pButtons);

        line_2 = new QFrame(MotorControl);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_2);

        stop = new QToolButton(MotorControl);
        stop->setObjectName(QString::fromUtf8("stop"));
        stop->setEnabled(false);

        horizontalLayout->addWidget(stop);

        powerW = new QWidget(MotorControl);
        powerW->setObjectName(QString::fromUtf8("powerW"));
        horizontalLayout_4 = new QHBoxLayout(powerW);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        power = new QToolButton(powerW);
        power->setObjectName(QString::fromUtf8("power"));
        power->setCheckable(true);

        horizontalLayout_4->addWidget(power);


        horizontalLayout->addWidget(powerW);


        retranslateUi(MotorControl);

        QMetaObject::connectSlotsByName(MotorControl);
    } // setupUi

    void retranslateUi(QWidget *MotorControl)
    {
        MotorControl->setWindowTitle(QApplication::translate("MotorControl", "Form", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        setup->setToolTip(QApplication::translate("MotorControl", "Setup and advanced control dialog", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        setup->setText(QApplication::translate("MotorControl", "SETUP", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        userPosition->setToolTip(QApplication::translate("MotorControl", "Position in \"User\" coordinates", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        goM->setToolTip(QApplication::translate("MotorControl", "Go to minus", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        goM->setText(QApplication::translate("MotorControl", "<", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        jogM->setToolTip(QApplication::translate("MotorControl", "Press to jog, release to stop jogging", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        jogM->setText(QApplication::translate("MotorControl", "<<", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        limitM->setToolTip(QApplication::translate("MotorControl", "Go to negative limit (hard or soft - whatever is activated first)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        limitM->setText(QApplication::translate("MotorControl", "|<", 0, QApplication::UnicodeUTF8));
        step->clear();
        step->insertItems(0, QStringList()
         << QApplication::translate("MotorControl", "relative", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MotorControl", "jog", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MotorControl", "limit", 0, QApplication::UnicodeUTF8)
        );
#ifndef QT_NO_TOOLTIP
        step->setToolTip(QApplication::translate("MotorControl", "Step", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        limitP->setToolTip(QApplication::translate("MotorControl", "Go to positive limit (hard or soft - whatever is activated first)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        limitP->setText(QApplication::translate("MotorControl", ">|", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        jogP->setToolTip(QApplication::translate("MotorControl", "Press to jog, release to stop jogging", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        jogP->setText(QApplication::translate("MotorControl", ">>", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        goP->setToolTip(QApplication::translate("MotorControl", "Go to plus", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        goP->setText(QApplication::translate("MotorControl", ">", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        stop->setToolTip(QApplication::translate("MotorControl", "Stop/on/off", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        stop->setText(QApplication::translate("MotorControl", "STOP", 0, QApplication::UnicodeUTF8));
        power->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MotorControl: public Ui_MotorControl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCAMOTORGUI_H
