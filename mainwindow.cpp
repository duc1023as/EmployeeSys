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
    QString noEmployee = dbUtils->getTotalQuantity("employee_id","employees");
    QString noDepartment = dbUtils->getTotalQuantity("department_id","departments");
    QString noJob = dbUtils->getTotalQuantity("job_id","jobs");

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

void MainWindow::loadAddPage()
{
    dbUtils->setListForCombobox(ui->comboBoxJobTitle,"job_title","jobs");
    dbUtils->setListForCombobox(ui->comboDepart,"department_name","departments");
}

void MainWindow::loadUpdatePage()
{
    dbUtils->setListForCombobox(ui->UcomboBoxJobTitle,"job_title","jobs");
    dbUtils->setListForCombobox(ui->UcomboDepart,"department_name","departments");
    dbUtils->setListForCombobox(ui->uCbboxEmpID,"employee_id","employees");
    //dbUtils->getMangerList(ui->UcomboManager,ui->UcomboDepart->currentText());

}

void MainWindow::on_loginButton_clicked()
{
    if(dbUtils->checkValidUser(ui->userNameTxT->text(),ui->passwordTxt->text())){
        qDebug() << "Login successfully";
        ui->loginStack->setCurrentIndex(1);
        ui->mainStack->setCurrentIndex(0);
        loadData();
    }
    else{
        QMessageBox::critical(this,tr("Error"),tr("Failed to login"));
    }
}


void MainWindow::on_logoutButton_clicked()
{
    ui->loginStack->setCurrentIndex(0);
    selectedButton(ui->searchButton);
    unSelectedButton(ui->addButton);
    unSelectedButton(ui->updateButton);
}


void MainWindow::on_searchButton_clicked()
{
    selectedButton(ui->searchButton);
    unSelectedButton(ui->addButton);
    unSelectedButton(ui->updateButton);
    loadData();
    ui->mainStack->setCurrentIndex(0);
}


void MainWindow::on_addButton_clicked()
{
    selectedButton(ui->addButton);
    unSelectedButton(ui->searchButton);
    unSelectedButton(ui->updateButton);
    ui->mainStack->setCurrentIndex(1);
    loadAddPage();
}


void MainWindow::on_updateButton_clicked()
{
    selectedButton(ui->updateButton);
    unSelectedButton(ui->searchButton);
    unSelectedButton(ui->addButton);
    ui->mainStack->setCurrentIndex(2);
    loadUpdatePage();
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


void MainWindow::on_comboBoxJobTitle_currentIndexChanged(int index)
{
    qDebug()<<ui->comboBoxJobTitle->currentText();
    QStringList result;
    try {
        result = dbUtils->getSalary(ui->comboBoxJobTitle->currentText());
    } catch (...) {
        qDebug() << "Failed to querry";
    }
    ui->minSalary->setText(result.at(0));
    ui->maxSalary->setText(result.at(1));
}

void MainWindow::on_salary_editingFinished()
{
    double salary = ui->salary->text().toDouble();
    double minSalary = ui->minSalary->text().toDouble();
    double maxSalary = ui->maxSalary->text().toDouble();
    if(salary < minSalary || salary > maxSalary){
        QMessageBox::warning(this,tr("Warning about Salary"),tr("You need to change salary"));
    }
}

void MainWindow::on_addEmpButton_clicked()
{
    //qDebug()<<dbUtils->getID("employees","employee_id","first_name",ui->comboManager->currentText());
    Employee employee{
        ui->fNameTxt->text().trimmed(),
        ui->lNameTxt->text().trimmed(),
        ui->emailTxt->text().trimmed(),
        ui->phoneTxt->text().trimmed(),
        ui->hireDate->date(),
        dbUtils->getID("jobs","job_id","job_title",ui->comboBoxJobTitle->currentText()),
        ui->salary->text().trimmed(),
        dbUtils->getID("employees","employee_id","first_name",ui->comboManager->currentText()),
        dbUtils->getID("departments","department_id","department_name",ui->comboDepart->currentText())
    };
    if(dbUtils->addEmployee(employee)){
        qDebug() << dbUtils->getCurrentEmpID();
        QMessageBox::information(this,"Success","Add new an employee successfully");
    }
    else{
        QMessageBox::warning(this,"Error","Failed to add an new employee");
    }
}

void MainWindow::on_comboDepart_currentIndexChanged(int index)
{

    dbUtils->getMangerList(ui->comboManager,ui->comboDepart->currentText());
}


void MainWindow::on_addDependButton_clicked()
{
    Dependent dependent {
        ui->fNameDeTxt->text().trimmed(),
        ui->lNameDeTxt->text().trimmed(),
        ui->comboBoxRelation->currentText(),
        dbUtils->getCurrentEmpID()
    };
    if(dbUtils->addDependent(dependent)){
        QMessageBox::information(this,"Success","Add new dependent successfully");
    }
    else{
        QMessageBox::warning(this,"Error","Failed to add new dependent");
    }
}

void MainWindow::on_uCbboxEmpID_currentTextChanged(const QString &arg1)
{
    QStringList data = dbUtils->getInfoEmp(ui->uCbboxEmpID->currentText());
    QStringList salary;

    ui->UfNameTxt->setText(data.at(0));
    ui->UlNameTxt->setText(data.at(1));
    ui->UemailTxt->setText(data.at(2));
    ui->UphoneTxt->setText(data.at(3));

    ui->UhireDate->setDate(QDate::fromString(data.at(4),"yyyy-MM-dd"));
    qDebug() << QDate::fromString(data.at(4),"yyyy-MM-dd");

    ui->UcomboBoxJobTitle->setCurrentText(data.at(5));
    ui->Usalary->setText(data.at(6));
    ui->UcomboDepart->setCurrentText(data.at(8));
//    ui->UcomboManager->setCurrentText(data.at(7));
    ui->UCurrentManager->setText(data.at(7));
    qDebug() << data.at(7);

    salary = dbUtils->getSalary(data.at(5));
    ui->UminSalary->setText(salary.at(0));
    ui->UmaxSalary->setText(salary.at(1));
}

void MainWindow::on_UcomboDepart_currentTextChanged(const QString &arg1)
{
    dbUtils->getMangerList(ui->UcomboManager,ui->UcomboDepart->currentText());
}

QString MainWindow::getManagerName() const
{
    return managerName;
}

void MainWindow::setManagerName(const QString &newManagerName)
{
    managerName = newManagerName;
}

void MainWindow::on_UcomboManager_activated(int index)
{
    ui->UCurrentManager->setText(ui->UcomboManager->currentText());
}


void MainWindow::on_updateEmpButton_clicked()
{
    Employee e;
    e.fName = ui->UfNameTxt->text();
    e.lName = ui->UlNameTxt->text();
    e.email = ui->UemailTxt->text();
    e.hireDate = ui->UhireDate->date();
    e.phone = ui->UphoneTxt->text();
    e.salary = ui->Usalary->text();
    e.departmentID = dbUtils->getID("departments","department_id","department_name",ui->UcomboDepart->currentText());
    e.jobID = dbUtils->getID("jobs","job_id","job_title",ui->UcomboBoxJobTitle->currentText());
    e.managerID = dbUtils->getID("employees","employee_id","first_name",ui->UcomboManager->currentText());

    qDebug() <<e.phone;
    if(dbUtils->updateEmployee(e,ui->uCbboxEmpID->currentText())){
        QMessageBox::information(this,"Success","Update Successfully");
    }
    else{
        QMessageBox::warning(this,"Error","Failed to update");
    }
}

void MainWindow::on_deleteEmpButton_clicked()
{
    QSharedPointer<QSqlQuery> query(new QSqlQuery());
    query->prepare("DELETE FROM employees WHERE employee_id = "+ui->uCbboxEmpID->currentText());
    if(query->exec()){
        QMessageBox::information(this,"Success","Delete employee successfully");
        dbUtils->setListForCombobox(ui->uCbboxEmpID,"employee_id","employees");
    }
    else{
        QMessageBox::warning(this,"Error","Failed to delete employee");
    }

}

