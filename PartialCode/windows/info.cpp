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
    ui->adFileInfo_label->setText( getFileInfo(0, "ad") );
    ui->rdFileInfo_label->setText( getFileInfo(1, "rd") );
    ui->mdFileInfo_label->setText( getFileInfo(2, "md") );
    ui->faFileInfo_label->setText( getFileInfo(3, "fa") );
    ui->compFileInfo_label->setText( getFileInfo(4, "COMP") );
}



/***************************************************************/
/************************ Private slots ************************/
/***************************************************************/
void Info::filenameListValue(const QStringList &newFilenameList)
{
    filenameList = newFilenameList;
    qDebug() << "Info update filenameList: " << filenameList;
}

void Info::fileCOMPListValue(const QStringList &newFileCOMPList)
{
    fileCOMPList = newFileCOMPList;
    qDebug() << "Info update fileCOMPList: " << fileCOMPList;
}

void Info::fileNbrRowsListValue(const QList<int> &newFileNbrRowsList)
{
    fileNbrRowsList = newFileNbrRowsList;
    qDebug() << "Info update fileNbrRowsList: " << fileNbrRowsList;
}

void Info::fileNbrColumnsListValue(const QList<int> &newFileNbrColumnsList)
{
    fileNbrColumnsList = newFileNbrColumnsList;
    qDebug() << "Info update fileNbrColumnsList: " << fileNbrColumnsList;
}

void Info::fileNbrSubjectsListValue(const QList<int> &newFileNbrSubjectsList)
{
    fileNbrSubjectsList = newFileNbrSubjectsList;
    qDebug() << "Info update fileNbrSubjectsList: " << fileNbrSubjectsList;
}


/***************************************************************/
/********************** Private functions **********************/
/***************************************************************/
QString Info::getFileInfo(int i, QString p)
{
    QString str;
    str.clear();
    str.append("<center><b>No File Information</b></center><br><b>Please select a correct data file</b><br>"
               "(Prefix should  be <b>" + p + "_</b>)");
    QString filename = filenameList.at(i);
    QFile file(filename);
    if( !file.open( QIODevice::ReadOnly ) )
    {
        qDebug() << "File info, getFileInfo(): Could not open the file";
    }
    else
    {
        QString prefix = filename.split('/').last().split('_').first();
        int nbRows = fileNbrRowsList.at(i);
        int nbColumns = fileNbrColumnsList.at(i);

        if(QString::compare(p, prefix, Qt::CaseInsensitive) == 0)
        {
            str.clear();
            str.append( "<b>Filename</b> " + filename.split('/').last() + "<br>" );
            if ( prefix == "COMP")
            {
                str.append( "<b>Number of test subjects</b>  " + QString::number(fileNbrSubjectsList.at(i)) + "<br>" );
                str.append( "<b>Data matrix</b>  " + QString::number(nbRows) + "x" + QString::number(nbColumns) + "<br>" );
                str.append( "<b>Number of COMP</b>  " + QString::number(fileCOMPList.size()) );
                for( int c = 0; c < fileCOMPList.size(); ++c )
                {
                    str.append( "<br>-  " + fileCOMPList.at(c) );
                }
            }
            else
            {
                if ( prefix == "ad" || prefix == "rd" || prefix == "md" || prefix == "fa" )
                {
                    str.append( "<b>Number of subjects</b>  " + QString::number(fileNbrSubjectsList.at(i)) + "<br>" );
                    str.append( "<b>Data matrix</b>  " + QString::number(nbRows) + "x" + QString::number(nbColumns) );
                }
            }
        }
    }
    return str;
}
