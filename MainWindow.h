#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QMainWindow"
#include "QString"
#include "QListWidgetItem"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_listWidget_itemActivated(QListWidgetItem *item);

    void on_reloadButton_clicked();

    void on_saveButton_clicked();

    void on_deleteButton_clicked();

private:
    Ui::MainWindow *ui;
    void getFiles();
    static QString basePath;
    static QString currentPath;
};

#endif // MAINWINDOW_H
