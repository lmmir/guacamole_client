#include "basemsg.h"
#include <QDebug>
QMap<QString, BaseMsg *> BaseMsg::sMapMsg;

void BaseMsg::setArgList(const QStringList &argList) { mArgList = argList; }

void BaseMsg::setMsgName(const QString &msgName) { mMsgName = msgName; }
BaseMsg *BaseMsg::parseMsg(const QString &strMsg) {
  QStringList strListArg = strMsg.split(",");

  int index = strListArg[0].indexOf(".");
  int length = strListArg[0].mid(0, index).toInt();
  if (length == 0) {
    return 0;
  }
  qDebug() << strMsg;

  QString opCode = strListArg[0].mid(index + 1);
  if (sMapMsg.find(opCode) == sMapMsg.end()) {
    return 0;
  }

  sMapMsg.value(opCode)->setMsgName(opCode);
  sMapMsg.value(opCode)->setArgList(strListArg);
  sMapMsg.value(opCode)->doMsg();
  return sMapMsg.value(opCode);
}
