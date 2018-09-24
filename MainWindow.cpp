#include "MainWindow.h"
#include "ui_mainwindow.h"

#include "QDebug"
#include "QFile"
#include "QMessageBox"
#include "FileUtil.h"

QString MainWindow::basePath = "/home/wolfx/.local/share/applications/";
QString MainWindow::currentPath = "";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->getFiles();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief 获取文件列表，并加入listWidget
 */
void MainWindow::getFiles() {
    QStringList files = FileUtil::getFileNames(basePath);
    qDebug() << files;
    ui->listWidget->clear();
    for (QString fileName : files){
        ui->listWidget->addItem(new QListWidgetItem(fileName));
    }
}

void MainWindow::on_listWidget_itemActivated(QListWidgetItem *item)
{
    currentPath = basePath + item->text();
    QString content = FileUtil::readTextFile(currentPath);
    currentPath = basePath + item->text();
    ui->plainTextEdit->clear();
    ui->plainTextEdit->setPlainText(content);
}

void MainWindow::on_reloadButton_clicked()
{
    this->getFiles();
}

void MainWindow::on_saveButton_clicked()
{
    QString content = ui->plainTextEdit->toPlainText();
    qDebug() << content;
    FileUtil::writeTextFile(currentPath, content);
}

void MainWindow::on_deleteButton_clicked()
{
    if (currentPath == "") {
        QMessageBox::warning(this,"警告","没有东西被选中！");
    } else {
        QFile::remove(currentPath);
        currentPath = "";
        this->getFiles();
        ui->plainTextEdit->clear();
    }

}
