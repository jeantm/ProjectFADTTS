#include "info.h"
#include "ui_info.h"

Info::Info(QWidget *parent) :
    QDialog(parent),
    IUi(new Ui::Info)
{
    IUi->setupUi(this);
}

Info::~Info()
{
    delete IUi;
}


/************ Public functions ************/
void Info::displayInfo(QStringList files)
{
    IUi->adFileInfo_label->setText( files.at(0) );
    IUi->rdFileInfo_label->setText( files.at(1) );
    IUi->mdFileInfo_label->setText( files.at(2) );
    IUi->faFileInfo_label->setText( files.at(3) );
    IUi->covariatesFileInfo_label->setText( files.at(4) );
}
