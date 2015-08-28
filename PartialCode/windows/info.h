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
    void filenameListValue(const QStringList &newFilenameList);

    void fileCOMPListValue(const QStringList &newFileCOMPList);

    void fileNbrRowsListValue(const QList<int> &newFileNbrRowsList);

    void fileNbrColumnsListValue(const QList<int> &newFileNbrColumnsList);

    void fileNbrSubjectsListValue(const QList<int> &newFileNbrSubjectsList);


private:
    Ui::Info *ui;

    QStringList filenameList;

    QStringList fileCOMPList;

    QList<int> fileNbrRowsList;

    QList<int> fileNbrColumnsList;

    QList<int> fileNbrSubjectsList;


    QString getFileInfo(int i, QString p);
};

#endif // INFO_H
