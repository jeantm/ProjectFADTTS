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

    void defaultInputPathMainWindowChanged(const QString&);


    // To Info
    void filesInfoChanged(const QStringList&);

    void filenameListChanged(const QMap<QString,QString>&);

    void fileCOMPListChanged(const QStringList&);

    void fileNbrRowsListChanged(const QMap<QString,int>&);

    void fileNbrColumnsListChanged(const QMap<QString,int>&);

    void fileNbrSubjectsListChanged(const QMap<QString,int>&);


    // To SubjectsList
    void defaultSubjectsListPathMainWindowChanged(const QString&);

    void fileDataSizeChanged(const QMap<QString,int>&, const QMap<QString,int>&);


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

    void on_load_inputSubjectList_PushButton_clicked();

    void on_save_checkedSubjectsList_pushButton_clicked();

    void on_para_inputSubjectList_lineEdit_textChanged();

    void on_match_subjectsList_pushButton_clicked();

    void on_para_search_lineEdit_textEdited();


    /************** Parameters  Tab **************/
    void setCOMPList();

    void on_covariatesCheckAll_pushButton_clicked();

    void on_covariatesUncheckAll_pushButton_clicked();




private:
    Ui::MainWindow *mainUi;

    SetInput *inputDialog;

    Info *info;

    QListWidget *matchedSubjectsListWidget, *covariatesListWidget;

    typedef QMap<QString, QLabel*> LabelMapType;
    LabelMapType dataSizeLabelMap;

    typedef QMap<QString, QCheckBox*> checkBoxMapType;
    checkBoxMapType fileCheckBoxMap;

    QMap<QString, QStringList> filesSubjectsList;

    QMap<QString, QString> filenameList;

    QMap<QString, int> fileNbrRowsList, fileNbrColumnsList,fileNbrSubjectsList;

    QStringList fileCOMPList;

    QString defaultInputPathMainWindow, defaultOutputPathMainWindow, defaultInputPathSubjectsList;




    /***************** Other *****************/
    void init();


    /*************** Input Tab ***************/
    void addFiles(QStringList files);

    void addFile(QLineEdit* & lineEdit);

    void editFile(QLineEdit* & lineEdit, QPushButton* & pushButton);

    void updateLineEdit(QLineEdit* & lineEdit, QPushButton *&pushButton);

    void updateFile(QString filePath, QString p);

    QString getPrefixPushButton(QPushButton* & pushButton);


    /*************** Subjects Tab ***************/
};

#endif // MAINWINDOW_H
