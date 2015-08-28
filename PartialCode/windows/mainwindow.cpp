#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mainUi(new Ui::MainWindow)
{
    mainUi->setupUi(this);

    inputDialog = new SetInput;
    info = new Info;
    subjectsListDialog = new SubjectsList;

    // Signal/Slot links within MainWindow/Input
    QObject::connect(this, SIGNAL(fileDataSizeChanged(QList<int>,QList<int>)), this, SLOT(fileDataSizeValue()));

    // Signal/Slot links with MainWindow/SubjectsList
    QObject::connect(this, SIGNAL(filePathSubjectsChanged(QString)), subjectsListDialog, SLOT(filePathSubjectsValue(QString)));
    QObject::connect(this, SIGNAL(defaultInputPathSubjectsChanged(QString)), subjectsListDialog, SLOT(defaultInputPathSubjectsValue(QString)));

    // Signal/Slot links with SetInput
    QObject::connect(this, SIGNAL(prefixChanged(QString)), inputDialog, SLOT(prefixValue(QString)));
    QObject::connect(this, SIGNAL(filePathInputChanged(QString)), inputDialog, SLOT(filePathInputValue(QString)));
    QObject::connect(this, SIGNAL(defaultInputPathMainWindowChanged(QString)), inputDialog, SLOT(defaultInputPathMainWindowValue(QString)));


    // Signal/Slot links with Info
    QObject::connect(this, SIGNAL(filenameListChanged(QStringList)), info, SLOT(filenameListValue(QStringList)));
    QObject::connect(this, SIGNAL(fileCOMPListChanged(QStringList)), info, SLOT(fileCOMPListValue(QStringList)));
    QObject::connect(this, SIGNAL(fileNbrRowsListChanged(QList<int>)), info, SLOT(fileNbrRowsListValue(QList<int>)));
    QObject::connect(this, SIGNAL(fileNbrColumnsListChanged(QList<int>)), info, SLOT(fileNbrColumnsListValue(QList<int>)));
    QObject::connect(this, SIGNAL(fileNbrSubjectsListChanged(QList<int>)), info, SLOT(fileNbrSubjectsListValue(QList<int>)));

    init();
}

MainWindow::~MainWindow()
{
    delete mainUi;
}


/***************************************************************/
/**************************** Other ****************************/
/***************************************************************/

/*************** Public function ***************/


/**************** Private slots *****************/
void MainWindow::init()
{
    // Init Input tab
    fileCOMPList.push_back("");
    for(int i = 0; i < 5; i++)
    {
        filenameList.insert(i,"");
        fileNbrRowsList.insert(i,0);
        fileNbrColumnsList.insert(i,0);
        fileNbrSubjectsList.insert(i,0);
        fileDataMap.insert(i,"");
        fileRowDataMap.insert(i,"");
    }

    defaultInputPathMainWindow = "/work/jeantm/FADTTS/Project/DataTest";
    defaultOutputPathMainWindow = "/work/jeantm/FADTTS/Project/DataTest";


    // Init Subjects tab

    /*QHBoxLayout* hlayout_data = new QHBoxLayout();
    mainUi->verticalLayout_data->addLayout(hlayout_data);

    for (label in labels){
        QLabel* label1 = new QLabel();
        label1->setText("ad");
        hlayout_data->addWidget(label1);

        dataSizeLabelMap[key] = label1;
    }*/

    fileCheckBoxMap.insert(0,mainUi->para_adData_checkBox);
    fileCheckBoxMap.insert(1,mainUi->para_rdData_checkBox);
    fileCheckBoxMap.insert(2,mainUi->para_mdData_checkBox);
    fileCheckBoxMap.insert(3,mainUi->para_faData_checkBox);
    fileCheckBoxMap.insert(4,mainUi->para_compData_checkBox);

    dataSizeLabelMap.insert(0,mainUi->adDataSize_label);
    dataSizeLabelMap.insert(1,mainUi->rdDataSize_label);
    dataSizeLabelMap.insert(2,mainUi->mdDataSize_label);
    dataSizeLabelMap.insert(3,mainUi->faDataSize_label);
    dataSizeLabelMap.insert(4,mainUi->compDataSize_label);


    DataSizeLabelMapType::ConstIterator iterLabel = dataSizeLabelMap.begin();
    FileCheckBoxMapType::ConstIterator iterCheckBox = fileCheckBoxMap.begin();
    while(iterLabel != dataSizeLabelMap.constEnd())
    {
        iterLabel.value()->setText("Data unavailable");
        iterLabel.value()->setEnabled(false);
        iterCheckBox.value()->setCheckState(Qt::Unchecked);
        iterCheckBox.value()->setEnabled(false);
        ++iterLabel;
        ++iterCheckBox;
    }

    defaultInputPathSubjectsList = "/work/jeantm/FADTTS/Project/DataTest";

    // Emission Signals
    emit filenameListChanged( filenameList );
    emit fileCOMPListChanged( fileCOMPList );
    emit fileNbrRowsListChanged( fileNbrRowsList );
    emit fileNbrColumnsListChanged( fileNbrColumnsList );
    emit fileNbrSubjectsListChanged( fileNbrSubjectsList );
}


/*************** Private function ***************/



/****************************************************************/
/************************** Input  tab **************************/
/****************************************************************/

/*************** Public function ***************/


/**************** Private slots *****************/
void MainWindow::on_inputAllFiles_pushButton_clicked()
{
    QString path = defaultInputPathMainWindow;
    QStringList files;
    files = QFileDialog::getOpenFileNames (this, "Open CSV file", path, "CSV (*.csv)");
    addFiles(files);

    // Update default path
    if( !files.isEmpty() )
    {
        QString filePath = files.at(0);
        QStringList strL =  filePath.split("/");
        strL.removeLast();
        QDir dir = strL.join("/");
        if( dir.exists() && dir.dirName() != ".")
        {
            defaultInputPathMainWindow = dir.absolutePath();
            emit defaultInputPathMainWindowChanged( dir.absolutePath() );
        }
    }
}

void MainWindow::on_inputADfile_pushButton_clicked()
{
    addFile(mainUi->para_inputADfile_lineEdit, mainUi->inputADfile_pushButton);
}

void MainWindow::on_inputRDfile_pushButton_clicked()
{
    addFile(mainUi->para_inputRDfile_lineEdit, mainUi->inputRDfile_pushButton);
}

void MainWindow::on_inputMDfile_pushButton_clicked()
{
    addFile(mainUi->para_inputMDfile_lineEdit, mainUi->inputMDfile_pushButton);
}

void MainWindow::on_inputFAfile_pushButton_clicked()
{
    addFile(mainUi->para_inputFAfile_lineEdit, mainUi->inputFAfile_pushButton);
}

void MainWindow::on_inputCOMPfile_pushButton_clicked()
{
    addFile(mainUi->para_inputCOMPfile_lineEdit, mainUi->inputCOMPfile_pushButton);
}


void MainWindow::on_editInputADfile_pushButton_clicked()
{
    editFile(mainUi->para_inputADfile_lineEdit, mainUi->inputADfile_pushButton);
}

void MainWindow::on_editInputRDfile_pushButton_clicked()
{
    editFile(mainUi->para_inputRDfile_lineEdit, mainUi->inputRDfile_pushButton);
}

void MainWindow::on_editInputMDfile_pushButton_clicked()
{
    editFile(mainUi->para_inputMDfile_lineEdit, mainUi->inputMDfile_pushButton);
}

void MainWindow::on_editInputFAfile_pushButton_clicked()
{
    editFile(mainUi->para_inputFAfile_lineEdit, mainUi->inputFAfile_pushButton);
}

void MainWindow::on_editInputCOMPfile_pushButton_clicked()
{
    editFile(mainUi->para_inputCOMPfile_lineEdit, mainUi->inputCOMPfile_pushButton);
}


void MainWindow::on_para_inputADfile_lineEdit_textChanged()
{
    updateLineEdit(mainUi->para_inputADfile_lineEdit, mainUi->inputADfile_pushButton, 0);
}

void MainWindow::on_para_inputRDfile_lineEdit_textChanged()
{
    updateLineEdit(mainUi->para_inputRDfile_lineEdit, mainUi->inputRDfile_pushButton, 1);
}

void MainWindow::on_para_inputMDfile_lineEdit_textChanged()
{
    updateLineEdit(mainUi->para_inputMDfile_lineEdit, mainUi->inputMDfile_pushButton, 2);
}

void MainWindow::on_para_inputFAfile_lineEdit_textChanged()
{
    updateLineEdit(mainUi->para_inputFAfile_lineEdit, mainUi->inputFAfile_pushButton, 3);
}

void MainWindow::on_para_inputCOMPfile_lineEdit_textChanged()
{
    updateLineEdit(mainUi->para_inputCOMPfile_lineEdit, mainUi->inputCOMPfile_pushButton, 4);
}


void MainWindow::on_inputs_info_pushButton_clicked()
{
    info->setModal(true);
    info->displayInfo();
    info->exec();
}

void MainWindow::on_output_dir_pushButton_clicked()
{
    QString filePath = mainUi->para_output_dir_lineEdit->text();
    QDir dir = filePath;
    QString dirPath;
    if( dir.exists() && dir.dirName() != "." )
    {
        dirPath = QFileDialog::getExistingDirectory(this, tr("Open Directory"), dir.absolutePath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    }
    else
    {
        dirPath = QFileDialog::getExistingDirectory(this, tr("Open Directory"), defaultOutputPathMainWindow, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    }
    if(dirPath != "")
    {
        defaultOutputPathMainWindow = dirPath;
        mainUi->para_output_dir_lineEdit->setText( dirPath );
    }
}


/*************** Private function ***************/
void MainWindow::updateLineEdit(QLineEdit* & lineEdit, QPushButton* & pushButton, int i)
{
    QString filePath = lineEdit->text();
    QStringList strL =  filePath.split("/");
    strL.removeLast();
    QDir dir = strL.join("/");
    if( dir.exists() && dir.dirName() != ".")
    {
        defaultInputPathMainWindow = dir.absolutePath();
        emit defaultInputPathMainWindowChanged( dir.absolutePath() );
    }

    QString prefix = getPrefixPushButton(pushButton);
    updateFile( filePath, prefix, i );
}

void MainWindow::updateFile(QString filePath, QString p, int i)
{
    QFile file(filePath);
    if( !file.open( QIODevice::ReadOnly ) )
    {
        filenameList.removeAt(i);
        fileNbrRowsList.removeAt(i);
        fileNbrColumnsList.removeAt(i);
        fileNbrSubjectsList.removeAt(i);
        filenameList.insert(i,"");
        fileNbrRowsList.insert(i,0);
        fileNbrColumnsList.insert(i,0);
        fileNbrSubjectsList.insert(i,0);
        if(p == "COMP")
        {
            fileCOMPList.clear();
            fileCOMPList.insert(0,"");
        }
        qDebug() << "File info, getFileInfo(): Could not open the file";
    }
    else
    {
        QFileInfo fInfo(file.fileName());
        QString prefix = fInfo.fileName().split("/").last().split('_').first();
        if(QString::compare(p, prefix, Qt::CaseInsensitive) == 0)
        {
            QTextStream ts( &file );
            QList<QStringList> list;
            while( !ts.atEnd() )
            {
                list << ts.readLine().split( "," );
            }
            file.close();
            int nbRows = list.count();
            int nbColumns = list[0].count();
            filenameList.removeAt(i);
            filenameList.insert(i,filePath);

            if ( prefix == "COMP")
            {
                fileNbrRowsList.removeAt(i);
                fileNbrRowsList.insert(i,nbRows-1);
                fileNbrColumnsList.removeAt(i);
                fileNbrColumnsList.insert(i,nbColumns-1);
                fileNbrSubjectsList.removeAt(i);
                fileNbrSubjectsList.insert(i,nbRows-1);
                for( int c = 1; c < nbColumns; ++c )
                {
                    fileCOMPList.removeAt(c-1);
                    fileCOMPList.insert(c-1,list[0].at(c));
                }
            }
            else
            {
                if ( prefix == "ad" || prefix == "rd" || prefix == "md" || prefix == "fa" )
                {
                    fileNbrRowsList.removeAt(i);
                    fileNbrRowsList.insert(i,nbRows);
                    fileNbrColumnsList.removeAt(i);
                    fileNbrColumnsList.insert(i,nbColumns-1);
                    fileNbrSubjectsList.removeAt(i);
                    fileNbrSubjectsList.insert(i,nbColumns-1);
                }
            }
        }
    }
    emit filenameListChanged( filenameList );
    emit fileCOMPListChanged( fileCOMPList );
    emit fileNbrRowsListChanged( fileNbrRowsList );
    emit fileNbrColumnsListChanged( fileNbrColumnsList );
    emit fileNbrSubjectsListChanged( fileNbrSubjectsList );
    emit fileDataSizeChanged(fileNbrRowsList, fileNbrColumnsList);
}

QString MainWindow::getPrefixPushButton(QPushButton* & pushButton)
{
    QString prefixPushButton = pushButton->text().split(" ").at(1);
    if (prefixPushButton == "Covariates")
    {
        prefixPushButton = "COMP";
    }
    return prefixPushButton;
}


void MainWindow::addFiles(QStringList files)
{
    QMap<QString, QStringList > map;
    foreach (QString fname, files)
    {
        QString prefix = fname.split("/").last().split('_').first();
        if(prefix == "ad" || prefix == "rd" || prefix == "md" || prefix == "fa" || prefix == "COMP")
        {
            (map[prefix]).push_back(fname);
            qDebug() << "Test add";
        }
        qDebug() << "Test Iteration List";
    }

    QMap<QString, QStringList >::ConstIterator iter = map.begin();
    while(iter != map.constEnd())
    {
        qDebug() << "Test Iteration Map";
        QString pref = iter.key();
        QString file;
        if( iter.value().size() == 1 )
        {
            file = iter.value().first();
        }
        else
        {
            file = "";
        }

        if(pref == "ad")
        {
            mainUi->para_inputADfile_lineEdit->setText(file);
        }
        if(pref == "rd")
        {
            mainUi->para_inputRDfile_lineEdit->setText(file);
        }
        if(pref == "md")
        {
            mainUi->para_inputMDfile_lineEdit->setText(file);
        }
        if(pref == "fa")
        {
            mainUi->para_inputFAfile_lineEdit->setText(file);
        }
        if(pref == "COMP")
        {
            mainUi->para_inputCOMPfile_lineEdit->setText(file);
        }
        ++iter;
    }
}

void MainWindow::addFile(QLineEdit* & lineEdit, QPushButton* & pushButton)
{
    QString filePath = lineEdit->text();
    QStringList strL =  filePath.split("/");
    strL.removeLast();
    QDir dir = strL.join("/");
    if( !dir.exists() || dir.dirName() == ".")
    {
        dir = defaultInputPathMainWindow;
    }
    QString file = QFileDialog::getOpenFileName (this, "Open CSV file", dir.absolutePath(), "CSV (*.csv)");
    QFile importedCSV(file);
    QString prefixFileName = file.split("/").last().split("_").first();
    QString prefixPushButton = getPrefixPushButton(pushButton);
    qDebug() << "prefixFileName: " << prefixFileName;
    qDebug() << "prefixPushButton: " << prefixPushButton;
    if(QString::compare(prefixPushButton, prefixFileName, Qt::CaseInsensitive) != 0)
    {
        qDebug() << "MainWindow addFile(): Wrong file";
        return;
    }
    else
    {
        if( !importedCSV.open( QIODevice::ReadOnly ) )
        {
            qDebug() << "MainWindow addFile(): Could not open the file";
            return;
        }
        else
        {
            importedCSV.close();
            lineEdit->setText( file );
        }
    }
}

void MainWindow::editFile(QLineEdit* & lineEdit, QPushButton* & pushButton)
{
    QString newFilepPath = lineEdit->text();
    emit filePathInputChanged( newFilepPath );
    emit prefixChanged( getPrefixPushButton( pushButton ) );

    inputDialog->setModal(true);
    inputDialog->loadData();
    inputDialog->exec();
}


/****************************************************************/
/************************* Subjects tab *************************/
/****************************************************************/

/*************** Public function ***************/


/**************** Private slots *****************/
void MainWindow::fileDataSizeValue()
{
    QString str;
    int i = 0;
    DataSizeLabelMapType::ConstIterator iterLabel = dataSizeLabelMap.begin();
    FileCheckBoxMapType::ConstIterator iterCheckBox = fileCheckBoxMap.begin();
    while(iterLabel != dataSizeLabelMap.constEnd())
    {
        int nbRows = fileNbrRowsList.at(i);
        int nbColumns = fileNbrColumnsList.at(i);
        if( (nbRows == 0) || (nbColumns == 0) )
        {
            str = "Data unavailable";
            iterLabel.value()->setEnabled(false);
            iterCheckBox.value()->setCheckState(Qt::Unchecked);
            iterCheckBox.value()->setEnabled(false);
        }
        else
        {
            str = "Data: " + QString::number(nbRows) + "x" + QString::number(nbColumns);
            iterLabel.value()->setEnabled(true);
            iterCheckBox.value()->setCheckState(Qt::Checked);
            iterCheckBox.value()->setEnabled(true);
        }
        iterLabel.value()->setText( str );
        ++iterLabel;
        ++iterCheckBox;
        i++;
    }
}

void MainWindow::on_inputSubjectList_lineEdit_clicked()
{
    QString filePath;
    QDir dir = mainUi->para_inputSubjectList_lineEdit->text();
    if( !dir.exists() || dir.dirName()=="." )
    {
        filePath = QFileDialog::getOpenFileName(this, "Open TXT file", defaultInputPathSubjectsList, "TXT (*.txt)");
    }
    else
    {
        filePath = QFileDialog::getOpenFileName(this, "Open TXT file", dir.absolutePath(), "TXT (*.txt)");
    }

    QFile importedTXT(filePath);
    if( !importedTXT.open( QIODevice::ReadOnly ) )
    {
        qDebug() << "MainWindow addFile(): Could not open the file";
        return;
    }
    else
    {
        importedTXT.close();
        mainUi->para_inputSubjectList_lineEdit->setText( filePath );
    }
}

void MainWindow::on_edit_inputSubjectList_lineEdit_clicked()
{
    subjectsListDialog->setModal(true);
    subjectsListDialog->loadData();
    subjectsListDialog->exec();
}

void MainWindow::on_para_inputSubjectList_lineEdit_textChanged()
{
    QString filePathSubjects = mainUi->para_inputSubjectList_lineEdit->text();
    QStringList strL =  filePathSubjects.split("/");
    strL.removeLast();
    QDir dir = strL.join("/");
    if( dir.exists() && dir.dirName() != ".")
    {
        defaultInputPathSubjectsList = dir.absolutePath();
        emit defaultInputPathSubjectsChanged( dir.absolutePath() );
    }

    QFile file(filePathSubjects);
    if( file.open( QIODevice::ReadOnly ) )
    {
        emit filePathSubjectsChanged( filePathSubjects );
    }
    else
    {
        emit filePathSubjectsChanged( "" );
    }
}


/*************** Private function ***************/

void MainWindow::on_create_subjectsListFrom_pushButton_clicked()
{

}
