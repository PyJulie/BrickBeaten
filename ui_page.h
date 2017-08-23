/********************************************************************************
** Form generated from reading UI file 'page.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGE_H
#define UI_PAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Page
{
public:
    QLabel *label;
    QPushButton *startButton;
    QPushButton *exitButton;
    QPushButton *menuButton;
    QPushButton *nextButton;
    QPushButton *rankButton;
    QLabel *label_2;

    void setupUi(QWidget *Page)
    {
        if (Page->objectName().isEmpty())
            Page->setObjectName(QStringLiteral("Page"));
        Page->resize(321, 414);
        label = new QLabel(Page);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(180, 50, 54, 12));
        startButton = new QPushButton(Page);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setGeometry(QRect(110, 270, 110, 50));
        startButton->setStyleSheet(QStringLiteral("background:transparent;"));
        startButton->setFlat(true);
        exitButton = new QPushButton(Page);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        exitButton->setGeometry(QRect(110, 340, 110, 50));
        exitButton->setStyleSheet(QStringLiteral("background:transparent;"));
        exitButton->setFlat(true);
        menuButton = new QPushButton(Page);
        menuButton->setObjectName(QStringLiteral("menuButton"));
        menuButton->setGeometry(QRect(90, 340, 110, 50));
        menuButton->setStyleSheet(QStringLiteral("background-image: url(:/sucai/menu.png);"));
        menuButton->setFlat(true);
        nextButton = new QPushButton(Page);
        nextButton->setObjectName(QStringLiteral("nextButton"));
        nextButton->setGeometry(QRect(90, 270, 110, 50));
        nextButton->setStyleSheet(QStringLiteral("background-image: url(:/sucai/continue.png);"));
        nextButton->setFlat(true);
        rankButton = new QPushButton(Page);
        rankButton->setObjectName(QStringLiteral("rankButton"));
        rankButton->setEnabled(true);
        rankButton->setGeometry(QRect(100, 210, 93, 41));
        rankButton->setStyleSheet(QStringLiteral("background:transparent;"));
        rankButton->setFlat(true);
        label_2 = new QLabel(Page);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 130, 241, 211));
        label_2->setTextFormat(Qt::AutoText);
        label_2->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        retranslateUi(Page);

        QMetaObject::connectSlotsByName(Page);
    } // setupUi

    void retranslateUi(QWidget *Page)
    {
        Page->setWindowTitle(QApplication::translate("Page", "Form", 0));
        label->setText(QString());
        startButton->setText(QString());
        exitButton->setText(QString());
        menuButton->setText(QString());
        nextButton->setText(QString());
        rankButton->setText(QString());
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Page: public Ui_Page {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGE_H
