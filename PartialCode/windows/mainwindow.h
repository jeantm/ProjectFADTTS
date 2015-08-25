#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QDir>
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
     void prefixChanged(const QString&);

     void filePathChanged(const QString&);
    
private slots:
    void on_inputADfile_pushButton_clicked();

    void on_inputRDfile_pushButton_clicked();

    void on_inputMDfile_pushButton_clicked();

    void on_inputFAfile_pushButton_clicked();

    void on_inputCovariatesfile_pushButton_clicked();

    void on_editInputADfile_pushButton_clicked();

    void on_editInputRDfile_pushButton_clicked();

    void on_editInputMDfile_pushButton_clicked();

    void on_editInputFAfile_pushButton_clicked();

    void on_editInputCovariatesfile_pushButton_clicked();

    void on_para_inputADfile_lineEdit_textChanged();

    void on_para_inputRDfile_lineEdit_textChanged();

    void on_para_inputMDfile_lineEdit_textChanged();

    void on_para_inputFAfile_lineEdit_textChanged();

    void on_para_inputCovariatesfile_lineEdit_textChanged();

    void on_inputs_info_pushButton_clicked();

    void on_output_dir_pushButton_clicked();

    void on_inputAllFiles_pushButton_clicked();

private:
    Ui::MainWindow *mainUi;

    SetInput *inputDialog;
    Info *info;

    QStringList filesInfo;

    void initFilesInfo();

    void setInputLineEdit(MainWindow * parent, QLineEdit* & lineEdit, QPushButton* & pushButton);

    void setInputDialog( QLineEdit* & lineEdit, QPushButton* & pushButton, int i);

    void emitToInputDialog(QLineEdit* & lineEdit, QPushButton* & pushButton);

    void setLineEdits(QString ADFile, QString RDFile, QString MDFile, QString FAFile, QString CovariatesFile);
};

#endif // MAINWINDOW_H
