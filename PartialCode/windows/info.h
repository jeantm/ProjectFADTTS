#ifndef INFO_H
#define INFO_H

#include <QDialog>
#include "setinput.h"
#include "mainwindow.h"

namespace Ui {
class Info;
}

class Info : public QDialog
{
    Q_OBJECT
    
public:
    explicit Info(QWidget *parent = 0);
    ~Info();

    void getInfo(QStringList files);
    
private:
    Ui::Info *IUi;
};

#endif // INFO_H
