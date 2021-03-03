#include "audiolistener.h"
#include "ui_audiolistener.h"
#include "ui_mainwindow.h"
#include "realtimevoice.h"
Audiolistener::Audiolistener(QWidget *parent) :
    QWidget(parent),
  ui(new Ui::Audiolistener)
{
     qDebug() <<"录音初始化"<<endl;
    ui->setupUi(this);

    ui->start->setVisible(false);


    QList<QAudioDeviceInfo> audioDeviceListI = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    foreach (QAudioDeviceInfo devInfo, audioDeviceListI)
    {
        QString strName = devInfo.deviceName();
        qDebug()<<strName<<endl;
        if (devInfo.isNull()) continue;
        if (strName[0] == 65533) continue;
        aDeviceList.push_back(devInfo);
        ui->audio_info->addItem(strName);
    }

}

Audiolistener::~Audiolistener()
{
    delete ui;
}




void Audiolistener::init(Ui::MainWindow *mt)
{
    parent=mt;
}

void Audiolistener::start_audio(){
    QAudioFormat format;

    format.setSampleRate(16000);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);

    QAudioDeviceInfo info = nowDev;

    if (!info.isFormatSupported(format))
    {
       qWarning()<<"default format not supported try to use nearest";
       format = info.nearestFormat(format);
    }
    audio = new QAudioInput(info, format, this);

   // audio->start(&outputFile);
    streamIn=audio->start();


       connect(audio,SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleStateChanged_input(QAudio::State)),Qt::QueuedConnection);
       streamIn=audio->start(); //开始音频采集
       //关联音频读数据信号
       connect(streamIn,SIGNAL(readyRead()),this,SLOT(audio_ReadyRead()),Qt::QueuedConnection);


     qDebug() <<"record begin!";
}


//录音状态
void Audiolistener::handleStateChanged_input(QAudio::State newState)
{
 switch (newState) {
     case QAudio::StoppedState:
         if (audio->error() != QAudio::NoError) {
             // Error handling
             qDebug()<<"录音出现错误.\n";
         } else {
             // Finished recording
             qDebug()<<"完成录音\n";
         }
         break;
     case QAudio::ActiveState:
         // Started recording - read from IO device
            qDebug()<<"开始从IO设备读取PCM声音数据.\n";
         break;
     default:
         // ... other cases as appropriate
         break;
 }
}

//有音频信号可以读
void Audiolistener::audio_ReadyRead()
{
    QByteArray byte=streamIn->readAll();
    parent->rtvoicemodel->sendData(byte);

}

void Audiolistener::stopRecording()
{
    audio->stop();
   // delete audio;
    qDebug() <<"record end!";
}

void Audiolistener::on_start_clicked()
{
    qDebug() <<"click start";

    QString staus=ui->start->text();
    if(staus=="开始"){
        ui->start->setText("停止");
        ui->start->setStyleSheet( "QPushButton{"
                                  "background-color:rgba(255,100,100,1);"

                                  "color:rgba(0,0,0,1);"

                                  "}"

                                  //鼠标悬停样式
                                  "QPushButton:hover{"
                                  "background-color:rgba(255,100,100,100);"
                                  "border-color:rgba(255,255,255,1);"
                                  "color:rgba(0,0,0,200);"
                                  "}");
        parent->rtvoicemodel->start_connect();

    }else{
         ui->start->setText("开始");
         ui->start->setStyleSheet( "QPushButton{"
                                   "background-color:rgba(100,255,100,1);"

                                   "color:rgba(0,0,0,1);"

                                   "}"

                                   //鼠标悬停样式
                                   "QPushButton:hover{"
                                   "background-color:rgba(100,255,100,100);"

                                   "color:rgba(0,0,0,1);"
                                   "}");
         this->stopRecording();
    }

}

void Audiolistener::on_ok_clicked()
{
    qDebug()<<"确认"<<endl;
    for(int i=0;i<aDeviceList.size();i++){
        qDebug()<<aDeviceList[i].deviceName()<<" "<<ui->audio_info->currentText()<<endl;
        if(aDeviceList[i].deviceName()==ui->audio_info->currentText()){
            qDebug()<<"选择了"<<aDeviceList[i].deviceName()<<endl;
            nowDev=aDeviceList[i];

            break;
        }
    }
    ui->ok->setVisible(false);
    ui->audio_info->setVisible(false);
    ui->start->setStyleSheet( "QPushButton{"
                              "background-color:rgba(100,255,100,1);"

                              "color:rgba(0,0,0,1);"

                              "}"

                              //鼠标悬停样式
                              "QPushButton:hover{"
                              "background-color:rgba(100,255,100,100);"
                              "border-color:rgba(255,255,255,200);"
                              "color:rgba(0,0,0,200);"
                              "}");
    ui->start->setVisible(true);
}
