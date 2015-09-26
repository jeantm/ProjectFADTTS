#ifndef PROCESSING_H
#define PROCESSING_H

#include <QObject>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QMap>
#include <QCheckBox>
#include <QListWidget>
#include <QDebug>
#include <QLocale>


class Processing
{
public:
    Processing();

    QStringList GenerateSrcFiles( QStringList finalInputFiles, QString finalSubjectsListFile,
                                  int subjectsCovariatesColumnId, QString currentFileOutputDir );

    QStringList GetFinalSubjectsList( QString finalSubjectsListFile );

    QStringList GetSubjectsList( QString subjectsListFile, int subjectsCovariatesColumnId );

    void ResetProcessing();

private:
    static const QString m_csvSeparator;

    QString m_finalSubjectsListFile;

    QStringList m_finalInputFiles, m_finalSubjectsList, m_srcFiles;

};

#endif // PROCESSING_H
