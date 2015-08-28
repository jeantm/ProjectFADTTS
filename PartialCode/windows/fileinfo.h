#ifndef FILEINFO_H
#define FILEINFO_H

#include <QString>
#include <QStringList>
#include <QFile>
#include <QMap>


class FileInfo
{
public:
    FileInfo();


    void initFInfo();


    QString getFilePath();

    QString getFileName();

    QString getFilePrefix();

    QStringList getCovariates();

    int getNbrRows();

    int getNbrColumns();

    int getNbrSubjects();

    int getNbrCovariates();



private:
    QString filePath;
    QString filename;
    QString prefix;
    QStringList covar;
    int nbrRows;
    int nbrColumns;
    int nbrSubjects;
    int nbrCovariates;

    void setFilePath(QString fPath);

    void setFileName(QString fName);

    void setFilePrefix(QString fP);

    void setCovariates(QStringList cov);

    void setNbrRows(int nRows);

    void setNbrColumns(int nColumns);

    void setNbrSubjects(int nSubjects);

    void setNbrCovariates(int nCovariates);
};

#endif // FILEINFO_H
