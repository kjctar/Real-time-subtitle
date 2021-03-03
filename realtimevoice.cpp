#include "realtimevoice.h"
#include "ui_realtimevoice.h"
#include "audiolistener.h"
#include "ui_mainwindow.h"
#include <iostream>
using namespace std;
Realtimevoice::Realtimevoice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Realtimevoice)
{
    ui->setupUi(this);

}

Realtimevoice::~Realtimevoice()
{
    delete ui;
}
void Realtimevoice::init(Ui::MainWindow *mt){
    parent=mt;


}
void Realtimevoice::start_connect(){
    QUuid id = QUuid::createUuid();
    QString strId = id.toString();

    strId.remove("{").remove("}"); // 一般习惯去掉
    string url="ws://vop.baidu.com/realtime_asr";
    url=url + "?sn=" +strId.toStdString();
    cout<<"url="<<url<<endl;

    client=new QWebSocket;
    client->setParent(this);
    client->open(QUrl(url.c_str()));//连接

    //连接结果
    connect(client,&QWebSocket::connected,[this](){
        cout<<"Port="<<client->localPort()<<endl;
        cout<<"Address="<<client->localAddress().toString().toStdString()<<endl;
        QJsonObject json;
        json.insert("type","START");
        QJsonObject json2;
        json2.insert("appid",23719646);
        json2.insert("appkey","y1t7dkkZ4b80D9zV57ErUK1v");
        json2.insert("dev_pid",1737);
        json2.insert("cuid","123456");
        json2.insert("sample",16000);
        json2.insert("format","pcm");
        json.insert("data",json2);
        QJsonDocument document;
        document.setObject(json);
        QByteArray simpbyte_array = document.toJson(QJsonDocument::Compact);
        QString json_str(simpbyte_array);
        qDebug() <<  json_str;
        //"{type: START,data:{appid: 23719646,appkey: y1t7dkkZ4b80D9zV57ErUK1v,dev_pid: 1737,cuid: 123456,sample: 16000,format: pcm}}"
        client->sendTextMessage(json_str);
        qDebug()<<"connected";
//        qDebug() <<"connetc_ok"<<connect(this ,SIGNAL(connect_ok()),new Audiolistener,SLOT(start_audio()));

//        emit connect_ok();

          parent->audiomodel->start_audio();

    });

    //断开连接
    connect(client,&QWebSocket::disconnected,[this](){
        qDebug()<<"disconnected";
    });


    //接收数据
    connect(client,&QWebSocket::textMessageReceived,[this](const QString &msg){
        //deal_orign_result(msg);
        QJsonParseError err_rpt;
        QJsonDocument  root_Doc = QJsonDocument::fromJson(msg.toStdString().c_str(), &err_rpt);//字符串格式化为JSON

        if(err_rpt.error != QJsonParseError::NoError)
        {
            qDebug() << "JSON格式错误";

        }else{

           QJsonObject root_Obj = root_Doc.object();
           QString retype=root_Obj.value("type").toString();
           //qDebug() <<retype<<endl;
           if(retype=="FIN_TEXT"){
               QJsonObject result = root_Doc.object();
               QString str=result.value("result").toString();
               qDebug() <<str<<endl;

               parent->tranmodel->trans(str);
//                qDebug() <<"tran:"<<connect(this,&Realtimevoice::pendings,parent->tranmodel, &Translater::trans);//弃用，
//                emit pendings(str);
               ui->originalword->setText(str);

           }


        }
        //cout<<msg.toStdString()<<endl;

    });

}
void Realtimevoice::stopConnect(){
    client->close();
}
void Realtimevoice::sendData(QByteArray byte){
      //qDebug() <<byte<<endl;
        // qDebug()<<"hh"<<endl;
         client->sendBinaryMessage(byte);

       //

}

