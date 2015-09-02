#include "info.h"
#include "ui_info.h"

Info::Info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Info)
{
    ui->setupUi(this);
}

Info::~Info()
{
    delete ui;
}


/***************************************************************/
/********************** Public functions ***********************/
/***************************************************************/
void Info::displayInfo()
{
    ui->adFileInfo_label->setText( getFileInfo("ad") );
    ui->rdFileInfo_label->setText( getFileInfo("rd") );
    ui->mdFileInfo_label->setText( getFileInfo("md") );
    ui->faFileInfo_label->setText( getFileInfo("fa") );
    ui->compFileInfo_label->setText( getFileInfo("COMP") );
}



/***************************************************************/
/************************ Private slots ************************/
/***************************************************************/
void Info::filenameListValue(const QMap<QString,QString> &newFilenameList)
{
    filenameList = newFilenameList;
    qDebug() << "Info update filenameList: " << filenameList;
}

void Info::fileCOMPListValue(const QStringList &newFileCOMPList)
{
    fileCOMPList = newFileCOMPList;
    qDebug() << "Info update fileCOMPList: " << fileCOMPList;
}

void Info::fileNbrRowsListValue(const QMap<QString,int> &newFileNbrRowsList)
{
    fileNbrRowsList = newFileNbrRowsList;
    qDebug() << "Info update fileNbrRowsList: " << fileNbrRowsList;
}

void Info::fileNbrColumnsListValue(const QMap<QString,int> &newFileNbrColumnsList)
{
    fileNbrColumnsList = newFileNbrColumnsList;
    qDebug() << "Info update fileNbrColumnsList: " << fileNbrColumnsList;
}

void Info::fileNbrSubjectsListValue(const QMap<QString,int> &newFileNbrSubjectsList)
{
    fileNbrSubjectsList = newFileNbrSubjectsList;
    qDebug() << "Info update fileNbrSubjectsList: " << fileNbrSubjectsList;
}


/***************************************************************/
/********************** Private functions **********************/
/***************************************************************/
QString Info::getFileInfo(QString p)
{
    QString str;
    str.clear();
    str.append("<center><b>No File Information</b></center><br><b>Please select a correct data file</b><br>");
    QString filename = filenameList[p];
    QFile file(filename);
    if( !file.open( QIODevice::ReadOnly ) )
    {
        qDebug() << "File info, getFileInfo(): Could not open the file";
    }
    else
    {
        int nbRows = fileNbrRowsList[p];
        int nbColumns = fileNbrColumnsList[p];

        str.clear();
        str.append( "<b>Filename</b> " + filename.split('/').last() + "<br>" );
        if ( p == "COMP")
        {
            str.append( "<b>Number of test subjects</b>  " + QString::number(fileNbrSubjectsList[p]) + "<br>" );
            str.append( "<b>Data matrix</b>  " + QString::number(nbRows) + "x" + QString::number(nbColumns) + "<br>" );
            str.append( "<b>Number of COMP</b>  " + QString::number(fileCOMPList.size()) );
            for( int c = 0; c < fileCOMPList.size(); ++c )
            {
                str.append( "<br>-  " + fileCOMPList.at(c) );
            }
        }
        else
        {
            if ( p == "ad" || p == "rd" || p == "md" || p == "fa" )
            {
                str.append( "<b>Number of subjects</b>  " + QString::number(fileNbrSubjectsList[p]) + "<br>" );
                str.append( "<b>Data matrix</b>  " + QString::number(nbRows-1) + "x" + QString::number(nbColumns) );
            }
        }
    }
    return str;
}
