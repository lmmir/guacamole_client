#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "basemsg.h"
#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  mWebSocket = new QWebSocket();
  connect(mWebSocket, &QWebSocket::textMessageReceived, this,
          &MainWindow::slotTextMessageReceived);
  connect(mWebSocket, &QWebSocket::disconnected, this,
          &MainWindow::slotDisconnected);
  connect(mWebSocket, SIGNAL(error(QAbstractSocket::SocketError)), this,
          SLOT(slotError(QAbstractSocket::SocketError)));

  QUrl url(
      "wss://xxxxxxxxx/guacamole/"
      "websocket-tunnel?token="
      "FC1069C8AD0C05CCA5FE2768C658CA2EDA6C13F3209746A4AF3E95CA2046425B&GUAC_"
      "DATA_SOURCE=mysql&GUAC_ID=1699&GUAC_TYPE=c&GUAC_WIDTH=1211&GUAC_HEIGHT="
      "891&GUAC_DPI=96&GUAC_AUDIO=audio%2FL8&GUAC_AUDIO=audio%2FL16&GUAC_IMAGE="
      "image%2Fjpeg&GUAC_IMAGE=image%2Fpng&GUAC_IMAGE=image%2Fwebp"); // replace
                                                                      // here
  mWebSocket->open(url);

  this->showFullScreen();

  ui->label->setVisible(false);
  this->setMouseTracking(true);
  this->grabKeyboard();
  this->centralWidget()->setMouseTracking(true);
  mImage = QImage(1920, 1080, QImage::Format_ARGB32_Premultiplied);
}

MainWindow::~MainWindow() {
  mWebSocket->close();
  mWebSocket->deleteLater();
  delete ui;
}

void MainWindow::renderImage(QImage &image) {
  QPainter painter(&mImage);
  painter.setCompositionMode(QPainter::CompositionMode_Source);
  // painter.fillRect(imageWithOverlay.rect(), Qt::transparent);

  painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
  painter.drawImage(mImage5.x.toInt(), mImage5.y.toInt(), image);
  painter.end();
  //  ui->label->setPixmap(QPixmap::fromImage(mImage));
  this->update();
}

void MainWindow::slotTextMessageReceived(const QString &text) {

  QStringList strList = text.split(";");
  if (strList.count() == 0) {
    return;
  }
  for (auto &s : strList) {

    BaseMsg *msg = BaseMsg::parseMsg(s);
    if (msg == 0) {
      continue;
    }
  }
}

void MainWindow::slotDisconnected() {
  // qDebug() << __FUNCTION__;
  qDebug() << __FUNCTION__;
}

void MainWindow::slotError(QAbstractSocket::SocketError error) {
  qDebug() << __FUNCTION__;
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
  // qDebug() << __FUNCTION__;
  qDebug() << __FUNCTION__;

  if (mWebSocket->state() != QAbstractSocket::SocketState::ConnectedState) {
    return;
  }
  QStringList cmd;
  cmd.append("5.mouse");
  QString x = QString::number(event->x());
  QString y = QString::number(event->y());
  QString mask = "0";
  if (event->button() == Qt::LeftButton) {
    mask = "1";
  }
  // 如果是鼠标右键按下
  else if (event->button() == Qt::RightButton) {
    mask = "4";
  }

  cmd.append(QString::number(x.length()) + "." + x);
  cmd.append(QString::number(y.length()) + "." + y);
  cmd.append(QString::number(mask.length()) + "." + mask);
  QString strCmd = cmd.join(",") + ";";
  mWebSocket->sendTextMessage(strCmd);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {

  if (mWebSocket->state() != QAbstractSocket::SocketState::ConnectedState) {
    return;
  }
  QStringList cmd;
  cmd.append("5.mouse");
  QString x = QString::number(event->x());
  QString y = QString::number(event->y());
  QString mask = "0";
  cmd.append(QString::number(x.length()) + "." + x);
  cmd.append(QString::number(y.length()) + "." + y);
  cmd.append(QString::number(mask.length()) + "." + mask);
  QString strCmd = cmd.join(",") + ";";
  mWebSocket->sendTextMessage(strCmd);
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event) {

  // qDebug() << __FUNCTION__;
  qDebug() << __FUNCTION__;
  QString strCmd;
  QStringList cmd;

  {
    cmd.append("5.mouse");
    QString x = QString::number(event->x());
    QString y = QString::number(event->y());
    QString mask = "0";
    if (event->button() == Qt::LeftButton) {
      mask = "1";
    }
    // 如果是鼠标右键按下
    else if (event->button() == Qt::RightButton) {
      mask = "4";
    }

    cmd.append(QString::number(x.length()) + "." + x);
    cmd.append(QString::number(y.length()) + "." + y);
    cmd.append(QString::number(mask.length()) + "." + mask);
    strCmd.append(cmd.join(",") + ";");
  }
  {
    cmd.append("5.mouse");
    QString x = QString::number(event->x());
    QString y = QString::number(event->y());
    QString mask = "0";
    cmd.append(QString::number(x.length()) + "." + x);
    cmd.append(QString::number(y.length()) + "." + y);
    cmd.append(QString::number(mask.length()) + "." + mask);
    strCmd.append(cmd.join(",") + ";");
  }
  {
    cmd.append("5.mouse");
    QString x = QString::number(event->x());
    QString y = QString::number(event->y());
    QString mask = "0";
    if (event->button() == Qt::LeftButton) {
      mask = "1";
    }
    // 如果是鼠标右键按下
    else if (event->button() == Qt::RightButton) {
      mask = "4";
    }

    cmd.append(QString::number(x.length()) + "." + x);
    cmd.append(QString::number(y.length()) + "." + y);
    cmd.append(QString::number(mask.length()) + "." + mask);
    strCmd.append(cmd.join(",") + ";");
  }
  {
    cmd.append("5.mouse");
    QString x = QString::number(event->x());
    QString y = QString::number(event->y());
    QString mask = "0";
    cmd.append(QString::number(x.length()) + "." + x);
    cmd.append(QString::number(y.length()) + "." + y);
    cmd.append(QString::number(mask.length()) + "." + mask);
    strCmd.append(cmd.join(",") + ";");
  }
  mWebSocket->sendTextMessage(strCmd);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
  if (mWebSocket->state() != QAbstractSocket::SocketState::ConnectedState) {
    return;
  }
  QStringList cmd;
  cmd.append("5.mouse");
  QString x = QString::number(event->x());
  QString y = QString::number(event->y());
  QString mask = "0";

  if (event->buttons() & Qt::LeftButton) {
    mask = "1";
  }
  // 如果是鼠标右键按下
  else if (event->buttons() == Qt::RightButton) {
    mask = "4";
  }
  cmd.append(QString::number(x.length()) + "." + x);
  cmd.append(QString::number(y.length()) + "." + y);
  cmd.append(QString::number(mask.length()) + "." + mask);
  QString strCmd = cmd.join(",") + ";";
  mWebSocket->sendTextMessage(strCmd);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {

  if (mWebSocket->state() != QAbstractSocket::SocketState::ConnectedState) {
    return;
  }

  qDebug() << event->modifiers();
  QString strKey = QString::number(event->key());
  QStringList cmd;
  cmd.append("3.key");
  cmd.append(QString::number(strKey.length()) + "." + strKey);

  QString mask = "1";
  cmd.append(QString::number(mask.length()) + "." + mask);
  QString strCmd = cmd.join(",") + ";";
  mWebSocket->sendTextMessage(strCmd);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
  if (mWebSocket->state() != QAbstractSocket::SocketState::ConnectedState) {
    return;
  }
  QStringList cmd;
  cmd.append("3.key");

  QString mask = "0";

  cmd.append(QString::number(mask.length()) + "." + mask);
  QString strCmd = cmd.join(",") + ";";
  mWebSocket->sendTextMessage(strCmd);
}

void MainWindow::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  painter.drawImage(0, 0, mImage);
  painter.end();
}

void MainWindow::doMsg(SyncMsg *msg) {

  if (mWebSocket->state() == QAbstractSocket::SocketState::ConnectedState) {
    mWebSocket->sendTextMessage(msg->createResponse());
  }
}

void MainWindow::doMsg(ImgMsg *msg) {
  mImage5.data.clear();
  mImage5.x = msg->getParam(5).split(".")[1];
  mImage5.y = msg->getParam(6).split(".")[1];
}

void MainWindow::doMsg(BlobMsg *msg) {
  int index = msg->getParam(2).indexOf(".");
  QString str = msg->getParam(2).mid(index + 1);
  QByteArray ba = QByteArray::fromBase64(str.toUtf8());
  mImage5.data.append(ba);
}

void MainWindow::doMsg(EndMsg *msg) {
  QImage image = QImage::fromData(mImage5.data);
  if (image.isNull()) {
    return;
  }
  renderImage(image);
}
