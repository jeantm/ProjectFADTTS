#ifndef SUBJECTSLIST_H
#define SUBJECTSLIST_H

#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QString>
#include <QListWidget>

namespace Ui {
class SubjectsList;
}

class SubjectsList : public QDialog
{
    Q_OBJECT
    
public:
    explicit SubjectsList(QWidget *parent = 0);
    ~SubjectsList();

    void loadData();
    
private slots:
    void on_saveFile_pushButton_clicked();


    void filePathSubjectsValue(const QString &newFilePathSubjects);

    void defaultInputPathSubjectsValue(const QString &newDefaultSubjectsPathMainWindow);

    void on_deleteSubjects_pushButton_clicked();

private:
    Ui::SubjectsList *ui;

    QListWidget *SubjectsListWidget;

    QString checkFilePathSubjects;

    QString defaultPathSetSubjects;


    void displayData(QFile &f);

    void displayFileInfo(QString f);
};

#endif // SUBJECTSLIST_H
