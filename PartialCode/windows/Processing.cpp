#include "Processing.h"

Processing::Processing()
{
}

const QString Processing::m_csvSeparator = QLocale().groupSeparator();

QStringList Processing::GenerateSrcFiles( QStringList finalInputFiles, QString finalSubjectsListFile,
                                   int subjectsCovariatesColumnId, QString currentFileOutputDir )
{
    m_finalInputFiles = finalInputFiles;
    QStringList finalSubjectsList = GetFinalSubjectsList( finalSubjectsListFile );
    foreach (QString finalInputFile, finalInputFiles)
    {
        QStringList subjects = GetSubjectsList( finalInputFile, subjectsCovariatesColumnId );
        QFile srcFile( currentFileOutputDir + "/" +
                       QFileInfo( QFile( finalInputFile ) ).fileName().split( "." ).first() +
                       "_SRC.txt" );
        if( srcFile.open( QIODevice::WriteOnly ) )
        {
            QTextStream tsSRC( &srcFile );
            QStringList rowData;

            QFile file( finalInputFile );
            file.open( QIODevice::ReadOnly );
            QTextStream ts( &file );
            QList<QStringList> data;
            while( !ts.atEnd() )
            {
                data << ts.readLine().split( m_csvSeparator );
            }
            file.close();
            int nbRows = data.count();
            int nbColumns = data.at( 0 ).count();

            if( nbColumns < nbRows )
            {
                for( int r = 1; r < nbRows; ++r )
                {
                    QString currentSubject = data.at( r ).at( subjectsCovariatesColumnId );

                    rowData.clear();
                    if( subjects.count( currentSubject ) == 1 )
                    {
                        for( int c = 0; c < nbColumns; ++c )
                        {
                            if( c != subjectsCovariatesColumnId )
                            {
                                rowData << data.at( r ).at( c );
                            }
                        }
                        tsSRC << QObject::tr( qPrintable( rowData.join( m_csvSeparator ) ) ) << endl;
                    }
                    else
                    {
                        /***************** WARNING POPUP *****************/
                        // not in subject lisst ref or appears twice in datafile
                    }
                }
            }
            else
            {
                QList<int> subjectID;
                for( int c = 0; c < nbColumns; ++c )
                {
                    QString CurrentSubject = data.at( 0 ).at( c );
                    if( ( c == 0 || ( finalSubjectsList.contains( CurrentSubject ) && subjects.count( CurrentSubject ) == 1 ) ) )
                    {
                        subjectID.append( c );
                    }
                    else
                    {
                        /***************** WARNING POPUP *****************/
                        // not in subject lisst ref or appears twice in datafile
                    }
                }

                for( int r = 1; r < nbRows; ++r )
                {
                    rowData.clear();
                    foreach (int id, subjectID)
                    {
                        rowData << data.at( r ).at( id );
                    }
                    tsSRC << QObject::tr( qPrintable( rowData.join( m_csvSeparator ) ) ) << endl;
                }
            }
            srcFile.flush();
            srcFile.close();

            m_srcFiles.append( srcFile.fileName() );
        }
    }
    return m_srcFiles;
}

QStringList Processing::GetFinalSubjectsList( QString finalSubjectsListFile )
{
    m_finalSubjectsListFile = finalSubjectsListFile;
    QStringList finalSubjectsList;
    QFile file( finalSubjectsListFile );
    if( file.open( QIODevice::ReadOnly ) )
    {
        QTextStream tsFinalSubjectsList( &file );
        while( !tsFinalSubjectsList.atEnd() )
        {
            finalSubjectsList.append( tsFinalSubjectsList.readLine() );
        }
        file.close();
    }
    m_finalSubjectsList = finalSubjectsList;
    return finalSubjectsList;
}

QStringList Processing::GetSubjectsList( QString subjectsListFile, int subjectsCovariatesColumnId )
{
    QStringList subjectsList;
    QFile file( subjectsListFile );
    QList<QStringList> data;
    if( file.open( QIODevice::ReadOnly ) )
    {
        QTextStream tsSubjectsList( &file );
        while( !tsSubjectsList.atEnd() )
        {
            data.append( tsSubjectsList.readLine().split( m_csvSeparator ) );
        }
        file.close();
        int nbRows = data.count();
        int nbColumns = data.at( 0 ).count();
        if( nbColumns < nbRows )
        {
            for( int r = 1; r < nbRows; r++ )
            {
                subjectsList.append( data.at( r ).at( subjectsCovariatesColumnId ) );
            }
        }
        else
        {
            for( int c = 1; c < nbColumns; c++ )
            {
                subjectsList.append( data.at( 0 ).at( c ) );
            }
        }
    }

    return subjectsList;
}


void Processing::ResetProcessing()
{
    m_finalSubjectsListFile.clear();
    m_finalInputFiles.clear();
    m_finalSubjectsList.clear();
    m_srcFiles.clear();
}
