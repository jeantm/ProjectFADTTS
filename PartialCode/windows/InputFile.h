#ifndef INPUTFILE_H
#define INPUTFILE_H

#include <QObject>
#include <QStringList>
#include <QMap>
#include <QLocale>

class InputFile : public QObject
{
    Q_OBJECT

public:

    explicit InputFile(QObject *parent = 0);

    /***************************************/
    /*************** Getters ***************/
    /***************************************/
    QString GetAxialDiffusivityFilePrefix() const;

    QString GetRadialDiffusivityFilePrefix() const;

    QString GetMeanDiffusivityFilePrefix() const;

    QString GetFractionalAnisotropyFilePrefix() const;

    QString GetCovariatesFilePrefix() const;

    QStringList GetFilePrefixList() const;


    QString GetCurrentFileInputDir() const;

    QString GetCurrentFileOutputDir() const;

    QString GetCurrentSubjectsListInputDir() const;

    QString GetCurrentSaveFileDir() const;


    QMap<QString, QString> GetFilenameMap() const;

    QMap<QString, QStringList> GetFilesSubjectsMap() const;

    QMap<QString, int> GetFileNbrRowsMap() const;

    QMap<QString, int> GetFileNbrColumnsMap() const;

    QMap<QString, int> GetFileNbrSubjectsMap() const;

    QString GetFilenameMap( QString pref ) const;

    QStringList GetFilesSubjectsMap( QString pref ) const;

    int GetFileNbrRowsMap( QString pref ) const;

    int GetFileNbrColumnsMap( QString pref ) const;

    int GetFileNbrSubjectsMap( QString pref ) const;

    QStringList GetCovariatesList() const;


    QString GetCSVSeparator() const;

    int GetSubjectColumnId() const;

    QMap<QString, QStringList >::ConstIterator GetFilesSubjectsMapIterator();


    /***************************************/
    /*************** Setters ***************/
    /***************************************/
    QString& SetCurrentFileInputDir();

    QString& SetCurrentSubjectsListInputDir();


    QString& SetFilenameMap( QString pref );

    QStringList& SetFilesSubjectsMap( QString pref );

    int& SetFileNbrRowsMap( QString pref );

    int& SetFileNbrColumnsMap( QString pref );

    int& SetFileNbrSubjectsMap( QString pref );

    QStringList& SetCovariatesList( );


    void SetSubjectColumnId( int id );

    void SetCurrentFileOutputDir( QString CurrentFileOutputDir );


    /***************************************/
    /************** Functions **************/
    /***************************************/
    void InitFileInformation();

    void AddFileSubject( QString prefID, QString subjectID );

    void AddCovariate( QString covariate );

    void AddIntercept();

    void ClearFileInformation( QString prefID );

    void ClearFileSubjects( QString prefID );

    void ClearCovariatesList();


private:

//    int m_subjectColumnId;

    QString m_covariatesFilePrefix;
//    QString m_csvSeparator,
//    m_axialDiffusivityFilePrefix, m_radialDiffusivityFilePrefix,
//    m_meanDiffusivityFilePrefix, m_fractionalAnisotropyFilePrefix, m_covariatesFilePrefix,
//    m_currentFileInputDir, m_currentFileOutputDir, m_currentSubjectsListInputDir, m_currentSaveFileDir;

    QStringList m_covariatesList, m_filePrefixList;

    QMap<QString, QStringList> m_filesSubjectsMap;

    QMap<QString, QString> m_filenameMap;

    QMap<QString, int> m_fileNbrRowsMap, m_fileNbrColumnsMap, m_fileNbrSubjectsMap;
};

#endif // INPUTFILE_H
