#ifndef INPUTFILE_H
#define INPUTFILE_H

#include <QObject>
#include <QStringList>
#include <QMap>

class InputFile : public QObject
{
    Q_OBJECT
public:
    explicit InputFile(QObject *parent = 0);

    explicit InputFile(QStringList filePrefixList);
    

    QMap<QString, QStringList> GetFilesSubjectsMap() const;

    QMap<QString, QString> GetFilenameMap() const;

    QMap<QString, int> GetFileNbrRowsMap() const;

    QMap<QString, int> GetFileNbrColumnsMap() const;

    QMap<QString, int> GetFileNbrSubjectsMap() const;

    QStringList GetCovariatesList() const;

    int GetSubjectColumnId() const;


    QStringList GetFilesSubjectsMap( QString pref ) const;

    QString GetFilenameMap( QString pref ) const;

    int GetFileNbrRowsMap( QString pref ) const;

    int GetFileNbrColumnsMap( QString pref ) const;

    int GetFileNbrSubjectsMap( QString pref ) const;


    void SetFilesSubjectsMap( QString pref, QStringList filesSubjects );

    void SetFilenameMap( QString pref, QString filename );

    void SetFileNbrRowsMap( QString pref, int nbrRows );

    void SetFileNbrColumnsMap( QString pref, int nbrColumns );

    void SetFileNbrSubjectsMap( QString pref, int nbrSubjects );

    void SetSubjectColumnId( int id);


signals:
    
public slots:

private:
    QMap<QString, QStringList> m_filesSubjectsMap;

    QMap<QString, QString> m_filenameMap;

    QMap<QString, int> m_fileNbrRowsMap, m_fileNbrColumnsMap, m_fileNbrSubjectsMap;

    QStringList m_covariatesList;

    int m_subjectColumnId;
    
};

#endif // INPUTFILE_H
