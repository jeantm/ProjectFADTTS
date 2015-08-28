#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QDir>
#include <QMap>
#include <QList>
#include <QTextCharFormat>
#include "setinput.h"
#include "info.h"
#include "subjectslist.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



signals:
    /*************** Input Tab ***************/

    // To SetInput
    void prefixChanged(const QString&);

    void filePathInputChanged(const QString&);

    void filePathSubjectsChanged(const QString&);

    void defaultInputPathMainWindowChanged(const QString&);

    void defaultInputPathSubjectsChanged(const QString&);

    // To Info
    void filesInfoChanged(const QStringList&);

    void filenameListChanged(const QStringList&);

    void fileCOMPListChanged(const QStringList&);

    void fileNbrRowsListChanged(const QList<int>&);

    void fileNbrColumnsListChanged(const QList<int>&);

    void fileNbrSubjectsListChanged(const QList<int>&);

    /*************** Subjects Tab ***************/

    void fileDataSizeChanged(const QList<int>&, const QList<int>&);

    // To SubjectsList
    void defaultSubjectsListPathMainWindowChanged(const QString&);


private slots:
    /*************** Input Tab ***************/
    void on_inputAllFiles_pushButton_clicked();

    void on_inputADfile_pushButton_clicked();

    void on_inputRDfile_pushButton_clicked();

    void on_inputMDfile_pushButton_clicked();

    void on_inputFAfile_pushButton_clicked();

    void on_inputCOMPfile_pushButton_clicked();


    void on_editInputADfile_pushButton_clicked();

    void on_editInputRDfile_pushButton_clicked();

    void on_editInputMDfile_pushButton_clicked();

    void on_editInputFAfile_pushButton_clicked();

    void on_editInputCOMPfile_pushButton_clicked();


    void on_para_inputADfile_lineEdit_textChanged();

    void on_para_inputRDfile_lineEdit_textChanged();

    void on_para_inputMDfile_lineEdit_textChanged();

    void on_para_inputFAfile_lineEdit_textChanged();

    void on_para_inputCOMPfile_lineEdit_textChanged();


    void on_inputs_info_pushButton_clicked();

    void on_output_dir_pushButton_clicked();


    /*************** Subjects Tab ***************/
    void fileDataSizeValue();

    void on_edit_inputSubjectList_lineEdit_clicked();

    void on_inputSubjectList_lineEdit_clicked();

    void on_para_inputSubjectList_lineEdit_textChanged();

    void on_create_subjectsListFrom_pushButton_clicked();

private:
    Ui::MainWindow *mainUi;

    SetInput *inputDialog;

    Info *info;

    SubjectsList *subjectsListDialog;

    QStringList filenameList;

    QStringList fileCOMPList;

    QList<int> fileNbrRowsList;

    QList<int> fileNbrColumnsList;

    QList<int> fileNbrSubjectsList;

    typedef QMap<int, QLabel*> FileDataMapType;
    QMap<int, QString> fileDataMap;

    typedef QMap<int, QLabel*> FileRowDataMapType;
    QMap<int, QString> fileRowDataMap;


    /*************** Input Tab ***************/
    QString defaultInputPathMainWindow, defaultOutputPathMainWindow;

    void init();

    void updateLineEdit(QLineEdit* & lineEdit, QPushButton *&pushButton, int i);

    void updateFile(QString filePath, QString p, int i);

    QString getPrefixPushButton(QPushButton* & pushButton);

    void addFiles(QStringList files);

    void addFile(QLineEdit* & lineEdit, QPushButton* & pushButton);

    void editFile(QLineEdit* & lineEdit, QPushButton* & pushButton);


    /*************** Subjects Tab ***************/
    QString defaultInputPathSubjectsList;

    typedef QMap<int, QLabel*> DataSizeLabelMapType;
    DataSizeLabelMapType dataSizeLabelMap;

    typedef QMap<int, QCheckBox*> FileCheckBoxMapType;
    FileCheckBoxMapType fileCheckBoxMap;

};

#endif // MAINWINDOW_H
