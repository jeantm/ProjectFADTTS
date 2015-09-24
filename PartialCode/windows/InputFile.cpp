#include "InputFile.h"

InputFile::InputFile( QObject *parent ) :
    QObject(parent)
{
}


//QString InputFile::GetAxialDiffusivityFilePrefix() const
//{
//    return m_axialDiffusivityFilePrefix;
//}

//QString InputFile::GetRadialDiffusivityFilePrefix() const
//{
//    return m_radialDiffusivityFilePrefix;
//}

//QString InputFile::GetMeanDiffusivityFilePrefix() const
//{
//    return m_meanDiffusivityFilePrefix;
//}

//QString InputFile::GetFractionalAnisotropyFilePrefix() const
//{
//    return m_fractionalAnisotropyFilePrefix;
//}

//QString InputFile::GetCovariatesFilePrefix() const
//{
//    return m_covariatesFilePrefix;
//}

QStringList InputFile::GetFilePrefixList() const
{
    return m_filePrefixList;
}


void InputFile::InitFileInformation()
{
    /// Retrieve platform separator ("," ";" ...)
//    m_csvSeparator = QLocale().groupSeparator();

//    /// Set the default file prefixes
//    m_axialDiffusivityFilePrefix = "ad";
//    m_radialDiffusivityFilePrefix = "rd";
//    m_meanDiffusivityFilePrefix = "md";
//    m_fractionalAnisotropyFilePrefix = "fa";
//    m_covariatesFilePrefix = "COMP";
//    m_filePrefixList << m_axialDiffusivityFilePrefix << m_radialDiffusivityFilePrefix << m_meanDiffusivityFilePrefix
//                 << m_fractionalAnisotropyFilePrefix << m_covariatesFilePrefix;
//    int nbrDuplicates = m_filePrefixList.removeDuplicates();
//    if( nbrDuplicates != 0 )
//    {
//        CriticalPopUp( tr( qPrintable( "Careful, you have " + QString::number( nbrDuplicates ) + " duplicates<br>"
//                       "in your file prefix list.<br>The application may not work properly." ) ) );
//    }

    foreach( QString pref, m_filePrefixList )
    {
        m_filenameMap[ pref ];
        m_fileNbrRowsMap[ pref ];
        m_fileNbrColumnsMap[ pref ];
        m_fileNbrSubjectsMap[ pref ];
        ( m_filesSubjectsMap[ pref ] );
    }

//    m_subjectColumnId = 0;
}

QMap<QString, QStringList >::ConstIterator InputFile::GetFilesSubjectsMapIterator()
{
    return m_filesSubjectsMap.begin();
}


void InputFile::ClearFileInformation( QString prefID )
{
    m_filenameMap[ prefID ].clear();
    m_fileNbrRowsMap[ prefID ] = 0;
    m_fileNbrColumnsMap[ prefID ] = 0;
    m_fileNbrSubjectsMap[ prefID ] = 0;
    ( m_filesSubjectsMap[ prefID ] ).clear();

    if( prefID == m_covariatesFilePrefix )
    {
        m_covariatesList.clear();
    }
}


//QString InputFile::GetCSVSeparator() const
//{
//    return m_csvSeparator;
//}

//QString InputFile::GetCurrentFileInputDir() const
//{
//    return m_currentFileInputDir;
//}

//QString InputFile::GetCurrentFileOutputDir() const
//{
//    return m_currentFileOutputDir;
//}

//void InputFile::SetCurrentFileOutputDir( QString CurrentFileOutputDir )
//{
//    m_currentFileOutputDir = CurrentFileOutputDir;
//}

//QString InputFile::GetCurrentSubjectsListInputDir() const
//{
//    return m_currentSubjectsListInputDir;
//}

//QString InputFile::GetCurrentSaveFileDir() const
//{
//    return m_currentSaveFileDir;
//}

void InputFile::ClearFileSubjects( QString prefID )
{
    ( m_filesSubjectsMap[ prefID ] ).clear();
}

//QString& InputFile::SetCurrentFileInputDir()
//{
//    return m_currentFileInputDir;
//}

//QString& InputFile::SetCurrentSubjectsListInputDir()
//{
//    return m_currentSubjectsListInputDir;
//}

void InputFile::AddFileSubject( QString prefID, QString subjectID )
{
    m_filesSubjectsMap[ prefID ].append( tr( qPrintable( subjectID ) ) );
}

void InputFile::AddCovariate( QString covariate )
{
    m_covariatesList.append( tr( qPrintable( covariate ) ) );
}

void InputFile::AddIntercept()
{
    m_covariatesList.prepend( tr( "Intercept" ) );
}

QStringList& InputFile::SetCovariatesList()
{
    return m_covariatesList;
}

void InputFile::ClearCovariatesList()
{
    m_covariatesList.clear();
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

//int InputFile::GetSubjectColumnId() const
//{
//    return m_subjectColumnId;
//}


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


QStringList& InputFile::SetFilesSubjectsMap( QString pref )
{
    return m_filesSubjectsMap[ pref ];
}

QString& InputFile::SetFilenameMap( QString pref )
{
    return m_filenameMap[ pref ];
}

int& InputFile::SetFileNbrRowsMap( QString pref )
{
    return m_fileNbrRowsMap[ pref ];
}

int& InputFile::SetFileNbrColumnsMap( QString pref )
{
    return m_fileNbrColumnsMap[ pref ];
}

int& InputFile::SetFileNbrSubjectsMap( QString pref )
{
    return m_fileNbrSubjectsMap[ pref ];
}

//void InputFile::SetSubjectColumnId( int id )
//{
//    m_subjectColumnId = id;
//}
