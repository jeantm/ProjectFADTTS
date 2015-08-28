#include "subjectslist.h"
#include "ui_subjectslist.h"

SubjectsList::SubjectsList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SubjectsList)
{
    ui->setupUi(this);

    SubjectsListWidget = new QListWidget();
    SubjectsListWidget = ui->subjectsList_listWidget;
}

SubjectsList::~SubjectsList()
{
    delete ui;
}

/***************************************************************/
/********************** Public functions ***********************/
/***************************************************************/
void SubjectsList::loadData()
{
    SubjectsListWidget->clear();
    QFile importedTXT(checkFilePathSubjects);

    if( !importedTXT.open( QIODevice::ReadOnly ) )
    {
        qDebug() << "SubjectsList loadData(): Could not open the file";
    }
    else
    {
        displayData(importedTXT);
    }
}


/***************************************************************/
/************************ Private slots ************************/
/***************************************************************/
void SubjectsList::on_saveFile_pushButton_clicked()
{
    QString filePath = QFileDialog::getSaveFileName (this, "Open TXT file", defaultPathSetSubjects, "TXT (*.txt)");
    QFile exportedTXT( filePath );
    if( exportedTXT.open( QIODevice::WriteOnly ) )
    {
        QTextStream ts( &exportedTXT );
        QStringList strList;
        strList.clear();
        for (int i = 0; i < SubjectsListWidget->count(); i++)
        {
            strList << "\"" + SubjectsListWidget->item(i)->text() + "\"";

            ts << strList.join( "\n" )+"\n";
        }
        exportedTXT.flush();
        exportedTXT.close(); // done with file
    }
}

void SubjectsList::filePathSubjectsValue(const QString &newFilePathSubjects)
{
    checkFilePathSubjects = newFilePathSubjects;
    qDebug() << "checkFilePathSubjects: " << checkFilePathSubjects;
}

void SubjectsList::defaultInputPathSubjectsValue(const QString &newDefaultSubjectsPathMainWindow)
{
    defaultPathSetSubjects = newDefaultSubjectsPathMainWindow;
    qDebug() << "defaultPathSetSubjects: " << defaultPathSetSubjects;
}


/***************************************************************/
/********************** Private functions **********************/
/***************************************************************/
void SubjectsList::displayData(QFile &f)
{
    QTextStream ts( &f );
    QStringList list;

    // read entire file and parse lines into list of stringlist's
    while( !ts.atEnd() )
    {
        list << ts.readLine().split( "," );
    }
    f.close();

    SubjectsListWidget->setUpdatesEnabled( false );
    QStringListIterator it(list);
    while(it.hasNext())
    {
        QListWidgetItem *listItem = new QListWidgetItem(it.next(),SubjectsListWidget);
        listItem->setCheckState(Qt::Unchecked);
        SubjectsListWidget->addItem(listItem);
    }
    SubjectsListWidget->setUpdatesEnabled( true );  // done with load
}

void SubjectsList::on_deleteSubjects_pushButton_clicked()
{
    int iMax = SubjectsListWidget->count();
    for (int i = 0; i < SubjectsListWidget->count(); i++)
    {
        QListWidgetItem *listItem = SubjectsListWidget->item(i);
        if( listItem->checkState() == 2)
        {
            delete SubjectsListWidget->takeItem(i);
            iMax = SubjectsListWidget->count();
            i--;
        }
    }
}
