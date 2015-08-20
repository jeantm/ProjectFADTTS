#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mainUi(new Ui::MainWindow)
{
    mainUi->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete mainUi;
}

QStringList MainWindow::getFiles()
{
    return files;
}

void MainWindow::on_inputADfile_pushButton_clicked()
{
    SetInput setADfile;
    setADfile.setModal(true);
    setADfile.exec();
    QString adFile = setADfile.getFilenameLineEdit();
    mainUi->para_inputADfile_lineEdit->setText(adFile);
    files[0]=adFile;
}

void MainWindow::on_inputRDfile_pushButton_clicked()
{
    SetInput setRDfile;
    setRDfile.setModal(true);
    setRDfile.exec();
    QString rdFile = setRDfile.getFilenameLineEdit();
    mainUi->para_inputRDfile_lineEdit->setText(rdFile);
    files[1]=rdFile;
}

void MainWindow::on_inputMDfile_pushButton_clicked()
{
    SetInput setMDfile;
    setMDfile.setModal(true);
    setMDfile.exec();
    QString mdFile = setMDfile.getFilenameLineEdit();
    mainUi->para_inputMDfile_lineEdit->setText(mdFile);
    files[2]=mdFile;
}

void MainWindow::on_inputFAfile_pushButton_clicked()
{
    SetInput setFAfile;
    setFAfile.setModal(true);
    setFAfile.exec();
    QString faFile = setFAfile.getFilenameLineEdit();
    mainUi->para_inputFAfile_lineEdit->setText(faFile);
    files[3]=faFile;
}

void MainWindow::on_inputCovariatesfile_pushButton_clicked()
{
    SetInput setCovariatesfile;
    setCovariatesfile.setModal(true);
    setCovariatesfile.exec();
    QString covariatesFile = setCovariatesfile.getFilenameLineEdit();
    mainUi->para_inputCovariatesfilelineEdit->setText(covariatesFile);
    files[4]=covariatesFile;
}

void MainWindow::on_inputs_info_pushButton_clicked()
{
    Info info;
    info.setModal(true);
    info.getInfo(files);
    info.exec();

    /*info = new Info(this);
    info->getInfo();
    info->show();*/
}

void MainWindow::on_output_dir_pushButton_clicked()
{

}


