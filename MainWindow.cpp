#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QInputDialog>
#include <QProcess>

#include "MainWindow.h"
#include "ui_mainwindow.h"
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
    int success = FileUtil::writeTextFile(currentPath, content);
    qDebug() << success;
    if (success == 0) {
        QMessageBox::information(this,"消息","保存成功");
    } else {
        QMessageBox::warning(this,"警告","保存失败");
    }
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
        QMessageBox::information(this,"消息","删除成功");
    }
}

void MainWindow::on_newButton_clicked()
{
    bool ok = false;
    QString fileName = QInputDialog::getText(this, "对话框", "请输入文件名（无后缀）" , QLineEdit::Normal, "", &ok);
    if (ok) {
        qDebug() << fileName;
        QString content = "[Desktop Entry]";
        FileUtil::writeTextFile(basePath + fileName + ".desktop", content);
        QProcess *cmd = new QProcess;
        cmd->start("chmod +x " + basePath + fileName + ".desktop"); // 赋予执行权限
        cmd->waitForFinished();
        delete cmd;
        this->on_reloadButton_clicked();
    }
}
