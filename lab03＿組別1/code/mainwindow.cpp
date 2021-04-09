#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QTime>
void delay( int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}
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
void MainWindow::shine(QLabel *l){
    l->setHidden(false);
}
void MainWindow::off(QLabel *l){
    l->setHidden(true);
}
void MainWindow::check(QCheckBox *c, bool t){
    c->setChecked(t);
}
void MainWindow::on_pushButton_clicked()
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);

    QString times = ui->textEdit->toPlainText();
    int t = times.toInt();
    for(int i = 0 ; i<2*t;i++){
        if(i % 2 ==0 ){
            shine(ui->label_2);
            shine(ui->label_3);
            off(ui->label_4);
            off(ui->label_5);
            check(ui->checkBox,true);
            check(ui->checkBox_2,true);
            check(ui->checkBox_3,false);
            check(ui->checkBox_4,false);
            delay(500);
        }
        else{
            shine(ui->label_4);
            shine(ui->label_5);
            off(ui->label_2);
            off(ui->label_3);
            check(ui->checkBox_3,true);
            check(ui->checkBox_4,true);
            check(ui->checkBox,false);
            check(ui->checkBox_2,false);
            delay(500);
        }

    }
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->label_2->setHidden(!ui->checkBox->isChecked());
    ui->label_3->setHidden(!ui->checkBox_2->isChecked());
    ui->label_4->setHidden(!ui->checkBox_3->isChecked());
    ui->label_5->setHidden(!ui->checkBox_4->isChecked());
}
