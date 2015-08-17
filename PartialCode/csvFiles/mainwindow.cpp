#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Load_clicked()
{
    QString defaultPath = "/work/jeantm/FADTTS/Project/DataTest";
    QString filePath;
    if( ui->lineEdit_Filename->text().compare("path/filename.csv") == 0 )
    {
        filePath = QFileDialog::getOpenFileName (this, "Open CSV file", defaultPath, "CSV (*.csv)");
    }
    else
    {
        filePath = QFileDialog::getOpenFileName (this, "Open CSV file", ui->lineEdit_Filename->text(), "CSV (*.csv)");
    }

    QFile importedCSV(filePath);
    QFileInfo fileInfo(importedCSV.fileName());
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
            ui->tableWidget->setRowCount( list.count() );  // number of stringlists give row count
            ui->tableWidget->setColumnCount( list[0].count() );  // count of entries from intial stringlist for column count

            ui->tableWidget->setUpdatesEnabled( false );  // for faster processing of large lists
            foreach( QStringList l, list )
            {
                foreach( QString str, l )
                {
                    // remove quotes if str quoted
                    if( str.endsWith( '"' ) ) str.chop(1);
                    if( str.startsWith( '"' ) ) str.remove(0,1);
                    ui->tableWidget->setItem( row, col++, new QTableWidgetItem( str ));
                }
                row++; col=0;
            }
            ui->tableWidget->setUpdatesEnabled( true );  // done with load

            // display file info
            getInfo(fileInfo);
            ui->lineEdit_Filename->setText(filePath);
    }
}

void MainWindow::on_pushButton_Save_clicked()
{
    QString path = ui->lineEdit_Filename->text();
    QString filePath = QFileDialog::getSaveFileName (this, "Open CSV file", path, "CSV (*.csv)");
    QFile exportedCSV( filePath );
    if( exportedCSV.open( QIODevice::WriteOnly ) )
    {
        QTextStream ts( &exportedCSV );
        QStringList strList;

        for( int r = 0; r < ui->tableWidget->rowCount(); ++r )
        {
            strList.clear();
            for( int c = 0; c < ui->tableWidget->columnCount(); ++c )
            {
                strList << "\""+ui->tableWidget->item( r, c )->text()+"\"";
            }
                ts << strList.join( "," )+"\n";
        }
        exportedCSV.close(); // done with file
    }
}

void MainWindow::on_pushButton_DeleteRows_clicked()
{
    QItemSelection selection( ui->tableWidget->selectionModel()->selection() );

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
            ui->tableWidget->removeRow(current);
            prev = current;
        }
    }
}

void MainWindow::on_pushButton_DeleteColumns_clicked()
{
    QItemSelection selection( ui->tableWidget->selectionModel()->selection() );

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
            ui->tableWidget->removeColumn(current);
            prev = current;
        }
    }
}

void MainWindow::getInfo(QFileInfo fileInfo)
{
    QString filename(fileInfo.fileName());
    QString prefix = filename.split('_').first();
    QString str;
    int nbRows = ui->tableWidget->rowCount();
    int nbColumns = ui->tableWidget->columnCount();

    str.clear();
    str.append( "<center><b>Info</b></center><br>" );
    str.append( "<b>File</b> " + filename + "<br>" );

    if ( prefix == "COMP")
    {
        str.append( "<br><b>Number of test subjects</b>  " + QString::number(nbRows-1) + "<br>" );
        str.append( "<br><b>Number of covariates</b>  " + QString::number(nbColumns-1) + "<br>" );

        for( int c = 1; c < nbColumns; ++c )
        {
            str.append( "-  " + ui->tableWidget->item( 0, c )->text() + "<br>" );
        }
        str.append( "<br><b>Data matrix</b>  " + QString::number(nbRows-1) + "x" + QString::number(nbColumns-1));
    }

    if ( prefix == "ad" || prefix == "rd" || prefix == "md" || prefix == "fa" )
    {
        str.append( "<br><b>Number of subjects</b>  " + QString::number(nbColumns-1) + "<br>" );

        str.append( "<br><b>Data matrix</b>  " + QString::number(nbRows) + "x" + QString::number(nbColumns-1));
    }
    ui->textBrowser_Info->setText( str );
}

void MainWindow::on_pushButton_GenerateMatlabInput_clicked()
{
    QString path = ui->lineEdit_Filename->text().split('.').first() + ".txt";
    QString filePath = QFileDialog::getSaveFileName (this, "Open TXT file", path, "TXT (*.txt)");
    QFile exportedCSV( filePath );
    QFileInfo fileInfo( exportedCSV.fileName() );
    QString prefix = (fileInfo.fileName()).split('_').first();

    if( exportedCSV.open( QIODevice::WriteOnly ) )
    {
        QTextStream ts( &exportedCSV );
        QStringList strList;
        int cInit = 0;
        if ( prefix == "COMP" )
        {
            cInit = 1;
        }
        qDebug() << cInit; //Test

        for( int r = 1; r < ui->tableWidget->rowCount(); ++r )
        {
            strList.clear();
            for( int c = cInit; c < ui->tableWidget->columnCount(); ++c )
            {
                strList << ui->tableWidget->item( r, c )->text();
            }
            ts << strList.join( "," )+"\n";
        }
        exportedCSV.close(); // done with file
    }
}
