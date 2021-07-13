#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "QFileDialog"
#include <QMessageBox>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <mymodel.h>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _model = new MyModel(this);

    ui->tableView->setModel(_model);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString str = QFileDialog::getOpenFileName(this, "Выберите файл для чтения", "", "*.xml");
    if (str.isEmpty())
        return;
    QFile file(str);
    if(!file.open(QIODevice::ReadOnly))
        return;

    QByteArray data=file.readAll();

    _model->DeserializeXML(QString::fromUtf8(data));

    file.close();


}

void MainWindow::on_pushButton_2_clicked()
{
    QString str = QFileDialog::getSaveFileName(this, "Выберите файл для сохранения", "", "*.xml");
    if (str.isEmpty())
        return;
    QFile file(str);
    if(!file.open(QIODevice::WriteOnly))
        return;

    QByteArray data;

    data=_model->SerializeXML().toUtf8();

    file.write(data);
    file.close();

}

void MainWindow::on_pushButton_3_clicked()
{
    _model->DelAuth(ui->tableView->currentIndex().row());
}

void MainWindow::on_pushButton_4_clicked()
{
    if((ui->lineEdit->text()!=QString(""))||(ui->lineEdit_2->text()!=QString(""))||(ui->lineEdit_3->text()!=QString("")))
    {
        _model->AddAuthor(ui->lineEdit->text(),ui->lineEdit_2->text(),ui->lineEdit_3->text(), ui->dateEdit->date().toString());
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
    }
        else
        QMessageBox::warning(this,
                             "Ошибка",
                             "Заполните хотя бы одну строку из ФИО",
                             QMessageBox::Ok);
}

void MainWindow::on_pushButton_5_clicked()
{
    if((ui->lineEdit_12->text()!=QString(""))||(ui->lineEdit_13->text()!=QString(""))||(ui->lineEdit_10->text()!=QString("")))
    {
        _model->UpdAuth(ui->tableView->currentIndex().row(),ui->lineEdit_12->text(),ui->lineEdit_13->text(),ui->lineEdit_10->text(), ui->dateEdit_2->date().toString());
        ui->lineEdit_12->clear();
        ui->lineEdit_13->clear();
        ui->lineEdit_10->clear();
    }
    else
        QMessageBox::warning(this,
                             "Ошибка",
                             "Заполните хотя бы одну строку из ФИО",
                             QMessageBox::Ok);
}
