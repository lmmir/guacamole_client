#include "dlglogin.h"
#include "ui_dlglogin.h"
#include <QElapsedTimer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <mainwindow.h>
DlgLogin::DlgLogin(QWidget *parent) : QDialog(parent), ui(new Ui::DlgLogin) {
  ui->setupUi(this);
}

DlgLogin::~DlgLogin() { delete ui; }

void DlgLogin::on_buttonBox_accepted() {
  QNetworkRequest request;

  request.setHeader(QNetworkRequest::ContentTypeHeader,
                    "application/x-www-form-urlencoded");
  request.setUrl(QUrl(QString("https://%1/guacamole/api/tokens")
                          .arg(QApplication::arguments()[1])));

  QString account = ui->led_account->text();

  QString pwd = ui->led_password->text();

  if (account.isEmpty()) {
    account = QApplication::arguments()[2];
  }
  if (pwd.isEmpty()) {
    pwd = QApplication::arguments()[3];
  }
  QByteArray ba = QString("username=%1&password=%2")
                      .arg(account)
                      .arg(QString::fromUtf8(QUrl::toPercentEncoding(pwd)))
                      .toUtf8();

  qDebug() << ba;
  QNetworkReply *reply = mNetworkAccessManager.post(request, ba);

  QElapsedTimer et;
  et.start();
  while (true) {
    QApplication::processEvents(QEventLoop::AllEvents, 100);
    if (reply->isFinished()) {
      break;
    }
    if (et.elapsed() > 10000) {
      reply->abort();
      reply->deleteLater();
      return;
    }
  }
  ba = reply->readAll();
  QJsonObject jsonObject = QJsonDocument::fromJson(ba).object();
  if (!jsonObject["authToken"].toString().isEmpty()) {
    MainWindow *w = new MainWindow(jsonObject["authToken"].toString());
    w->show();
    reply->deleteLater();
    this->close();
  }
}

void DlgLogin::on_buttonBox_rejected() {}
