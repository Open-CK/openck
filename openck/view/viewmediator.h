#ifndef VIEWMEDIATOR_H
#define VIEWMEDIATOR_H

#include "window/datadialog.h"
#include "window/mainwindow.h"

#include <QObject>

#include <memory>

class ViewMediator : public QObject
{
    Q_OBJECT

public:
    ViewMediator();
    ~ViewMediator();

    void setUpDataDialog(const QString& dataPath);

public slots:
    void showDataDialog();

private:
    std::unique_ptr<MainWindow> w;
    std::unique_ptr<DataDialog> dataDlg;
};

#endif //VIEWMEDIATOR_H