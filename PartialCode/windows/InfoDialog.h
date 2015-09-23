#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QtCore>
#include <QtGui>


namespace Ui {
class InfoDialog;
}

class InfoDialog : public QDialog
{
    Q_OBJECT
    

public:
    explicit InfoDialog( QWidget *parent = 0 );
    ~InfoDialog();
    
    void DisplayInfo( const QStringList pefixList );

    void ChangeFilePrefixListValue( const QStringList &newFilePrefixList );

    void ChangeFilenameMapValue( const QMap<QString, QString> &newFilenameMap );

    void ChangeCovariatesListValue( const QStringList &newCovariatesList );

    void ChangeFileNbrRowsMapValue( const QMap<QString,int> &newFileNbrRowsMap );

    void ChangeFileNbrColumnsMapValue( const QMap<QString,int> &newFileNbrColumnsMap );

    void ChangeFileNbrSubjectsMapValue( const QMap<QString, int> &newFileNbrSubjectsMap );


private:
    Ui::InfoDialog *m_ui;

    QMap<QString, QString> m_filenameMap;

    QMap<QString,int> m_fileNbrRowsMap;

    QMap<QString,int> m_fileNbrColumnsMap;

    QMap<QString,int> m_fileNbrSubjectsMap;

    typedef QMap<QString, QLabel*> labelMapType;
    labelMapType m_fileInfoLabelMap;

    QStringList m_covariatesList, m_filePrefix;

    QString m_axialDiffusivityFilePrefixe, m_radialDiffusivityFilePrefixe,
    m_meanDiffusivityFilePrefixe, m_fractionalAnisotropyPrefixe, m_covariatesFilePrefixe;


    QString GetFileInfo( const QString p );

    void SetFilePrefix();

    void SetInfoFileLabelMap();
};

#endif // INFODIALOG_H
