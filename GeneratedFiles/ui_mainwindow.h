/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *ParametersLayout;
    QPushButton *scanPortsButton;
    QFormLayout *formLayout;
    QLabel *label;
    QComboBox *comPortsBox;
    QLabel *label_2;
    QComboBox *comSpeedBox;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *periodBox;
    QLineEdit *dumpFileBox;
    QPushButton *connectButton;
    QPushButton *streamButton;
    QSpacerItem *verticalSpacer;
    QGridLayout *graphsLayout;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1024, 600);
        QIcon icon;
        icon.addFile(QStringLiteral("app.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        ParametersLayout = new QVBoxLayout();
        ParametersLayout->setSpacing(6);
        ParametersLayout->setObjectName(QStringLiteral("ParametersLayout"));
        scanPortsButton = new QPushButton(centralWidget);
        scanPortsButton->setObjectName(QStringLiteral("scanPortsButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scanPortsButton->sizePolicy().hasHeightForWidth());
        scanPortsButton->setSizePolicy(sizePolicy);
        scanPortsButton->setMaximumSize(QSize(240, 16777215));
        QFont font;
        font.setPointSize(10);
        scanPortsButton->setFont(font);

        ParametersLayout->addWidget(scanPortsButton);

        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setFont(font);

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        comPortsBox = new QComboBox(centralWidget);
        comPortsBox->setObjectName(QStringLiteral("comPortsBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Ignored, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(comPortsBox->sizePolicy().hasHeightForWidth());
        comPortsBox->setSizePolicy(sizePolicy2);
        comPortsBox->setFont(font);

        formLayout->setWidget(0, QFormLayout::FieldRole, comPortsBox);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setFont(font);

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        comSpeedBox = new QComboBox(centralWidget);
        comSpeedBox->setObjectName(QStringLiteral("comSpeedBox"));
        sizePolicy2.setHeightForWidth(comSpeedBox->sizePolicy().hasHeightForWidth());
        comSpeedBox->setSizePolicy(sizePolicy2);
        comSpeedBox->setFont(font);

        formLayout->setWidget(1, QFormLayout::FieldRole, comSpeedBox);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);
        label_3->setFont(font);

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);
        label_4->setFont(font);

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        periodBox = new QLineEdit(centralWidget);
        periodBox->setObjectName(QStringLiteral("periodBox"));
        QSizePolicy sizePolicy3(QSizePolicy::Ignored, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(periodBox->sizePolicy().hasHeightForWidth());
        periodBox->setSizePolicy(sizePolicy3);

        formLayout->setWidget(2, QFormLayout::FieldRole, periodBox);

        dumpFileBox = new QLineEdit(centralWidget);
        dumpFileBox->setObjectName(QStringLiteral("dumpFileBox"));
        sizePolicy.setHeightForWidth(dumpFileBox->sizePolicy().hasHeightForWidth());
        dumpFileBox->setSizePolicy(sizePolicy);
        dumpFileBox->setMaximumSize(QSize(90, 16777215));

        formLayout->setWidget(3, QFormLayout::FieldRole, dumpFileBox);


        ParametersLayout->addLayout(formLayout);

        connectButton = new QPushButton(centralWidget);
        connectButton->setObjectName(QStringLiteral("connectButton"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(connectButton->sizePolicy().hasHeightForWidth());
        connectButton->setSizePolicy(sizePolicy4);
        connectButton->setMaximumSize(QSize(240, 16777215));
        connectButton->setFont(font);

        ParametersLayout->addWidget(connectButton);

        streamButton = new QPushButton(centralWidget);
        streamButton->setObjectName(QStringLiteral("streamButton"));
        sizePolicy4.setHeightForWidth(streamButton->sizePolicy().hasHeightForWidth());
        streamButton->setSizePolicy(sizePolicy4);
        streamButton->setMaximumSize(QSize(240, 16777215));
        streamButton->setFont(font);

        ParametersLayout->addWidget(streamButton);

        verticalSpacer = new QSpacerItem(1, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        ParametersLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(ParametersLayout);

        graphsLayout = new QGridLayout();
        graphsLayout->setSpacing(6);
        graphsLayout->setObjectName(QStringLiteral("graphsLayout"));

        horizontalLayout->addLayout(graphsLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        scanPortsButton->setText(QApplication::translate("MainWindow", "Scan ports", 0));
        label->setText(QApplication::translate("MainWindow", "Com port:", 0));
        label_2->setText(QApplication::translate("MainWindow", "Baud rate:", 0));
        label_3->setText(QApplication::translate("MainWindow", "Period, ms:", 0));
        label_4->setText(QApplication::translate("MainWindow", "Dump file:", 0));
        connectButton->setText(QApplication::translate("MainWindow", "Device identification", 0));
        streamButton->setText(QApplication::translate("MainWindow", "Start stream", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
