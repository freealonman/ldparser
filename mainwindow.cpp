#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Windows.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::on_openLog_clicked()
{
    QFileDialog fd;
    fd.setAcceptMode(QFileDialog::AcceptOpen);
    fd.setNameFilter("Логи дальномера (*.txt)");
    if (fd.exec())
    {
        ld_file = new QFile(fd.selectedFiles()[0]);
        if(ld_file->open(QIODevice::ReadOnly))
        {
            QTextStream ts(ld_file);
            while ( !ts.atEnd())
            {
                QString l1 = ts.readLine();
                QString l2 = ts.readLine();
                QString l3 = ts.readLine();
                QString l4 = ts.readLine();
                QString l5 = ts.readLine();
                QString date = l2.mid(7, 9);
                QString time = l2.mid(25,8);
                QString h1;
                QString h2;

                if (l5.size() != 52)
                {
                    QString l6 = ts.readLine();
                    QString l7 = ts.readLine();
                    QString l8 = ts.readLine();
                    h1 = l5.mid(37,2) + l5.mid(43,2);
                    h2 = l8.mid(37,2) + l8.mid(43,2);
                    if (l8.size() != 52) {ts.readLine();}
                } else
                {
                    QString l6 = ts.readLine();
                    QString l7 = ts.readLine();
                    h1 = l5.mid(37,2) + l5.mid(43,2);
                    h2 = l7.mid(37,2) + l7.mid(43,2);
                    if (l7.size() != 52) {ts.readLine();}
                }

                QByteArray qb1 = QByteArray::fromHex(h1.toLatin1());
                QByteArray qb2 = QByteArray::fromHex(h2.toLatin1());
                WORD H1 = (qb1[0]*256) + static_cast<byte>(qb1[1]);
                WORD H2 = (qb2[0]*256) + static_cast<byte>(qb2[1]);
                if (H2 == 0) {H2=H1;}
                parsed_log.push_back(date + ";" + time + ";" + QString::number(H1) + ";" + QString::number(H2) + '\n');
            }
            MessageBox(0, L"Файл обработан", L"Завершено", MB_OK);
        }
    }
}

void MainWindow::on_saveCvs_clicked()
{
    QFileDialog fd;
    fd.setAcceptMode(QFileDialog::AcceptSave);

    fd.setNameFilter("csv Высоты (*csv)");
    if (fd.exec())
    {
        csv_file = new QFile(fd.selectedFiles()[0] + ".csv");
        if (csv_file->open(QIODevice::WriteOnly))
        {
            for (int i=0; i < parsed_log.size(); i++)
            {

                csv_file->write(parsed_log[i].toStdString().c_str(), parsed_log[i].size());
            }
            MessageBox(0, L"Сохранение csv", L"Завершено", MB_OK);
            csv_file->close();
        }
    }
}
