#include "EditInputDialog.h"
#include "ui_EditInputDialog.h"


EditInputDialog::EditInputDialog( QWidget *parent ) :
    QDialog( parent ),
    m_ui( new Ui::EditInputDialog )
{
    m_ui->setupUi( this );

    Init();
}

EditInputDialog::~EditInputDialog()
{
    delete m_dataTableWidget;
    delete m_ui;
}

/***************************************************************/
/********************** Public functions ***********************/
/***************************************************************/
void EditInputDialog::DisplayData()
{
    UploadData();
    RefreshFileInfo();
}

void EditInputDialog::ChangePrefixValue( const QString &newPrefix )
{
    m_prefixExpected = newPrefix;
}

void EditInputDialog::ChangeFilePrefixListValue( const QStringList &newFilePrefixList )
{
    m_filePrefixList = newFilePrefixList;
    m_covariatesFilePrefix = m_filePrefixList.last();
}

void EditInputDialog::ChangeFilePathInputValue( const QString &newFilePathInput )
{
    m_filePathInput = newFilePathInput;
    m_filename = QFileInfo( QFile( m_filePathInput ) ).fileName();
}

void EditInputDialog::SetcsvSeparator( const QString &csvSeparator )
{
    m_csvSeparator = csvSeparator;
}

void EditInputDialog::ChangeCurrentFileInputDirValue( const QString &newCurrentInputPathMainWindow )
{
    m_currentPathSetInput = newCurrentInputPathMainWindow;
}

void EditInputDialog::ResetSubjectColumnId()
{
    m_ui->para_subjectsColumn_spinBox->setValue( 1 );
}

/***************************************************************/
/************************ Private slots ************************/
/***************************************************************/
void EditInputDialog::on_deleteRows_pushButton_clicked()
{
    QItemSelection selection( m_dataTableWidget->selectionModel()->selection() );

    QList<int> rows;
    foreach( const QModelIndex &index, selection.indexes() )
    {
        rows.append( index.row() );
    }
    qSort( rows );

    int prev = -1;
    for( int i = rows.count() - 1; i >= 0; i -= 1 )
    {
        int current = rows.at( i );
        if( current != prev )
        {
            m_dataTableWidget->removeRow( current );
            prev = current;
        }
    }
    m_rowDeleted = true;

    RefreshFileInfo();
}

void EditInputDialog::on_deleteColumns_pushButton_clicked()
{
    QItemSelection selection( m_dataTableWidget->selectionModel()->selection() );

    QList<int> columns;
    foreach( const QModelIndex &index, selection.indexes() )
    {
        columns.append( index.column() );
    }
    qSort( columns );

    int prev = -1;
    for( int i = columns.count() - 1; i >= 0; i -= 1 )
    {
        int current = columns.at( i );
        if( current != prev )
        {
            m_dataTableWidget->removeColumn( current );
            prev = current;
        }
    }
    m_columnDeleted = true;

    RefreshFileInfo();
}

void EditInputDialog::on_para_subjectsColumn_spinBox_valueChanged( int idColumn )
{
    m_subjectColumnId = idColumn-1;
    emit SubjectColumnIdChanged( m_subjectColumnId );
    qDebug() << "m_subjectColumnId in EditInputDialog: " <<  m_subjectColumnId;
    RefreshFileInfo();
}

void EditInputDialog::on_saveFile_pushButton_clicked()
{
    SaveCSVFile();
    RefreshFileInfo();
}


/***************************************************************/
/********************** Private functions **********************/
/***************************************************************/
void EditInputDialog::Init()
{
    m_dataTableWidget = new QTableWidget;
    m_dataTableWidget = m_ui->data_tableWidget;
    m_dataTableWidget->setEditTriggers( QAbstractItemView::NoEditTriggers );
    m_rowDeleted = false;
    m_columnDeleted = false;
    m_ui->para_subjectsColumn_spinBox->setValue( 1 );
}

void EditInputDialog::IsCOMPFile( const QStringList strList )
{
    bool ok;
    foreach( QString str, strList )
    {
        if( str.endsWith( '"' ) )
        {
            str.chop( 1 );
        }
        if( str.startsWith( '"' ) )
        {
            str.remove( 0, 1 );
        }
        str.toFloat( &ok );
        if( !ok )
        {
            m_isCOMP = !ok;
            return;
        }
    }
    m_isCOMP = !ok;
}

void EditInputDialog::UploadData()
{
    QFile importedCSV( m_filePathInput );
    importedCSV.open( QIODevice::ReadOnly );
    QTextStream ts( &importedCSV );
    QList<QStringList> list;
    int row = 0, col = 0;

    // read entire file and parse lines into list of stringlist's
    while( !ts.atEnd() )
    {
        list << ts.readLine().split( m_csvSeparator );
    }
    importedCSV.close();  // done with file
    IsCOMPFile( list.at( 1 ) );
    m_ui->para_subjectsColumn_spinBox->setMaximum( list.at( 0 ).count() );
    // prep table
    m_dataTableWidget->setRowCount( list.count() );  // number of stringlists gives row count
    m_dataTableWidget->setColumnCount( list.at( 0 ).count() );  // count of entries from intial stringlist for column count

    m_dataTableWidget->setUpdatesEnabled( false );
    foreach( QStringList l, list )
    {
        foreach( QString str, l )
        {
            // remove quotes if str quoted
            if( str.endsWith( '"' ) )
            {
                str.chop( 1 );
            }
            if( str.startsWith( '"' ) )
            {
                str.remove( 0, 1 );
            }
            m_dataTableWidget->setItem( row, col++, new QTableWidgetItem( str ) );
        }
        row++; col=0;
    }
    m_dataTableWidget->setUpdatesEnabled( true );
}

void EditInputDialog::RefreshFileInfo()
{
    QString str;
    m_ui->para_subjectsColumn_spinBox->setHidden( true );
    m_ui->subjectsColumn_label->setHidden( true );

    int nbRows = m_dataTableWidget->rowCount();
    int nbColumns = m_dataTableWidget->columnCount();

    if( m_prefixExpected == m_covariatesFilePrefix )
    {
        m_ui->para_subjectsColumn_spinBox->setHidden( false );
        m_ui->subjectsColumn_label->setHidden( false );

        if( m_isCOMP )
        {
            str.append( tr( qPrintable( "<br><br><b>Filename</b> " + m_filename + "<br>" ) ) );
            str.append( tr( qPrintable( "<br><b>Number of test subjects</b>  " + QString::number( nbRows-1 ) + "<br>" ) ) );
            str.append( tr( qPrintable( "<br><b>Data matrix</b>  " + QString::number( nbRows-1 ) + "x" + QString::number( nbColumns-1 ) + "<br>" ) ) );
            str.append( tr( qPrintable( "<br><b>Number of covariates</b>  " + QString::number( nbColumns-1 ) ) ) );
            m_covariates.clear();
            for( int c = 0; c < nbColumns; ++c )
            {
                if( c != m_subjectColumnId )
                {
                    QString cov = m_dataTableWidget->item( 0, c )->text();
                    str.append( tr( qPrintable( "<br>-  " + cov ) ) );
                    m_covariates.append( cov );
                }
            }
            m_covariates.prepend( tr( "Intercept" ) );
            emit CovariatesChanged( m_covariates );
        }
        else
        {
            str.append( tr( qPrintable( "<br><center><i>WARNING<br><br>Please make sure you have uploaded<br>a " + m_prefixExpected + " file</i></center>" ) ) );
        }
    }
    else
    {
        if( m_filePrefixList.contains( m_prefixExpected ) )
        {
            if( !m_isCOMP )
            {
                str.append( tr( qPrintable( "<br><br><b>Filename</b> " + m_filename + "<br>" ) ) );
                str.append( tr( qPrintable( "<br><b>Number of subjects</b>  " + QString::number( nbColumns-1 ) + "<br>" ) ) );
                str.append( tr( qPrintable( "<br><b>Data matrix</b>  " + QString::number( nbRows-1 ) + "x" + QString::number( nbColumns ) ) ) );
            }
            else
            {
                str.append( tr( qPrintable( "<br><center><i>WARNING<br><br>Please make sure you have uploaded<br>a " + m_prefixExpected + " file</i></center>" ) ) );
            }

        }
    }
    m_ui->fileInformation_label->setText( str );
}

bool EditInputDialog::SaveCSVFile()
{
    QString filePath = QFileDialog::getSaveFileName( this, tr( qPrintable( "Save " + m_prefixExpected + " file as ..." ) ), m_currentPathSetInput, tr( ".csv( *.csv ) ;; .*( * )" ) );
    QFile exportedCSV( filePath );
    if( exportedCSV.open( QIODevice::WriteOnly ) )
    {
        QTextStream ts( &exportedCSV );
        QStringList strList;

        for( int r = 0; r < m_dataTableWidget->rowCount(); ++r )
        {
            strList.clear();
            for( int c = 0; c < m_dataTableWidget->columnCount(); ++c )
            {
                strList << m_dataTableWidget->item( r, c )->text();
            }
            ts << strList.join( m_csvSeparator ) << endl;
        }
        exportedCSV.flush();
        exportedCSV.close();
        emit FilePathChanged( filePath, m_prefixExpected );
        m_filename = QFileInfo( QFile( filePath ) ).fileName();
        qDebug() << "Emit OK" << filePath << " || " << QFileInfo( QFile( filePath ) ).fileName() << "||"  <<  m_prefixExpected;
        m_columnDeleted = false;
        m_rowDeleted = false;
        return true;
    }
    else
    {
        return false;
    }
}

void EditInputDialog::ResetTableWidget()
{
    m_rowDeleted = false;
    m_columnDeleted = false;
    m_dataTableWidget->clear();
    m_dataTableWidget->setRowCount( 0 );
    m_dataTableWidget->setColumnCount( 0 );
}

void EditInputDialog::closeEvent( QCloseEvent *event )
{
    if( m_rowDeleted || m_columnDeleted )
    {
        QMessageBox msgBox;
        msgBox.setText( tr( "The data have been modified." ) );
        msgBox.setInformativeText( tr( "Do you want to save your changes?" ) );
        msgBox.setStandardButtons( QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel );
        msgBox.setDefaultButton( QMessageBox::Save );
        int ret = msgBox.exec();
        switch( ret )
        {
        case QMessageBox::Save:
        {
            bool save = SaveCSVFile();
            if( save )
            {
                ResetTableWidget();
                event->accept();
            }
            else
            {
                event->ignore();
            }
        }
            break;
        case QMessageBox::Discard:
            ResetTableWidget();
            event->accept();
            break;
        case QMessageBox::Cancel:
            event->ignore();
            break;
        default:
            event->accept();
                break;
        }
    }
    else
    {
        ResetTableWidget();
        event->accept();
    }
}
