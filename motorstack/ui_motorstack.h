/********************************************************************************
** Form generated from reading UI file 'motorstack.ui'
**
** Created: Mon Jul 18 16:50:57 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MOTORSTACK_H
#define UI_MOTORSTACK_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MotorStack
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *all;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QFrame *line_3;
    QLabel *label_2;
    QComboBox *viewModeAll;
    QFrame *line_2;
    QPushButton *stopAll;
    QWidget *powerW;
    QHBoxLayout *horizontalLayout_3;
    QFrame *line;
    QLabel *label;
    QToolButton *offAll;
    QToolButton *onAll;
    QTableWidget *table;
    QWidget *manipulate;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *clear;
    QPushButton *add;

    void setupUi(QWidget *MotorStack)
    {
        if (MotorStack->objectName().isEmpty())
            MotorStack->setObjectName(QString::fromUtf8("MotorStack"));
        MotorStack->resize(633, 218);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MotorStack->sizePolicy().hasHeightForWidth());
        MotorStack->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(MotorStack);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        all = new QWidget(MotorStack);
        all->setObjectName(QString::fromUtf8("all"));
        sizePolicy.setHeightForWidth(all->sizePolicy().hasHeightForWidth());
        all->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(all);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(all);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(label_3);

        line_3 = new QFrame(all);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_3);

        label_2 = new QLabel(all);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(label_2);

        viewModeAll = new QComboBox(all);
        viewModeAll->setObjectName(QString::fromUtf8("viewModeAll"));

        horizontalLayout->addWidget(viewModeAll);

        line_2 = new QFrame(all);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_2);

        stopAll = new QPushButton(all);
        stopAll->setObjectName(QString::fromUtf8("stopAll"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(1);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(stopAll->sizePolicy().hasHeightForWidth());
        stopAll->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(stopAll);

        powerW = new QWidget(all);
        powerW->setObjectName(QString::fromUtf8("powerW"));
        sizePolicy.setHeightForWidth(powerW->sizePolicy().hasHeightForWidth());
        powerW->setSizePolicy(sizePolicy);
        horizontalLayout_3 = new QHBoxLayout(powerW);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        line = new QFrame(powerW);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(line);

        label = new QLabel(powerW);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(label);

        offAll = new QToolButton(powerW);
        offAll->setObjectName(QString::fromUtf8("offAll"));

        horizontalLayout_3->addWidget(offAll);

        onAll = new QToolButton(powerW);
        onAll->setObjectName(QString::fromUtf8("onAll"));

        horizontalLayout_3->addWidget(onAll);


        horizontalLayout->addWidget(powerW);


        verticalLayout->addWidget(all);

        table = new QTableWidget(MotorStack);
        if (table->columnCount() < 7)
            table->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        table->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        table->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        table->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        table->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        table->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        table->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        table->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        table->setObjectName(QString::fromUtf8("table"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(table->sizePolicy().hasHeightForWidth());
        table->setSizePolicy(sizePolicy3);
        table->setMinimumSize(QSize(633, 0));
        table->setLineWidth(0);
        table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        table->setAlternatingRowColors(true);
        table->setSelectionMode(QAbstractItemView::NoSelection);
        table->setShowGrid(false);

        verticalLayout->addWidget(table);

        manipulate = new QWidget(MotorStack);
        manipulate->setObjectName(QString::fromUtf8("manipulate"));
        sizePolicy.setHeightForWidth(manipulate->sizePolicy().hasHeightForWidth());
        manipulate->setSizePolicy(sizePolicy);
        horizontalLayout_2 = new QHBoxLayout(manipulate);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        clear = new QPushButton(manipulate);
        clear->setObjectName(QString::fromUtf8("clear"));

        horizontalLayout_2->addWidget(clear);

        add = new QPushButton(manipulate);
        add->setObjectName(QString::fromUtf8("add"));
        sizePolicy2.setHeightForWidth(add->sizePolicy().hasHeightForWidth());
        add->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(add);


        verticalLayout->addWidget(manipulate);


        retranslateUi(MotorStack);

        QMetaObject::connectSlotsByName(MotorStack);
    } // setupUi

    void retranslateUi(QWidget *MotorStack)
    {
        MotorStack->setWindowTitle(QApplication::translate("MotorStack", "Form", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MotorStack", "All:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MotorStack", "view", 0, QApplication::UnicodeUTF8));
        viewModeAll->clear();
        viewModeAll->insertItems(0, QStringList()
         << QApplication::translate("MotorStack", "Hide", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MotorStack", "Show", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MotorStack", "Minimalistic", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MotorStack", "Comfortable", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MotorStack", "Configure", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MotorStack", "EPICS", 0, QApplication::UnicodeUTF8)
        );
        stopAll->setText(QApplication::translate("MotorStack", "Stop", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MotorStack", "Power:", 0, QApplication::UnicodeUTF8));
        offAll->setText(QApplication::translate("MotorStack", "OFF", 0, QApplication::UnicodeUTF8));
        onAll->setText(QApplication::translate("MotorStack", "ON", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = table->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MotorStack", "Setup", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = table->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MotorStack", "Position", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = table->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MotorStack", "<", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = table->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MotorStack", "Step", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = table->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MotorStack", ">", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = table->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("MotorStack", "Stop", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = table->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("MotorStack", "O", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ___qtablewidgetitem6->setToolTip(QApplication::translate("MotorStack", "Power", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        clear->setText(QApplication::translate("MotorStack", "Clear All", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        add->setToolTip(QApplication::translate("MotorStack", "Add motor to the interface", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        add->setText(QApplication::translate("MotorStack", "Add motor", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MotorStack: public Ui_MotorStack {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOTORSTACK_H
