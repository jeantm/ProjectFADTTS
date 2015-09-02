#ifndef INFO_H
#define INFO_H

#include <QDialog>
#include <QDebug>
#include <QFile>
#include <QFileDialog>

#include <QTextStream>
#include <QString>
#include <QStandardItemModel>
#include <QtCore>
#include <QtGui>


namespace Ui {
class Info;
}

class Info : public QDialog
{
    Q_OBJECT
    
public:
    explicit Info(QWidget *parent = 0);
    ~Info();

    void displayInfo();
    
private slots:
    void filenameListValue(const QMap<QString, QString> &newFilenameList);

    void fileCOMPListValue(const QStringList &newFileCOMPList);

    void fileNbrRowsListValue(const QMap<QString,int> &newFileNbrRowsList);

    void fileNbrColumnsListValue(const QMap<QString,int> &newFileNbrColumnsList);

    void fileNbrSubjectsListValue(const QMap<QString, int> &newFileNbrSubjectsList);


private:
    Ui::Info *ui;

    QMap<QString, QString> filenameList;

    QStringList fileCOMPList;

    QMap<QString,int> fileNbrRowsList;

    QMap<QString,int> fileNbrColumnsList;

    QMap<QString,int> fileNbrSubjectsList;


    QString getFileInfo(QString p);
};

#endif // INFO_H
