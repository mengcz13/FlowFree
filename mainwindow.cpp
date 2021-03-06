#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    selectdialog(new SelectSectionDialog)
{
    ui->setupUi(this);

    connect(ui->PastButton,SIGNAL(clicked(bool)),ui->gamebody,SLOT(past_sec()));
    connect(ui->NextButton,SIGNAL(clicked(bool)),ui->gamebody,SLOT(next_sec()));
    connect(ui->RestartButton,SIGNAL(clicked(bool)),ui->gamebody,SLOT(restart_sec()));
    connect(ui->AutoSolveButton,SIGNAL(clicked(bool)),ui->gamebody,SLOT(autosolve_sec()));

    connect(ui->prefixed_radioButton,SIGNAL(clicked()),ui->RandomButton,SLOT(hide()));
    connect(ui->prefixed_radioButton,SIGNAL(clicked()),ui->size_spinBox,SLOT(hide()));
    connect(ui->prefixed_radioButton,SIGNAL(clicked()),ui->colortype_spinBox_2,SLOT(hide()));
    connect(ui->prefixed_radioButton,SIGNAL(clicked()),ui->size_label,SLOT(hide()));
    connect(ui->prefixed_radioButton,SIGNAL(clicked()),ui->colortype_label_2,SLOT(hide()));
    connect(ui->prefixed_radioButton,SIGNAL(clicked()),ui->PastButton,SLOT(show()));
    connect(ui->prefixed_radioButton,SIGNAL(clicked()),ui->NextButton,SLOT(show()));
    connect(ui->prefixed_radioButton,SIGNAL(clicked()),ui->selectSectionButton,SLOT(show()));
    connect(ui->prefixed_radioButton,SIGNAL(clicked()),ui->label,SLOT(show()));
    connect(ui->prefixed_radioButton,SIGNAL(clicked()),ui->gamebody,SLOT(init()));

    connect(ui->random_radioButton,SIGNAL(clicked()),ui->PastButton,SLOT(hide()));
    connect(ui->random_radioButton,SIGNAL(clicked()),ui->NextButton,SLOT(hide()));
    connect(ui->random_radioButton,SIGNAL(clicked()),ui->selectSectionButton,SLOT(hide()));
    connect(ui->random_radioButton,SIGNAL(clicked()),ui->label,SLOT(hide()));
    connect(ui->random_radioButton,SIGNAL(clicked()),ui->RandomButton,SLOT(show()));
    connect(ui->random_radioButton,SIGNAL(clicked()),ui->size_spinBox,SLOT(show()));
    connect(ui->random_radioButton,SIGNAL(clicked()),ui->colortype_spinBox_2,SLOT(show()));
    connect(ui->random_radioButton,SIGNAL(clicked()),ui->size_label,SLOT(show()));
    connect(ui->random_radioButton,SIGNAL(clicked()),ui->colortype_label_2,SLOT(show()));

    connect(ui->RandomButton,SIGNAL(clicked(bool)),ui->gamebody,SLOT(randomize()));
    connect(ui->size_spinBox,SIGNAL(valueChanged(int)),ui->gamebody,SLOT(set_size(int)));
    connect(ui->colortype_spinBox_2,SIGNAL(valueChanged(int)),ui->gamebody,SLOT(set_colortype(int)));

    ui->prefixed_radioButton->click();

    selectdialog->addsections(ui->gamebody->get_max_sec_num());
    connect(ui->selectSectionButton,SIGNAL(clicked(bool)),selectdialog,SLOT(exec()));
    connect(selectdialog,SIGNAL(sendSelectedSection(int)),ui->gamebody,SLOT(load_section(int)));

    connect(ui->gamebody,SIGNAL(currentSectionChanged(QString)),ui->label,SLOT(setText(QString)));

    ui->gamebody->load_section(0);

}


MainWindow::~MainWindow()
{
    delete ui;
}


