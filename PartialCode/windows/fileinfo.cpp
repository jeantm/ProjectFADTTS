#include "fileinfo.h"

/************ Public functions ************/
FileInfo::FileInfo()
{
    filePath = "";
    filename = "";
    prefix = "";
    for(int i = 0; i < 5; i++)
    {
        covar.insert(i,"");
    }
    nbrRows = 0;
    nbrColumns = 0;
    nbrSubjects = 0;
    nbrCovariates = 0;
}

void FileInfo::initFInfo()
{
    filePath = "Coucou";
    filename = "";
    prefix = "";
    for(int i = 0; i < 5; i++)
    {
        covar.insert(i,"");
    }
    nbrRows = 0;
    nbrColumns = 0;
    nbrSubjects = 0;
    nbrCovariates = 100;
}


QString FileInfo::getFilePath()
{
    return this->filePath;
}

QString FileInfo::getFileName()
{
    return this->filename;
}

QString FileInfo::getFilePrefix()
{
    return this->prefix;
}

QStringList FileInfo::getCovariates()
{
    return this->covar;
}

int FileInfo::getNbrRows()
{
    return this->nbrRows;
}

int FileInfo::getNbrColumns()
{
    return this->nbrColumns;
}

int FileInfo::getNbrSubjects()
{
    return this->nbrSubjects;
}

int FileInfo::getNbrCovariates()
{
    return this->nbrCovariates;
}



/************ Private functions ************/
void FileInfo::setFilePath(QString fPath)
{
    filePath = fPath;
}

void FileInfo::setFileName(QString fName)
{
    filename = fName;
}

void FileInfo::setFilePrefix(QString fP)
{
    prefix = fP;
}

void FileInfo::setCovariates(QStringList cov)
{
    for(int i = 0; i < nbrCovariates; i++)
    {
        covar.removeAt(i);
        covar.insert(i,cov.at(i));
    }
}

void FileInfo::setNbrRows(int nRows)
{
    nbrRows = nRows;
}

void FileInfo::setNbrColumns(int nColumns)
{
    nbrColumns = nColumns;
}

void FileInfo::setNbrSubjects(int nSubjects)
{
    nbrSubjects = nSubjects;
}

void FileInfo::setNbrCovariates(int nCovariates)
{
    nbrCovariates = nCovariates;
}
