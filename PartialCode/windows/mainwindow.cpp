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

    matchedSubjectsListWidget = new QListWidget();
    matchedSubjectsListWidget = mainUi->matchSubjects_listWidget;

    covariatesListWidget = new QListWidget();
    covariatesListWidget = mainUi->covariates_listWidget;

    // Signal/Slot within MainWindow/Input
    QObject::connect(this, SIGNAL(fileDataSizeChanged(QMap<QString,int>,QMap<QString,int>)), this, SLOT(fileDataSizeValue()));

    // Signal/Slot with MainWindow/Parameters
    QObject::connect(this, SIGNAL(fileCOMPListChanged(QStringList)), this, SLOT(setCOMPList()));

    // Signal/Slot with SetInput
    QObject::connect(this, SIGNAL(prefixChanged(QString)), inputDialog, SLOT(prefixValue(QString)));
    QObject::connect(this, SIGNAL(filePathInputChanged(QString)), inputDialog, SLOT(filePathInputValue(QString)));
    QObject::connect(this, SIGNAL(defaultInputPathMainWindowChanged(QString)), inputDialog, SLOT(defaultInputPathMainWindowValue(QString)));

    // Signal/Slot with Info
    QObject::connect(this, SIGNAL(filenameListChanged(QMap<QString,QString>)), info, SLOT(filenameListValue(QMap<QString,QString>)));
    QObject::connect(this, SIGNAL(fileCOMPListChanged(QStringList)), info, SLOT(fileCOMPListValue(QStringList)));
    QObject::connect(this, SIGNAL(fileNbrRowsListChanged(QMap<QString,int>)), info, SLOT(fileNbrRowsListValue(QMap<QString,int>)));
    QObject::connect(this, SIGNAL(fileNbrColumnsListChanged(QMap<QString,int>)), info, SLOT(fileNbrColumnsListValue(QMap<QString,int>)));
    QObject::connect(this, SIGNAL(fileNbrSubjectsListChanged(QMap<QString,int>)), info, SLOT(fileNbrSubjectsListValue(QMap<QString,int>)));

    init();
}

MainWindow::~MainWindow()
{
    delete mainUi;
}


/***************************************************************/
/**************************** Other ****************************/
/***************************************************************/

/*************** Public  function ***************/


/**************** Private slots *****************/
void MainWindow::init()
{
    // Init Input tab
    QStringList prefixList;
    prefixList << "ad" << "rd" << "md" << "fa" << "COMP";
    foreach(QString pref, prefixList)
    {
        filenameList[pref] = "";
        fileNbrRowsList[pref] = 0;
        fileNbrColumnsList[pref] = 0;
        fileNbrSubjectsList[pref] = 0;
        (filesSubjectsList[pref]).push_back("No Subject");
    }
    fileCOMPList.push_back("");

    QString defaultPath = "/work/jeantm/FADTTS/Project/DataTest";
    defaultInputPathMainWindow = defaultPath;
    defaultOutputPathMainWindow = defaultPath;


    // Subjects List tab
    fileCheckBoxMap.insert("ad", mainUi->para_adData_checkBox);
    fileCheckBoxMap.insert("rd", mainUi->para_rdData_checkBox);
    fileCheckBoxMap.insert("md", mainUi->para_mdData_checkBox);
    fileCheckBoxMap.insert("fa", mainUi->para_faData_checkBox);
    fileCheckBoxMap.insert("COMP", mainUi->para_compData_checkBox);

    dataSizeLabelMap.insert("ad", mainUi->adDataSize_label);
    dataSizeLabelMap.insert("rd", mainUi->rdDataSize_label);
    dataSizeLabelMap.insert("md", mainUi->mdDataSize_label);
    dataSizeLabelMap.insert("fa", mainUi->faDataSize_label);
    dataSizeLabelMap.insert("COMP", mainUi->compDataSize_label);

    LabelMapType::ConstIterator iterLabel = dataSizeLabelMap.begin();
    checkBoxMapType::ConstIterator iterCheckBox = fileCheckBoxMap.begin();
    while(iterLabel != dataSizeLabelMap.constEnd())
    {
        iterLabel.value()->setText("Data unavailable");
        iterLabel.value()->setEnabled(false);
        iterCheckBox.value()->setCheckState(Qt::Unchecked);
        iterCheckBox.value()->setEnabled(false);
        ++iterLabel;
        ++iterCheckBox;
    }

    defaultInputPathSubjectsList = defaultPath;


    // Signals Emission
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

/*************** Public  function ***************/


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
    addFile(mainUi->para_inputADfile_lineEdit);
}

void MainWindow::on_inputRDfile_pushButton_clicked()
{
    addFile(mainUi->para_inputRDfile_lineEdit);
}

void MainWindow::on_inputMDfile_pushButton_clicked()
{
    addFile(mainUi->para_inputMDfile_lineEdit);
}

void MainWindow::on_inputFAfile_pushButton_clicked()
{
    addFile(mainUi->para_inputFAfile_lineEdit);
}

void MainWindow::on_inputCOMPfile_pushButton_clicked()
{
    addFile(mainUi->para_inputCOMPfile_lineEdit);
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
    updateLineEdit(mainUi->para_inputADfile_lineEdit, mainUi->inputADfile_pushButton);
}

void MainWindow::on_para_inputRDfile_lineEdit_textChanged()
{
    updateLineEdit(mainUi->para_inputRDfile_lineEdit, mainUi->inputRDfile_pushButton);
}

void MainWindow::on_para_inputMDfile_lineEdit_textChanged()
{
    updateLineEdit(mainUi->para_inputMDfile_lineEdit, mainUi->inputMDfile_pushButton);
}

void MainWindow::on_para_inputFAfile_lineEdit_textChanged()
{
    updateLineEdit(mainUi->para_inputFAfile_lineEdit, mainUi->inputFAfile_pushButton);
}

void MainWindow::on_para_inputCOMPfile_lineEdit_textChanged()
{
    updateLineEdit(mainUi->para_inputCOMPfile_lineEdit, mainUi->inputCOMPfile_pushButton);
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
void MainWindow::addFiles(QStringList files)
{
    QMap<QString, QStringList > map;
    foreach (QString fname, files)
    {
        QString prefix = fname.split("/").last().split('_').first();
        if(prefix == "ad" || prefix == "rd" || prefix == "md" || prefix == "fa" || prefix == "COMP")
        {
            (map[prefix]).push_back(fname);
        }
    }

    QMap<QString, QStringList >::ConstIterator iter = map.begin();
    while(iter != map.constEnd())
    {
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

void MainWindow::addFile(QLineEdit* & lineEdit)
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

void MainWindow::editFile(QLineEdit* & lineEdit, QPushButton* & pushButton)
{
    QString newFilepPath = lineEdit->text();
    emit filePathInputChanged( newFilepPath );
    emit prefixChanged( getPrefixPushButton( pushButton ) );

    inputDialog->setModal(true);
    inputDialog->loadData();
    inputDialog->exec();
}

void MainWindow::updateLineEdit(QLineEdit* & lineEdit, QPushButton* & pushButton)
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
    updateFile( filePath, prefix);
}

void MainWindow::updateFile(QString filePath, QString p)
{
    QFile file(filePath);
    if( !file.open( QIODevice::ReadOnly ) )
    {
        filenameList[p] = "";
        fileNbrRowsList[p] = 0;
        fileNbrColumnsList[p] = 0;
        fileNbrSubjectsList[p] = 0;
        (filesSubjectsList[p]).clear();
        filesSubjectsList[p] = QStringList("No Subject");

        if(p == "COMP")
        {
            fileCOMPList.clear();
            fileCOMPList.insert(0,"");
        }
        qDebug() << "File info, getFileInfo(): Could not open the file";
    }
    else
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

        filenameList[p] = filePath;
        (filesSubjectsList[p]).clear();

        if ( p == "COMP")
        {
            fileNbrRowsList[p] = nbRows-1;
            fileNbrColumnsList[p] = nbColumns-1;
            fileNbrSubjectsList[p] = nbRows-1;

            fileCOMPList.clear();
            for( int c = 1; c < nbColumns; ++c )
            {
                fileCOMPList.insert(c-1,list[0].at(c));
            }
            for(int r = 1; r < nbRows; r++)
            {
                (filesSubjectsList[p]) << list[r].at(0);
            }
        }
        else
        {
            if ( p == "ad" || p == "rd" || p == "md" || p == "fa" )
            {
                fileNbrRowsList[p] = nbRows-1;
                fileNbrColumnsList[p] = nbColumns;
                fileNbrSubjectsList[p] = nbColumns-1;

                for(int c = 1; c < nbColumns; c++)
                {
                    (filesSubjectsList[p]) << list[0].at(c);
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
    QString prefixPushButton = pushButton->text().split(" ").at(1).toLower();
    if (prefixPushButton == "covariates")
    {
        prefixPushButton = "COMP";
    }
    return prefixPushButton;
}


/****************************************************************/
/************************* Subjects tab *************************/
/****************************************************************/

/*************** Public  function ***************/


/**************** Private slots *****************/
void MainWindow::fileDataSizeValue()
{
    QString str;
    LabelMapType::ConstIterator iterLabel = dataSizeLabelMap.begin();
    checkBoxMapType::ConstIterator iterCheckBox = fileCheckBoxMap.begin();
    while(iterLabel != dataSizeLabelMap.constEnd())
    {
        int nbRows = fileNbrRowsList[iterCheckBox.key()];
        int nbColumns = fileNbrColumnsList[iterCheckBox.key()];
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
    }
}

void MainWindow::on_load_inputSubjectList_PushButton_clicked()
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

void MainWindow::on_save_checkedSubjectsList_pushButton_clicked()
{
    QString filePath = QFileDialog::getSaveFileName (this, "Open TXT file", defaultInputPathSubjectsList, "TXT (*.txt)");
    QFile exportedTXT( filePath );
    if( exportedTXT.open( QIODevice::WriteOnly ) )
    {
        QTextStream ts( &exportedTXT );
        QStringList strList;
        strList.clear();
        for (int i = 0; i < matchedSubjectsListWidget->count(); i++)
        {
            if(matchedSubjectsListWidget->item(i)->checkState() == Qt::Checked)
            {
                strList << matchedSubjectsListWidget->item(i)->text();
            }
            ts << strList.join( "\n" )+"\n";
        }
        exportedTXT.flush();
        exportedTXT.close();
        mainUi->para_inputSubjectList_lineEdit->setText(filePath);
    }
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
    }
}

void MainWindow::on_match_subjectsList_pushButton_clicked()
{
    QFile subjectsListTXT(mainUi->para_inputSubjectList_lineEdit->text());
    QTextStream ts( &subjectsListTXT );
    QStringList subjectsListRef;
    if( !subjectsListTXT.open( QIODevice::ReadOnly ) )
    {
        checkBoxMapType::ConstIterator iterCheckBox = fileCheckBoxMap.begin();
        QMap<QString, QStringList >::ConstIterator it = filesSubjectsList.begin();
        while(iterCheckBox != fileCheckBoxMap.constEnd())
        {
            if(iterCheckBox.value()->isChecked())
            {
                if(!it.value().contains("No Subject"))
                {
                    foreach (QString subject, it.value())
                    {
                        if(!subjectsListRef.contains(subject))
                        {
                            subjectsListRef << subject;
                        }
                    }
                }
            }
            ++iterCheckBox;
            ++it;
        }
    }
    else
    {
        while( !ts.atEnd() )
        {
            subjectsListRef << ts.readLine().split( "\n" );
        }
        subjectsListTXT.close();
    }

    QMap<QString, QStringList> selectedSubjectList;
    checkBoxMapType::ConstIterator iterCheckBox = fileCheckBoxMap.begin();
    QMap<QString, QStringList >::ConstIterator iterSubjectsList = filesSubjectsList.begin();
    while(iterCheckBox != fileCheckBoxMap.constEnd())
    {
        if(iterCheckBox.value()->isChecked())
        {
            (selectedSubjectList[iterSubjectsList.key()]) << iterSubjectsList.value();
        }
        ++iterCheckBox;
        ++iterSubjectsList;
    }

    QMap< QString, QMap<QString, bool> > allSubjects;
    QStringListIterator itRef(subjectsListRef);
    while(itRef.hasNext())
    {
        QString subjRef = QString(itRef.next().toLocal8Bit().data());

        QMap<QString, QStringList >::ConstIterator iterSelectedSubjectsList = selectedSubjectList.begin();
        while(iterSelectedSubjectsList != selectedSubjectList.constEnd())
        {
            if(iterSelectedSubjectsList.value().contains(subjRef))
            {
                ((allSubjects[subjRef])[iterSelectedSubjectsList.key()]) = true;
            }
            else
            {
                ((allSubjects[subjRef])[iterSelectedSubjectsList.key()]) = false;
            }
            ++iterSelectedSubjectsList;
        }
    }

    QStringList matchedSubjectsList;
    QMap<QString, QStringList > unMatchedSubjectsList;
    QMap< QString, QMap<QString, bool> >::ConstIterator iterAllSubjects = allSubjects.begin();
    while(iterAllSubjects != allSubjects.constEnd())
    {
        bool subInAll = true;
        QMap<QString, bool>::ConstIterator it = iterAllSubjects.value().begin();
        while(it != iterAllSubjects.value().constEnd())
        {
            subInAll = subInAll && it.value();
            ++it;
        }

        if(subInAll)
        {
            matchedSubjectsList << iterAllSubjects.key();
        }
        else
        {
            QMap<QString, bool>::ConstIterator it = iterAllSubjects.value().begin();
            while(it != iterAllSubjects.value().constEnd())
            {
                if(!it.value() && !(unMatchedSubjectsList[iterAllSubjects.key()]).contains("refList")
                        && (mainUi->para_inputSubjectList_lineEdit->text() != ""))
                {
                    (unMatchedSubjectsList[iterAllSubjects.key()]).append("refList");
                }
                if(it.value())
                {
                    (unMatchedSubjectsList[iterAllSubjects.key()]).append(it.key());
                }
                ++it;
            }
        }
        ++iterAllSubjects;
    }

    matchedSubjectsListWidget->clear();
    matchedSubjectsListWidget->setUpdatesEnabled( false );
    matchedSubjectsListWidget->setSelectionMode(QAbstractItemView::NoSelection);
    QStringListIterator iterMatchedSubjectsList(matchedSubjectsList);
    while(iterMatchedSubjectsList.hasNext())
    {
        QString text = QString(iterMatchedSubjectsList.next().toLocal8Bit().data());
        QListWidgetItem *listItem = new QListWidgetItem(text,matchedSubjectsListWidget);
        listItem->setCheckState(Qt::Checked);
        listItem->setBackgroundColor(QColor(0,255,0,127));
        matchedSubjectsListWidget->addItem(listItem);
    }
    QMap<QString, QStringList >::ConstIterator iterUnMatchedSubjectsList = unMatchedSubjectsList.begin();
    while(iterUnMatchedSubjectsList != unMatchedSubjectsList.constEnd())
    {
        QStringList sortedText = iterUnMatchedSubjectsList.value();
        sortedText.sort();
        QString text = "- \"" + iterUnMatchedSubjectsList.key() + "\" --> " + sortedText.join(", ");
        QListWidgetItem *listItem = new QListWidgetItem(text,matchedSubjectsListWidget);
        listItem->setBackgroundColor(QColor(255,0,0,127));
        listItem->setTextColor(QColor(0,0,0,191));
        matchedSubjectsListWidget->addItem(listItem);
        ++iterUnMatchedSubjectsList;
    }
    matchedSubjectsListWidget->setUpdatesEnabled( true );

    mainUi->matchSubjects_label->clear();
    QString text;
    if((unMatchedSubjectsList.size() == 0) && (matchedSubjectsList.size() != 0))
    {
        text = "All subjects matched (" + QString::number(matchedSubjectsList.size()) + ")";
    }
    else
    {
        if(unMatchedSubjectsList.size() != 0)
        {
            text = "Out of the " + QString::number(subjectsListRef.size()) + " subjects\n" +
                    " - " +QString::number(matchedSubjectsList.size()) + " matched\n" +
                    " - " +QString::number(unMatchedSubjectsList.size()) + " unmatched\n";
        }
    }
    mainUi->matchSubjects_label->setText(text);
}

void MainWindow::on_para_search_lineEdit_textEdited()
{
    QListWidget *list = matchedSubjectsListWidget;
    QString search_str = mainUi->para_search_lineEdit->text();
    if(search_str != "")
    {
        for( int i = 0; i < list->count(); i++ )
        {
            QListWidgetItem* current = list->item( i );
            if( current->text().contains( search_str ) )
            {
                current->setHidden(false);
            }
            else
            {
                current->setHidden(true);
            }
        }
    }
    else
    {
        for( int i = 0; i < list->count(); i++ )
        {
            list->item( i )->setHidden(false);
        }
    }
}


/*************** Private function ***************/


/****************************************************************/
/************************ Parameters tab ************************/
/****************************************************************/

/*************** Public  function ***************/


/**************** Private slots *****************/
void MainWindow::setCOMPList()
{
    covariatesListWidget->clear();
    if( !(fileCOMPList.first() == "") )
    {
        foreach (QString covar, fileCOMPList)
        {
            QListWidgetItem *listItem = new QListWidgetItem(covar,covariatesListWidget);
            listItem->setCheckState(Qt::Checked);
            covariatesListWidget->addItem(listItem);
        }
    }
}

void MainWindow::on_covariatesCheckAll_pushButton_clicked()
{
    QListWidget *list = covariatesListWidget;
    for( int i = 0; i < list->count(); i++ )
    {
        list->item( i )->setCheckState(Qt::Checked);
    }
}

void MainWindow::on_covariatesUncheckAll_pushButton_clicked()
{
    QListWidget *list = covariatesListWidget;
    for( int i = 0; i < list->count(); i++ )
    {
        list->item( i )->setCheckState(Qt::Unchecked);
    }
}




/*************** Private function ***************/












