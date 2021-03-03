#ifndef AUDIOLISTENER_H
#define AUDIOLISTENER_H

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

#include "mainwindow.h"
namespace Ui {
class Audiolistener;
}

class Audiolistener : public QWidget
{
    Q_OBJECT

public:
    explicit Audiolistener(QWidget *parent = nullptr);
    ~Audiolistener();
    void stopRecording();
public slots:
    void init(Ui::MainWindow *mt);
    void start_audio();

    void handleStateChanged_input(QAudio::State newState);
    void audio_ReadyRead();
    void on_start_clicked();

signals:
    void start_click();
private slots:
    void on_ok_clicked();

private:
    Ui::Audiolistener *ui;
    QFile outputFile;   // class member.
    QAudioInput* audio; // class member.
    QAudioOutput *outAudio;
    QIODevice* streamIn;
    Ui::MainWindow *parent;
    QVector<QAudioDeviceInfo> aDeviceList;
    QAudioDeviceInfo nowDev;

};

#endif // AUDIOLISTENER_H
