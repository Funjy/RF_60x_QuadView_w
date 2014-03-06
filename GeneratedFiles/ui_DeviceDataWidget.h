/********************************************************************************
** Form generated from reading UI file 'DeviceDataWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVICEDATAWIDGET_H
#define UI_DEVICEDATAWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qwt_text_label.h"

QT_BEGIN_NAMESPACE

class Ui_DeviceDataWidget
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *mainLayout;
    QHBoxLayout *topLayout;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_2;
    QLineEdit *addressBox;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QwtTextLabel *snLabel;
    QLabel *snBox;
    QSpacerItem *horizontalSpacer_5;
    QwtTextLabel *baseDistLabel;
    QLabel *baseDistBox;
    QSpacerItem *horizontalSpacer_6;
    QwtTextLabel *rangeLabel;
    QLabel *rangeBox;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *bottomLayout;

    void setupUi(QWidget *DeviceDataWidget)
    {
        if (DeviceDataWidget->objectName().isEmpty())
            DeviceDataWidget->setObjectName(QStringLiteral("DeviceDataWidget"));
        DeviceDataWidget->resize(673, 382);
        horizontalLayout_2 = new QHBoxLayout(DeviceDataWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        mainLayout = new QVBoxLayout();
        mainLayout->setSpacing(6);
        mainLayout->setObjectName(QStringLiteral("mainLayout"));
        topLayout = new QHBoxLayout();
        topLayout->setSpacing(6);
        topLayout->setObjectName(QStringLiteral("topLayout"));

        mainLayout->addLayout(topLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        label_2 = new QLabel(DeviceDataWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(label_2);

        addressBox = new QLineEdit(DeviceDataWidget);
        addressBox->setObjectName(QStringLiteral("addressBox"));
        addressBox->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(addressBox->sizePolicy().hasHeightForWidth());
        addressBox->setSizePolicy(sizePolicy1);
        addressBox->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_3->addWidget(addressBox);

        horizontalSpacer_4 = new QSpacerItem(40, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        mainLayout->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        snLabel = new QwtTextLabel(DeviceDataWidget);
        snLabel->setObjectName(QStringLiteral("snLabel"));
        sizePolicy.setHeightForWidth(snLabel->sizePolicy().hasHeightForWidth());
        snLabel->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(snLabel);

        snBox = new QLabel(DeviceDataWidget);
        snBox->setObjectName(QStringLiteral("snBox"));
        sizePolicy.setHeightForWidth(snBox->sizePolicy().hasHeightForWidth());
        snBox->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(snBox);

        horizontalSpacer_5 = new QSpacerItem(12, 1, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        baseDistLabel = new QwtTextLabel(DeviceDataWidget);
        baseDistLabel->setObjectName(QStringLiteral("baseDistLabel"));
        sizePolicy.setHeightForWidth(baseDistLabel->sizePolicy().hasHeightForWidth());
        baseDistLabel->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(baseDistLabel);

        baseDistBox = new QLabel(DeviceDataWidget);
        baseDistBox->setObjectName(QStringLiteral("baseDistBox"));
        sizePolicy.setHeightForWidth(baseDistBox->sizePolicy().hasHeightForWidth());
        baseDistBox->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(baseDistBox);

        horizontalSpacer_6 = new QSpacerItem(12, 1, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);

        rangeLabel = new QwtTextLabel(DeviceDataWidget);
        rangeLabel->setObjectName(QStringLiteral("rangeLabel"));
        sizePolicy.setHeightForWidth(rangeLabel->sizePolicy().hasHeightForWidth());
        rangeLabel->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(rangeLabel);

        rangeBox = new QLabel(DeviceDataWidget);
        rangeBox->setObjectName(QStringLiteral("rangeBox"));
        sizePolicy.setHeightForWidth(rangeBox->sizePolicy().hasHeightForWidth());
        rangeBox->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(rangeBox);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        mainLayout->addLayout(horizontalLayout);

        bottomLayout = new QHBoxLayout();
        bottomLayout->setSpacing(6);
        bottomLayout->setObjectName(QStringLiteral("bottomLayout"));

        mainLayout->addLayout(bottomLayout);


        horizontalLayout_2->addLayout(mainLayout);


        retranslateUi(DeviceDataWidget);

        QMetaObject::connectSlotsByName(DeviceDataWidget);
    } // setupUi

    void retranslateUi(QWidget *DeviceDataWidget)
    {
        DeviceDataWidget->setWindowTitle(QApplication::translate("DeviceDataWidget", "DeviceDataWidget", 0));
        label_2->setText(QApplication::translate("DeviceDataWidget", "Network address:", 0));
        snLabel->setPlainText(QApplication::translate("DeviceDataWidget", "S/N:", 0));
        snBox->setText(QApplication::translate("DeviceDataWidget", "N/A", 0));
        baseDistLabel->setPlainText(QApplication::translate("DeviceDataWidget", "Base distance:", 0));
        baseDistBox->setText(QApplication::translate("DeviceDataWidget", "N/A", 0));
        rangeLabel->setPlainText(QApplication::translate("DeviceDataWidget", "Range:", 0));
        rangeBox->setText(QApplication::translate("DeviceDataWidget", "N/A", 0));
    } // retranslateUi

};

namespace Ui {
    class DeviceDataWidget: public Ui_DeviceDataWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICEDATAWIDGET_H
