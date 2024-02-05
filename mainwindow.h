#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "basemsg.h"
#include <QMainWindow>
#include <QWebSocket>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow,
                   public SyncMsg,
                   public ImgMsg,
                   public BlobMsg,
                   public EndMsg {
  Q_OBJECT

public:
  MainWindow(QString token, QWidget *parent = nullptr);
  ~MainWindow();

protected:
  void renderImage(QImage &image);

protected slots:
  void slotTextMessageReceived(const QString &text);
  void slotDisconnected();
  void slotError(QAbstractSocket::SocketError error);

private:
  QWebSocket *mWebSocket;

  ImgMsg::Image mImage5;
  Ui::MainWindow *ui;

  QImage mImage;

protected:
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void mouseDoubleClickEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);

  void keyPressEvent(QKeyEvent *event);
  void keyReleaseEvent(QKeyEvent *event);
  void paintEvent(QPaintEvent *event);

public:
  void doMsg(SyncMsg *msg);
  void doMsg(ImgMsg *msg);
  void doMsg(BlobMsg *msg);
  void doMsg(EndMsg *msg);
};
#endif // MAINWINDOW_H
