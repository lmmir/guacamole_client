#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "basemsg.h"
#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>
MainWindow::MainWindow(QString token, QWidget *parent)
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
      QString("wss://%2/guacamole/"
              "websocket-tunnel?token="
              "%1&GUAC_"
              "DATA_SOURCE=mysql&GUAC_ID=1700&GUAC_TYPE=c&GUAC_WIDTH=1211&GUAC_"
              "HEIGHT="
              "891&GUAC_DPI=96&GUAC_AUDIO=audio%2FL8&GUAC_AUDIO=audio%2FL16&"
              "GUAC_IMAGE="
              "image%2Fjpeg&GUAC_IMAGE=image%2Fpng&GUAC_IMAGE=image%2Fwebp")
          .arg(token)
          .arg(QApplication::arguments()[1])); // replace
                                               // here
  mWebSocket->open(url);

  this->showFullScreen();

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

void MainWindow::renderImage() {

  //  QImage image = QImage::fromData(mMapImg[stream].data);
  //  if (image.isNull()) {
  //    return;
  //  }

  QPainter painter(&mImage);
  // painter.setCompositionMode(QPainter::CompositionMode_Source);

  // painter.setCompositionMode(QPainter::CompositionMode_SourceOver);

  for (auto &item : mMapImg) {
    if (item.layer == -1)
      continue;
    QImage image = QImage::fromData(item.data);
    if (image.isNull()) {
      continue;
    }
    painter.drawImage(item.x.toInt(), item.y.toInt(), image);
  }

  painter.end();

  this->update();
  for (auto it = mMapImg.begin(); it != mMapImg.end(); it++) {
    if (it.value().layer > 0) {
      mMapImg.erase(it);
    }
  }
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
  // qDebug() << __FUNCTION__;

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
  // qDebug() << __FUNCTION__;
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

  // qDebug() << event->modifiers();
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
  ImgMsg::Image img;
  int stream = msg->getParam(1).toInt();
  img.x = msg->getParam(5);
  img.y = msg->getParam(6);

  img.layer = msg->getParam(3).toInt();
  img.mask = msg->getParam(2).toInt();
  img.stream = msg->getParam(1).toInt();

  mMapImg[stream] = img;

  // qDebug() << "img:" << img.mask << img.layer << img.x << img.y;
}

void MainWindow::doMsg(BlobMsg *msg) {
  int stream = msg->getParam(1).toInt();
  QString str = msg->getParam(2);
  QByteArray ba = QByteArray::fromBase64(str.toUtf8());
  mMapImg[stream].data.append(ba);
}

void MainWindow::doMsg(EndMsg *msg) {
  int stream = msg->getParam(1).toInt();
  if (mMapImg.find(stream) == mMapImg.end()) {
    return;
  }

  renderImage();
}

void MainWindow::doMsg(SizeMsg *msg) {
  int layer = msg->getParam(1).toInt();
  int width = msg->getParam(2).toInt();
  int height = msg->getParam(3).toInt();
  // qDebug() << "size:" << layer << width << height;
}

void MainWindow::doMsg(CursorMsg *msg) {

  for (auto &item : mMapImg) {
    if (item.layer == -1) {
      QImage image = QImage::fromData(item.data);
      if (image.isNull()) {
        break;
      }
      int x = msg->getParam(1).toInt();
      int y = msg->getParam(2).toInt();
      int srcLayer = msg->getParam(3).toInt();
      int srcX = msg->getParam(4).toInt();
      int srcY = msg->getParam(5).toInt();
      int srcWidth = msg->getParam(6).toInt();
      int srcHeight = msg->getParam(7).toInt();

      QCursor cursor(QPixmap::fromImage(image));
      setCursor(cursor);
      // qDebug() << "cursor:" << msg->getMsg();
      break;
    }
  }

  // this->update();
}
