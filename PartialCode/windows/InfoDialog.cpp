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
void InfoDialog::DisplayInfo()
{
    qDebug() << "Test1";
    SetInfoFileLabelMap();
    qDebug() << "Test2";
    foreach( QString prefix, m_data.GetFilePrefixList() )
    {
        m_fileInfoLabelMap.value( prefix )->setText( tr( qPrintable( "<center><b>" + prefix.toUpper() + " File</b></center><br>" + GetFileInfo( prefix ) ) ) );
    }
}

void InfoDialog::ChangeDataValue( const Data& newData )
{
    m_data.UpdateData( newData );

//    qDebug() << m_data.m_axialDiffusivityFilePrefix;
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
    str.append( tr ( "<i>No File Information.<br>Please select a correct data file</i>" ) );
    const QString filename = m_data.GetFilename( p );
    QFile file( filename );

    if( file.open( QIODevice::ReadOnly ) )
    {
        int nbRows = m_data.GetFileNbrRows( p );
        int nbColumns = m_data.GetFileNbrColumns( p );

        str.clear();
        str.append( tr( qPrintable( "<b>Filename</b> " + QFileInfo( QFile( filename ) ).fileName() + "<br>" ) ) );
        if( p == m_data.GetCovariatesFilePrefix() )
        {
            str.append( tr( qPrintable( "<b>Number of test subjects</b>  " + QString::number( m_data.GetFileNbrSubjects( p ) ) + "<br>" ) ) );
            str.append( tr( qPrintable( "<b>Data matrix</b>  " + QString::number( nbRows ) + "x" + QString::number( nbColumns ) + "<br>" ) ) );
            str.append( tr( qPrintable( "<b>Number of COMP</b>  " + QString::number( m_data.GetCovariatesList().size()-1 ) ) ) );
            for( int c = 1; c < m_data.GetCovariatesList().size(); ++c )
            {
                str.append( tr( qPrintable( "<br>-  " + m_data.GetCovariatesList().at( c ) ) ) );
            }
        }
        else
        {
            if( m_data.GetFilePrefixList().contains( p ) )
            {
                str.append( tr( qPrintable( "<b>Number of subjects</b>  " + QString::number( m_data.GetFileNbrSubjects( p ) ) + "<br>" ) ) );
                str.append( tr( qPrintable( "<b>Data matrix</b>  " + QString::number( nbRows ) + "x" + QString::number( nbColumns ) ) ) );
            }
        }
    }
    return str;
}


void InfoDialog::SetInfoFileLabelMap()
{
    m_fileInfoLabelMap.insert( m_data.GetAxialDiffusivityFilePrefix(), m_ui->adFileInfo_label );
    m_fileInfoLabelMap.insert( m_data.GetRadialDiffusivityFilePrefix(), m_ui->rdFileInfo_label );
    m_fileInfoLabelMap.insert( m_data.GetMeanDiffusivityFilePrefix(), m_ui->mdFileInfo_label );
    m_fileInfoLabelMap.insert( m_data.GetFractionalAnisotropyFilePrefix(), m_ui->faFileInfo_label );
    m_fileInfoLabelMap.insert( m_data.GetCovariatesFilePrefix(), m_ui->compFileInfo_label );
}
