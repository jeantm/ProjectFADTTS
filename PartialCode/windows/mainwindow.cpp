#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mainUi(new Ui::MainWindow)
{
    mainUi->setupUi(this);

    inputDialog = new SetInput;
    info = new Info;

    QObject::connect(this, SIGNAL(prefixChanged(QString)), inputDialog, SLOT(prefixValue(QString)));
    QObject::connect(this, SIGNAL(filePathChanged(QString)), inputDialog, SLOT(filePathValue(QString)));

}

MainWindow::~MainWindow()
{
    delete mainUi;
}

/************ Public functions *************/

/************ Private functions ************/
void MainWindow::on_inputADfile_pushButton_clicked()
{
    QString newPrefix = mainUi->inputADfile_pushButton->text().split(" ").first();
    QString newFilePath = mainUi->para_inputADfile_lineEdit->text();
    emit prefixChanged(newPrefix);
    emit filePathChanged(newFilePath);

    inputDialog->setModal(true);
    inputDialog->exec();
    QString adFile = inputDialog->getFilenameLineEdit();
    filesInfo.insert(0,inputDialog->displayFileInfo(adFile));
    mainUi->para_inputADfile_lineEdit->setText(adFile);
}

void MainWindow::on_inputRDfile_pushButton_clicked()
{
    QString newPrefix = mainUi->inputRDfile_pushButton->text().split(" ").first();
    QString newFilePath = mainUi->para_inputRDfile_lineEdit->text();
    emit prefixChanged(newPrefix);
    emit filePathChanged(newFilePath);

    inputDialog->setModal(true);
    inputDialog->exec();
    QString rdFile = inputDialog->getFilenameLineEdit();
    filesInfo.insert(1,inputDialog->displayFileInfo(rdFile));
    mainUi->para_inputRDfile_lineEdit->setText(rdFile);
}

void MainWindow::on_inputMDfile_pushButton_clicked()
{
    QString newPrefix = mainUi->inputMDfile_pushButton->text().split(" ").first();
    QString newFilePath = mainUi->para_inputMDfile_lineEdit->text();
    emit prefixChanged(newPrefix);
    emit filePathChanged(newFilePath);

    inputDialog->setModal(true);
    inputDialog->exec();
    QString mdFile = inputDialog->getFilenameLineEdit();
    filesInfo.insert(2,inputDialog->displayFileInfo(mdFile));
    mainUi->para_inputMDfile_lineEdit->setText(mdFile);
}

void MainWindow::on_inputFAfile_pushButton_clicked()
{
    QString newPrefix = mainUi->inputFAfile_pushButton->text().split(" ").first();
    QString newFilePath = mainUi->para_inputFAfile_lineEdit->text();
    emit prefixChanged(newPrefix);
    emit filePathChanged(newFilePath);

    inputDialog->setModal(true);
    inputDialog->exec();
    QString faFile = inputDialog->getFilenameLineEdit();
    filesInfo.insert(3,inputDialog->displayFileInfo(faFile));
    mainUi->para_inputFAfile_lineEdit->setText(faFile);
}

void MainWindow::on_inputCovariatesfile_pushButton_clicked()
{
    QString newPrefix = mainUi->inputCovariatesfile_pushButton->text().split(" ").first();
    QString newFilePath = mainUi->para_inputCovariatesfile_lineEdit->text();
    emit prefixChanged(newPrefix);
    emit filePathChanged(newFilePath);

    inputDialog->setModal(true);
    inputDialog->exec();
    QString covariatesFile = inputDialog->getFilenameLineEdit();
    filesInfo.insert(4,inputDialog->displayFileInfo(covariatesFile));
    mainUi->para_inputCovariatesfile_lineEdit->setText(covariatesFile);
}

void MainWindow::on_inputs_info_pushButton_clicked()
{
    if( filesInfo.isEmpty() )
    {
        initFilesInfo();
    }
    info->setModal(true);
    info->displayInfo(filesInfo);
    info->exec();
}

void MainWindow::on_output_dir_pushButton_clicked()
{
    QString defaultPath = "/work/jeantm/FADTTS/Project/DataTest";
    QString dirPath;
    if( mainUi->para_output_dir_lineEdit->text().compare("") == 0 )
    {
        dirPath = QFileDialog::getExistingDirectory(this, tr("Open Directory"), defaultPath, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    }
    else
    {
        dirPath = QFileDialog::getExistingDirectory(this, tr("Open Directory"), mainUi->para_output_dir_lineEdit->text(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    }
    mainUi->para_output_dir_lineEdit->setText( dirPath );
}

void MainWindow::initFilesInfo()
{
    QStringList pref;
    pref << "ad" << "rd" << "md" << "fa" << "COMP";
    for(int i = 0; i < 5; i++)
    {
        filesInfo.insert(i,"<center><b>No File Information<br>Please select a correct data file</b><br>"
                         "(Prefix must be " + pref.at(i) + "_)</center>");
    }
}

