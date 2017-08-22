#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    page = new Page();
    setCentralWidget(page);
    setFixedSize(300, 450);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete page;
}
