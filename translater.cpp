#include "translater.h"
#include "ui_translater.h"

Translater::Translater(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Translater)
{
    ui->setupUi(this);

}

Translater::~Translater()
{
    delete ui;
}
void Translater::init(Ui::MainWindow *mt){
    parent=mt;
}
void Translater::pendResult(QNetworkReply *reply){
    qDebug()<<"接收到翻译结果"<<endl;
      QJsonParseError jsonError;
      QByteArray all=reply->readAll();//获得api返回值
     /* 大概是这样的一个东西
     {"from":"en","to":"zh","trans_result":[{"src":"apple","dst":"\u82f9\u679c"}]}
     你需要解码 */
      QJsonDocument json = QJsonDocument::fromJson(all, &jsonError);
      QJsonObject object = json.object();//json转码；
      QString cResult;
      if(object.contains("error_code"))
      {
          int nResult=object.value("error_code").toInt();

          switch (nResult) {
          case 52001:
              cResult ="52001 请求超时 重试";
              break;
          case 52002:
              cResult ="52002 系统错误 重试";
              break;
          case 54000:
              cResult ="54000 必填参数为空";
              break;
          case 54001:
              cResult ="54001 签名错误";
              break;
          case 54003:
              cResult ="54003 速度过快访问频率受限";
              break;
          case 54004:
              cResult ="54004 账户余额不足";
              break;
          case 54005:
              cResult ="54005 请求频繁";
              break;
          case 58002:
              cResult ="58002 服务关闭";
              break;
          default:
              cResult =" ";
              break;
          }
      }
      else {
          QJsonArray value = object.value("trans_result").toArray();//一次解码
          /*
           {"from":"en","to":"zh",
             "trans_result":[{"src":"apple","dst":"\u82f9\u679c"}]}
             第一次解码
           */
          QJsonObject object1=value.at(0).toObject();//二次解码开【】括号；
          /*
             {"src":"apple","dst":"\u82f9\u679c"}
             第二次解码
           */
          //from=object.value("from").toString();
          cResult=object1.value("dst").toString();//得到翻译结果
      }
      qDebug()<<cResult<<endl;
      ui->tran_result->setText(cResult);
      reply->deleteLater();
}
void Translater::trans(QString text){
     QString MD5;
    char salt[60];
    sprintf(salt,"%d",rand());  //获取随机数

    QString sign=QString("%1%2%3%4")\
        .arg(Tran_APID).arg(text).arg(salt).arg(Tran_APID_KEY);//连接加密文件 宏MY_APID 是你的开发账号 宏MY_APID_KEY 是你的开发者密匙

    QByteArray str = QCryptographicHash::hash(sign.toUtf8(),QCryptographicHash::Md5);
    MD5.append(str.toHex());//生成md5加密文件
    QString myurl=QString("http://api.fanyi.baidu.com/api/trans/vip/translate?" \
           "q=%1&from=%2&to=%3&appid=%4""&salt=%5&sign=%6")\
           .arg(text).arg(Tran_FROM).arg(Tran_TO).arg(Tran_APID).arg(salt).arg(MD5);//连接上传文本 MY_APID 是你的开发账号
    qDebug()<<"发送翻译请求:"<<myurl<<endl;
    HttpMg = new QNetworkAccessManager(this);
    HttpMg->get(QNetworkRequest(myurl));//发送上传；
    //得到返回值触发槽函数int replyFinished（）

    connect(HttpMg,&QNetworkAccessManager::finished,this,&Translater::pendResult);

}
