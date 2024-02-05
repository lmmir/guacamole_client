#ifndef DLGLOGIN_H
#define DLGLOGIN_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
namespace Ui {
class DlgLogin;
}

class DlgLogin : public QDialog {
  Q_OBJECT

public:
  explicit DlgLogin(QWidget *parent = nullptr);
  ~DlgLogin();

protected slots:
  void on_buttonBox_accepted();
  void on_buttonBox_rejected();

private:
  Ui::DlgLogin *ui;
  QNetworkAccessManager mNetworkAccessManager;
};

#endif // DLGLOGIN_H
