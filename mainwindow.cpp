#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "audiolistener.h"
#include "realtimevoice.h"
#include "translater.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


//        qDebug() <<"getrealtimevoice:"<<connect(this,SIGNAL(broadcast(ui)),new Realtimevoice , SLOT(init(MainWindow*)),Qt::UniqueConnection);
//        qDebug() <<"getrealtimevoice:"<<connect(this,SIGNAL(broadcast(ui)),new Audiolistener , SLOT(init(MainWindow*)),Qt::UniqueConnection);
        ui->setupUi(this);
        ui->audiomodel->init(ui);
        ui->rtvoicemodel->init(ui);
        ui->tranmodel->init(ui);

       // init();
       //read();
}



MainWindow::~MainWindow()
{
    delete ui;
}



