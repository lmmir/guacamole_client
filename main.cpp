#include "mainwindow.h"

#include <QApplication>
#include <QClipboard>
#include <QDebug>
#include <dlglogin.h>
#include <iostream>
#include <stdio.h>
int main(int argc, char *argv[]) {

  QApplication a(argc, argv);
  DlgLogin dlgLogin;
  if (dlgLogin.exec() == QDialog::Accepted) {
  }

  return a.exec();
}
