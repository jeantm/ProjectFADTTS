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


/************ Public functions ************/
QString SetInput::getFileInfo(QString f)
{
    QFile file(f);
    QString str;
    str.clear();

    if( file.open( QIODevice::ReadOnly ) )
    {
        QFileInfo fileInfo(file.fileName());
        QString filename(fileInfo.fileName());
        QString prefix = filename.split('_').first();
        int nbRows = ui->data_tableWidget->rowCount();
        int nbColumns = ui->data_tableWidget->columnCount();

        str.append( "<br><br><b>Filename</b> " + filename + "<br>" );
        if ( prefix == "COMP")
        {
            str.append( "<br><b>Number of test subjects</b>  " + QString::number(nbRows-1) + "<br>" );
            str.append( "<br><b>Number of covariates</b>  " + QString::number(nbColumns-1) + "<br>" );
            for( int c = 1; c < nbColumns; ++c )
            {
                str.append( "-  " + ui->data_tableWidget->item( 0, c )->text() + "<br>" );
            }
            str.append( "<br><b>Data matrix</b>  " + QString::number(nbRows-1) + "x" + QString::number(nbColumns-1));
        }

        else
        {
            if ( prefix == "ad" || prefix == "rd" || prefix == "md" || prefix == "fa" )
            {
                str.append( "<br><b>Number of subjects</b>  " + QString::number(nbColumns-1) + "<br>" );

                str.append( "<br><b>Data matrix</b>  " + QString::number(nbRows) + "x" + QString::number(nbColumns-1));
            }
            else
            {
                str.append("<b>File information unavailable</b>");
            }
        }
    }
    else
    {
        str.append("<b>File information unavailable</b>");
    }
    return str;
}

QString SetInput::getFilenameLineEdit()
{
    return ui->filename_lineEdit->text();
}


/************ Private functions ************/
void SetInput::on_searchFile_pushButton_clicked()
{
    QString defaultPath = "/work/jeantm/FADTTS/Project/DataTest";
    QString filePath;
    if( ui->filename_lineEdit->text().compare("") == 0 )
    {
        filePath = QFileDialog::getOpenFileName (this, "Open CSV file", defaultPath, "CSV (*.csv)");
    }
    else
    {
        filePath = QFileDialog::getOpenFileName (this, "Open CSV file", ui->filename_lineEdit->text(), "CSV (*.csv)");
    }
    QFile importedCSV(filePath);

    if( !importedCSV.open( QIODevice::ReadOnly ) )
    {
        qDebug() << "Could not open the file";
    }
    else
    {
            QTextStream ts( &importedCSV );
            QList<QStringList> list;
            int row = 0, col = 0;

            // read entire file and parse lines into list of stringlist's
            while( !ts.atEnd() )
            {
                list << ts.readLine().split( "," );
            }
            importedCSV.close();  // done with file

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

            // display file info
            ui->fileInformation_label->setText( getFileInfo(filePath) );

            ui->filename_lineEdit->setText( filePath );
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
