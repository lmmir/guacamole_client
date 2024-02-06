#ifndef BASEMSG_H
#define BASEMSG_H

#include <QDebug>
#include <QMap>
#include <QObject>
#include <QStringList>
class BaseMsg {
protected:
  virtual ~BaseMsg() { //
                       // qDebug() << __FUNCTION__;
  }
  virtual void doMsg() = 0;

public:
  QString getParam(int index) { //
    return mArgList[index].split(".")[1];
  }

  QString getName() { //
    return mMsgName;
  }
  QString getMsg() { return mArgList.join(","); }

  void setArgList(const QStringList &argList);

  void setMsgName(const QString &msgName);

  static BaseMsg *parseMsg(const QString &strMsg);

protected:
  QStringList mArgList;
  QString mMsgName;
  static QMap<QString, BaseMsg *> sMapMsg;
};

template <class C> class TBaseMsg : public BaseMsg {

public:
  virtual void doMsg(C *msg) = 0;
  virtual void doMsg() { this->doMsg((C *)this); }

protected:
  void registerMsg(QString key, BaseMsg *msg) { //
    sMapMsg[key] = msg;
  }

signals:
};

class ImgMsg : public TBaseMsg<ImgMsg> {
public:
  struct Image {
    QString x;
    QString y;
    QByteArray data;
    int mask;
    int stream;
    int layer;
  };

public:
  ImgMsg() { registerMsg("img", this); }

protected:
};

class EndMsg : public TBaseMsg<EndMsg> {
public:
  EndMsg() { registerMsg("end", this); }

protected:
};

class BlobMsg : public TBaseMsg<BlobMsg> {
public:
  BlobMsg() { //
    registerMsg("blob", this);
  }

protected:
};
class CursorMsg : public TBaseMsg<CursorMsg> {
public:
  CursorMsg() { //
    registerMsg("cursor", this);
  }

protected:
};
class SizeMsg : public TBaseMsg<SizeMsg> {
public:
  SizeMsg() { //
    registerMsg("size", this);
  }

protected:
};
class SyncMsg : public TBaseMsg<SyncMsg> {
public:
  SyncMsg() { //
    registerMsg("sync", this);
  }
  QString createResponse() {

    QString str = this->getParam(1);
    QString strSync = "4.sync,13." + str + ";";
    return strSync;
  }

protected:
};

#endif // BASEMSG_H
