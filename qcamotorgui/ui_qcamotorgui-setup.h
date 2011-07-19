/********************************************************************************
** Form generated from reading UI file 'qcamotorgui-setup.ui'
**
** Created: Mon Jul 18 16:50:52 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QCAMOTORGUI_2D_SETUP_H
#define UI_QCAMOTORGUI_2D_SETUP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <qtpvwidgets.h>

QT_BEGIN_NAMESPACE

class Ui_MotorSetup
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *mainSetup;
    QGridLayout *gridLayout_4;
    QLabel *label_2;
    QLabel *label_20;
    QComboBox *viewMode;
    QToolButton *pv;
    QWidget *loadSave;
    QHBoxLayout *horizontalLayout;
    QLabel *label_14;
    QLabel *label_52;
    QComboBox *loadConfig;
    QToolButton *saveConfig;
    QWidget *generalSetup;
    QVBoxLayout *verticalLayout_2;
    QWidget *nameSetup;
    QHBoxLayout *nameSetupLay;
    QLabel *label;
    QMLineEdit *description;
    QWidget *otherSetup;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_19;
    QToolButton *power;
    QLabel *label_23;
    QLabel *label_39;
    QMSpinBox *precision;
    QLabel *label_25;
    QLabel *label_40;
    QMLineEdit *units;
    QWidget *messageSetup;
    QHBoxLayout *messageSetupLay;
    QLabel *label_26;
    QLabel *message;
    QPushButton *clearMessage;
    QFrame *line_5;
    QWidget *spmgSetup;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_34;
    QRadioButton *Spmg;
    QRadioButton *sPmg;
    QRadioButton *spMg;
    QRadioButton *spmG;
    QWidget *control;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QLabel *label_21;
    QToolButton *goLimitM;
    QWidget *placeControlRel;
    QVBoxLayout *layControlRel;
    QToolButton *goM;
    QMDoubleSpinBox *step;
    QToolButton *stepD10;
    QToolButton *stepD2;
    QToolButton *stepM2;
    QToolButton *stepM10;
    QToolButton *goP;
    QToolButton *goLimitP;
    QLabel *label_7;
    QWidget *placeControlUser;
    QVBoxLayout *layControlUser;
    QWidget *placeControlRaw;
    QVBoxLayout *layControlRaw;
    QToolButton *jogM;
    QPushButton *stop;
    QToolButton *jogP;
    QFrame *line_4;
    QWidget *configure;
    QGridLayout *gridLayout_6;
    QLabel *label_41;
    QLabel *label_42;
    QLabel *label_44;
    QWidget *placeCfgUser;
    QVBoxLayout *layCfgUser;
    QWidget *placeCfgRaw;
    QVBoxLayout *layCfgRaw;
    QFrame *line_11;
    QLabel *label_47;
    QLabel *label_46;
    QLabel *label_53;
    QWidget *placeCfgHi;
    QVBoxLayout *layCfgHi;
    QWidget *placeCfgLo;
    QVBoxLayout *layCfgLo;
    QFrame *line_14;
    QLabel *label_18;
    QLabel *label_45;
    QMDoubleSpinBox *accelerationS;
    QMDoubleSpinBox *speedS;
    QFrame *line_15;
    QLabel *label_59;
    QLabel *label_60;
    QLabel *label_61;
    QMDoubleSpinBox *unitsPerRevGui;
    QWidget *placeCfgStepsPerRev;
    QVBoxLayout *layCfgStepsPerRev;
    QFrame *line_2;
    QWidget *epics;
    QVBoxLayout *verticalLayout_4;
    QWidget *positionsEpics;
    QGridLayout *gridLayout_5;
    QLabel *label_36;
    QLabel *label_37;
    QLabel *label_31;
    QLabel *label_35;
    QMDoubleSpinBox *dialGoal;
    QFrame *line_7;
    QLabel *label_12;
    QLabel *label_33;
    QLabel *label_32;
    QMDoubleSpinBox *limitHiDial;
    QMDoubleSpinBox *dialPosition;
    QMDoubleSpinBox *limitLoDial;
    QWidget *placeEpicsUserMove;
    QVBoxLayout *layEpicsUserMove;
    QWidget *placeEpicsHi;
    QVBoxLayout *layEpicsHi;
    QWidget *placeEpicsUserSet;
    QVBoxLayout *layEpicsUserSet;
    QWidget *placeEpicsLo;
    QVBoxLayout *layEpicsLo;
    QWidget *placeEpicsRawSet;
    QVBoxLayout *layEpicsRawSet;
    QWidget *placeEpicsRawMove;
    QVBoxLayout *layEpicsRawMove;
    QFrame *line_3;
    QWidget *resolutionSetup;
    QGridLayout *resolutionSetup_lay;
    QLabel *label_15;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QCheckBox *useReadback;
    QLabel *label_10;
    QCheckBox *useEncoder;
    QMDoubleSpinBox *encoderResolution;
    QMDoubleSpinBox *readbackResolution;
    QLabel *label_27;
    QLabel *label_16;
    QFrame *line_10;
    QLabel *label_13;
    QLabel *label_38;
    QRadioButton *offsetVar;
    QRadioButton *offsetFrz;
    QRadioButton *dirPos;
    QRadioButton *dirNeg;
    QRadioButton *useMode;
    QRadioButton *setMode;
    QMDoubleSpinBox *offset;
    QFrame *line;
    QLabel *label_30;
    QMDoubleSpinBox *unitsPerStep;
    QWidget *placeEpicsStepsPerRev;
    QVBoxLayout *layEpicsStepsPerRev;
    QMDoubleSpinBox *unitsPerRev;
    QFrame *line_6;
    QWidget *speedSetup;
    QGridLayout *gridLayout;
    QLabel *label_8;
    QLabel *label_9;
    QMDoubleSpinBox *backlashSpeed;
    QMDoubleSpinBox *backlashAcceleration;
    QLabel *label_48;
    QLabel *label_49;
    QLabel *label_50;
    QLabel *label_51;
    QMDoubleSpinBox *jogAcceleration;
    QMDoubleSpinBox *jogSpeed;
    QMDoubleSpinBox *maximumSpeed;
    QMDoubleSpinBox *acceleration;
    QMDoubleSpinBox *speed;
    QLabel *label_11;
    QMDoubleSpinBox *revSpeed;
    QFrame *line_9;
    QWidget *backlashSetup;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_22;
    QMDoubleSpinBox *backlash;
    QWidget *hidden;
    QVBoxLayout *layHide;
    QMDoubleSpinBox *rawGoal;
    QMDoubleSpinBox *userGoal;
    QMDoubleSpinBox *userPosition;
    QMDoubleSpinBox *rawPosition;
    QMDoubleSpinBox *limitHi;
    QMDoubleSpinBox *limitLo;
    QMSpinBox *stepsPerRev;
    QToolButton *callRelative;
    QMDoubleSpinBox *userVarGoal;
    QLabel *absLabel;
    QButtonGroup *spmgGroup;
    QButtonGroup *dirGroup;
    QButtonGroup *setGroup;
    QButtonGroup *offGroup;

    void setupUi(QDialog *MotorSetup)
    {
        if (MotorSetup->objectName().isEmpty())
            MotorSetup->setObjectName(QString::fromUtf8("MotorSetup"));
        MotorSetup->resize(642, 1247);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MotorSetup->sizePolicy().hasHeightForWidth());
        MotorSetup->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(MotorSetup);
        verticalLayout->setSpacing(1);
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
        mainSetup = new QWidget(MotorSetup);
        mainSetup->setObjectName(QString::fromUtf8("mainSetup"));
        sizePolicy.setHeightForWidth(mainSetup->sizePolicy().hasHeightForWidth());
        mainSetup->setSizePolicy(sizePolicy);
        gridLayout_4 = new QGridLayout(mainSetup);
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setSizeConstraint(QLayout::SetMinAndMaxSize);
        label_2 = new QLabel(mainSetup);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_4->addWidget(label_2, 0, 0, 1, 1);

        label_20 = new QLabel(mainSetup);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_20->sizePolicy().hasHeightForWidth());
        label_20->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(label_20, 0, 2, 1, 1);

        viewMode = new QComboBox(mainSetup);
        viewMode->setObjectName(QString::fromUtf8("viewMode"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(viewMode->sizePolicy().hasHeightForWidth());
        viewMode->setSizePolicy(sizePolicy2);
        viewMode->setMaxVisibleItems(6);
        viewMode->setMaxCount(6);

        gridLayout_4->addWidget(viewMode, 0, 3, 1, 1);

        pv = new QToolButton(mainSetup);
        pv->setObjectName(QString::fromUtf8("pv"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(pv->sizePolicy().hasHeightForWidth());
        pv->setSizePolicy(sizePolicy3);
        pv->setAutoRaise(true);

        gridLayout_4->addWidget(pv, 0, 1, 1, 1);


        verticalLayout->addWidget(mainSetup);

        loadSave = new QWidget(MotorSetup);
        loadSave->setObjectName(QString::fromUtf8("loadSave"));
        loadSave->setEnabled(false);
        sizePolicy.setHeightForWidth(loadSave->sizePolicy().hasHeightForWidth());
        loadSave->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(loadSave);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_14 = new QLabel(loadSave);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        horizontalLayout->addWidget(label_14);

        label_52 = new QLabel(loadSave);
        label_52->setObjectName(QString::fromUtf8("label_52"));
        sizePolicy1.setHeightForWidth(label_52->sizePolicy().hasHeightForWidth());
        label_52->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(label_52);

        loadConfig = new QComboBox(loadSave);
        loadConfig->setObjectName(QString::fromUtf8("loadConfig"));
        loadConfig->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 0, 0,64);"));

        horizontalLayout->addWidget(loadConfig);

        saveConfig = new QToolButton(loadSave);
        saveConfig->setObjectName(QString::fromUtf8("saveConfig"));
        sizePolicy2.setHeightForWidth(saveConfig->sizePolicy().hasHeightForWidth());
        saveConfig->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(saveConfig);


        verticalLayout->addWidget(loadSave);

        generalSetup = new QWidget(MotorSetup);
        generalSetup->setObjectName(QString::fromUtf8("generalSetup"));
        generalSetup->setEnabled(false);
        sizePolicy.setHeightForWidth(generalSetup->sizePolicy().hasHeightForWidth());
        generalSetup->setSizePolicy(sizePolicy);
        generalSetup->setVisible(true);
        verticalLayout_2 = new QVBoxLayout(generalSetup);
        verticalLayout_2->setSpacing(1);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetMinAndMaxSize);
        nameSetup = new QWidget(generalSetup);
        nameSetup->setObjectName(QString::fromUtf8("nameSetup"));
        sizePolicy2.setHeightForWidth(nameSetup->sizePolicy().hasHeightForWidth());
        nameSetup->setSizePolicy(sizePolicy2);
        nameSetupLay = new QHBoxLayout(nameSetup);
        nameSetupLay->setSpacing(1);
        nameSetupLay->setContentsMargins(0, 0, 0, 0);
        nameSetupLay->setObjectName(QString::fromUtf8("nameSetupLay"));
        nameSetupLay->setSizeConstraint(QLayout::SetMinAndMaxSize);
        label = new QLabel(nameSetup);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        nameSetupLay->addWidget(label);

        description = new QMLineEdit(nameSetup);
        description->setObjectName(QString::fromUtf8("description"));
        sizePolicy2.setHeightForWidth(description->sizePolicy().hasHeightForWidth());
        description->setSizePolicy(sizePolicy2);
        description->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 0, 0,64);"));

        nameSetupLay->addWidget(description);


        verticalLayout_2->addWidget(nameSetup);

        otherSetup = new QWidget(generalSetup);
        otherSetup->setObjectName(QString::fromUtf8("otherSetup"));
        sizePolicy2.setHeightForWidth(otherSetup->sizePolicy().hasHeightForWidth());
        otherSetup->setSizePolicy(sizePolicy2);
        horizontalLayout_5 = new QHBoxLayout(otherSetup);
        horizontalLayout_5->setSpacing(1);
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setSizeConstraint(QLayout::SetMinAndMaxSize);
        label_19 = new QLabel(otherSetup);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        sizePolicy1.setHeightForWidth(label_19->sizePolicy().hasHeightForWidth());
        label_19->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(label_19);

        power = new QToolButton(otherSetup);
        power->setObjectName(QString::fromUtf8("power"));
        sizePolicy1.setHeightForWidth(power->sizePolicy().hasHeightForWidth());
        power->setSizePolicy(sizePolicy1);
        power->setCheckable(true);

        horizontalLayout_5->addWidget(power);

        label_23 = new QLabel(otherSetup);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        sizePolicy1.setHeightForWidth(label_23->sizePolicy().hasHeightForWidth());
        label_23->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(label_23);

        label_39 = new QLabel(otherSetup);
        label_39->setObjectName(QString::fromUtf8("label_39"));
        sizePolicy1.setHeightForWidth(label_39->sizePolicy().hasHeightForWidth());
        label_39->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(label_39);

        precision = new QMSpinBox(otherSetup);
        precision->setObjectName(QString::fromUtf8("precision"));
        sizePolicy.setHeightForWidth(precision->sizePolicy().hasHeightForWidth());
        precision->setSizePolicy(sizePolicy);
        precision->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 0, 0,64);"));
        precision->setKeyboardTracking(false);
        precision->setMaximum(9);

        horizontalLayout_5->addWidget(precision);

        label_25 = new QLabel(otherSetup);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        sizePolicy1.setHeightForWidth(label_25->sizePolicy().hasHeightForWidth());
        label_25->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(label_25);

        label_40 = new QLabel(otherSetup);
        label_40->setObjectName(QString::fromUtf8("label_40"));
        sizePolicy1.setHeightForWidth(label_40->sizePolicy().hasHeightForWidth());
        label_40->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(label_40);

        units = new QMLineEdit(otherSetup);
        units->setObjectName(QString::fromUtf8("units"));
        sizePolicy.setHeightForWidth(units->sizePolicy().hasHeightForWidth());
        units->setSizePolicy(sizePolicy);
        units->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 0, 0,64);"));

        horizontalLayout_5->addWidget(units);


        verticalLayout_2->addWidget(otherSetup);

        messageSetup = new QWidget(generalSetup);
        messageSetup->setObjectName(QString::fromUtf8("messageSetup"));
        sizePolicy2.setHeightForWidth(messageSetup->sizePolicy().hasHeightForWidth());
        messageSetup->setSizePolicy(sizePolicy2);
        messageSetupLay = new QHBoxLayout(messageSetup);
        messageSetupLay->setSpacing(1);
        messageSetupLay->setContentsMargins(0, 0, 0, 0);
        messageSetupLay->setObjectName(QString::fromUtf8("messageSetupLay"));
        messageSetupLay->setSizeConstraint(QLayout::SetMinAndMaxSize);
        label_26 = new QLabel(messageSetup);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        sizePolicy1.setHeightForWidth(label_26->sizePolicy().hasHeightForWidth());
        label_26->setSizePolicy(sizePolicy1);

        messageSetupLay->addWidget(label_26);

        message = new QLabel(messageSetup);
        message->setObjectName(QString::fromUtf8("message"));
        sizePolicy2.setHeightForWidth(message->sizePolicy().hasHeightForWidth());
        message->setSizePolicy(sizePolicy2);
        message->setFrameShape(QFrame::StyledPanel);
        message->setFrameShadow(QFrame::Plain);

        messageSetupLay->addWidget(message);

        clearMessage = new QPushButton(messageSetup);
        clearMessage->setObjectName(QString::fromUtf8("clearMessage"));
        sizePolicy1.setHeightForWidth(clearMessage->sizePolicy().hasHeightForWidth());
        clearMessage->setSizePolicy(sizePolicy1);

        messageSetupLay->addWidget(clearMessage);


        verticalLayout_2->addWidget(messageSetup);


        verticalLayout->addWidget(generalSetup);

        line_5 = new QFrame(MotorSetup);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        sizePolicy.setHeightForWidth(line_5->sizePolicy().hasHeightForWidth());
        line_5->setSizePolicy(sizePolicy);
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_5);

        spmgSetup = new QWidget(MotorSetup);
        spmgSetup->setObjectName(QString::fromUtf8("spmgSetup"));
        spmgSetup->setEnabled(false);
        sizePolicy.setHeightForWidth(spmgSetup->sizePolicy().hasHeightForWidth());
        spmgSetup->setSizePolicy(sizePolicy);
        spmgSetup->setVisible(true);
        horizontalLayout_2 = new QHBoxLayout(spmgSetup);
        horizontalLayout_2->setSpacing(1);
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetMinAndMaxSize);
        label_34 = new QLabel(spmgSetup);
        label_34->setObjectName(QString::fromUtf8("label_34"));
        sizePolicy1.setHeightForWidth(label_34->sizePolicy().hasHeightForWidth());
        label_34->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(label_34);

        Spmg = new QRadioButton(spmgSetup);
        spmgGroup = new QButtonGroup(MotorSetup);
        spmgGroup->setObjectName(QString::fromUtf8("spmgGroup"));
        spmgGroup->addButton(Spmg);
        Spmg->setObjectName(QString::fromUtf8("Spmg"));
        sizePolicy.setHeightForWidth(Spmg->sizePolicy().hasHeightForWidth());
        Spmg->setSizePolicy(sizePolicy);
        Spmg->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 0, 0,64);"));

        horizontalLayout_2->addWidget(Spmg);

        sPmg = new QRadioButton(spmgSetup);
        spmgGroup->addButton(sPmg);
        sPmg->setObjectName(QString::fromUtf8("sPmg"));
        sizePolicy.setHeightForWidth(sPmg->sizePolicy().hasHeightForWidth());
        sPmg->setSizePolicy(sizePolicy);
        sPmg->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 0, 0,64);"));

        horizontalLayout_2->addWidget(sPmg);

        spMg = new QRadioButton(spmgSetup);
        spmgGroup->addButton(spMg);
        spMg->setObjectName(QString::fromUtf8("spMg"));
        sizePolicy.setHeightForWidth(spMg->sizePolicy().hasHeightForWidth());
        spMg->setSizePolicy(sizePolicy);
        spMg->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 0, 0,64);"));

        horizontalLayout_2->addWidget(spMg);

        spmG = new QRadioButton(spmgSetup);
        spmgGroup->addButton(spmG);
        spmG->setObjectName(QString::fromUtf8("spmG"));
        sizePolicy.setHeightForWidth(spmG->sizePolicy().hasHeightForWidth());
        spmG->setSizePolicy(sizePolicy);
        spmG->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 0, 0,64);"));

        horizontalLayout_2->addWidget(spmG);


        verticalLayout->addWidget(spmgSetup);

        control = new QWidget(MotorSetup);
        control->setObjectName(QString::fromUtf8("control"));
        control->setEnabled(false);
        sizePolicy.setHeightForWidth(control->sizePolicy().hasHeightForWidth());
        control->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(control);
        gridLayout_2->setSpacing(1);
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_3 = new QLabel(control);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        label_21 = new QLabel(control);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        sizePolicy2.setHeightForWidth(label_21->sizePolicy().hasHeightForWidth());
        label_21->setSizePolicy(sizePolicy2);
        label_21->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_21, 0, 1, 1, 2);

        goLimitM = new QToolButton(control);
        goLimitM->setObjectName(QString::fromUtf8("goLimitM"));
        goLimitM->setEnabled(false);
        sizePolicy2.setHeightForWidth(goLimitM->sizePolicy().hasHeightForWidth());
        goLimitM->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(goLimitM, 3, 0, 1, 1);

        placeControlRel = new QWidget(control);
        placeControlRel->setObjectName(QString::fromUtf8("placeControlRel"));
        sizePolicy2.setHeightForWidth(placeControlRel->sizePolicy().hasHeightForWidth());
        placeControlRel->setSizePolicy(sizePolicy2);
        layControlRel = new QVBoxLayout(placeControlRel);
        layControlRel->setSpacing(0);
        layControlRel->setContentsMargins(0, 0, 0, 0);
        layControlRel->setObjectName(QString::fromUtf8("layControlRel"));
        layControlRel->setSizeConstraint(QLayout::SetMinAndMaxSize);

        gridLayout_2->addWidget(placeControlRel, 3, 1, 1, 2);

        goM = new QToolButton(control);
        goM->setObjectName(QString::fromUtf8("goM"));
        goM->setEnabled(false);
        sizePolicy2.setHeightForWidth(goM->sizePolicy().hasHeightForWidth());
        goM->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(goM, 4, 0, 1, 1);

        step = new QMDoubleSpinBox(control);
        step->setObjectName(QString::fromUtf8("step"));
        sizePolicy2.setHeightForWidth(step->sizePolicy().hasHeightForWidth());
        step->setSizePolicy(sizePolicy2);
        step->setKeyboardTracking(false);
        step->setMinimum(-2.14748e+09);
        step->setMaximum(2.14748e+09);

        gridLayout_2->addWidget(step, 4, 1, 1, 2);

        stepD10 = new QToolButton(control);
        stepD10->setObjectName(QString::fromUtf8("stepD10"));
        sizePolicy2.setHeightForWidth(stepD10->sizePolicy().hasHeightForWidth());
        stepD10->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(stepD10, 5, 0, 1, 1);

        stepD2 = new QToolButton(control);
        stepD2->setObjectName(QString::fromUtf8("stepD2"));
        sizePolicy2.setHeightForWidth(stepD2->sizePolicy().hasHeightForWidth());
        stepD2->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(stepD2, 5, 1, 1, 1);

        stepM2 = new QToolButton(control);
        stepM2->setObjectName(QString::fromUtf8("stepM2"));
        sizePolicy2.setHeightForWidth(stepM2->sizePolicy().hasHeightForWidth());
        stepM2->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(stepM2, 5, 2, 1, 1);

        stepM10 = new QToolButton(control);
        stepM10->setObjectName(QString::fromUtf8("stepM10"));
        sizePolicy2.setHeightForWidth(stepM10->sizePolicy().hasHeightForWidth());
        stepM10->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(stepM10, 5, 3, 1, 1);

        goP = new QToolButton(control);
        goP->setObjectName(QString::fromUtf8("goP"));
        goP->setEnabled(false);
        sizePolicy2.setHeightForWidth(goP->sizePolicy().hasHeightForWidth());
        goP->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(goP, 4, 3, 1, 1);

        goLimitP = new QToolButton(control);
        goLimitP->setObjectName(QString::fromUtf8("goLimitP"));
        goLimitP->setEnabled(false);
        sizePolicy2.setHeightForWidth(goLimitP->sizePolicy().hasHeightForWidth());
        goLimitP->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(goLimitP, 3, 3, 1, 1);

        label_7 = new QLabel(control);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        sizePolicy2.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy2);
        label_7->setLayoutDirection(Qt::RightToLeft);

        gridLayout_2->addWidget(label_7, 0, 3, 1, 1);

        placeControlUser = new QWidget(control);
        placeControlUser->setObjectName(QString::fromUtf8("placeControlUser"));
        sizePolicy2.setHeightForWidth(placeControlUser->sizePolicy().hasHeightForWidth());
        placeControlUser->setSizePolicy(sizePolicy2);
        layControlUser = new QVBoxLayout(placeControlUser);
        layControlUser->setSpacing(0);
        layControlUser->setContentsMargins(0, 0, 0, 0);
        layControlUser->setObjectName(QString::fromUtf8("layControlUser"));
        layControlUser->setSizeConstraint(QLayout::SetMinAndMaxSize);

        gridLayout_2->addWidget(placeControlUser, 1, 0, 1, 2);

        placeControlRaw = new QWidget(control);
        placeControlRaw->setObjectName(QString::fromUtf8("placeControlRaw"));
        sizePolicy2.setHeightForWidth(placeControlRaw->sizePolicy().hasHeightForWidth());
        placeControlRaw->setSizePolicy(sizePolicy2);
        layControlRaw = new QVBoxLayout(placeControlRaw);
        layControlRaw->setSpacing(0);
        layControlRaw->setContentsMargins(0, 0, 0, 0);
        layControlRaw->setObjectName(QString::fromUtf8("layControlRaw"));
        layControlRaw->setSizeConstraint(QLayout::SetMinAndMaxSize);

        gridLayout_2->addWidget(placeControlRaw, 1, 2, 1, 2);

        jogM = new QToolButton(control);
        jogM->setObjectName(QString::fromUtf8("jogM"));
        jogM->setEnabled(false);
        sizePolicy2.setHeightForWidth(jogM->sizePolicy().hasHeightForWidth());
        jogM->setSizePolicy(sizePolicy2);
        jogM->setCheckable(false);

        gridLayout_2->addWidget(jogM, 2, 0, 1, 1);

        stop = new QPushButton(control);
        stop->setObjectName(QString::fromUtf8("stop"));
        stop->setEnabled(false);
        sizePolicy2.setHeightForWidth(stop->sizePolicy().hasHeightForWidth());
        stop->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(stop, 2, 1, 1, 2);

        jogP = new QToolButton(control);
        jogP->setObjectName(QString::fromUtf8("jogP"));
        jogP->setEnabled(false);
        sizePolicy2.setHeightForWidth(jogP->sizePolicy().hasHeightForWidth());
        jogP->setSizePolicy(sizePolicy2);
        jogP->setCheckable(false);

        gridLayout_2->addWidget(jogP, 2, 3, 1, 1);


        verticalLayout->addWidget(control);

        line_4 = new QFrame(MotorSetup);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        sizePolicy.setHeightForWidth(line_4->sizePolicy().hasHeightForWidth());
        line_4->setSizePolicy(sizePolicy);
        line_4->setVisible(true);
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_4);

        configure = new QWidget(MotorSetup);
        configure->setObjectName(QString::fromUtf8("configure"));
        configure->setEnabled(false);
        sizePolicy.setHeightForWidth(configure->sizePolicy().hasHeightForWidth());
        configure->setSizePolicy(sizePolicy);
        gridLayout_6 = new QGridLayout(configure);
        gridLayout_6->setSpacing(1);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setContentsMargins(0, 0, 0, -1);
        label_41 = new QLabel(configure);
        label_41->setObjectName(QString::fromUtf8("label_41"));

        gridLayout_6->addWidget(label_41, 0, 0, 1, 1);

        label_42 = new QLabel(configure);
        label_42->setObjectName(QString::fromUtf8("label_42"));
        sizePolicy2.setHeightForWidth(label_42->sizePolicy().hasHeightForWidth());
        label_42->setSizePolicy(sizePolicy2);
        label_42->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_42, 0, 1, 1, 2);

        label_44 = new QLabel(configure);
        label_44->setObjectName(QString::fromUtf8("label_44"));
        sizePolicy2.setHeightForWidth(label_44->sizePolicy().hasHeightForWidth());
        label_44->setSizePolicy(sizePolicy2);
        label_44->setLayoutDirection(Qt::RightToLeft);
        label_44->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_44, 0, 3, 1, 1);

        placeCfgUser = new QWidget(configure);
        placeCfgUser->setObjectName(QString::fromUtf8("placeCfgUser"));
        sizePolicy2.setHeightForWidth(placeCfgUser->sizePolicy().hasHeightForWidth());
        placeCfgUser->setSizePolicy(sizePolicy2);
        layCfgUser = new QVBoxLayout(placeCfgUser);
        layCfgUser->setSpacing(0);
        layCfgUser->setContentsMargins(0, 0, 0, 0);
        layCfgUser->setObjectName(QString::fromUtf8("layCfgUser"));
        layCfgUser->setSizeConstraint(QLayout::SetMinAndMaxSize);

        gridLayout_6->addWidget(placeCfgUser, 1, 0, 1, 2);

        placeCfgRaw = new QWidget(configure);
        placeCfgRaw->setObjectName(QString::fromUtf8("placeCfgRaw"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(100);
        sizePolicy4.setHeightForWidth(placeCfgRaw->sizePolicy().hasHeightForWidth());
        placeCfgRaw->setSizePolicy(sizePolicy4);
        layCfgRaw = new QVBoxLayout(placeCfgRaw);
        layCfgRaw->setSpacing(0);
        layCfgRaw->setContentsMargins(0, 0, 0, 0);
        layCfgRaw->setObjectName(QString::fromUtf8("layCfgRaw"));
        layCfgRaw->setSizeConstraint(QLayout::SetMinAndMaxSize);

        gridLayout_6->addWidget(placeCfgRaw, 1, 2, 1, 2);

        line_11 = new QFrame(configure);
        line_11->setObjectName(QString::fromUtf8("line_11"));
        line_11->setFrameShape(QFrame::HLine);
        line_11->setFrameShadow(QFrame::Sunken);

        gridLayout_6->addWidget(line_11, 2, 0, 1, 4);

        label_47 = new QLabel(configure);
        label_47->setObjectName(QString::fromUtf8("label_47"));

        gridLayout_6->addWidget(label_47, 3, 0, 1, 1);

        label_46 = new QLabel(configure);
        label_46->setObjectName(QString::fromUtf8("label_46"));
        label_46->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_46, 3, 1, 1, 2);

        label_53 = new QLabel(configure);
        label_53->setObjectName(QString::fromUtf8("label_53"));
        label_53->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_53, 3, 3, 1, 1);

        placeCfgHi = new QWidget(configure);
        placeCfgHi->setObjectName(QString::fromUtf8("placeCfgHi"));
        layCfgHi = new QVBoxLayout(placeCfgHi);
        layCfgHi->setSpacing(0);
        layCfgHi->setContentsMargins(0, 0, 0, 0);
        layCfgHi->setObjectName(QString::fromUtf8("layCfgHi"));
        layCfgHi->setSizeConstraint(QLayout::SetMinAndMaxSize);

        gridLayout_6->addWidget(placeCfgHi, 4, 2, 1, 2);

        placeCfgLo = new QWidget(configure);
        placeCfgLo->setObjectName(QString::fromUtf8("placeCfgLo"));
        layCfgLo = new QVBoxLayout(placeCfgLo);
        layCfgLo->setSpacing(0);
        layCfgLo->setContentsMargins(0, 0, 0, 0);
        layCfgLo->setObjectName(QString::fromUtf8("layCfgLo"));
        layCfgLo->setSizeConstraint(QLayout::SetMinAndMaxSize);

        gridLayout_6->addWidget(placeCfgLo, 4, 0, 1, 2);

        line_14 = new QFrame(configure);
        line_14->setObjectName(QString::fromUtf8("line_14"));
        line_14->setFrameShape(QFrame::HLine);
        line_14->setFrameShadow(QFrame::Sunken);

        gridLayout_6->addWidget(line_14, 5, 0, 1, 4);

        label_18 = new QLabel(configure);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout_6->addWidget(label_18, 6, 0, 1, 2);

        label_45 = new QLabel(configure);
        label_45->setObjectName(QString::fromUtf8("label_45"));
        label_45->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_45, 6, 3, 1, 1);

        accelerationS = new QMDoubleSpinBox(configure);
        accelerationS->setObjectName(QString::fromUtf8("accelerationS"));
        sizePolicy.setHeightForWidth(accelerationS->sizePolicy().hasHeightForWidth());
        accelerationS->setSizePolicy(sizePolicy);
        accelerationS->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 0, 0,64);"));
        accelerationS->setKeyboardTracking(false);
        accelerationS->setMaximum(2.14748e+09);

        gridLayout_6->addWidget(accelerationS, 7, 2, 1, 2);

        speedS = new QMDoubleSpinBox(configure);
        speedS->setObjectName(QString::fromUtf8("speedS"));
        sizePolicy.setHeightForWidth(speedS->sizePolicy().hasHeightForWidth());
        speedS->setSizePolicy(sizePolicy);
        speedS->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 0, 0,64);"));
        speedS->setKeyboardTracking(false);
        speedS->setMaximum(2.14748e+09);

        gridLayout_6->addWidget(speedS, 7, 0, 1, 2);

        line_15 = new QFrame(configure);
        line_15->setObjectName(QString::fromUtf8("line_15"));
        line_15->setFrameShape(QFrame::HLine);
        line_15->setFrameShadow(QFrame::Sunken);

        gridLayout_6->addWidget(line_15, 8, 0, 1, 4);

        label_59 = new QLabel(configure);
        label_59->setObjectName(QString::fromUtf8("label_59"));

        gridLayout_6->addWidget(label_59, 9, 0, 1, 1);

        label_60 = new QLabel(configure);
        label_60->setObjectName(QString::fromUtf8("label_60"));
        label_60->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_60, 9, 3, 1, 1);

        label_61 = new QLabel(configure);
        label_61->setObjectName(QString::fromUtf8("label_61"));
        label_61->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_61, 9, 1, 1, 2);

        unitsPerRevGui = new QMDoubleSpinBox(configure);
        unitsPerRevGui->setObjectName(QString::fromUtf8("unitsPerRevGui"));
        unitsPerRevGui->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 0, 0,64);"));
        unitsPerRevGui->setDecimals(7);
        unitsPerRevGui->setMinimum(-2.14748e+09);
        unitsPerRevGui->setMaximum(2.14748e+09);

        gridLayout_6->addWidget(unitsPerRevGui, 10, 0, 1, 2);

        placeCfgStepsPerRev = new QWidget(configure);
        placeCfgStepsPerRev->setObjectName(QString::fromUtf8("placeCfgStepsPerRev"));
        layCfgStepsPerRev = new QVBoxLayout(placeCfgStepsPerRev);
        layCfgStepsPerRev->setSpacing(0);
        layCfgStepsPerRev->setContentsMargins(0, 0, 0, 0);
        layCfgStepsPerRev->setObjectName(QString::fromUtf8("layCfgStepsPerRev"));
        layCfgStepsPerRev->setSizeConstraint(QLayout::SetMinAndMaxSize);

        gridLayout_6->addWidget(placeCfgStepsPerRev, 10, 2, 1, 2);


        verticalLayout->addWidget(configure);

        line_2 = new QFrame(MotorSetup);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        sizePolicy.setHeightForWidth(line_2->sizePolicy().hasHeightForWidth());
        line_2->setSizePolicy(sizePolicy);
        line_2->setVisible(true);
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        epics = new QWidget(MotorSetup);
        epics->setObjectName(QString::fromUtf8("epics"));
        epics->setEnabled(false);
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(epics->sizePolicy().hasHeightForWidth());
        epics->setSizePolicy(sizePolicy5);
        epics->setVisible(true);
        verticalLayout_4 = new QVBoxLayout(epics);
        verticalLayout_4->setSpacing(1);
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setSizeConstraint(QLayout::SetMinAndMaxSize);
        positionsEpics = new QWidget(epics);
        positionsEpics->setObjectName(QString::fromUtf8("positionsEpics"));
        sizePolicy.setHeightForWidth(positionsEpics->sizePolicy().hasHeightForWidth());
        positionsEpics->setSizePolicy(sizePolicy);
        gridLayout_5 = new QGridLayout(positionsEpics);
        gridLayout_5->setSpacing(1);
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label_36 = new QLabel(positionsEpics);
        label_36->setObjectName(QString::fromUtf8("label_36"));
        sizePolicy2.setHeightForWidth(label_36->sizePolicy().hasHeightForWidth());
        label_36->setSizePolicy(sizePolicy2);

        gridLayout_5->addWidget(label_36, 0, 1, 1, 1);

        label_37 = new QLabel(positionsEpics);
        label_37->setObjectName(QString::fromUtf8("label_37"));
        sizePolicy2.setHeightForWidth(label_37->sizePolicy().hasHeightForWidth());
        label_37->setSizePolicy(sizePolicy2);

        gridLayout_5->addWidget(label_37, 0, 2, 1, 1);

        label_31 = new QLabel(positionsEpics);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        sizePolicy2.setHeightForWidth(label_31->sizePolicy().hasHeightForWidth());
        label_31->setSizePolicy(sizePolicy2);

        gridLayout_5->addWidget(label_31, 0, 3, 1, 1);

        label_35 = new QLabel(positionsEpics);
        label_35->setObjectName(QString::fromUtf8("label_35"));
        sizePolicy1.setHeightForWidth(label_35->sizePolicy().hasHeightForWidth());
        label_35->setSizePolicy(sizePolicy1);

        gridLayout_5->addWidget(label_35, 1, 0, 1, 1);

        dialGoal = new QMDoubleSpinBox(positionsEpics);
        dialGoal->setObjectName(QString::fromUtf8("dialGoal"));
        sizePolicy.setHeightForWidth(dialGoal->sizePolicy().hasHeightForWidth());
        dialGoal->setSizePolicy(sizePolicy);
        dialGoal->setKeyboardTracking(false);
        dialGoal->setMinimum(-2.14748e+09);
        dialGoal->setMaximum(2.14748e+09);

        gridLayout_5->addWidget(dialGoal, 1, 2, 1, 1);

        line_7 = new QFrame(positionsEpics);
        line_7->setObjectName(QString::fromUtf8("line_7"));
        sizePolicy.setHeightForWidth(line_7->sizePolicy().hasHeightForWidth());
        line_7->setSizePolicy(sizePolicy);
        line_7->setFrameShape(QFrame::HLine);
        line_7->setFrameShadow(QFrame::Sunken);

        gridLayout_5->addWidget(line_7, 2, 0, 1, 4);

        label_12 = new QLabel(positionsEpics);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        sizePolicy1.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy1);

        gridLayout_5->addWidget(label_12, 3, 0, 1, 1);

        label_33 = new QLabel(positionsEpics);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        sizePolicy1.setHeightForWidth(label_33->sizePolicy().hasHeightForWidth());
        label_33->setSizePolicy(sizePolicy1);

        gridLayout_5->addWidget(label_33, 4, 0, 1, 1);

        label_32 = new QLabel(positionsEpics);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        sizePolicy1.setHeightForWidth(label_32->sizePolicy().hasHeightForWidth());
        label_32->setSizePolicy(sizePolicy1);

        gridLayout_5->addWidget(label_32, 5, 0, 1, 1);

        limitHiDial = new QMDoubleSpinBox(positionsEpics);
        limitHiDial->setObjectName(QString::fromUtf8("limitHiDial"));
        sizePolicy.setHeightForWidth(limitHiDial->sizePolicy().hasHeightForWidth());
        limitHiDial->setSizePolicy(sizePolicy);
        limitHiDial->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 0, 0,64);"));
        limitHiDial->setKeyboardTracking(false);
        limitHiDial->setMinimum(-2.14748e+09);
        limitHiDial->setMaximum(2.14748e+09);

        gridLayout_5->addWidget(limitHiDial, 3, 2, 1, 1);

        dialPosition = new QMDoubleSpinBox(positionsEpics);
        dialPosition->setObjectName(QString::fromUtf8("dialPosition"));
        sizePolicy.setHeightForWidth(dialPosition->sizePolicy().hasHeightForWidth());
        dialPosition->setSizePolicy(sizePolicy);
        dialPosition->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 0, 0,64);"));
        dialPosition->setKeyboardTracking(false);
        dialPosition->setMinimum(-2.14748e+09);
        dialPosition->setMaximum(2.14748e+09);

        gridLayout_5->addWidget(dialPosition, 4, 2, 1, 1);

        limitLoDial = new QMDoubleSpinBox(positionsEpics);
        limitLoDial->setObjectName(QString::fromUtf8("limitLoDial"));
        sizePolicy.setHeightForWidth(limitLoDial->sizePolicy().hasHeightForWidth());
        limitLoDial->setSizePolicy(sizePolicy);
        limitLoDial->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 0, 0,64);"));
        limitLoDial->setKeyboardTracking(false);
        limitLoDial->setMinimum(-2.14748e+09);
        limitLoDial->setMaximum(2.14748e+09);

        gridLayout_5->addWidget(limitLoDial, 5, 2, 1, 1);

        placeEpicsUserMove = new QWidget(positionsEpics);
        placeEpicsUserMove->setObjectName(QString::fromUtf8("placeEpicsUserMove"));
        sizePolicy2.setHeightForWidth(placeEpicsUserMove->sizePolicy().hasHeightForWidth());
        placeEpicsUserMove->setSizePolicy(sizePolicy2);
        layEpicsUserMove = new QVBoxLayout(placeEpicsUserMove);
        layEpicsUserMove->setSpacing(0);
        layEpicsUserMove->setContentsMargins(0, 0, 0, 0);
        layEpicsUserMove->setObjectName(QString::fromUtf8("layEpicsUserMove"));

        gridLayout_5->addWidget(placeEpicsUserMove, 1, 1, 1, 1);

        placeEpicsHi = new QWidget(positionsEpics);
        placeEpicsHi->setObjectName(QString::fromUtf8("placeEpicsHi"));
        sizePolicy2.setHeightForWidth(placeEpicsHi->sizePolicy().hasHeightForWidth());
        placeEpicsHi->setSizePolicy(sizePolicy2);
        layEpicsHi = new QVBoxLayout(placeEpicsHi);
        layEpicsHi->setSpacing(0);
        layEpicsHi->setContentsMargins(0, 0, 0, 0);
        layEpicsHi->setObjectName(QString::fromUtf8("layEpicsHi"));

        gridLayout_5->addWidget(placeEpicsHi, 3, 1, 1, 1);

        placeEpicsUserSet = new QWidget(positionsEpics);
        placeEpicsUserSet->setObjectName(QString::fromUtf8("placeEpicsUserSet"));
        sizePolicy2.setHeightForWidth(placeEpicsUserSet->sizePolicy().hasHeightForWidth());
        placeEpicsUserSet->setSizePolicy(sizePolicy2);
        layEpicsUserSet = new QVBoxLayout(placeEpicsUserSet);
        layEpicsUserSet->setSpacing(0);
        layEpicsUserSet->setContentsMargins(0, 0, 0, 0);
        layEpicsUserSet->setObjectName(QString::fromUtf8("layEpicsUserSet"));

        gridLayout_5->addWidget(placeEpicsUserSet, 4, 1, 1, 1);

        placeEpicsLo = new QWidget(positionsEpics);
        placeEpicsLo->setObjectName(QString::fromUtf8("placeEpicsLo"));
        sizePolicy2.setHeightForWidth(placeEpicsLo->sizePolicy().hasHeightForWidth());
        placeEpicsLo->setSizePolicy(sizePolicy2);
        layEpicsLo = new QVBoxLayout(placeEpicsLo);
        layEpicsLo->setSpacing(0);
        layEpicsLo->setContentsMargins(0, 0, 0, 0);
        layEpicsLo->setObjectName(QString::fromUtf8("layEpicsLo"));

        gridLayout_5->addWidget(placeEpicsLo, 5, 1, 1, 1);

        placeEpicsRawSet = new QWidget(positionsEpics);
        placeEpicsRawSet->setObjectName(QString::fromUtf8("placeEpicsRawSet"));
        sizePolicy2.setHeightForWidth(placeEpicsRawSet->sizePolicy().hasHeightForWidth());
        placeEpicsRawSet->setSizePolicy(sizePolicy2);
        layEpicsRawSet = new QVBoxLayout(placeEpicsRawSet);
        layEpicsRawSet->setSpacing(0);
        layEpicsRawSet->setContentsMargins(0, 0, 0, 0);
        layEpicsRawSet->setObjectName(QString::fromUtf8("layEpicsRawSet"));

        gridLayout_5->addWidget(placeEpicsRawSet, 4, 3, 1, 1);

        placeEpicsRawMove = new QWidget(positionsEpics);
        placeEpicsRawMove->setObjectName(QString::fromUtf8("placeEpicsRawMove"));
        sizePolicy2.setHeightForWidth(placeEpicsRawMove->sizePolicy().hasHeightForWidth());
        placeEpicsRawMove->setSizePolicy(sizePolicy2);
        layEpicsRawMove = new QVBoxLayout(placeEpicsRawMove);
        layEpicsRawMove->setSpacing(0);
        layEpicsRawMove->setContentsMargins(0, 0, 0, 0);
        layEpicsRawMove->setObjectName(QString::fromUtf8("layEpicsRawMove"));

        gridLayout_5->addWidget(placeEpicsRawMove, 1, 3, 1, 1);


        verticalLayout_4->addWidget(positionsEpics);

        line_3 = new QFrame(epics);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        sizePolicy.setHeightForWidth(line_3->sizePolicy().hasHeightForWidth());
        line_3->setSizePolicy(sizePolicy);
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout_4->addWidget(line_3);

        resolutionSetup = new QWidget(epics);
        resolutionSetup->setObjectName(QString::fromUtf8("resolutionSetup"));
        sizePolicy.setHeightForWidth(resolutionSetup->sizePolicy().hasHeightForWidth());
        resolutionSetup->setSizePolicy(sizePolicy);
        resolutionSetup_lay = new QGridLayout(resolutionSetup);
        resolutionSetup_lay->setSpacing(1);
        resolutionSetup_lay->setContentsMargins(0, 0, 0, 0);
        resolutionSetup_lay->setObjectName(QString::fromUtf8("resolutionSetup_lay"));
        label_15 = new QLabel(resolutionSetup);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        sizePolicy1.setHeightForWidth(label_15->sizePolicy().hasHeightForWidth());
        label_15->setSizePolicy(sizePolicy1);

        resolutionSetup_lay->addWidget(label_15, 0, 1, 1, 1);

        label_4 = new QLabel(resolutionSetup);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);

        resolutionSetup_lay->addWidget(label_4, 1, 0, 1, 1);

        label_5 = new QLabel(resolutionSetup);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy1);

        resolutionSetup_lay->addWidget(label_5, 2, 0, 1, 1);

        label_6 = new QLabel(resolutionSetup);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy1.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy1);

        resolutionSetup_lay->addWidget(label_6, 3, 0, 1, 1);

        useReadback = new QCheckBox(resolutionSetup);
        useReadback->setObjectName(QString::fromUtf8("useReadback"));
        sizePolicy1.setHeightForWidth(useReadback->sizePolicy().hasHeightForWidth());
        useReadback->setSizePolicy(sizePolicy1);
        useReadback->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 0, 0,64);"));

        resolutionSetup_lay->addWidget(useReadback, 2, 2, 1, 1);

        label_10 = new QLabel(resolutionSetup);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        sizePolicy1.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy1);

        resolutionSetup_lay->addWidget(label_10, 0, 2, 1, 1);

        useEncoder = new QCheckBox(resolutionSetup);
        useEncoder->setObjectName(QString::fromUtf8("useEncoder"));
        sizePolicy1.setHeightForWidth(useEncoder->sizePolicy().hasHeightForWidth());
        useEncoder->setSizePolicy(sizePolicy1);
        useEncoder->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 0, 0,64);"));

        resolutionSetup_lay->addWidget(useEncoder, 3, 2, 1, 1);

        encoderResolution = new QMDoubleSpinBox(resolutionSetup);
        encoderResolution->setObjectName(QString::fromUtf8("encoderResolution"));
        sizePolicy1.setHeightForWidth(encoderResolution->sizePolicy().hasHeightForWidth());
        encoderResolution->setSizePolicy(sizePolicy1);
        encoderResolution->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 0, 0,64);"));
        encoderResolution->setKeyboardTracking(false);
        encoderResolution->setDecimals(7);
        encoderResolution->setMinimum(-2.14748e+09);
        encoderResolution->setMaximum(2.14748e+09);

        resolutionSetup_lay->addWidget(encoderResolution, 3, 1, 1, 1);

        readbackResolution = new QMDoubleSpinBox(resolutionSetup);
        readbackResolution->setObjectName(QString::fromUtf8("readbackResolution"));
        sizePolicy1.setHeightForWidth(readbackResolution->sizePolicy().hasHeightForWidth());
        readbackResolution->setSizePolicy(sizePolicy1);
        readbackResolution->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 0, 0,64);"));
        readbackResolution->setKeyboardTracking(false);
        readbackResolution->setDecimals(7);
        readbackResolution->setMinimum(-2.14748e+09);
        readbackResolution->setMaximum(2.14748e+09);

        resolutionSetup_lay->addWidget(readbackResolution, 2, 1, 1, 1);

        label_27 = new QLabel(resolutionSetup);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        resolutionSetup_lay->addWidget(label_27, 5, 0, 1, 1);

        label_16 = new QLabel(resolutionSetup);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        sizePolicy1.setHeightForWidth(label_16->sizePolicy().hasHeightForWidth());
        label_16->setSizePolicy(sizePolicy1);

        resolutionSetup_lay->addWidget(label_16, 2, 4, 1, 1);

        line_10 = new QFrame(resolutionSetup);
        line_10->setObjectName(QString::fromUtf8("line_10"));
        line_10->setFrameShape(QFrame::VLine);
        line_10->setFrameShadow(QFrame::Sunken);

        resolutionSetup_lay->addWidget(line_10, 0, 3, 4, 1);

        label_13 = new QLabel(resolutionSetup);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        sizePolicy1.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy1);

        resolutionSetup_lay->addWidget(label_13, 0, 4, 2, 1);

        label_38 = new QLabel(resolutionSetup);
        label_38->setObjectName(QString::fromUtf8("label_38"));
        sizePolicy1.setHeightForWidth(label_38->sizePolicy().hasHeightForWidth());
        label_38->setSizePolicy(sizePolicy1);

        resolutionSetup_lay->addWidget(label_38, 3, 4, 1, 1);

        offsetVar = new QRadioButton(resolutionSetup);
        offGroup = new QButtonGroup(MotorSetup);
        offGroup->setObjectName(QString::fromUtf8("offGroup"));
        offGroup->addButton(offsetVar);
        offsetVar->setObjectName(QString::fromUtf8("offsetVar"));
        sizePolicy2.setHeightForWidth(offsetVar->sizePolicy().hasHeightForWidth());
        offsetVar->setSizePolicy(sizePolicy2);
        offsetVar->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 0, 0,64);"));

        resolutionSetup_lay->addWidget(offsetVar, 0, 5, 1, 1);

        offsetFrz = new QRadioButton(resolutionSetup);
        offGroup->addButton(offsetFrz);
        offsetFrz->setObjectName(QString::fromUtf8("offsetFrz"));
        sizePolicy2.setHeightForWidth(offsetFrz->sizePolicy().hasHeightForWidth());
        offsetFrz->setSizePolicy(sizePolicy2);
        offsetFrz->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 0, 0,64);"));

        resolutionSetup_lay->addWidget(offsetFrz, 0, 6, 1, 1);

        dirPos = new QRadioButton(resolutionSetup);
        dirGroup = new QButtonGroup(MotorSetup);
        dirGroup->setObjectName(QString::fromUtf8("dirGroup"));
        dirGroup->addButton(dirPos);
        dirPos->setObjectName(QString::fromUtf8("dirPos"));
        sizePolicy2.setHeightForWidth(dirPos->sizePolicy().hasHeightForWidth());
        dirPos->setSizePolicy(sizePolicy2);
        dirPos->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 0, 0,64);"));

        resolutionSetup_lay->addWidget(dirPos, 2, 5, 1, 1);

        dirNeg = new QRadioButton(resolutionSetup);
        dirGroup->addButton(dirNeg);
        dirNeg->setObjectName(QString::fromUtf8("dirNeg"));
        sizePolicy2.setHeightForWidth(dirNeg->sizePolicy().hasHeightForWidth());
        dirNeg->setSizePolicy(sizePolicy2);
        dirNeg->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 0, 0,64);"));

        resolutionSetup_lay->addWidget(dirNeg, 2, 6, 1, 1);

        useMode = new QRadioButton(resolutionSetup);
        setGroup = new QButtonGroup(MotorSetup);
        setGroup->setObjectName(QString::fromUtf8("setGroup"));
        setGroup->addButton(useMode);
        useMode->setObjectName(QString::fromUtf8("useMode"));
        sizePolicy2.setHeightForWidth(useMode->sizePolicy().hasHeightForWidth());
        useMode->setSizePolicy(sizePolicy2);
        useMode->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 0, 0,64);"));

        resolutionSetup_lay->addWidget(useMode, 3, 5, 1, 1);

        setMode = new QRadioButton(resolutionSetup);
        setGroup->addButton(setMode);
        setMode->setObjectName(QString::fromUtf8("setMode"));
        sizePolicy2.setHeightForWidth(setMode->sizePolicy().hasHeightForWidth());
        setMode->setSizePolicy(sizePolicy2);
        setMode->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 0, 0,64);"));

        resolutionSetup_lay->addWidget(setMode, 3, 6, 1, 1);

        offset = new QMDoubleSpinBox(resolutionSetup);
        offset->setObjectName(QString::fromUtf8("offset"));
        sizePolicy2.setHeightForWidth(offset->sizePolicy().hasHeightForWidth());
        offset->setSizePolicy(sizePolicy2);
        offset->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 0, 0,64);"));
        offset->setKeyboardTracking(false);
        offset->setMinimum(-2.14748e+09);
        offset->setMaximum(2.14748e+09);

        resolutionSetup_lay->addWidget(offset, 1, 5, 1, 2);

        line = new QFrame(resolutionSetup);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        resolutionSetup_lay->addWidget(line, 4, 0, 1, 7);

        label_30 = new QLabel(resolutionSetup);
        label_30->setObjectName(QString::fromUtf8("label_30"));

        resolutionSetup_lay->addWidget(label_30, 5, 4, 1, 1);

        unitsPerStep = new QMDoubleSpinBox(resolutionSetup);
        unitsPerStep->setObjectName(QString::fromUtf8("unitsPerStep"));
        sizePolicy2.setHeightForWidth(unitsPerStep->sizePolicy().hasHeightForWidth());
        unitsPerStep->setSizePolicy(sizePolicy2);
        unitsPerStep->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 0, 0,64);"));
        unitsPerStep->setKeyboardTracking(false);
        unitsPerStep->setDecimals(7);
        unitsPerStep->setMinimum(-2.14748e+09);
        unitsPerStep->setMaximum(2.14748e+09);

        resolutionSetup_lay->addWidget(unitsPerStep, 1, 1, 1, 1);

        placeEpicsStepsPerRev = new QWidget(resolutionSetup);
        placeEpicsStepsPerRev->setObjectName(QString::fromUtf8("placeEpicsStepsPerRev"));
        layEpicsStepsPerRev = new QVBoxLayout(placeEpicsStepsPerRev);
        layEpicsStepsPerRev->setSpacing(0);
        layEpicsStepsPerRev->setContentsMargins(0, 0, 0, 0);
        layEpicsStepsPerRev->setObjectName(QString::fromUtf8("layEpicsStepsPerRev"));
        layEpicsStepsPerRev->setSizeConstraint(QLayout::SetMinAndMaxSize);

        resolutionSetup_lay->addWidget(placeEpicsStepsPerRev, 5, 5, 1, 2);

        unitsPerRev = new QMDoubleSpinBox(resolutionSetup);
        unitsPerRev->setObjectName(QString::fromUtf8("unitsPerRev"));
        unitsPerRev->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 0, 0,64);"));
        unitsPerRev->setDecimals(7);
        unitsPerRev->setMinimum(-2.14748e+09);
        unitsPerRev->setMaximum(2.14748e+09);

        resolutionSetup_lay->addWidget(unitsPerRev, 5, 1, 1, 1);


        verticalLayout_4->addWidget(resolutionSetup);

        line_6 = new QFrame(epics);
        line_6->setObjectName(QString::fromUtf8("line_6"));
        sizePolicy.setHeightForWidth(line_6->sizePolicy().hasHeightForWidth());
        line_6->setSizePolicy(sizePolicy);
        line_6->setVisible(true);
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);

        verticalLayout_4->addWidget(line_6);

        speedSetup = new QWidget(epics);
        speedSetup->setObjectName(QString::fromUtf8("speedSetup"));
        sizePolicy.setHeightForWidth(speedSetup->sizePolicy().hasHeightForWidth());
        speedSetup->setSizePolicy(sizePolicy);
        speedSetup->setVisible(true);
        gridLayout = new QGridLayout(speedSetup);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_8 = new QLabel(speedSetup);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        sizePolicy1.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(label_8, 2, 0, 1, 1);

        label_9 = new QLabel(speedSetup);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        sizePolicy1.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(label_9, 5, 0, 1, 1);

        backlashSpeed = new QMDoubleSpinBox(speedSetup);
        backlashSpeed->setObjectName(QString::fromUtf8("backlashSpeed"));
        sizePolicy.setHeightForWidth(backlashSpeed->sizePolicy().hasHeightForWidth());
        backlashSpeed->setSizePolicy(sizePolicy);
        backlashSpeed->setKeyboardTracking(false);
        backlashSpeed->setMaximum(2.14748e+09);

        gridLayout->addWidget(backlashSpeed, 5, 1, 1, 1);

        backlashAcceleration = new QMDoubleSpinBox(speedSetup);
        backlashAcceleration->setObjectName(QString::fromUtf8("backlashAcceleration"));
        sizePolicy.setHeightForWidth(backlashAcceleration->sizePolicy().hasHeightForWidth());
        backlashAcceleration->setSizePolicy(sizePolicy);
        backlashAcceleration->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 0, 0,64);"));
        backlashAcceleration->setKeyboardTracking(false);
        backlashAcceleration->setMaximum(2.14748e+09);

        gridLayout->addWidget(backlashAcceleration, 5, 3, 1, 1);

        label_48 = new QLabel(speedSetup);
        label_48->setObjectName(QString::fromUtf8("label_48"));
        sizePolicy.setHeightForWidth(label_48->sizePolicy().hasHeightForWidth());
        label_48->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_48, 0, 1, 1, 1);

        label_49 = new QLabel(speedSetup);
        label_49->setObjectName(QString::fromUtf8("label_49"));
        sizePolicy1.setHeightForWidth(label_49->sizePolicy().hasHeightForWidth());
        label_49->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(label_49, 6, 0, 1, 1);

        label_50 = new QLabel(speedSetup);
        label_50->setObjectName(QString::fromUtf8("label_50"));
        sizePolicy.setHeightForWidth(label_50->sizePolicy().hasHeightForWidth());
        label_50->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_50, 0, 3, 1, 1);

        label_51 = new QLabel(speedSetup);
        label_51->setObjectName(QString::fromUtf8("label_51"));
        sizePolicy1.setHeightForWidth(label_51->sizePolicy().hasHeightForWidth());
        label_51->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(label_51, 3, 0, 1, 1);

        jogAcceleration = new QMDoubleSpinBox(speedSetup);
        jogAcceleration->setObjectName(QString::fromUtf8("jogAcceleration"));
        sizePolicy.setHeightForWidth(jogAcceleration->sizePolicy().hasHeightForWidth());
        jogAcceleration->setSizePolicy(sizePolicy);
        jogAcceleration->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 0, 0,64);"));
        jogAcceleration->setKeyboardTracking(false);
        jogAcceleration->setMaximum(2.14748e+09);

        gridLayout->addWidget(jogAcceleration, 6, 3, 1, 1);

        jogSpeed = new QMDoubleSpinBox(speedSetup);
        jogSpeed->setObjectName(QString::fromUtf8("jogSpeed"));
        sizePolicy.setHeightForWidth(jogSpeed->sizePolicy().hasHeightForWidth());
        jogSpeed->setSizePolicy(sizePolicy);
        jogSpeed->setKeyboardTracking(false);
        jogSpeed->setMaximum(2.14748e+09);

        gridLayout->addWidget(jogSpeed, 6, 1, 1, 1);

        maximumSpeed = new QMDoubleSpinBox(speedSetup);
        maximumSpeed->setObjectName(QString::fromUtf8("maximumSpeed"));
        sizePolicy.setHeightForWidth(maximumSpeed->sizePolicy().hasHeightForWidth());
        maximumSpeed->setSizePolicy(sizePolicy);
        maximumSpeed->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 0, 0,64);"));
        maximumSpeed->setKeyboardTracking(false);
        maximumSpeed->setMinimum(0);
        maximumSpeed->setMaximum(2.14748e+09);
        maximumSpeed->setValue(0);

        gridLayout->addWidget(maximumSpeed, 2, 1, 1, 1);

        acceleration = new QMDoubleSpinBox(speedSetup);
        acceleration->setObjectName(QString::fromUtf8("acceleration"));
        sizePolicy.setHeightForWidth(acceleration->sizePolicy().hasHeightForWidth());
        acceleration->setSizePolicy(sizePolicy);
        acceleration->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 0, 0,64);"));
        acceleration->setKeyboardTracking(false);
        acceleration->setMaximum(2.14748e+09);

        gridLayout->addWidget(acceleration, 3, 3, 1, 1);

        speed = new QMDoubleSpinBox(speedSetup);
        speed->setObjectName(QString::fromUtf8("speed"));
        sizePolicy.setHeightForWidth(speed->sizePolicy().hasHeightForWidth());
        speed->setSizePolicy(sizePolicy);
        speed->setKeyboardTracking(false);
        speed->setMaximum(2.14748e+09);

        gridLayout->addWidget(speed, 3, 1, 1, 1);

        label_11 = new QLabel(speedSetup);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout->addWidget(label_11, 7, 0, 1, 1);

        revSpeed = new QMDoubleSpinBox(speedSetup);
        revSpeed->setObjectName(QString::fromUtf8("revSpeed"));
        revSpeed->setMaximum(2.14748e+09);

        gridLayout->addWidget(revSpeed, 7, 1, 1, 1);


        verticalLayout_4->addWidget(speedSetup);


        verticalLayout->addWidget(epics);

        line_9 = new QFrame(MotorSetup);
        line_9->setObjectName(QString::fromUtf8("line_9"));
        sizePolicy.setHeightForWidth(line_9->sizePolicy().hasHeightForWidth());
        line_9->setSizePolicy(sizePolicy);
        line_9->setVisible(true);
        line_9->setFrameShape(QFrame::HLine);
        line_9->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_9);

        backlashSetup = new QWidget(MotorSetup);
        backlashSetup->setObjectName(QString::fromUtf8("backlashSetup"));
        backlashSetup->setEnabled(false);
        sizePolicy.setHeightForWidth(backlashSetup->sizePolicy().hasHeightForWidth());
        backlashSetup->setSizePolicy(sizePolicy);
        backlashSetup->setVisible(true);
        horizontalLayout_4 = new QHBoxLayout(backlashSetup);
        horizontalLayout_4->setSpacing(1);
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setSizeConstraint(QLayout::SetMinAndMaxSize);
        label_22 = new QLabel(backlashSetup);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        sizePolicy2.setHeightForWidth(label_22->sizePolicy().hasHeightForWidth());
        label_22->setSizePolicy(sizePolicy2);

        horizontalLayout_4->addWidget(label_22);

        backlash = new QMDoubleSpinBox(backlashSetup);
        backlash->setObjectName(QString::fromUtf8("backlash"));
        sizePolicy.setHeightForWidth(backlash->sizePolicy().hasHeightForWidth());
        backlash->setSizePolicy(sizePolicy);
        backlash->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 0, 0,64);"));
        backlash->setKeyboardTracking(false);
        backlash->setMinimum(-2.14748e+09);
        backlash->setMaximum(2.14748e+09);

        horizontalLayout_4->addWidget(backlash);


        verticalLayout->addWidget(backlashSetup);

        hidden = new QWidget(MotorSetup);
        hidden->setObjectName(QString::fromUtf8("hidden"));
        sizePolicy5.setHeightForWidth(hidden->sizePolicy().hasHeightForWidth());
        hidden->setSizePolicy(sizePolicy5);
        hidden->setVisible(true);
        layHide = new QVBoxLayout(hidden);
        layHide->setSpacing(0);
        layHide->setContentsMargins(0, 0, 0, 0);
        layHide->setObjectName(QString::fromUtf8("layHide"));
        rawGoal = new QMDoubleSpinBox(hidden);
        rawGoal->setObjectName(QString::fromUtf8("rawGoal"));
        sizePolicy2.setHeightForWidth(rawGoal->sizePolicy().hasHeightForWidth());
        rawGoal->setSizePolicy(sizePolicy2);
        rawGoal->setKeyboardTracking(false);
        rawGoal->setDecimals(0);
        rawGoal->setMinimum(-2.14748e+09);
        rawGoal->setMaximum(2.14748e+09);

        layHide->addWidget(rawGoal);

        userGoal = new QMDoubleSpinBox(hidden);
        userGoal->setObjectName(QString::fromUtf8("userGoal"));
        sizePolicy.setHeightForWidth(userGoal->sizePolicy().hasHeightForWidth());
        userGoal->setSizePolicy(sizePolicy);
        userGoal->setKeyboardTracking(false);
        userGoal->setMinimum(-2.14748e+09);
        userGoal->setMaximum(2.14748e+09);

        layHide->addWidget(userGoal);

        userPosition = new QMDoubleSpinBox(hidden);
        userPosition->setObjectName(QString::fromUtf8("userPosition"));
        sizePolicy.setHeightForWidth(userPosition->sizePolicy().hasHeightForWidth());
        userPosition->setSizePolicy(sizePolicy);
        userPosition->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 0, 0,64);"));
        userPosition->setKeyboardTracking(false);
        userPosition->setMinimum(-2.14748e+09);
        userPosition->setMaximum(2.14748e+09);

        layHide->addWidget(userPosition);

        rawPosition = new QMDoubleSpinBox(hidden);
        rawPosition->setObjectName(QString::fromUtf8("rawPosition"));
        sizePolicy.setHeightForWidth(rawPosition->sizePolicy().hasHeightForWidth());
        rawPosition->setSizePolicy(sizePolicy);
        rawPosition->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 0, 0,64);"));
        rawPosition->setKeyboardTracking(false);
        rawPosition->setDecimals(0);
        rawPosition->setMinimum(-2.14748e+09);
        rawPosition->setMaximum(2.14748e+09);

        layHide->addWidget(rawPosition);

        limitHi = new QMDoubleSpinBox(hidden);
        limitHi->setObjectName(QString::fromUtf8("limitHi"));
        sizePolicy.setHeightForWidth(limitHi->sizePolicy().hasHeightForWidth());
        limitHi->setSizePolicy(sizePolicy);
        limitHi->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 0, 0,64);"));
        limitHi->setKeyboardTracking(false);
        limitHi->setMinimum(-2.14748e+09);
        limitHi->setMaximum(2.14748e+09);

        layHide->addWidget(limitHi);

        limitLo = new QMDoubleSpinBox(hidden);
        limitLo->setObjectName(QString::fromUtf8("limitLo"));
        sizePolicy.setHeightForWidth(limitLo->sizePolicy().hasHeightForWidth());
        limitLo->setSizePolicy(sizePolicy);
        limitLo->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 0, 0,64);"));
        limitLo->setKeyboardTracking(false);
        limitLo->setMinimum(-2.14748e+09);
        limitLo->setMaximum(2.14748e+09);

        layHide->addWidget(limitLo);

        stepsPerRev = new QMSpinBox(hidden);
        stepsPerRev->setObjectName(QString::fromUtf8("stepsPerRev"));
        stepsPerRev->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 0, 0,64);"));
        stepsPerRev->setMaximum(2147483647);

        layHide->addWidget(stepsPerRev);

        callRelative = new QToolButton(hidden);
        callRelative->setObjectName(QString::fromUtf8("callRelative"));
        sizePolicy2.setHeightForWidth(callRelative->sizePolicy().hasHeightForWidth());
        callRelative->setSizePolicy(sizePolicy2);

        layHide->addWidget(callRelative);

        userVarGoal = new QMDoubleSpinBox(hidden);
        userVarGoal->setObjectName(QString::fromUtf8("userVarGoal"));
        sizePolicy.setHeightForWidth(userVarGoal->sizePolicy().hasHeightForWidth());
        userVarGoal->setSizePolicy(sizePolicy);
        userVarGoal->setMinimum(-2.14748e+09);
        userVarGoal->setMaximum(2.14748e+09);

        layHide->addWidget(userVarGoal);

        absLabel = new QLabel(hidden);
        absLabel->setObjectName(QString::fromUtf8("absLabel"));
        sizePolicy1.setHeightForWidth(absLabel->sizePolicy().hasHeightForWidth());
        absLabel->setSizePolicy(sizePolicy1);

        layHide->addWidget(absLabel);


        verticalLayout->addWidget(hidden);


        retranslateUi(MotorSetup);
        QObject::connect(clearMessage, SIGNAL(clicked()), message, SLOT(clear()));

        viewMode->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MotorSetup);
    } // setupUi

    void retranslateUi(QDialog *MotorSetup)
    {
        MotorSetup->setWindowTitle(QApplication::translate("MotorSetup", "Dialog", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MotorSetup", "PV name", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("MotorSetup", "View mode", 0, QApplication::UnicodeUTF8));
        viewMode->clear();
        viewMode->insertItems(0, QStringList()
         << QApplication::translate("MotorSetup", "Set PV", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MotorSetup", "Minimalistic", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MotorSetup", "Comfortable", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MotorSetup", "Configure", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MotorSetup", "EPICS", 0, QApplication::UnicodeUTF8)
        );
#ifndef QT_NO_TOOLTIP
        viewMode->setToolTip(QApplication::translate("MotorSetup", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Bitstream Vera Sans'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">View mode of the dialog:</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Setup</span>: Only allows to chose the motor and View mode.</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Nano</span>: Only minimal control.</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; t"
                        "ext-indent:0px;\"><span style=\" font-weight:600;\">Micro</span>: Advanced control.</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Mili</span>: Advanced control with full text description and basic setup.</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Macro</span>: Advanced control and important setup.</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Epics</span>: Full set of control and setup elements including low level ones. Please use it only if you know what you are doing.</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        pv->setToolTip(QApplication::translate("MotorSetup", "Copy PV", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pv->setText(QString());
        label_14->setText(QApplication::translate("MotorSetup", "Configuration:", 0, QApplication::UnicodeUTF8));
        label_52->setText(QApplication::translate("MotorSetup", "Load", 0, QApplication::UnicodeUTF8));
        loadConfig->clear();
        loadConfig->insertItems(0, QStringList()
         << QApplication::translate("MotorSetup", "From file", 0, QApplication::UnicodeUTF8)
        );
        saveConfig->setText(QApplication::translate("MotorSetup", "Save As", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MotorSetup", "Description", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        description->setToolTip(QApplication::translate("MotorSetup", "Description / name to be used in the main interface window", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        description->setText(QString());
        label_19->setText(QApplication::translate("MotorSetup", "Power", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        power->setToolTip(QApplication::translate("MotorSetup", "Turn the power on/off", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        power->setText(QApplication::translate("MotorSetup", "ON", 0, QApplication::UnicodeUTF8));
        label_23->setText(QString());
        label_39->setText(QApplication::translate("MotorSetup", "Precision", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        precision->setToolTip(QApplication::translate("MotorSetup", "Precsision", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_25->setText(QString());
        label_40->setText(QApplication::translate("MotorSetup", "Units", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        units->setToolTip(QApplication::translate("MotorSetup", "Units", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_26->setText(QApplication::translate("MotorSetup", "Message:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        message->setToolTip(QApplication::translate("MotorSetup", "Messages", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        message->setText(QApplication::translate("MotorSetup", "Select motor's PV in the top left box.", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        clearMessage->setToolTip(QApplication::translate("MotorSetup", "Clean the message box", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        clearMessage->setText(QApplication::translate("MotorSetup", "clean", 0, QApplication::UnicodeUTF8));
        label_34->setText(QApplication::translate("MotorSetup", "Drive mode:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        Spmg->setToolTip(QApplication::translate("MotorSetup", "Stop the motor and forget the destination. The motor will not move while in this mode.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        Spmg->setText(QApplication::translate("MotorSetup", "Stop", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        sPmg->setToolTip(QApplication::translate("MotorSetup", "Stops the motion, but does not reset the destination: you can continue going switching to \"Move\" or \"Go\" modes. The motor will not move while in this mode.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        sPmg->setText(QApplication::translate("MotorSetup", "Pause", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        spMg->setToolTip(QApplication::translate("MotorSetup", "The motor will reset to \"Pause\" when a motion completes. This behavior supports users who want a motor to sit still until they say \"Move\", no matter what changes occur in the drive fields.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        spMg->setText(QApplication::translate("MotorSetup", "Move", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        spmG->setToolTip(QApplication::translate("MotorSetup", "Normal motion mode.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        spmG->setText(QApplication::translate("MotorSetup", "Go", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MotorSetup", "User", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("MotorSetup", "Move absolutely", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        goLimitM->setToolTip(QApplication::translate("MotorSetup", "Go to negative limit (hard or soft - whatever is activated first)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        goLimitM->setText(QApplication::translate("MotorSetup", "|<", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        goM->setToolTip(QApplication::translate("MotorSetup", "Move to minus by the step", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        goM->setText(QApplication::translate("MotorSetup", "<", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        step->setToolTip(QApplication::translate("MotorSetup", "Step", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        stepD10->setToolTip(QApplication::translate("MotorSetup", "Divide step by 10", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        stepD10->setText(QApplication::translate("MotorSetup", "1/10", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        stepD2->setToolTip(QApplication::translate("MotorSetup", "Divide step by 2", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        stepD2->setText(QApplication::translate("MotorSetup", "1/2", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        stepM2->setToolTip(QApplication::translate("MotorSetup", "Multiply step by 2", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        stepM2->setText(QApplication::translate("MotorSetup", "2", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        stepM10->setToolTip(QApplication::translate("MotorSetup", "Multiply step by 10", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        stepM10->setText(QApplication::translate("MotorSetup", "10", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        goP->setToolTip(QApplication::translate("MotorSetup", "Move to plus by step", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        goP->setText(QApplication::translate("MotorSetup", ">", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        goLimitP->setToolTip(QApplication::translate("MotorSetup", "Go to positive limit (hard or soft - whatever is activated first)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        goLimitP->setText(QApplication::translate("MotorSetup", ">|", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MotorSetup", "Raw", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        jogM->setToolTip(QApplication::translate("MotorSetup", "Press to jog, release to stop jogging", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        jogM->setText(QApplication::translate("MotorSetup", "<<", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        stop->setToolTip(QApplication::translate("MotorSetup", "Stop motion", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        stop->setText(QApplication::translate("MotorSetup", "STOP", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        jogP->setToolTip(QApplication::translate("MotorSetup", "Press to jog, release to stop jogging", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        jogP->setText(QApplication::translate("MotorSetup", ">>", 0, QApplication::UnicodeUTF8));
        label_41->setText(QApplication::translate("MotorSetup", "User", 0, QApplication::UnicodeUTF8));
        label_42->setText(QApplication::translate("MotorSetup", "Set position", 0, QApplication::UnicodeUTF8));
        label_44->setText(QApplication::translate("MotorSetup", "Raw", 0, QApplication::UnicodeUTF8));
        label_47->setText(QApplication::translate("MotorSetup", "Lo", 0, QApplication::UnicodeUTF8));
        label_46->setText(QApplication::translate("MotorSetup", "Limits", 0, QApplication::UnicodeUTF8));
        label_53->setText(QApplication::translate("MotorSetup", "Hi", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("MotorSetup", "Speeds", 0, QApplication::UnicodeUTF8));
        label_45->setText(QApplication::translate("MotorSetup", "Accelerations", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        accelerationS->setToolTip(QApplication::translate("MotorSetup", "Normal acceleration (seconds to speed)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        accelerationS->setSuffix(QApplication::translate("MotorSetup", "s", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        speedS->setToolTip(QApplication::translate("MotorSetup", "Normal speed", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_59->setText(QApplication::translate("MotorSetup", "Units/rev", 0, QApplication::UnicodeUTF8));
        label_60->setText(QApplication::translate("MotorSetup", "Steps/rev", 0, QApplication::UnicodeUTF8));
        label_61->setText(QApplication::translate("MotorSetup", "Resolution", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        unitsPerRevGui->setToolTip(QApplication::translate("MotorSetup", "Units per revolution", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_36->setText(QApplication::translate("MotorSetup", "User", 0, QApplication::UnicodeUTF8));
        label_37->setText(QApplication::translate("MotorSetup", "Dial", 0, QApplication::UnicodeUTF8));
        label_31->setText(QApplication::translate("MotorSetup", "Raw", 0, QApplication::UnicodeUTF8));
        label_35->setText(QApplication::translate("MotorSetup", "Move", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        dialGoal->setToolTip(QApplication::translate("MotorSetup", "Move absolute in \"Dial\" coordinates", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_12->setText(QApplication::translate("MotorSetup", "Hi limit", 0, QApplication::UnicodeUTF8));
        label_33->setText(QApplication::translate("MotorSetup", "Set", 0, QApplication::UnicodeUTF8));
        label_32->setText(QApplication::translate("MotorSetup", "Lo Limit", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        limitHiDial->setToolTip(QApplication::translate("MotorSetup", "Hi limit in dial coordinates", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        dialPosition->setToolTip(QApplication::translate("MotorSetup", "Set position in dial coordinates (does not move the motor)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        limitLoDial->setToolTip(QApplication::translate("MotorSetup", "Lo limit in dial coordinates", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_15->setText(QApplication::translate("MotorSetup", "Resolution", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MotorSetup", "Motor", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MotorSetup", "Readback", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MotorSetup", "Encoder", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        useReadback->setToolTip(QApplication::translate("MotorSetup", "Use \"readback location\" link if present", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        useReadback->setText(QString());
        label_10->setText(QApplication::translate("MotorSetup", "Use", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        useEncoder->setToolTip(QApplication::translate("MotorSetup", "Use encoder if present", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        useEncoder->setText(QString());
#ifndef QT_NO_TOOLTIP
        encoderResolution->setToolTip(QApplication::translate("MotorSetup", "Set encoder resolution", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        readbackResolution->setToolTip(QApplication::translate("MotorSetup", "Set readback resolution", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_27->setText(QApplication::translate("MotorSetup", "Units/Rev", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("MotorSetup", "Direction", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("MotorSetup", "Offset", 0, QApplication::UnicodeUTF8));
        label_38->setText(QApplication::translate("MotorSetup", "\"Set\" mode", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        offsetVar->setToolTip(QApplication::translate("MotorSetup", "Variable offset", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        offsetVar->setText(QApplication::translate("MotorSetup", "Variable", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        offsetFrz->setToolTip(QApplication::translate("MotorSetup", "Frozen offset", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        offsetFrz->setText(QApplication::translate("MotorSetup", "Frozen", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        dirPos->setToolTip(QApplication::translate("MotorSetup", "Positive user direction", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        dirPos->setText(QApplication::translate("MotorSetup", "Positive", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        dirNeg->setToolTip(QApplication::translate("MotorSetup", "Negative user direction", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        dirNeg->setText(QApplication::translate("MotorSetup", "Negative", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        useMode->setToolTip(QApplication::translate("MotorSetup", "Changes the set switch to \"Use\" mode", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        useMode->setText(QApplication::translate("MotorSetup", "Use", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        setMode->setToolTip(QApplication::translate("MotorSetup", "Changes the set switch to \"Set\" mode", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        setMode->setText(QApplication::translate("MotorSetup", "Set", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        offset->setToolTip(QApplication::translate("MotorSetup", "Offset (difference between dial and user coordinates)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_30->setText(QApplication::translate("MotorSetup", "Steps/Rev", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        unitsPerStep->setToolTip(QApplication::translate("MotorSetup", "Set motor resolution (travel distance per raw step)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        unitsPerRev->setToolTip(QApplication::translate("MotorSetup", "Units per revolution", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_8->setText(QApplication::translate("MotorSetup", "Maximum", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MotorSetup", "Backlash", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        backlashSpeed->setToolTip(QApplication::translate("MotorSetup", "Backlash speed", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        backlashAcceleration->setToolTip(QApplication::translate("MotorSetup", "Backlash acceleration (seconds to speed)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        backlashAcceleration->setSuffix(QApplication::translate("MotorSetup", "s", 0, QApplication::UnicodeUTF8));
        label_48->setText(QApplication::translate("MotorSetup", "Speed", 0, QApplication::UnicodeUTF8));
        label_49->setText(QApplication::translate("MotorSetup", "Jog", 0, QApplication::UnicodeUTF8));
        label_50->setText(QApplication::translate("MotorSetup", "Acceleration", 0, QApplication::UnicodeUTF8));
        label_51->setText(QApplication::translate("MotorSetup", "Normal", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        jogAcceleration->setToolTip(QApplication::translate("MotorSetup", "Jog acceleration (seconds to speed)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        jogAcceleration->setSuffix(QApplication::translate("MotorSetup", "s", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        jogSpeed->setToolTip(QApplication::translate("MotorSetup", "Jog speed", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        maximumSpeed->setToolTip(QApplication::translate("MotorSetup", "Maximum speed (no speed can be larger than this)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        acceleration->setToolTip(QApplication::translate("MotorSetup", "Normal acceleration (seconds to speed)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        acceleration->setSuffix(QApplication::translate("MotorSetup", "s", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        speed->setToolTip(QApplication::translate("MotorSetup", "Normal speed", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_11->setText(QApplication::translate("MotorSetup", "Revolve", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        revSpeed->setToolTip(QApplication::translate("MotorSetup", "Speed of the motor in terms of turns per second", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        revSpeed->setSuffix(QApplication::translate("MotorSetup", "rev/s", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("MotorSetup", "Backlash", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        backlash->setToolTip(QApplication::translate("MotorSetup", "Backlash distance", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        rawGoal->setToolTip(QApplication::translate("MotorSetup", "Move absolute in \"Raw\" coordinates", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        userGoal->setToolTip(QApplication::translate("MotorSetup", "Move absolutely", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        userPosition->setToolTip(QApplication::translate("MotorSetup", "Set position in user coordinates (does not move the motor)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        rawPosition->setToolTip(QApplication::translate("MotorSetup", "Set raw position (does not move the motor)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        limitHi->setToolTip(QApplication::translate("MotorSetup", "Hi limit in user coordinates", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        limitLo->setToolTip(QApplication::translate("MotorSetup", "Lo limit in user coordinates", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        stepsPerRev->setToolTip(QApplication::translate("MotorSetup", "Steps per revolution", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        callRelative->setToolTip(QApplication::translate("MotorSetup", "Move relatively", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        callRelative->setText(QApplication::translate("MotorSetup", "Move relatively", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        userVarGoal->setToolTip(QApplication::translate("MotorSetup", "Move absolutely", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        absLabel->setText(QApplication::translate("MotorSetup", "Move to:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MotorSetup: public Ui_MotorSetup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCAMOTORGUI_2D_SETUP_H
