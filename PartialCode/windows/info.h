#ifndef INFO_H
#define INFO_H

#include <QDialog>
#include <QDebug>


namespace Ui {
class Info;
}

class Info : public QDialog
{
    Q_OBJECT
    
public:
    explicit Info(QWidget *parent = 0);
    ~Info();

    void displayInfo(QStringList file);
    
private:
    Ui::Info *IUi;
};

#endif // INFO_H
