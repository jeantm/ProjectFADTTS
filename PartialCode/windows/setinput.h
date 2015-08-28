#ifndef SETINPUT_H
#define SETINPUT_H

#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QString>
#include <QStandardItemModel>
#include <QtCore>
#include <QtGui>


namespace Ui {
class SetInput;
}

class SetInput : public QDialog
{
    Q_OBJECT
    


public:
    explicit SetInput(QWidget *parent = 0);
    ~SetInput();

    void loadData();



private slots:
    void on_saveFile_pushButton_clicked();

    void on_deleteRows_pushButton_clicked();

    void on_deleteColumns_pushButton_clicked();


    void prefixValue(const QString &newPrefix);

    void filePathInputValue(const QString &newFilePathInput);

    void defaultInputPathMainWindowValue(const QString &newDefaultInputPathMainWindow);



private:
    Ui::SetInput *ui;

    QString checkPrefix;

    QString checkFilePathInput;

    QString defaultPathSetInput;

    QStringList covariates;


    void displayData(QFile &f);

    void displayFileInfo(QString f);
};

#endif // SETINPUT_H
