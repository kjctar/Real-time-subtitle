#ifndef REALTIMEVOICE_H
#define REALTIMEVOICE_H

#include <QWidget>
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
#include <QFile>
#include <QString>
#include "mainwindow.h"
using namespace std;
namespace Ui {
class Realtimevoice;
}

class Realtimevoice : public QWidget
{
    Q_OBJECT

public:
    explicit Realtimevoice(QWidget *parent = nullptr);
    ~Realtimevoice();

signals:
    void pendings(QString str);


public slots:
    void stopConnect();
    void init(Ui::MainWindow *mt);
    void sendData( QByteArray byte);
    void start_connect();
private:
    Ui::Realtimevoice *ui;
    QWebSocket *client;
    Ui::MainWindow  *parent;
};

#endif // REALTIMEVOICE_H
