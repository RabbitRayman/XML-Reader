#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QXmlStreamReader>
#include <mymodel.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    struct Auth{
        QString lastname;
        QString firstname;
        QString middlename;
        QString birthdate;
    };
    QMap<quint32, Auth> parseAuthor(QXmlStreamReader& xml);
    void addElementDataToMap(QXmlStreamReader& xml, QMap<int, Auth>& map) const;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    MyModel * _model;
};
#endif // MAINWINDOW_H
