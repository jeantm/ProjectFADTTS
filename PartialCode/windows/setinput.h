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

    QString displayFileInfo(QString f);

    QString getFilenameLineEdit();

private slots:
    void on_searchFile_pushButton_clicked();

    void on_saveFile_pushButton_clicked();

    void on_deleteRows_pushButton_clicked();

    void on_deleteColumns_pushButton_clicked();

    void prefixValue(const QString &newPrefix);

    void filePathValue(const QString &newFilePath);


private:
    Ui::SetInput *ui;

    QString checkPrefix;

    QString checkFilePath;

};

class InfoFile {
private:
    int nbRows, nbColumns;
    QString filename, prefix;

public:
    InfoFile (QString f, Ui::SetInput *ui);

    int getNbRows();
    int getNbColumns();
    QString getFilename();
    QString getPrefix();
} ;



#endif // SETINPUT_H
