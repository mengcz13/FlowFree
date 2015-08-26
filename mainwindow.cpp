#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->PastButton,SIGNAL(clicked(bool)),ui->gamebody,SLOT(past_sec()));
    connect(ui->NextButton,SIGNAL(clicked(bool)),ui->gamebody,SLOT(next_sec()));
    connect(ui->RestartButton,SIGNAL(clicked(bool)),ui->gamebody,SLOT(restart_sec()));
    connect(ui->AutoSolveButton,SIGNAL(clicked(bool)),ui->gamebody,SLOT(autosolve_sec()));
}


MainWindow::~MainWindow()
{
    delete ui;
}
