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

    void on_inputs_info_pushButton_clicked();

    void on_output_dir_pushButton_clicked();

private:
    Ui::MainWindow *mainUi;

    SetInput *inputDialog;
    Info *info;

    QStringList filesInfo;

    void initFilesInfo();
};

#endif // MAINWINDOW_H
