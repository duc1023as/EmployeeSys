#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include "db/databaseutils.h"
#include "globalVariables.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void selectedButton(QPushButton *button);
    void unSelectedButton(QPushButton *button);
    void loadData();
    void checkLength(QString& text);
    void loadAddPage();

private slots:
    void on_loginButton_clicked();
    void on_logoutButton_clicked();
    void on_searchButton_clicked();
    void on_addButton_clicked();
    void on_updateButton_clicked();
    void on_deleteButton_clicked();
    void on_techButton_clicked();
    void on_aboutButton_clicked();
    void on_searchBar_returnPressed();
    void on_clearButton_clicked();
    void on_comboBoxJobTitle_currentIndexChanged(int index);
    void on_salary_editingFinished();
    void on_addEmpButton_clicked();

    void on_comboDepart_currentIndexChanged(int index);

    void on_addDependButton_clicked();

private:
    Ui::MainWindow *ui;
    DatabaseUtils *dbUtils;
};
#endif // MAINWINDOW_H
