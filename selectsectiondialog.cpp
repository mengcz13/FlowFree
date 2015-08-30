#include "selectsectiondialog.h"
#include "ui_selectsectiondialog.h"

SelectSectionDialog::SelectSectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectSectionDialog)
{
    ui->setupUi(this);
}

SelectSectionDialog::~SelectSectionDialog()
{
    delete ui;
}

void SelectSectionDialog::accept(){
    emit sendSelectedSection(ui->comboBox->currentIndex());
    close();
}

void SelectSectionDialog::addsections(int s){
    for (int i=0;i<s;++i){
        ui->comboBox->addItem(QString("Section %1").arg(i+1));
    }
}
