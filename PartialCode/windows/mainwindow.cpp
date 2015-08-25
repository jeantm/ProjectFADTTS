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
    //QObject::connect(inputDialog, SIGNAL(filePathChanged(QString)), this, SLOT(filePathValue(QString)));

}

MainWindow::~MainWindow()
{
    delete mainUi;
}

/************ Public functions *************/


/************ Private slots ************/
void MainWindow::on_inputAllFiles_pushButton_clicked()
{
    QString path = "/work/jeantm/FADTTS/Project/DataTest";
    QStringList files;
    files = QFileDialog::getOpenFileNames (this, "Open CSV file", path, "CSV (*.csv)");
    qDebug() << files;
    int findADFile = 0;
    int findRDFile = 0;
    int findMDFile = 0;
    int findFAFile = 0;
    int findCovariatesFile = 0;
    QString ADFile, RDFile, MDFile, FAFile, CovariatesFile;
    foreach(QString f, files)
    {
        qDebug() << f;
        QString prefix = f.split('/').last().split('_').first();
        qDebug() << prefix;
        if(prefix == "ad")
        {
            findADFile++;
            if(findADFile == 1)
            {
                ADFile = f;
            }
            else
            {
                ADFile ="";
            }
        }
        if(prefix == "rd")
        {
            findRDFile++;
            if(findRDFile == 1)
            {
                RDFile = f;
            }
            else
            {
                RDFile ="";
            }
        }
        if(prefix == "md")
        {
            findMDFile++;
            if(findMDFile == 1)
            {
                MDFile = f;
            }
            else
            {
                MDFile ="";
            }
        }
        if(prefix == "fa")
        {
            findFAFile++;
            if(findFAFile == 1)
            {
                FAFile = f;
            }
            else
            {
                FAFile ="";
            }
        }
        if(prefix == "COMP")
        {
            findCovariatesFile++;
            if(findCovariatesFile == 1)
            {
                CovariatesFile = f;
            }
            else
            {
                CovariatesFile ="";
            }
        }
    }

    setLineEdits(ADFile, RDFile, MDFile, FAFile, CovariatesFile);
}

void MainWindow::on_inputADfile_pushButton_clicked()
{
    setInputLineEdit(this, mainUi->para_inputADfile_lineEdit, mainUi->inputADfile_pushButton);
}

void MainWindow::on_inputRDfile_pushButton_clicked()
{
    setInputLineEdit(this, mainUi->para_inputRDfile_lineEdit, mainUi->inputRDfile_pushButton);
}

void MainWindow::on_inputMDfile_pushButton_clicked()
{
    setInputLineEdit(this, mainUi->para_inputMDfile_lineEdit, mainUi->inputMDfile_pushButton);
}

void MainWindow::on_inputFAfile_pushButton_clicked()
{
    setInputLineEdit(this, mainUi->para_inputFAfile_lineEdit, mainUi->inputFAfile_pushButton);
}

void MainWindow::on_inputCovariatesfile_pushButton_clicked()
{
    setInputLineEdit(this, mainUi->para_inputCovariatesfile_lineEdit, mainUi->inputCovariatesfile_pushButton);
}


void MainWindow::on_editInputADfile_pushButton_clicked()
{
    setInputDialog(mainUi->para_inputADfile_lineEdit, mainUi->inputADfile_pushButton, 0);
}

void MainWindow::on_editInputRDfile_pushButton_clicked()
{
    setInputDialog(mainUi->para_inputRDfile_lineEdit, mainUi->inputRDfile_pushButton, 1);
}

void MainWindow::on_editInputMDfile_pushButton_clicked()
{
    setInputDialog(mainUi->para_inputMDfile_lineEdit, mainUi->inputMDfile_pushButton, 2);
}

void MainWindow::on_editInputFAfile_pushButton_clicked()
{
    setInputDialog(mainUi->para_inputFAfile_lineEdit, mainUi->inputFAfile_pushButton, 3);
}

void MainWindow::on_editInputCovariatesfile_pushButton_clicked()
{
    setInputDialog(mainUi->para_inputCovariatesfile_lineEdit, mainUi->inputCovariatesfile_pushButton, 4);
}


void MainWindow::on_para_inputADfile_lineEdit_textChanged()
{
    emitToInputDialog(mainUi->para_inputADfile_lineEdit, mainUi->inputADfile_pushButton);
}

void MainWindow::on_para_inputRDfile_lineEdit_textChanged()
{
    emitToInputDialog(mainUi->para_inputRDfile_lineEdit, mainUi->inputRDfile_pushButton);
}

void MainWindow::on_para_inputMDfile_lineEdit_textChanged()
{
    emitToInputDialog(mainUi->para_inputMDfile_lineEdit, mainUi->inputMDfile_pushButton);
}

void MainWindow::on_para_inputFAfile_lineEdit_textChanged()
{
    emitToInputDialog(mainUi->para_inputFAfile_lineEdit, mainUi->inputFAfile_pushButton);
}

void MainWindow::on_para_inputCovariatesfile_lineEdit_textChanged()
{
    emitToInputDialog(mainUi->para_inputCovariatesfile_lineEdit, mainUi->inputCovariatesfile_pushButton);
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


/************ Private functions ************/
void MainWindow::initFilesInfo()
{
    QStringList pref;
    pref << "ad" << "rd" << "md" << "fa" << "COMP";
    for(int i = 0; i < 5; i++)
    {
        filesInfo.insert(i,"<center><b>No File Information<br>Please select a correct data file</b><br>"
                         "(Prefix must be <b>" + pref.at(i) + "_</b>)</center>");
    }
}

void MainWindow::setInputLineEdit(MainWindow * parent, QLineEdit* & lineEdit, QPushButton* & pushButton)
{
    QString defaultPath = "/work/jeantm/FADTTS/Project/DataTest";
    QString filePath;
    if( lineEdit->text().compare("") == 0 )
    {
        filePath = QFileDialog::getOpenFileName (parent, "Open CSV file", defaultPath, "CSV (*.csv)");
    }
    else
    {
        filePath = QFileDialog::getOpenFileName (parent, "Open CSV file", lineEdit->text(), "CSV (*.csv)");
    }
    QFile importedCSV(filePath);
    QFileInfo fInfo(importedCSV.fileName());
    QString filename = (fInfo.fileName());
    QString prefix = filename.split('_').first();
    QString p = pushButton->text().split(" ").first();
    if (p == "Covariates")
    {
        p = "COMP";
    }
    if(QString::compare(p, prefix, Qt::CaseInsensitive) != 0)
    {
        lineEdit->setText( "" );
        return;
    }
    else
    {
        if( !importedCSV.open( QIODevice::ReadOnly ) )
        {
            qDebug() << "MainWindow LineEdit PushButton: Could not open the file";
            lineEdit->setText( "" );
            return;
        }
        else
        {
            importedCSV.close();
            lineEdit->setText( filePath );
        }
    }
}

void MainWindow::setInputDialog(QLineEdit* & lineEdit, QPushButton* & pushButton, int i)
{
    QString newPrefix = pushButton->text().split(" ").first();
    if (newPrefix == "Covariates")
    {
        newPrefix = "COMP";
    }
    QString newFilePath = lineEdit->text();
    emit prefixChanged(newPrefix);
    emit filePathChanged(newFilePath);

    inputDialog->setModal(true);
    inputDialog->loadData();


    inputDialog->exec();
    QString adFile = inputDialog->getFilenameLineEdit();
    //filesInfo.insert(i,inputDialog->displayFileInfo(adFile));
    qDebug() << adFile;
    lineEdit->setText(adFile);

}

void MainWindow::emitToInputDialog(QLineEdit* & lineEdit, QPushButton* & pushButton)
{
    QString newPrefix = pushButton->text().split(" ").first();
    if (newPrefix == "Covariates")
    {
        newPrefix = "COMP";
    }
    QString newFilePath = lineEdit->text();
    emit prefixChanged(newPrefix);
    emit filePathChanged(newFilePath);
}


void MainWindow::setLineEdits(QString ADFile, QString RDFile, QString MDFile, QString FAFile, QString CovariatesFile)
{
    mainUi->para_inputADfile_lineEdit->setText(ADFile);
    mainUi->para_inputRDfile_lineEdit->setText(RDFile);
    mainUi->para_inputMDfile_lineEdit->setText(MDFile);
    mainUi->para_inputFAfile_lineEdit->setText(FAFile);
    mainUi->para_inputCovariatesfile_lineEdit->setText(CovariatesFile);
}
