#include "setinput.h"
#include "ui_setinput.h"


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

/***************************************************************/
/********************** Public functions ***********************/
/***************************************************************/
void SetInput::loadData()
{
    ui->data_tableWidget->clear();

    QString prefix = checkFilePathInput.split("/").last().split("_").first();
    QFile importedCSV(checkFilePathInput);

    if( !importedCSV.open( QIODevice::ReadOnly ) )
    {
        qDebug() << "SetInput loadData(): Could not open the file";
    }
    else
    {
        if(QString::compare(checkPrefix, prefix, Qt::CaseInsensitive) == 0)
        {
            displayData(importedCSV);
        }
        else
        {
            qDebug() << "SetInput loadData(): Wrong file prefixe";
        }
    }
    displayFileInfo( checkFilePathInput );
}


/***************************************************************/
/************************ Private slots ************************/
/***************************************************************/
void SetInput::on_saveFile_pushButton_clicked()
{
    QString filePath = QFileDialog::getSaveFileName (this, "Open CSV file", defaultPathSetInput, "CSV (*.csv)");
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
        exportedCSV.flush();
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

void SetInput::filePathInputValue(const QString &newFilePathInput)
{
    checkFilePathInput = newFilePathInput;
}

void SetInput::defaultInputPathMainWindowValue(const QString &newDefaultInputPathMainWindow)
{
    defaultPathSetInput = newDefaultInputPathMainWindow;
}


/***************************************************************/
/********************** Private functions **********************/
/***************************************************************/
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

void SetInput::displayFileInfo(QString f)
{
    QString str;
    str.clear();
    str.append("<br><center><b>No File Information</b></center><br><b>Please select a correct data file</b><br>"
               "(Prefix should  be <b>" + checkPrefix.toLower() + "_</b>)");
    QFile file(f);

    if( !file.open( QIODevice::ReadOnly ) )
    {
        qDebug() << "SetInput displayFileInfo(): Could not open the file";
    }
    else
    {
        file.close();
        QFileInfo fInfo(file.fileName());
        QString filename = fInfo.fileName();
        QString prefix = filename.split('_').first();
        int nbRows = ui->data_tableWidget->rowCount();
        int nbColumns = ui->data_tableWidget->columnCount();

        if(QString::compare(checkPrefix, prefix, Qt::CaseInsensitive) == 0)
        {
            str.clear();
            str.append( "<br><br><b>Filename</b> " + filename + "<br>" );
            if ( prefix == "COMP")
            {
                str.append( "<br><b>Number of test subjects</b>  " + QString::number(nbRows-1) + "<br>" );
                str.append( "<br><b>Data matrix</b>  " + QString::number(nbRows-1) + "x" + QString::number(nbColumns-1) + "<br>");
                str.append( "<br><b>Number of COMP</b>  " + QString::number(nbColumns-1));
                for( int c = 1; c < nbColumns; ++c )
                {
                    QString cov = ui->data_tableWidget->item( 0, c )->text();
                    str.append( "<br>-  " + cov);
                    covariates.append(cov);
                }
                covariates.push_front("Intercept");
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
    }
    ui->fileInformation_label->setText( str );
}
