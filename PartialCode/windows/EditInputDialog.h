#ifndef EDITINPUTDIALOG_H
#define EDITINPUTDIALOG_H

#include <QtCore>
#include <QtGui>


namespace Ui {
class EditInputDialog;
}

class EditInputDialog : public QDialog
{
    Q_OBJECT
    


public:
    explicit EditInputDialog( QWidget *parent = 0 );
    ~EditInputDialog();

    void DisplayData();

    void ChangePrefixValue( const QString &newPrefix );

    void ChangeFilePrefixListValue( const QStringList &newFilePrefixList );

    void ChangeFilePathInputValue( const QString &newFilePathInput );

    void ChangeCurrentFileInputDirValue( const QString &newCurrentInputPathMainWindow );

    void SetcsvSeparator( const QString &csvSeparator );

    void ResetSubjectColumnId();


signals:
    void FilePathChanged( const QString&, const QString&  );

    void CovariatesChanged( const QStringList&  );

    void SubjectColumnIdChanged( const int& );


private slots:
    void on_deleteRows_pushButton_clicked();

    void on_deleteColumns_pushButton_clicked();

    void on_para_subjectsColumn_spinBox_valueChanged( int idColumn );

    void on_saveFile_pushButton_clicked();


private:
    Ui::EditInputDialog *m_ui;

    QTableWidget *m_dataTableWidget;

    QString m_prefixExpected, m_currentPathSetInput, m_filePathInput, m_filename, m_csvSeparator, m_covariatesFilePrefix;

    QStringList m_covariates, m_filePrefixList;

    bool m_rowDeleted, m_columnDeleted, m_isCOMP;

    int m_subjectColumnId;

    void Init();



    void IsCOMPFile( const QStringList strList );

    void UploadData();

    void RefreshFileInfo();

    bool SaveCSVFile();

    void ResetTableWidget();

    void closeEvent( QCloseEvent *event );
};

#endif // SETINPUT_H
