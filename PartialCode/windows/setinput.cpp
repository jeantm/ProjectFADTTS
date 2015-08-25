#include "setinput.h"
#include "ui_setinput.h"


/**************************************************************/
/*********************** SetInput Class ***********************/
/**************************************************************/
SetInput::SetInput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetInput)
{
    ui->setupUi(this);
}

SetInput::~SetInput()
{
    delete ui;
}

/************ Public functions *************/
QString SetInput::displayFileInfo(QString f)
{
    QString str;
    str.clear();
    if( access(f.toLatin1().data(), 0) == 0 )
    {
        InfoFile fInfo(f, ui);
        QString filename = fInfo.getFilename();
        QString prefix = fInfo.getPrefix();
        int nbRows = fInfo.getNbRows();
        int nbColumns = fInfo.getNbColumns();

        if(QString::compare(checkPrefix, fInfo.getPrefix(), Qt::CaseInsensitive) == 0)
        {
            str.append( "<br><br><b>Filename</b> " + filename + "<br>" );
            if ( prefix == "COMP")
            {
                str.append( "<br><b>Number of test subjects</b>  " + QString::number(nbRows-1) + "<br>" );
                str.append( "<br><b>Data matrix</b>  " + QString::number(nbRows-1) + "x" + QString::number(nbColumns-1) + "<br>");
                str.append( "<br><b>Number of covariates</b>  " + QString::number(nbColumns-1));
                for( int c = 1; c < nbColumns; ++c )
                {
                    str.append( "<br>-  " + ui->data_tableWidget->item( 0, c )->text());
                }
            }

            else
            {
                if ( prefix == "ad" || prefix == "rd" || prefix == "md" || prefix == "fa" )
                {
                    str.append( "<br><b>Number of subjects</b>  " + QString::number(nbColumns-1) + "<br>" );
                    str.append( "<br><b>Data matrix</b>  " + QString::number(nbRows) + "x" + QString::number(nbColumns-1));
                }
            }
        }
        else
        {
            str.append("<center><b>No File Information<br>Please select a correct data file</b><br>"
                       "(Prefix shoud  be <b>" + checkPrefix.toLower() + "_</b>)</center>");
        }
    }
    else
    {
        str.append("<center><b>No File Information<br>Please select a correct data file</b><br>"
                   "(Prefix shoud  be <b>" + checkPrefix.toLower() + "_</b>)</center>");
    }
    return str;
}

QString SetInput::getFilenameLineEdit()
{
    return ui->filename_lineEdit->text();
}

void SetInput::loadData()
{
    qDebug() << " SetInput load data: " + checkFilePath;
    ui->data_tableWidget->clear();
    ui->filename_lineEdit->setText( checkFilePath );

    if(access(checkFilePath.toLatin1().data(), 0) == 0)
    {
        InfoFile fInfo(checkFilePath, ui);
        QFile importedCSV(checkFilePath);
        if( !importedCSV.open( QIODevice::ReadOnly ) )
        {
            qDebug() << "SetInput load data: Could not open the file";
            return;
        }
        else
        {
            if(QString::compare(checkPrefix, fInfo.getPrefix(), Qt::CaseInsensitive) == 0)
            {
                displayData(importedCSV);
            }
            else
            {
                ui->fileInformation_label->setText( displayFileInfo(checkFilePath) );
                qDebug() << "SetInput load data: Wrong file prefixe";
                return;
            }
            ui->fileInformation_label->setText( displayFileInfo(checkFilePath) );
        }
    }
    else
    {
        ui->fileInformation_label->setText( displayFileInfo(checkFilePath) );
        qDebug() << "SetInput load data: File does not existe";
        return;
    }
}


/************ Private slots ************/
void SetInput::on_searchFile_pushButton_clicked()
{
    ui->data_tableWidget->clear();
    QString defaultPath = "/work/jeantm/FADTTS/Project/DataTest";
    QString filePath;
    if( access(checkFilePath.toLatin1().data(), 0) != 0 )
    {
        filePath = QFileDialog::getOpenFileName (this, "Open CSV file", defaultPath, "CSV (*.csv)");
    }
    else
    {
        filePath = QFileDialog::getOpenFileName (this, "Open CSV file", checkFilePath, "CSV (*.csv)");
    }
    InfoFile fInfo(filePath, ui);
    QFile importedCSV(filePath);

    if( !importedCSV.open( QIODevice::ReadOnly ) )
    {
        qDebug() << "SetInput search PushButton: Could not open the file";
        return;
    }
    else
    {
        if(QString::compare(checkPrefix, fInfo.getPrefix(), Qt::CaseInsensitive) == 0)
        {
            displayData(importedCSV);

            // display file info
            ui->fileInformation_label->setText( displayFileInfo(filePath) );
            ui->filename_lineEdit->setText( filePath );
        }
        else
        {
            ui->fileInformation_label->setText( displayFileInfo(filePath) );
            qDebug() << "SetInput search PushButton: Wrong kind of file";
            return;
        }
    }
}

void SetInput::on_saveFile_pushButton_clicked()
{
    QString path = ui->filename_lineEdit->text();
    QString filePath = QFileDialog::getSaveFileName (this, "Open CSV file", path, "CSV (*.csv)");
    QFile exportedCSV( filePath );
    if( exportedCSV.open( QIODevice::WriteOnly ) )
    {
        QTextStream ts( &exportedCSV );
        QStringList strList;

        for( int r = 0; r < ui->data_tableWidget->rowCount(); ++r )
        {
            strList.clear();
            for( int c = 0; c < ui->data_tableWidget->columnCount(); ++c )
            {
                strList << "\""+ui->data_tableWidget->item( r, c )->text()+"\"";
            }
                ts << strList.join( "," )+"\n";
        }
        exportedCSV.close(); // done with file
    }
}

void SetInput::on_deleteRows_pushButton_clicked()
{
    QItemSelection selection( ui->data_tableWidget->selectionModel()->selection() );

    QList<int> rows;
    foreach( const QModelIndex & index, selection.indexes() )
    {
        rows.append( index.row() );
    }
    qSort( rows );

    int prev = -1;
    for( int i = rows.count() - 1; i >= 0; i -= 1 )
    {
        int current = rows[i];
        if( current != prev )
        {
            ui->data_tableWidget->removeRow(current);
            prev = current;
        }
    }
}

void SetInput::on_deleteColumns_pushButton_clicked()
{
    QItemSelection selection( ui->data_tableWidget->selectionModel()->selection() );

    QList<int> columns;
    foreach( const QModelIndex & index, selection.indexes() )
    {
        columns.append( index.column() );
    }
    qSort( columns );

    int prev = -1;
    for( int i = columns.count() - 1; i >= 0; i -= 1 )
    {
        int current = columns[i];
        if( current != prev )
        {
            ui->data_tableWidget->removeColumn(current);
            prev = current;
        }
    }
}

void SetInput::prefixValue(const QString &newPrefix)
{
    checkPrefix = newPrefix;
}

void SetInput::filePathValue(const QString &newFilePath)
{
    checkFilePath = newFilePath;
}


/************ Private functions ************/
void SetInput::displayData(QFile &f)
{
    QTextStream ts( &f );
    QList<QStringList> list;
    int row = 0, col = 0;

    // read entire file and parse lines into list of stringlist's
    while( !ts.atEnd() )
    {
        list << ts.readLine().split( "," );
    }
    f.close();  // done with file

    // prep table
    ui->data_tableWidget->setRowCount( list.count() );  // number of stringlists gives row count
    ui->data_tableWidget->setColumnCount( list[0].count() );  // count of entries from intial stringlist for column count

    ui->data_tableWidget->setUpdatesEnabled( false );  // for faster processing of large lists
    foreach( QStringList l, list )
    {
        foreach( QString str, l )
        {
            // remove quotes if str quoted
            if( str.endsWith( '"' ) ) str.chop(1);
            if( str.startsWith( '"' ) ) str.remove(0,1);
            ui->data_tableWidget->setItem( row, col++, new QTableWidgetItem( str ));
        }
        row++; col=0;
    }
    ui->data_tableWidget->setUpdatesEnabled( true );  // done with load
}

/**************************************************************/
/*********************** InfoFile Class ***********************/
/**************************************************************/

/************ Public functions ************/
InfoFile::InfoFile(QString f, Ui::SetInput *ui)
{
    QFile file(f);
    QFileInfo fInfo(file.fileName());
    filename = (fInfo.fileName());
    prefix = filename.split('_').first();
    nbRows = ui->data_tableWidget->rowCount();
    nbColumns = ui->data_tableWidget->columnCount();
}

int InfoFile::getNbRows()
{
    return nbRows;
}

int InfoFile::getNbColumns()
{
    return nbColumns;
}

QString InfoFile::getFilename()
{
    return filename;
}

QString InfoFile::getPrefix()
{
    return prefix;
}
