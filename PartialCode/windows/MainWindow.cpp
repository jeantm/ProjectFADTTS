#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <iostream>

using namespace std;

/// Retrieve platform separator ("," ";" ...)
const QString MainWindow::m_csvSeparator = QLocale().groupSeparator();

const QColor MainWindow::m_green = QColor( 0,255,0,127 );
const QColor MainWindow::m_red = QColor( 255,0,0,127 );
const QColor MainWindow::m_grey = QColor( 220,220,220,255 );
const QColor MainWindow::m_yellow = QColor( 255,255,0,127 );
const QColor MainWindow::m_lightBlack = QColor( 0,0,0,191 );

const int MainWindow::m_IconSize = 12;
/********************************************************************/
/****************** Change that horrible hard code ******************/
/********************************************************************/
const QPixmap MainWindow::m_okPixmap = QPixmap( "/NIRAL/work/jeantm/FADTTS/Project/PartialCode/windows/okIcon.png" );
const QPixmap MainWindow::m_koPixmap = QPixmap( "/NIRAL/work/jeantm/FADTTS/Project/PartialCode/windows/koIcon.png" );
const QPixmap MainWindow::m_warningPixmap = QPixmap( "/NIRAL/work/jeantm/FADTTS/Project/PartialCode/windows/warningIcon.png" );


MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow( parent ),
    m_mainUi( new Ui::MainWindow )
{
    m_mainUi->setupUi( this );
    m_editInputDialog = new EditInputDialog;
    m_infoDialog = new InfoDialog;

    m_sortedSubjectsListWidget = new QListWidget();
    m_sortedSubjectsListWidget = m_mainUi->sortedSubjects_listWidget;

    m_covariatesListWidget = new QListWidget();
    m_covariatesListWidget = m_mainUi->covariates_listWidget;

    Init();
}

MainWindow::~MainWindow()
{
    delete m_mainUi;
    delete m_editInputDialog;
    delete m_infoDialog;
    delete m_sortedSubjectsListWidget;
    delete m_covariatesListWidget;
}


/***************************************************************/
/**************************** Other ****************************/
/***************************************************************/

/*********************** Public function ***********************/


/***********************  Private slots  ***********************/


/*********************** Private function **********************/
void MainWindow::Init()
{
    m_data.InitFileInformation();

    InitInputTab();

    InitSubjectTab();

    InitParameterTab();

    SetCovariatesList();

    UpdateParamTab();
}

void MainWindow::InitInputTab()
{
    /// Map of PushButtons to add each file separetely and
    /// SignalMapper to link them to the slot AddFile()
    m_inputTabAddFilePushButtonMap.insert( m_data.GetAxialDiffusivityFilePrefix(), m_mainUi->inputADfile_pushButton );
    m_inputTabAddFilePushButtonMap.insert( m_data.GetRadialDiffusivityFilePrefix(), m_mainUi->inputRDfile_pushButton );
    m_inputTabAddFilePushButtonMap.insert( m_data.GetMeanDiffusivityFilePrefix(), m_mainUi->inputMDfile_pushButton );
    m_inputTabAddFilePushButtonMap.insert( m_data.GetFractionalAnisotropyFilePrefix(), m_mainUi->inputFAfile_pushButton );
    m_inputTabAddFilePushButtonMap.insert( m_data.GetCovariatesFilePrefix(), m_mainUi->inputCOMPfile_pushButton );
    QSignalMapper *signalMapperAddFile = new QSignalMapper( this );
    QObject::connect( signalMapperAddFile, SIGNAL( mapped( const QString& ) ), this, SLOT( AddFile( const QString& ) ) );
    for( int i = 0; i < m_data.GetFilePrefixList().size(); ++i )
    {
        QObject::connect( m_inputTabAddFilePushButtonMap[ m_data.GetFilePrefixList().at( i ) ], SIGNAL( clicked() ), signalMapperAddFile,SLOT(map() ) );
        signalMapperAddFile->setMapping( m_inputTabAddFilePushButtonMap[ m_data.GetFilePrefixList().at( i ) ], m_data.GetFilePrefixList().at( i ) );
    }

    /// Map of LineEdits where the file path of each file is set and
    /// SignalMapper to link them to the slot UpdateLineEdit()
    m_inputTabFilePathLineEditMap.insert( m_data.GetAxialDiffusivityFilePrefix(), m_mainUi->para_inputADfile_lineEdit );
    m_inputTabFilePathLineEditMap.insert( m_data.GetRadialDiffusivityFilePrefix(), m_mainUi->para_inputRDfile_lineEdit );
    m_inputTabFilePathLineEditMap.insert( m_data.GetMeanDiffusivityFilePrefix(), m_mainUi->para_inputMDfile_lineEdit );
    m_inputTabFilePathLineEditMap.insert( m_data.GetFractionalAnisotropyFilePrefix(), m_mainUi->para_inputFAfile_lineEdit );
    m_inputTabFilePathLineEditMap.insert( m_data.GetCovariatesFilePrefix(), m_mainUi->para_inputCOMPfile_lineEdit );
    QSignalMapper *signalMapperUpdateLineEdit = new QSignalMapper(this);
    QObject::connect( signalMapperUpdateLineEdit, SIGNAL( mapped( const QString& ) ), this, SLOT( UpdateLineEdit( const QString& ) ) );
    for( int i = 0; i < m_data.GetFilePrefixList().size(); ++i )
    {
        QObject::connect( m_inputTabFilePathLineEditMap[ m_data.GetFilePrefixList().at( i ) ], SIGNAL( textChanged( const QString& ) ), signalMapperUpdateLineEdit,SLOT(map() ) );
        signalMapperUpdateLineEdit->setMapping( m_inputTabFilePathLineEditMap[ m_data.GetFilePrefixList().at( i ) ], m_data.GetFilePrefixList().at( i ) );
    }

    /// Map of Labels to set the icon information of each file entered in a LineEdit
    m_inputTabIconLabelMap.insert( m_data.GetAxialDiffusivityFilePrefix(), m_mainUi->iconInputADFile_label );
    m_inputTabIconLabelMap.insert( m_data.GetRadialDiffusivityFilePrefix(), m_mainUi->iconInputRDFile_label );
    m_inputTabIconLabelMap.insert( m_data.GetMeanDiffusivityFilePrefix(), m_mainUi->iconInputMDFile_label );
    m_inputTabIconLabelMap.insert( m_data.GetFractionalAnisotropyFilePrefix(), m_mainUi->iconInputFAFile_label );
    m_inputTabIconLabelMap.insert( m_data.GetCovariatesFilePrefix(), m_mainUi->iconInputCOMPFile_label );
    // SignalMapper on lineEdit textChanged?

    /// Map of PushButtons to edit the files and
    /// SignalMapper to link them to the slot EditFile()
    m_inputTabEditFilePushButtonMap.insert( m_data.GetAxialDiffusivityFilePrefix(), m_mainUi->editInputADfile_pushButton );
    m_inputTabEditFilePushButtonMap.insert( m_data.GetRadialDiffusivityFilePrefix(), m_mainUi->editInputRDfile_pushButton );
    m_inputTabEditFilePushButtonMap.insert( m_data.GetMeanDiffusivityFilePrefix(), m_mainUi->editInputMDfile_pushButton );
    m_inputTabEditFilePushButtonMap.insert( m_data.GetFractionalAnisotropyFilePrefix(), m_mainUi->editInputFAfile_pushButton );
    m_inputTabEditFilePushButtonMap.insert( m_data.GetCovariatesFilePrefix(), m_mainUi->editInputCOMPfile_pushButton );
    QSignalMapper *signalMapperEditFile = new QSignalMapper( this );
    QObject::connect( signalMapperEditFile, SIGNAL( mapped( const QString& ) ), this, SLOT( EditFile( const QString& ) ) );
    for( int i = 0; i < m_data.GetFilePrefixList().size(); ++i )
    {
        QObject::connect( m_inputTabEditFilePushButtonMap[ m_data.GetFilePrefixList().at( i ) ], SIGNAL( clicked() ), signalMapperEditFile, SLOT(map() ) );
        signalMapperEditFile->setMapping( m_inputTabEditFilePushButtonMap[ m_data.GetFilePrefixList().at( i ) ], m_data.GetFilePrefixList().at( i ) );
    }

    /// File information send to m_infoDialog
    m_infoDialog->ChangeDataValue( m_data );

    /// Signal/Slot connection to receive updates from m_editInputDialog
    QObject::connect( m_editInputDialog, SIGNAL( FilePathChanged( QString, QString ) ), this, SLOT( FilePathValue( QString , QString ) ) );
    QObject::connect( m_editInputDialog, SIGNAL( CovariatesChanged( QStringList ) ), this, SLOT( CovariatesValue( QStringList ) ) );
    QObject::connect( m_editInputDialog, SIGNAL( SubjectColumnIdChanged( int ) ), this, SLOT( SubjectColumnIdValue( int ) ) );
}

void MainWindow::InitSubjectTab()
{
    /// Map of CheckBoxes to select the files we want to work on and
    /// SignalMapper to link them to the slot SortSubjects()
    m_paramTabFileCheckBoxMap.insert( m_data.GetAxialDiffusivityFilePrefix(), m_mainUi->para_adData_checkBox );
    m_paramTabFileCheckBoxMap.insert( m_data.GetRadialDiffusivityFilePrefix(), m_mainUi->para_rdData_checkBox );
    m_paramTabFileCheckBoxMap.insert( m_data.GetMeanDiffusivityFilePrefix(), m_mainUi->para_mdData_checkBox );
    m_paramTabFileCheckBoxMap.insert( m_data.GetFractionalAnisotropyFilePrefix(), m_mainUi->para_faData_checkBox );
    m_paramTabFileCheckBoxMap.insert( m_data.GetCovariatesFilePrefix(), m_mainUi->para_compData_checkBox );
    QSignalMapper *signalMapperSelectFile = new QSignalMapper(this);
    QObject::connect( signalMapperSelectFile, SIGNAL( mapped( const QString& ) ), this, SLOT( SortSubjects() ) );
    for ( int i = 0; i < m_data.GetFilePrefixList().size(); ++i )
    {
        QObject::connect( m_paramTabFileCheckBoxMap[ m_data.GetFilePrefixList().at( i ) ], SIGNAL( toggled( const bool& ) ), signalMapperSelectFile,SLOT( map() ) );
        signalMapperSelectFile->setMapping( m_paramTabFileCheckBoxMap[ m_data.GetFilePrefixList().at( i ) ], m_data.GetFilePrefixList().at( i ) );
    }

    /// Map of Labels displaying the matrix data size of the files that have been chosen
    m_paramTabFileSizeLabelMap.insert( m_data.GetAxialDiffusivityFilePrefix(), m_mainUi->adDataSize_label );
    m_paramTabFileSizeLabelMap.insert( m_data.GetRadialDiffusivityFilePrefix(),m_mainUi->rdDataSize_label );
    m_paramTabFileSizeLabelMap.insert( m_data.GetMeanDiffusivityFilePrefix(), m_mainUi->mdDataSize_label );
    m_paramTabFileSizeLabelMap.insert( m_data.GetFractionalAnisotropyFilePrefix(), m_mainUi->faDataSize_label );
    m_paramTabFileSizeLabelMap.insert( m_data.GetCovariatesFilePrefix(), m_mainUi->compDataSize_label );
}

void MainWindow::InitParameterTab()
{
    /********** To do soon **********/
}


void MainWindow::UpdateCurrentDirEditInputDialog(const QString newfilePath, QString& currentDir, EditInputDialog *editInputDialog )
{

    QDir dir = UpdateCurrentDir( newfilePath, currentDir );
    if( dir.exists() )
    {
        editInputDialog->ChangeCurrentFileInputDirValue( dir.absolutePath() );
    }
}

QDir MainWindow::UpdateCurrentDir( const QString newfilePath, QString& currentDir )
{
    QDir dir = QFileInfo( QFile( newfilePath ) ).absolutePath();
    if( dir.exists() )
    {
        currentDir = dir.absolutePath();
    }

    return dir;
}

void MainWindow::WarningPopUp( const QString warningText )
{
    QMessageBox::warning( this, tr( "WARNING" ), tr( qPrintable( warningText ) ), QMessageBox::Ok );
}

void MainWindow::CriticalPopUp( const QString criticalText )
{
    QMessageBox::critical( this, tr( "CRITICAL ERROR" ), tr( qPrintable( criticalText ) ), QMessageBox::Ok );
}

void MainWindow::SetIcon( QLabel *label , const QPixmap icon )
{
    label->setPixmap( icon.scaled( QSize( m_IconSize, m_IconSize ), Qt::IgnoreAspectRatio ) );
}

/***************************************************************/
/************************** Input tab **************************/
/***************************************************************/

/*********************** Public function ***********************/


/***********************  Private slots  ***********************/
void MainWindow::on_inputAddDataFiles_pushButton_clicked()
{
    QString dirPath = m_currentFileInputDir;
    QStringList fileList;
    fileList = QFileDialog::getOpenFileNames( this, tr( "Choose CSV files" ), dirPath, tr( ".csv( *.csv ) ;; .*( * )" ) );
    AddFiles( fileList );
}

void MainWindow::on_inputInfo_pushButton_clicked()
{
    m_infoDialog->setModal( true );
    m_infoDialog->setWindowTitle( tr( "Info Files" ) );
    m_infoDialog->DisplayInfo();
    m_infoDialog->exec();
}

void MainWindow::on_outputDir_pushButton_clicked()
{
    QLineEdit *lineEdit = m_mainUi->para_outputDir_lineEdit;
    QString filePath = lineEdit->text();
    QDir dir = QFileInfo( QFile( filePath ) ).absolutePath();
    QString dirPath;
    if( dir.exists() && !filePath.isEmpty() )
    {
        dirPath = QFileDialog::getExistingDirectory( this, tr( "Choose Output Directory" ), dir.absolutePath(), QFileDialog::ShowDirsOnly );
    }
    else
    {
        dirPath = QFileDialog::getExistingDirectory( this, tr( "Choose Output Directory" ), m_data.GetOutputDir(), QFileDialog::ShowDirsOnly );
    }
    if( !dirPath.isEmpty() )
    {
        m_data.SetOutputDir() =  dirPath;
        lineEdit->setText( dirPath );
    }
}

void MainWindow::on_para_outputDir_lineEdit_textChanged( const QString&  textLineEdit )
{
    QLabel *label = m_mainUi->iconOutputDir_label;
    if( !textLineEdit.isEmpty() )
    {
        if( QDir( textLineEdit ).exists() )
        {
            SetIcon( label, m_okPixmap );
            m_data.SetOutputDir() = textLineEdit;
        }
        else
        {
            SetIcon( label, m_koPixmap );
        }
    }
    else
    {
        label->clear();
    }
}

void MainWindow::FilePathValue( const QString& newFilePath, const QString& prefID )
{
    m_inputTabFilePathLineEditMap[ prefID ]->setText( newFilePath );
}

void MainWindow::CovariatesValue( const QStringList& newCovariates )
{
    m_data.ClearCovariatesList();
    m_data.SetCovariatesList() = newCovariates;
    m_infoDialog->ChangeDataValue( m_data );
    SetCovariatesList();
}

void MainWindow::SubjectColumnIdValue( const int&  newSubjectColumnIdValue )
{
    /// Subjects not on the 1st column anymore
    m_data.SetSubjectColumnId( newSubjectColumnIdValue );

    SetInfoSubjectsColumnID();

    /// Updates needed
    UpdateFileInformation( m_inputTabFilePathLineEditMap[ m_data.GetCovariatesFilePrefix() ]->text(), m_data.GetCovariatesFilePrefix() );
    SortSubjects();
}

void MainWindow::AddFile( const QString& prefID )
{
    QLineEdit *lineEdit = m_inputTabFilePathLineEditMap[ prefID ];
    QString filePath = lineEdit->text();
    QDir dir = QFileInfo( QFile( filePath ) ).absolutePath();
    if( filePath.isEmpty() || !dir.exists() )
    {
        dir = m_currentFileInputDir;
    }

    QString file = QFileDialog::getOpenFileName( this, tr( qPrintable( "Choose " + prefID + " file" ) ), dir.absolutePath(), tr( ".csv( *.csv ) ;; .*( * )" ) );
    QFile importedCSV( file );
    if( !importedCSV.open( QIODevice::ReadOnly ) )
    {
        return;
    }
    else
    {
        importedCSV.close();
        lineEdit->setText( file );
    }
}

void MainWindow::EditFile( const QString& prefID )
{
    if( m_data.GetFilename( prefID ).isEmpty() )
    {
        QString warningMessage = tr( "<center>File edition unable</center>" );
        if( m_inputTabFilePathLineEditMap[ prefID ]->text().isEmpty() )
        {
            warningMessage.append( tr( "No file specified" ) );
        }
        else
        {
            warningMessage.append( tr( qPrintable( "Could not open the file:<br><i>" + m_inputTabFilePathLineEditMap[ prefID ]->text() + "</i>" ) ) );
        }
        WarningPopUp( warningMessage );
    }
    else
    {
        LaunchEditInputWindow( prefID );
    }
}

void MainWindow::UpdateLineEdit( const QString& prefID )
{
    QLineEdit *lineEdit = m_inputTabFilePathLineEditMap[ prefID ];
    QString filePath = lineEdit->text();
    if( !filePath.isEmpty() )
    {
        UpdateCurrentDirEditInputDialog( filePath, m_currentFileInputDir, m_editInputDialog );

    }

    if( prefID == m_data.GetCovariatesFilePrefix() )
    {
        m_editInputDialog->ResetSubjectColumnId();   /// By default Subjects are on 1st column
    }

    SetInfoSubjectsColumnID();
    UpdateFileInformation( filePath, prefID );
    SortSubjects();
}


/*********************** Private function ***********************/
void MainWindow::AddFiles( const QStringList filesList )
{
    QMap<QString, QStringList > map;
    foreach( QString file, filesList )
    {
        QString p = QFileInfo( QFile ( file ) ).fileName().split( '_' ).first();
        /// If m_filePrefixList contains the prefix, the file is linked to this prefix
        if( m_data.GetFilePrefixList().contains( p ) )
        {
            ( map[ p ] ).append( file );
        }
    }

    QMap<QString, QStringList >::ConstIterator iter = map.begin();

    while( iter != map.constEnd() )
    {
        QString prefix = iter.key();
        QString file;
        if( iter.value().size() == 1 )
        {
            file = iter.value().first();
        }
        else
        {
            /// If a prefix is linked with more than one file, those files are ignored
            file.clear();
        }

        if( m_inputTabFilePathLineEditMap.contains( prefix ) )
        {
            m_inputTabFilePathLineEditMap[ prefix ]->setText( file );
        }
        ++iter;
    }
}

void MainWindow::UpdateFileInformation( const QString filePath, const QString prefID )
{
    QFile file( filePath );
    if( !file.open( QIODevice::ReadOnly ) )
    {
        if( !m_inputTabFilePathLineEditMap[ prefID ]->text().isEmpty() )
        {
            SetIcon( prefID, m_koPixmap );
        }
        else
        {
            m_inputTabIconLabelMap[ prefID ]->clear();
        }
        m_data.ClearFileInformation( prefID );
    }
    else
    {
        QTextStream ts( &file );
        QList<QStringList> data;
        while( !ts.atEnd() )
        {
            data.append( ts.readLine().split( m_csvSeparator ) );
        }
        file.close();
        int nbRows = data.count();
        int nbColumns = data.at( 0 ).count();

        if( IsMatrixDimensionOK( data ) )
        {
            SetIcon( prefID, m_okPixmap );
            m_data.SetFilename( prefID ) = filePath;
            m_data.ClearFileSubjects( prefID );

            if( prefID == m_data.GetCovariatesFilePrefix() )
            {
                m_data.SetFileNbrRows( prefID ) = nbRows-1;
                m_data.SetFileNbrColumns( prefID ) = nbColumns-1;
                m_data.SetFileNbrSubjects( prefID ) = nbRows-1;

                m_data.ClearCovariatesList();
                for( int c = 0; c < nbColumns; ++c )
                {
                    if( c != m_data.GetSubjectColumnId() )
                    {
                        m_data.AddCovariate( data.at( 0 ).at( c ) );
                    }
                }
                /// Intercept representes everything that has not been classified in one of the previous
                /// cavariates. It is important to add it as 1st element of m_covariatesList
                m_data.AddIntercept();
                for( int r = 1; r < nbRows; r++ )
                {
                    m_data.AddFileSubject( prefID, data.at( r ).at( m_data.GetSubjectColumnId() ) );
                }
            }
            else
            {
                if( m_data.GetFilePrefixList().contains( prefID ) )
                {
                    m_data.SetFileNbrRows( prefID ) = nbRows-1;
                    m_data.SetFileNbrColumns( prefID ) = nbColumns;
                    m_data.SetFileNbrSubjects( prefID ) = nbColumns-1;
                    for( int c = 1; c < nbColumns; c++ )
                    {
                        m_data.AddFileSubject( prefID, data.at( 0 ).at( c ) );
                    }
                }
            }
        }
        else
        {
            SetIcon( prefID, m_koPixmap );

            QString criticalText = tr( qPrintable( "Data file corrupted:<br><i>" + m_data.GetFilename( prefID ) + "</i><br>"
                    "For each row, the number of columns is not constant.<br>"
                    "We advise you to check your data file." ) );
            CriticalPopUp( criticalText );

            m_data.ClearFileInformation( prefID );
            return;
        }
    }

    /// Updates sent to m_infoDialog
//    m_infoDialog->ChangeFilenameMapValue( m_data.GetFilenameMap() );
//    m_infoDialog->ChangeCovariatesListValue( m_data.GetCovariatesList() );
//    m_infoDialog->ChangeFileNbrRowsMapValue( m_data.GetFileNbrRowsMap() );
//    m_infoDialog->ChangeFileNbrColumnsMapValue( m_data.GetFileNbrColumnsMap() );
//    m_infoDialog->ChangeFileNbrSubjectsMapValue( m_data.GetFileNbrSubjectsMap() );
    m_infoDialog->ChangeDataValue( m_data );
    SetCovariatesList();
    UpdateParamTab();
}

bool MainWindow::IsMatrixDimensionOK( const QList<QStringList> data )
{
    int strLSize = data.at( 0 ).count();
    foreach (QStringList strL,  data)
    {
        if( strLSize != strL.count() )
        {
            return false;

        }
    }
    return true;
}

void MainWindow::SetIcon( const QString prefID, const QPixmap icon )
{
    QLabel *label = m_inputTabIconLabelMap[ prefID ];
    label->setPixmap( icon.scaled( QSize( m_IconSize, m_IconSize ), Qt::IgnoreAspectRatio ) );
}

void MainWindow::SetInfoSubjectsColumnID()
{
    QString filePath = m_inputTabFilePathLineEditMap[ m_data.GetCovariatesFilePrefix() ]->text();
    if( !filePath.isEmpty() && QFile( filePath ).open( QIODevice::ReadOnly ) )
    {
        QFile( filePath ).close();
        m_mainUi->subjectColumnId_label->setText( tr( qPrintable( "<b><i><span style=""font-size:7pt;"">" +
                                                      QString::number( m_data.GetSubjectColumnId() + 1 ) + "<i/><b/><span/>") ) );
    }
    else
    {
        m_mainUi->subjectColumnId_label->clear();
    }
}

void  MainWindow::LaunchEditInputWindow( QString prefID )
{
    QString filepPath = m_inputTabFilePathLineEditMap[ prefID ]->text();
    m_editInputDialog->ChangeFilePrefixListValue( m_data.GetFilePrefixList() );
    m_editInputDialog->ChangePrefixValue( prefID );
    m_editInputDialog->ChangeFilePathInputValue( filepPath );
    m_editInputDialog->setModal( true );
    m_editInputDialog->setWindowTitle( tr( qPrintable( "Edit " + prefID + " File" ) ) );
    m_editInputDialog->DisplayData();
    m_editInputDialog->exec();
}


/****************************************************************/
/************************* Subjects tab *************************/
/****************************************************************/

/*********************** Public  function ***********************/


/***********************  Private slots  ************************/
void MainWindow::on_loadInputSubjectList_PushButton_clicked()
{
    QLineEdit *lineEdit = m_mainUi->para_inputSubjectList_lineEdit;
    QString filePath;
    QDir dir = QFileInfo( QFile( lineEdit->text() ) ).absolutePath();
    if( !dir.exists() || dir.dirName() == "." ) // Do we want it?
    {
        filePath = QFileDialog::getOpenFileName( this, tr( "Choose subject list file" ), m_currentSubjectsListInputDir, tr( ".txt( *.txt ) ;; .*( * )" ) );
    }
    else
    {
        filePath = QFileDialog::getOpenFileName( this, tr( "Choose subject list file" ), dir.absolutePath(), tr( ".txt ( *.txt ) ;; .*( * )" ) );
    }

    QFile importedTXT( filePath );
    if( !importedTXT.open( QIODevice::ReadOnly ) )
    {
        return;
    }
    else
    {
        importedTXT.close();
        lineEdit->setText( filePath );
    }
}

void MainWindow::on_reset_pushButton_clicked()
{
    m_mainUi->para_inputSubjectList_lineEdit->clear();
}

void MainWindow::on_para_inputSubjectList_lineEdit_textChanged( const QString& textLineEdit )
{
    if( !textLineEdit.isEmpty() )
    {
        UpdateCurrentDir( textLineEdit, m_currentSubjectsListInputDir );

    }

    SortSubjects();
}

void MainWindow::on_saveCheckedSubjectsList_pushButton_clicked()
{
    QString filePath = QFileDialog::getSaveFileName( this, tr( "Save subject list as ..." ), m_currentSubjectsListInputDir, tr( ".txt ( *.txt ) ;; .*( * )" ) );
    QFile exportedTXT( filePath );
    if( exportedTXT.open( QIODevice::WriteOnly ) )
    {
        QTextStream ts( &exportedTXT );
        for( int i = 0; i < m_sortedSubjectsListWidget->count(); i++ )
        {
            if( m_sortedSubjectsListWidget->item( i )->checkState() == Qt::Checked )
            {
                ts << m_sortedSubjectsListWidget->item( i )->text() <<  endl;
            }
        }
        exportedTXT.flush();
        exportedTXT.close();

        QString previousFilePath = m_mainUi->para_inputSubjectList_lineEdit->text();
        m_mainUi->para_inputSubjectList_lineEdit->setText( filePath );
        if( previousFilePath == filePath )
        {
            /// If filePath does not change, an update is needed to display the right subjects list
            SortSubjects();
        }
    }
}


void MainWindow::on_checkAllVisible_pushButton_clicked()
{
    QListWidget *list = m_sortedSubjectsListWidget;
    for( int i = 0; i < list->count(); i++ )
    {
        QListWidgetItem* current = list->item( i );
        if( !current->isHidden() && current->flags() == Qt::ItemIsEnabled )
        {
            current->setCheckState( Qt::Checked );
        }
    }
}

void MainWindow::on_unCheckAllVisible_pushButton_clicked()
{
    QListWidget *list = m_sortedSubjectsListWidget;
    for( int i = 0; i < list->count(); i++ )
    {
        QListWidgetItem* current = list->item( i );
        if( !current->isHidden() && current->flags() == Qt::ItemIsEnabled )
        {
            current->setCheckState( Qt::Unchecked );
        }
    }
}

void MainWindow::on_sortedSubjects_listWidget_itemClicked( QListWidgetItem *item )
{
    if( item->flags() == Qt::ItemIsEnabled )
    {
        if( item->checkState() == Qt::Unchecked )
        {
            item->setCheckState( Qt::Checked );
            item->setBackgroundColor( m_green );
        }
        else
        {
            if( item->checkState() == Qt::Checked )
            {
                item->setCheckState( Qt::Unchecked );
                item->setBackgroundColor( m_grey );
            }
        }
    }
}

void MainWindow::on_para_search_lineEdit_textEdited()
{
    Search();
}

void MainWindow::on_caseSensitive_checkBox_toggled( bool checked )
{
    if( checked )
    {
        caseSensitivity = Qt::CaseSensitive;
    }
    else
    {
        caseSensitivity = Qt::CaseInsensitive;
    }
    Search();
}


void MainWindow::SortSubjects()
{
    QFile subjectsListTXT( m_mainUi->para_inputSubjectList_lineEdit->text() );
    QStringList subjectsListRef = GetRefSubjectsList( subjectsListTXT );
    QMap<QString, QStringList> selectedSubjectList = GetAllSubjects();
    QMap< QString, QMap<QString, bool> > sortedSubjects = FindSubjectsInDataFile( subjectsListRef, selectedSubjectList );
    QStringList matchedSubjectsList;
    QMap<QString, QStringList > unMatchedSubjectsList;
    AssignSortedSubjects( sortedSubjects, matchedSubjectsList, unMatchedSubjectsList );
    DisplayFinalSubjectList( subjectsListRef, matchedSubjectsList, unMatchedSubjectsList );
    Search();
}


/*********************** Private function ***********************/
void MainWindow::UpdateParamTab()
{
    QString str;
    labelMapType::ConstIterator iterLabel = m_paramTabFileSizeLabelMap.begin();
    checkBoxMapType::ConstIterator iterCheckBox = m_paramTabFileCheckBoxMap.begin();
    while( iterLabel != m_paramTabFileSizeLabelMap.constEnd() )
    {
        int nbRows = m_data.GetFileNbrRows( iterCheckBox.key() );
        int nbColumns = m_data.GetFileNbrColumns( iterCheckBox.key() );
        if( ( nbRows == 0 ) || ( nbColumns == 0 ) )
        {
            str = tr( "N/A" );
            iterLabel.value()->setEnabled( false );
            iterCheckBox.value()->setCheckState( Qt::Unchecked );
            iterCheckBox.value()->setEnabled( false );
        }
        else
        {
            str = tr( qPrintable( QString::number( nbRows ) + "x" + QString::number( nbColumns ) ) );
            iterLabel.value()->setEnabled( true );
            iterCheckBox.value()->setCheckState( Qt::Checked );
            iterCheckBox.value()->setEnabled( true );
        }
        iterLabel.value()->setText( str );
        ++iterLabel;
        ++iterCheckBox;
    }
}

QStringList MainWindow::GetRefSubjectsList( QFile& refFile )
{  
    QStringList subjectsListRef;
    QLabel *label = m_mainUi->iconLoadList_label;
    if( !refFile.open( QIODevice::ReadOnly ) )
    {
        if( !refFile.fileName().isEmpty() )
        {
            SetIcon( label, m_koPixmap );
        }
        else
        {
            label->clear();
        }

        checkBoxMapType::ConstIterator iterPrefixCheckBox = m_paramTabFileCheckBoxMap.begin();
        QMap<QString, QStringList >::ConstIterator it = m_data.GetFilesSubjectsMapIterator();
        while( iterPrefixCheckBox != m_paramTabFileCheckBoxMap.constEnd() )
        {
            if( iterPrefixCheckBox.value()->isChecked() )
            {
                if( !it.value().isEmpty() )
                {
                    foreach( QString subject, it.value() )
                    {
                        if( !subjectsListRef.contains( subject ) )
                        {
                            subjectsListRef.append( subject );
                        }
                    }
                }
            }
            ++iterPrefixCheckBox;
            ++it;
        }
    }
    else
    {
        SetIcon( label, m_okPixmap );
        QTextStream ts( &refFile );
        while( !ts.atEnd() )
        {
            subjectsListRef.append( ts.readLine() );
        }
        refFile.close();
    }
    subjectsListRef.removeDuplicates();
    return subjectsListRef;
}

QMap<QString, QStringList> MainWindow::GetAllSubjects()
{
    QMap<QString, QStringList> selectedSubjectList;
    checkBoxMapType::ConstIterator iterPrefixCheckBox = m_paramTabFileCheckBoxMap.begin();
    QMap<QString, QStringList >::ConstIterator iterSubjectsList = m_data.GetFilesSubjectsMapIterator();
    while( iterPrefixCheckBox != m_paramTabFileCheckBoxMap.constEnd() )
    {
        if( iterPrefixCheckBox.value()->isChecked() )
        {
            ( selectedSubjectList[iterSubjectsList.key()] ).append( iterSubjectsList.value() );
        }
        ++iterPrefixCheckBox;
        ++iterSubjectsList;
    }

    return selectedSubjectList;
}

QMap< QString, QMap<QString, bool> > MainWindow::FindSubjectsInDataFile( const QStringList refList, const QMap<QString, QStringList> subjectsList )
{
    QMap< QString, QMap<QString, bool> > checkedSubjects;
    QStringListIterator itRef( refList );
    while( itRef.hasNext() )
    {
        QString subjRef = QString( itRef.next().toLocal8Bit().data() );

        QMap<QString, QStringList >::ConstIterator iterSubjectsList = subjectsList.begin();
        while( iterSubjectsList != subjectsList.constEnd() )
        {
            if( iterSubjectsList.value().contains( subjRef ) )
            {
                ( ( checkedSubjects[subjRef] )[iterSubjectsList.key()] ) = true;
            }
            else
            {
                ( ( checkedSubjects[subjRef] )[iterSubjectsList.key()] ) = false;
            }
            ++iterSubjectsList;
        }
    }
    return checkedSubjects;
}

void MainWindow::AssignSortedSubjects( const QMap< QString, QMap<QString, bool> > checkedSubjects, QStringList& matchedSubjectsList, QMap<QString, QStringList >& unMatchedSubjectsList )
{
    QMap< QString, QMap<QString, bool> >::ConstIterator iterCheckedSubjects = checkedSubjects.begin();
    while( iterCheckedSubjects != checkedSubjects.constEnd() )
    {
        bool subInAll = true;
        QMap<QString, bool>::ConstIterator it = iterCheckedSubjects.value().begin();
        while( it != iterCheckedSubjects.value().constEnd() )
        {
            subInAll = subInAll && it.value();
            ++it;
        }

        if( subInAll )
        {
            matchedSubjectsList.append( iterCheckedSubjects.key() );
        }
        else
        {
            QMap<QString, bool>::ConstIterator it = iterCheckedSubjects.value().begin();
            while( it != iterCheckedSubjects.value().constEnd() )
            {
                if( !it.value() && !( unMatchedSubjectsList[iterCheckedSubjects.key()] ).contains( "refList" )
                        && ( !m_mainUi->para_inputSubjectList_lineEdit->text().isEmpty() ) )
                {
                    ( unMatchedSubjectsList[iterCheckedSubjects.key()] ).append( tr( "refList" ) );
                }
                if( it.value() )
                {
                    ( unMatchedSubjectsList[iterCheckedSubjects.key()] ).append( it.key() );
                }
                ++it;
            }
        }
        ++iterCheckedSubjects;
    }
}

void MainWindow::DisplayFinalSubjectList( const QStringList subjectsListRef, const QStringList matchedSubjectsList, const QMap<QString, QStringList > unMatchedSubjectsList )
{
    m_sortedSubjectsListWidget->clear();
    m_sortedSubjectsListWidget->setUpdatesEnabled( false );
    m_sortedSubjectsListWidget->setSelectionMode( QAbstractItemView::NoSelection );

    QStringListIterator iterMatchedSubjectsList( matchedSubjectsList );
    while( iterMatchedSubjectsList.hasNext() )
    {
        QString text = QString( iterMatchedSubjectsList.next().toLocal8Bit().data() );
        QListWidgetItem *listItem = new QListWidgetItem( text, m_sortedSubjectsListWidget );
        listItem->setCheckState( Qt::Checked );
        listItem->setBackgroundColor( m_green );
        listItem->setFlags( Qt::ItemIsEnabled );
        m_sortedSubjectsListWidget->addItem( listItem );
    }

    QMap<QString, QStringList >::ConstIterator iterUnMatchedSubjectsList = unMatchedSubjectsList.begin();
    while( iterUnMatchedSubjectsList != unMatchedSubjectsList.constEnd() )
    {
        QStringList sortedText = iterUnMatchedSubjectsList.value();
        sortedText.sort();
        QString text = tr( qPrintable( iterUnMatchedSubjectsList.key() + " --> " + sortedText.join( ", " ) ) );
        QListWidgetItem *listItem = new QListWidgetItem( text, m_sortedSubjectsListWidget );
        listItem->setBackgroundColor( m_red );
        listItem->setTextColor( m_lightBlack );
        m_sortedSubjectsListWidget->addItem( listItem );
        ++iterUnMatchedSubjectsList;
    }
    m_sortedSubjectsListWidget->setUpdatesEnabled( true );

    m_mainUi->sortSubjects_label->clear();
    QString text;
    if( ( unMatchedSubjectsList.isEmpty() ) && ( !matchedSubjectsList.isEmpty() ) )
    {
        text = tr( qPrintable( "All subjects matched ( " + QString::number( matchedSubjectsList.size() ) + " )" ) );
    }
    else if( ( !unMatchedSubjectsList.isEmpty() ) && ( matchedSubjectsList.isEmpty() ) )
    {
        text = tr( qPrintable( "Warning! No subject matched ( " + QString::number( unMatchedSubjectsList.size() ) + " )" ) );
    }
    else if( !unMatchedSubjectsList.isEmpty() && ( !matchedSubjectsList.isEmpty() ) )
    {
        text = tr( qPrintable( QString::number( matchedSubjectsList.size() ) + "/" + QString::number( subjectsListRef.size() ) + " matched      " +
                QString::number( unMatchedSubjectsList.size() ) + "/" + QString::number( subjectsListRef.size() ) + " unmatched" ) );
    }
    //else both are empty
    m_mainUi->sortSubjects_label->setText( text );
}

void MainWindow::Search()
{
    QListWidget *list = m_sortedSubjectsListWidget;
    QLineEdit *lineEdit = m_mainUi->para_search_lineEdit;
    QString search_str = lineEdit->text();
    QPalette palette;
    if( !search_str.isEmpty() )
    {
        if(  list->count() != 0  )
        {
            search_str.prepend( "*" );
            search_str.append( "*" );
            QRegExp regExp( search_str );
            regExp.setPatternSyntax( QRegExp::Wildcard );
            regExp.setCaseSensitivity( caseSensitivity );
            for( int i = 0; i < list->count(); i++ )
            {
                QListWidgetItem* current = list->item( i );
                if( regExp.exactMatch( current->text() ) )
                {
                    current->setHidden( false );
                }
                else
                {
                    current->setHidden( true );
                }
            }
        }
        palette.setColor( QPalette::Base, m_yellow );
        lineEdit->setPalette( palette );
    }
    else
    {
        if( list->count() != 0 )
        {
            for( int i = 0; i < list->count(); i++ )
            {
                list->item( i )->setHidden( false );
            }

        }
        palette.setColor( QPalette::Base, Qt::white );
        lineEdit->setPalette( palette );
    }
}


/****************************************************************/
/************************ Parameters tab ************************/
/****************************************************************/

/*********************** Public  function ***********************/

/***********************  Private  slots  ***********************/
void MainWindow::on_covariates_listWidget_itemClicked( QListWidgetItem *item )
{
    if( item->flags() == Qt::ItemIsEnabled )
    {
        if( item->checkState() == Qt::Unchecked )
        {
            item->setCheckState( Qt::Checked );
        }
        else if( !item->text().contains( "Intercept" ) )
        {
            item->setCheckState( Qt::Unchecked );
        }
        else
        {            
            int ignoreWarning = QMessageBox::warning( this,
                                                      tr( "Uncheck Intercept" ),
                                                      tr( "You are about to uncheck the Intercept."
                                                          "This action is not recommended.<br>"
                                                          "Are you sure you want to do it?" ),
                                                      QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
            if( ignoreWarning == QMessageBox::Yes )
            {
                item->setCheckState( Qt::Unchecked );
            }
        }
    }
}

void MainWindow::on_covariatesCheckAll_pushButton_clicked()
{
    QListWidget *list = m_covariatesListWidget;
    for( int i = 0; i < list->count(); i++ )
    {
        list->item( i )->setCheckState( Qt::Checked );
    }
}

void MainWindow::on_covariatesUncheckAll_pushButton_clicked()
{
    QListWidget *list = m_covariatesListWidget;
    for( int i = 0; i < list->count(); i++ )
    {
        QListWidgetItem *currentItem = list->item( i );
        if( !currentItem->text().contains( "Intercept" ) )
        {
            currentItem->setCheckState( Qt::Unchecked );
        }
    }
}


/*********************** Private function ***********************/
void MainWindow::SetCovariatesList()
{
    m_covariatesListWidget->clear();
    if( !( m_data.GetCovariatesList().isEmpty() ) )
    {
        foreach( QString covar, m_data.GetCovariatesList() )
        {
            QListWidgetItem *listItem = new QListWidgetItem( covar, m_covariatesListWidget );
            listItem->setCheckState( Qt::Checked );
            listItem->setFlags( Qt::ItemIsEnabled );
            m_covariatesListWidget->addItem( listItem );
        }
    }
}


/****************************************************************/
/*************************** Run  tab ***************************/
/****************************************************************/

/*********************** Public  function ***********************/

/***********************  Private  slots  ***********************/
void MainWindow::on_run_pushButton_clicked()
{
    m_processing.ResetProcessing();

    QStringList finalInputFiles = GenerateFinalInputFiles();

    QString finalSubjectsListFilePath = GenerateFinalSubjectsList();

    QStringList srcFiles = m_processing.GenerateSrcFiles( finalInputFiles, finalSubjectsListFilePath,
                                                   m_data.GetSubjectColumnId(), m_data.GetOutputDir() );
}

/*********************** Private function ***********************/
QString MainWindow::GenerateFinalSubjectsList()
{
    QFile finalSubjects( m_data.GetOutputDir() + "/finalSubjectsList.txt" );
    if( finalSubjects.open( QIODevice::WriteOnly ) )
    {
        QTextStream tsFinalSubjects( &finalSubjects );
        for( int i = 0; i < m_sortedSubjectsListWidget->count(); i++ )
        {
            if( m_sortedSubjectsListWidget->item( i )->checkState() == Qt::Checked )
            {
                tsFinalSubjects << QObject::tr( qPrintable( m_sortedSubjectsListWidget->item( i )->text() ) ) << endl;
            }
        }
        finalSubjects.close();
    }
    return finalSubjects.fileName();
}

QStringList MainWindow::GenerateFinalInputFiles()
{
    QStringList finalInputFiles;
    foreach ( QString prefID, m_data.GetFilePrefixList() )
    {
        if( m_paramTabFileCheckBoxMap[ prefID ]->isChecked() )
        {
            finalInputFiles.append( m_data.GetFilename( prefID ) );
        }
    }
    return finalInputFiles;
}
