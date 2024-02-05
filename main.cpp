#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <iostream>
#include <stdio.h>

#include <dlglogin.h>
int main(int argc, char *argv[]) {

  QApplication a(argc, argv);
  DlgLogin dlgLogin;
  if (dlgLogin.exec() == QDialog::Accepted) {
  }

  return a.exec();
}
