#include "InfoDialog.h"
#include "ui_InfoDialog.h"

InfoDialog::InfoDialog( QWidget *parent ) :
    QDialog( parent ),
    m_ui( new Ui::InfoDialog )
{
    m_ui->setupUi( this );

}

InfoDialog::~InfoDialog()
{
    delete m_ui;
}



/***************************************************************/
/********************** Public functions ***********************/
/***************************************************************/
void InfoDialog::DisplayInfo( const QStringList pefixList )
{
    SetInfoFileLabelMap();

    foreach( QString prefix, pefixList )
    {
        m_fileInfoLabelMap.value( prefix )->setText( GetFileInfo( prefix ) );
    }
}

void InfoDialog::ChangeFilePrefixListValue( const QStringList &newFilePrefixList )
{
    m_filePrefix = newFilePrefixList;
    qDebug() << "Info update filePrefixList: " << m_filePrefix;

    SetFilePrefix();
}

void InfoDialog::ChangeFilenameMapValue( const QMap<QString,QString> &newFilenameMap )
{
    m_filenameMap = newFilenameMap;
    qDebug() << "Info update filenameMap: " << m_filenameMap;
}

void InfoDialog::ChangeCovariatesListValue( const QStringList &newCovariatesList )
{
    m_covariatesList = newCovariatesList;
    qDebug() << "Info update covariatesList: " << m_covariatesList;
}

void InfoDialog::ChangeFileNbrRowsMapValue( const QMap<QString,int> &newFileNbrRowsMap )
{
    m_fileNbrRowsMap = newFileNbrRowsMap;
    qDebug() << "Info update fileNbrRowsMap: " << m_fileNbrRowsMap;
}

void InfoDialog::ChangeFileNbrColumnsMapValue( const QMap<QString,int> &newFileNbrColumnsMap )
{
    m_fileNbrColumnsMap = newFileNbrColumnsMap;
    qDebug() << "Info update fileNbrColumnsMap: " << m_fileNbrColumnsMap;
}

void InfoDialog::ChangeFileNbrSubjectsMapValue( const QMap<QString,int> &newFileNbrSubjectsMap )
{
    m_fileNbrSubjectsMap = newFileNbrSubjectsMap;
    qDebug() << "Info update fileNbrSubjectsMap: " << m_fileNbrSubjectsMap;
}


/***************************************************************/
/************************ Private slots ************************/
/***************************************************************/

/***************************************************************/
/********************** Private functions **********************/
/***************************************************************/
QString InfoDialog::GetFileInfo( const QString p )
{
    QString str;
    str.append( tr ( "<center><b>No File Information</b></center><br><b>Please select a correct data file</b><br>" ) );
    const QString filename = m_filenameMap[p];
    QFile file( filename );

    if( file.open( QIODevice::ReadOnly ) )
    {
        int nbRows = m_fileNbrRowsMap[p];
        int nbColumns = m_fileNbrColumnsMap[p];

        str.clear();
        str.append( tr( qPrintable( "<b>Filename</b> " + QFileInfo( QFile( filename ) ).fileName() + "<br>" ) ) );
        if( p == m_covariatesFilePrefixe )
        {
            str.append( tr( qPrintable( "<b>Number of test subjects</b>  " + QString::number( m_fileNbrSubjectsMap[p] ) + "<br>" ) ) );
            str.append( tr( qPrintable( "<b>Data matrix</b>  " + QString::number( nbRows ) + "x" + QString::number( nbColumns ) + "<br>" ) ) );
            str.append( tr( qPrintable( "<b>Number of COMP</b>  " + QString::number( m_covariatesList.size()-1 ) ) ) );
            for( int c = 1; c < m_covariatesList.size(); ++c )
            {
                str.append( tr( qPrintable( "<br>-  " + m_covariatesList.at( c ) ) ) );
            }
        }
        else
        {
            if( m_filePrefix.contains( p ) )
            {
                str.append( tr( qPrintable( "<b>Number of subjects</b>  " + QString::number( m_fileNbrSubjectsMap[p] ) + "<br>" ) ) );
                str.append( tr( qPrintable( "<b>Data matrix</b>  " + QString::number( nbRows-1 ) + "x" + QString::number( nbColumns ) ) ) );
            }
        }
    }
    return str;
}

void InfoDialog::SetFilePrefix()
{
    m_axialDiffusivityFilePrefixe = m_filePrefix.at( 0 );
    m_radialDiffusivityFilePrefixe = m_filePrefix.at( 1 );
    m_meanDiffusivityFilePrefixe = m_filePrefix.at( 2 );
    m_fractionalAnisotropyPrefixe = m_filePrefix.at( 3 );
    m_covariatesFilePrefixe = m_filePrefix.at( 4 );
}

void InfoDialog::SetInfoFileLabelMap()
{
    m_fileInfoLabelMap.insert( m_axialDiffusivityFilePrefixe, m_ui->adFileInfo_label );
    m_fileInfoLabelMap.insert( m_radialDiffusivityFilePrefixe, m_ui->rdFileInfo_label );
    m_fileInfoLabelMap.insert( m_meanDiffusivityFilePrefixe, m_ui->mdFileInfo_label );
    m_fileInfoLabelMap.insert( m_fractionalAnisotropyPrefixe, m_ui->faFileInfo_label );
    m_fileInfoLabelMap.insert( m_covariatesFilePrefixe, m_ui->compFileInfo_label );
}
