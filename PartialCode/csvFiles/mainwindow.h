#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QString>
#include <QStandardItemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_Load_clicked();

    void on_pushButton_Save_clicked();

    void on_pushButton_DeleteRows_clicked();

    void on_pushButton_DeleteColumns_clicked();

    void getInfo( QFileInfo filename );

    void on_pushButton_GenerateMatlabInput_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
