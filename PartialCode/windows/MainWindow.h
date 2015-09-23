#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "EditInputDialog.h"
#include "InfoDialog.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow( QWidget *parent = 0 );
    ~MainWindow();


private slots:
    /*************** Input Tab ***************/
    void on_inputAddDataFiles_pushButton_clicked();

    void on_inputInfo_pushButton_clicked();

    void on_outputDir_pushButton_clicked();

    void on_para_outputDir_lineEdit_textChanged( const QString& textLineEdit );


    void FilePathValue( const QString& newFilePath, const QString& prefID );

    void CovariatesValue( const QStringList& newCovariates );

    void SubjectColumnIdValue( const int& newSubjectColumnIdValue );

    void AddFile( const QString& );

    void EditFile( const QString& );

    void UpdateLineEdit( const QString& );


    /*************** Subjects Tab ***************/
    void on_loadInputSubjectList_PushButton_clicked();

    void on_reset_pushButton_clicked();

    void on_para_inputSubjectList_lineEdit_textChanged( const QString& textLineEdit );

    void on_saveCheckedSubjectsList_pushButton_clicked();


    void on_checkAllVisible_pushButton_clicked();

    void on_unCheckAllVisible_pushButton_clicked();

    void on_sortedSubjects_listWidget_itemClicked( QListWidgetItem *item );

    void on_para_search_lineEdit_textEdited();

    void on_caseSensitive_checkBox_toggled( bool checked );


    void SortSubjects();


    /************** Parameters  Tab **************/
    void on_covariates_listWidget_itemClicked( QListWidgetItem *item );

    void on_covariatesCheckAll_pushButton_clicked();

    void on_covariatesUncheckAll_pushButton_clicked();


private:
    Ui::MainWindow *m_mainUi;

    EditInputDialog *m_editInputDialog;

    InfoDialog *m_infoDialog;

    QListWidget *m_sortedSubjectsListWidget, *m_covariatesListWidget;

    typedef QMap<QString, QLabel*> labelMapType;
    labelMapType m_paramTabFileSizeLabelMap, m_inputTabIconLabelMap;

    typedef QMap<QString, QCheckBox*> checkBoxMapType;
    checkBoxMapType m_paramTabFileCheckBoxMap;

    typedef QMap<QString, QLineEdit*> lineEditMapType;
    lineEditMapType m_inputTabFilePathLineEditMap;

    typedef QMap<QString, QPushButton*> pushButtonMapType;
    pushButtonMapType m_inputTabAddFilePushButtonMap, m_inputTabEditFilePushButtonMap;

    QMap<QString, QStringList> m_filesSubjectsMap;

    QMap<QString, QString> m_filenameMap;

    QMap<QString, int> m_fileNbrRowsMap, m_fileNbrColumnsMap, m_fileNbrSubjectsMap;

    QStringList m_covariatesList, m_filePrefixList;

    QString m_csvSeparator,
    m_axialDiffusivityFilePrefix, m_radialDiffusivityFilePrefix,
    m_meanDiffusivityFilePrefix, m_fractionalAnisotropyPrefix, m_covariatesFilePrefix,
    m_currentFileInputDir, m_currentFileOutputDir, m_currentSubjectsListInputDir, m_currentSaveFileDir;

    int m_subjectColumnId, m_IconSize;

    QPixmap m_okPixmap;
    QPixmap m_koPixmap;
    QPixmap m_warningPixmap;

    QColor m_green;
    QColor m_red;
    QColor m_grey;
    QColor m_yellow;\
    QColor m_lightBlack;

    Qt::CaseSensitivity caseSensitivity;


    /***************** Other *****************/
    void Init();

    void InitGeneral();

    void InitInputTab();

    void InitSubjectTab();

    void InitParameterTab();

    void UpdateCurrentDirEditInputDialog(const QString newfilePath, QString& currentDir, EditInputDialog* editInputDialog  );

    QDir UpdateCurrentDir(const QString newfilePath, QString& currentDir );

    void WarningPopUp( const QString warningText );

    void CriticalPopUp( const QString criticalText );

    void SetIcon( QLabel *label , const QPixmap icon );


    /*************** Input Tab ***************/
    void AddFiles( const QStringList filesList );

    void UpdateFileInformation( const QString filePath, const QString prefID );

    bool IsMatrixDimensionOK( const QList<QStringList> data );

    void ClearFileInformation( const QString prefID );

    void SetIcon( const QString prefID , const QPixmap icon );

    void LaunchEditInputWindow( QString prefID );


    /*************** Subjects Tab ***************/
    void UpdateParamTab();

    QStringList GetRefSubjectsList( QFile& refFile );

    QMap<QString, QStringList> GetAllSubjects();

    QMap< QString, QMap<QString, bool> > FindSubjectsInDataFile( const QStringList refList, const QMap<QString, QStringList> subjectsList );

    void AssignSortedSubjects( const QMap< QString, QMap<QString, bool> > checkedSubjects, QStringList& matchedSubjectsList, QMap<QString, QStringList >& unMatchedSubjectsList );

    void DisplayFinalSubjectList( const QStringList subjectsListRef, const QStringList matchedSubjectsList, const QMap<QString, QStringList > unMatchedSubjectsList );

    void Search();


    /*************** Parameters Tab ***************/
    void SetCovariatesList();


    /*************** Test Functions ***************/

};

#endif // MAINWINDOW_H
