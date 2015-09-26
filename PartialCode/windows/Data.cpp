#include "Data.h"

Data::Data( QObject *parent ) :
    QObject(parent)
{
}


/***************************************/
/*************** Getters ***************/
/***************************************/
QString Data::GetOutputDir() const
{
    return m_outputDir;
}

QStringList Data::GetFilePrefixList() const
{
    return m_filePrefixList;
}

QString Data::GetAxialDiffusivityFilePrefix() const
{
    return m_axialDiffusivityFilePrefix;
}

QString Data::GetRadialDiffusivityFilePrefix() const
{
    return m_radialDiffusivityFilePrefix;
}

QString Data::GetMeanDiffusivityFilePrefix() const
{
    return m_meanDiffusivityFilePrefix;
}

QString Data::GetFractionalAnisotropyFilePrefix() const
{
    return m_fractionalAnisotropyFilePrefix;
}

QString Data::GetCovariatesFilePrefix() const
{
    return m_covariatesFilePrefix;
}


QMap<QString, QString> Data::GetFilenameMap() const
{
    return m_filenameMap;
}

QMap<QString, QStringList> Data::GetFilesSubjectsMap() const
{
    return m_filesSubjectsMap;
}

QMap<QString, int> Data::GetFileNbrRowsMap() const
{
    return m_fileNbrRowsMap;
}

QMap<QString, int> Data::GetFileNbrColumnsMap() const
{
    return m_fileNbrColumnsMap;
}

QMap<QString, int> Data::GetFileNbrSubjectsMap() const
{
    return m_fileNbrSubjectsMap;
}

QString Data::GetFilename( QString pref ) const
{
    return m_filenameMap[ pref ];
}

QStringList Data::GetFilesSubjects( QString pref ) const
{
    return m_filesSubjectsMap[ pref ];
}

int Data::GetFileNbrRows( QString pref ) const
{
    return m_fileNbrRowsMap[ pref ];
}

int Data::GetFileNbrColumns( QString pref ) const
{
    return m_fileNbrColumnsMap[ pref ];
}

int Data::GetFileNbrSubjects( QString pref ) const
{
    return m_fileNbrSubjectsMap[ pref ];
}

QStringList Data::GetCovariatesList() const
{
    return m_covariatesList;
}


int Data::GetSubjectColumnId() const
{
    return m_subjectColumnId;
}

QMap<QString, QStringList >::ConstIterator Data::GetFilesSubjectsMapIterator()
{
    return m_filesSubjectsMap.begin();
}


/***************************************/
/*************** Setters ***************/
/***************************************/
QString& Data::SetOutputDir()
{
    return m_outputDir;
}
QString& Data::SetFilename( QString pref )
 {
     return m_filenameMap[ pref ];
 }

QStringList& Data::SetFilesSubjects( QString pref )
{
    return m_filesSubjectsMap[ pref ];
}

int& Data::SetFileNbrRows( QString pref )
{
    return m_fileNbrRowsMap[ pref ];
}

int& Data::SetFileNbrColumns( QString pref )
{
    return m_fileNbrColumnsMap[ pref ];
}

int& Data::SetFileNbrSubjects( QString pref )
{
    return m_fileNbrSubjectsMap[ pref ];
}

QStringList& Data::SetCovariatesList()
{
    return m_covariatesList;
}


QString& Data::SetCovariatesFilePrefix()
{
    return m_covariatesFilePrefix;
}

void Data::SetSubjectColumnId( int id )
{
    m_subjectColumnId = id;
}


/***************************************/
/************** Functions **************/
/***************************************/
void Data::UpdateData( const Data& newData )
{
    this->m_subjectColumnId = newData.m_subjectColumnId;

    this->m_outputDir = newData.m_outputDir;

    this->m_axialDiffusivityFilePrefix = newData.m_axialDiffusivityFilePrefix;
    this->m_radialDiffusivityFilePrefix = newData.m_radialDiffusivityFilePrefix;
    this->m_meanDiffusivityFilePrefix = newData.m_meanDiffusivityFilePrefix;
    this->m_fractionalAnisotropyFilePrefix = newData.m_fractionalAnisotropyFilePrefix;
    this->m_covariatesFilePrefix = newData.m_covariatesFilePrefix;

    this->m_covariatesList = newData.m_covariatesList;
    this->m_filePrefixList = newData.m_filePrefixList;

    this->m_filesSubjectsMap = newData.m_filesSubjectsMap;
    this->m_filenameMap = newData.m_filenameMap;
    this->m_fileNbrRowsMap = newData.m_fileNbrRowsMap;
    this->m_fileNbrColumnsMap = newData.m_fileNbrColumnsMap;
    this->m_fileNbrSubjectsMap = newData.m_fileNbrSubjectsMap;
}

void Data::InitFileInformation()
{
    m_axialDiffusivityFilePrefix = "ad";
    m_radialDiffusivityFilePrefix = "rd";
    m_meanDiffusivityFilePrefix = "md";
    m_fractionalAnisotropyFilePrefix = "fa";
    m_covariatesFilePrefix = "COMP";

    m_filePrefixList << m_axialDiffusivityFilePrefix << m_radialDiffusivityFilePrefix << m_meanDiffusivityFilePrefix
                 << m_fractionalAnisotropyFilePrefix << m_covariatesFilePrefix;
    int nbrDuplicates = m_filePrefixList.removeDuplicates();
    if( nbrDuplicates != 0 )
    {
//        CriticalPopUp( tr( qPrintable( "Careful, you have " + QString::number( nbrDuplicates ) + " duplicates<br>"
//                       "in your file prefix list.<br>The application may not work properly." ) ) );
    }

    foreach( QString pref, m_filePrefixList )
    {
        m_filenameMap[ pref ];
        m_fileNbrRowsMap[ pref ];
        m_fileNbrColumnsMap[ pref ];
        m_fileNbrSubjectsMap[ pref ];
        ( m_filesSubjectsMap[ pref ] );
    }

    m_subjectColumnId = 0;
}

void Data::AddFileSubject( QString prefID, QString subjectID )
{
    m_filesSubjectsMap[ prefID ].append( tr( qPrintable( subjectID ) ) );
}

void Data::AddCovariate( QString covariate )
{
    m_covariatesList.append( tr( qPrintable( covariate ) ) );
}

void Data::AddIntercept()
{
    m_covariatesList.prepend( tr( "Intercept" ) );
}

void Data::ClearFileInformation( QString prefID )
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

void Data::ClearFileSubjects( QString prefID )
{
    ( m_filesSubjectsMap[ prefID ] ).clear();
}

void Data::ClearCovariatesList()
{
    m_covariatesList.clear();
}
