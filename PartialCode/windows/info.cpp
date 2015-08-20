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

void Info::getInfo(QStringList files)
{
    IUi->adFileInfo_label->setText(getFileInfo(files[0]));
    IUi->rdFileInfo_label->setText(getFileInfo(files[1]));
    IUi->mdFileInfo_label->setText(getFileInfo(files[2]));
    IUi->faFileInfo_label->setText(getFileInfo(files[3]));
    IUi->covariatesFileInfo_label->setText(getFileInfo(files[4]));
}
