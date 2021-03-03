#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QtGui>
#include <QAudioInput>
#include <QAudioOutput>
#include <iostream>
#include <QWebSocket>
#include <string>
#include <map>
#include <QString>
#include <QUuid>
#include <QJsonObject>
#include <QMap>
#include <QJsonDocument>
#include <QByteArray>
#include "const.h"
namespace Ui {
class MainWindow;

}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();
    void read();
signals:
    void broadcast(Ui::MainWindow *);
private slots:

private:
    Ui::MainWindow *ui;


};

#endif // MAINWINDOW_H
