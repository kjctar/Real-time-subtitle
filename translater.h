#ifndef TRANSLATER_H
#define TRANSLATER_H
#include "mainwindow.h"
#include <QString>
#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
namespace Ui {
class Translater;
}

class Translater : public QWidget
{
    Q_OBJECT

public:

    explicit Translater(QWidget *parent = nullptr);
    ~Translater();
     void init(Ui::MainWindow *mt);
public slots:
     void trans(QString str);
     void pendResult(QNetworkReply *reply);
private:
    Ui::Translater *ui;
    Ui::MainWindow  *parent;
    QNetworkAccessManager * HttpMg;
};

#endif // TRANSLATER_H
