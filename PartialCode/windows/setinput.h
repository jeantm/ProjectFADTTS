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
#include "mainwindow.h"

namespace Ui {
class SetInput;
}

class SetInput : public QDialog
{
    Q_OBJECT
    
public:
    explicit SetInput(QWidget *parent = 0);
    ~SetInput();

    QString getFileInfo(QString f);

    QString getFilenameLineEdit();

private slots:
    void on_searchFile_pushButton_clicked();

    void on_saveFile_pushButton_clicked();

    void on_deleteRows_pushButton_clicked();

    void on_deleteColumns_pushButton_clicked();

private:
    Ui::SetInput *ui;

};

#endif // SETINPUT_H
