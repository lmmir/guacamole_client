#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <fcntl.h>
#include <iostream>
#include <linux/input.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {

  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
