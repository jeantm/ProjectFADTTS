#ifndef DATA_H
#define DATA_H

#include <QObject>
#include <QStringList>
#include <QMap>

class Data : public QObject
{
    Q_OBJECT

public:

    explicit Data(QObject *parent = 0);


    /***************************************/
    /*************** Getters ***************/
    /***************************************/
    QString GetOutputDir() const;

    QStringList GetFilePrefixList() const;

    QString GetAxialDiffusivityFilePrefix() const;

    QString GetRadialDiffusivityFilePrefix() const;

    QString GetMeanDiffusivityFilePrefix() const;

    QString GetFractionalAnisotropyFilePrefix() const;

    QString GetCovariatesFilePrefix() const;


    QMap<QString, QString> GetFilenameMap() const;

    QMap<QString, QStringList> GetFilesSubjectsMap() const;

    QMap<QString, int> GetFileNbrRowsMap() const;

    QMap<QString, int> GetFileNbrColumnsMap() const;

    QMap<QString, int> GetFileNbrSubjectsMap() const;

    QString GetFilename( QString pref ) const;

    QStringList GetFilesSubjects( QString pref ) const;

    int GetFileNbrRows( QString pref ) const;

    int GetFileNbrColumns( QString pref ) const;

    int GetFileNbrSubjects( QString pref ) const;

    QStringList GetCovariatesList() const;


    int GetSubjectColumnId() const;

    QMap<QString, QStringList >::ConstIterator GetFilesSubjectsMapIterator();


    /***************************************/
    /*************** Setters ***************/
    /***************************************/
    QString& SetOutputDir();

    QString& SetFilename( QString pref );

    QStringList& SetFilesSubjects( QString pref );

    int& SetFileNbrRows( QString pref );

    int& SetFileNbrColumns( QString pref );

    int& SetFileNbrSubjects( QString pref );

    QStringList& SetCovariatesList( );


    QString& SetCovariatesFilePrefix();

    void SetSubjectColumnId( int id );


    /***************************************/
    /************** Functions **************/
    /***************************************/
    void UpdateData( const Data& newData );

    void InitFileInformation();

    void AddFileSubject( QString prefID, QString subjectID );

    void AddCovariate( QString covariate );

    void AddIntercept();

    void ClearFileInformation( QString prefID );

    void ClearFileSubjects( QString prefID );

    void ClearCovariatesList();


private:

    int m_subjectColumnId;

    QString m_outputDir,
    m_axialDiffusivityFilePrefix, m_radialDiffusivityFilePrefix,
    m_meanDiffusivityFilePrefix, m_fractionalAnisotropyFilePrefix, m_covariatesFilePrefix;

    QStringList m_covariatesList, m_filePrefixList;

    QMap<QString, QStringList> m_filesSubjectsMap;

    QMap<QString, QString> m_filenameMap;

    QMap<QString, int> m_fileNbrRowsMap, m_fileNbrColumnsMap, m_fileNbrSubjectsMap;
};

#endif // DATA_H
