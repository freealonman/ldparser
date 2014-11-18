#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QStringList>

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
    void on_openLog_clicked();

    void on_saveCvs_clicked();

private:
    Ui::MainWindow *ui;
    QFile* ld_file;
    QFile* csv_file;
    QStringList parsed_log;

};

#endif // MAINWINDOW_H
