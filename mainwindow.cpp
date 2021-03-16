#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    MyCustomWidget *customWidget = new MyCustomWidget();
}

MainWindow::~MainWindow() {
    delete ui;
}
