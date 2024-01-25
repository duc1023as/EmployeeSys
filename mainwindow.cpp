#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->infoTable->setAlternatingRowColors(true);
    ui->infoTable->setStyleSheet("alternate-background-color:#E4E4E4;background-color:white;selection-background-color:#1492E6;selection-color:white");
    ui->infoTable->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");

    dbUtils = DatabaseUtils::getInstance();
    if(!dbUtils->connectToDB("employee_management")){
        QMessageBox::critical(this,"Error","Checking whether your server is running or not");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete dbUtils;
}

void MainWindow::selectedButton(QPushButton *button)
{
    button->setStyleSheet("QPushButton{border:none;text-align:left;padding-left:20px;background:#6666FF;color:white;border-left:6px solid #97FFFF;}");
}

void MainWindow::unSelectedButton(QPushButton *button)
{
    button->setStyleSheet("QPushButton{background:#003366;border:none;color:white;text-align:left;padding-left:26px;}QPushButton:hover{border:none;text-align:left;padding-left:26px;background:#6666FF;color:white;}");
}

void MainWindow::loadData()
{
    QString noEmployee = dbUtils->getTotalEmployee();
    QString noDepartment = dbUtils->getTotalDepartment();
    QString noJob = dbUtils->getTotalJob();

    checkLength(noEmployee);
    checkLength(noDepartment);
    checkLength(noJob);

    ui->noEmployee->setText(noEmployee);
    ui->noDepart->setText(noDepartment);
    ui->noJob->setText(noJob);

    dbUtils->setEmployeeDetails(ui->infoTable);
}

void MainWindow::checkLength(QString &text)
{
    if(text.length() == 2){
        text.push_front('0');
    }
    else if(text.length() == 3){
        text.push_front('0');
        text.push_front('0');
    }
}

void MainWindow::on_loginButton_clicked()
{
    if(dbUtils->checkValidUser(ui->userNameTxT->text(),ui->passwordTxt->text())){
        qDebug() << "Login successfully";
        ui->loginStack->setCurrentIndex(1);
        loadData();
    }
    else{
        QMessageBox::critical(this,tr("Error"),tr("Failed to login"));
    }
}


void MainWindow::on_logoutButton_clicked()
{
    ui->loginStack->setCurrentIndex(0);
}


void MainWindow::on_searchButton_clicked()
{
    selectedButton(ui->searchButton);
    unSelectedButton(ui->addButton);
    unSelectedButton(ui->updateButton);
    unSelectedButton(ui->deleteButton);
    unSelectedButton(ui->techButton);
    unSelectedButton(ui->aboutButton);
}


void MainWindow::on_addButton_clicked()
{
    selectedButton(ui->addButton);
    unSelectedButton(ui->searchButton);
    unSelectedButton(ui->updateButton);
    unSelectedButton(ui->deleteButton);
    unSelectedButton(ui->techButton);
    unSelectedButton(ui->aboutButton);
}


void MainWindow::on_updateButton_clicked()
{
    selectedButton(ui->updateButton);
    unSelectedButton(ui->searchButton);
    unSelectedButton(ui->addButton);
    unSelectedButton(ui->deleteButton);
    unSelectedButton(ui->techButton);
    unSelectedButton(ui->aboutButton);
}


void MainWindow::on_deleteButton_clicked()
{
    selectedButton(ui->deleteButton);
    unSelectedButton(ui->searchButton);
    unSelectedButton(ui->addButton);
    unSelectedButton(ui->updateButton);
    unSelectedButton(ui->techButton);
    unSelectedButton(ui->aboutButton);
}


void MainWindow::on_techButton_clicked()
{
    selectedButton(ui->techButton);
    unSelectedButton(ui->searchButton);
    unSelectedButton(ui->addButton);
    unSelectedButton(ui->updateButton);
    unSelectedButton(ui->deleteButton);
    unSelectedButton(ui->aboutButton);
}


void MainWindow::on_aboutButton_clicked()
{
    selectedButton(ui->aboutButton);
    unSelectedButton(ui->searchButton);
    unSelectedButton(ui->addButton);
    unSelectedButton(ui->updateButton);
    unSelectedButton(ui->deleteButton);
    unSelectedButton(ui->techButton);
}


void MainWindow::on_searchBar_returnPressed()
{
    ui->infoTable->setModel(nullptr);
    dbUtils->searchEmployeeDetails(ui->infoTable,ui->searchBar->text().trimmed());
}


void MainWindow::on_clearButton_clicked()
{
    ui->searchBar->setText("");
}

