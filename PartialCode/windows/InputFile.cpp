#include "InputFile.h"

InputFile::InputFile(QObject *parent) :
    QObject(parent)
{
}

InputFile::InputFile(QStringList filePrefixList)
{
    foreach( QString pref, filePrefixList )
    {
        m_filenameMap[ pref ];
        m_fileNbrRowsMap[ pref ];
        m_fileNbrColumnsMap[ pref ];
        m_fileNbrSubjectsMap[ pref ];
        ( m_filesSubjectsMap[ pref ] );
    }

    m_subjectColumnId = 0;
}

QMap<QString, QStringList> InputFile::GetFilesSubjectsMap() const
{
    return m_filesSubjectsMap;
}

QMap<QString, QString> InputFile::GetFilenameMap() const
{
    return m_filenameMap;
}

QMap<QString, int> InputFile::GetFileNbrRowsMap() const
{
    return m_fileNbrRowsMap;
}

QMap<QString, int> InputFile::GetFileNbrColumnsMap() const
{
    return m_fileNbrColumnsMap;
}

QMap<QString, int> InputFile::GetFileNbrSubjectsMap() const
{
    return m_fileNbrSubjectsMap;
}

QStringList InputFile::GetCovariatesList() const
{
    return m_covariatesList;
}

int InputFile::GetSubjectColumnId() const
{
    return m_subjectColumnId;
}


QStringList InputFile::GetFilesSubjectsMap( QString pref ) const
{
    return m_filesSubjectsMap[ pref ];
}

QString InputFile::GetFilenameMap( QString pref ) const
{
    return m_filenameMap[ pref ];
}

int InputFile::GetFileNbrRowsMap( QString pref ) const
{
    return m_fileNbrRowsMap[ pref ];
}

int InputFile::GetFileNbrColumnsMap( QString pref ) const
{
    return m_fileNbrColumnsMap[ pref ];
}

int InputFile::GetFileNbrSubjectsMap( QString pref ) const
{
    return m_fileNbrSubjectsMap[ pref ];
}


void InputFile::SetFilesSubjectsMap( QString pref, QStringList filesSubjects )
{
    m_filesSubjectsMap[ pref ] = filesSubjects;
}

void InputFile::SetFilenameMap( QString pref, QString filename )
{
    m_filenameMap[ pref ] = filename;
}

void InputFile::SetFileNbrRowsMap( QString pref, int nbrRows )
{
    m_fileNbrRowsMap[ pref ] = nbrRows;
}

void InputFile::SetFileNbrColumnsMap( QString pref, int nbrColumns )
{
    m_fileNbrColumnsMap[ pref ] = nbrColumns;
}

void InputFile::SetFileNbrSubjectsMap( QString pref, int nbrSubjects )
{
    m_fileNbrSubjectsMap[ pref ] = nbrSubjects;
}

void InputFile::SetSubjectColumnId( int id)
{
    m_subjectColumnId = id;
}
