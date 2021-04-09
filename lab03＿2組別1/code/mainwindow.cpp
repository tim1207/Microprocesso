#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gpio.h"
#include <QTimer>
#include <QTime>
bool fuck =true;
int arr_pin[] = {396,393,255,481};
void turnOn(unsigned int target){
    gpio_export(target);
    gpio_set_dir(target,"out");
    gpio_set_value(target,1);
}
void turnOff(unsigned int target){
    gpio_set_value(target,0);
    gpio_unexport(target);
}

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
void led_choose(unsigned int x , bool t){
    if(t){
    	gpio_export(x);
    	gpio_set_dir(x,"out");
    	gpio_set_value(x,1);
    }
    else{
	gpio_set_value(x,0);
        gpio_unexport(x);
    }
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
void MainWindow::on_shining_clicked()
{
    ui->led1->setHidden(!ui->check_led1->isChecked());
    ui->led2->setHidden(!ui->check_led1_2->isChecked());
    ui->led3->setHidden(!ui->check_led1_3->isChecked());
    ui->led4->setHidden(!ui->check_led1_4->isChecked());
    led_choose(arr_pin[0],ui->check_led1->isChecked());
    led_choose(arr_pin[1],ui->check_led1_2->isChecked());
    led_choose(arr_pin[2],ui->check_led1_3->isChecked());
    led_choose(arr_pin[3],ui->check_led1_4->isChecked());

}

void MainWindow::on_Switching_on_clicked()
{
    fuck = true;
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);
    int t = ui->spinBox->value();
    t+=1;
    int i =0 ;

    while(fuck)
    {
        if(i % 2 ==0 ){
            shine(ui->led1);
            shine(ui->led2);
            off(ui->led3);
            off(ui->led4);
            check(ui->check_led1,true);
            check(ui->check_led1_2,true);
            check(ui->check_led1_3,false);
            check(ui->check_led1_4,false);
	    turnOn(arr_pin[0]);
            turnOn(arr_pin[1]);
            turnOff(arr_pin[2]);
            turnOff(arr_pin[3]);
            delay(5000/t);
        }
        else{
            shine(ui->led3);
            shine(ui->led4);
            off(ui->led1);
            off(ui->led2);
            check(ui->check_led1_3,true);
            check(ui->check_led1_4,true);
            check(ui->check_led1_2,false);
            check(ui->check_led1,false);
	    turnOff(arr_pin[0]);
            turnOff(arr_pin[1]);
            turnOn(arr_pin[2]);
            turnOn(arr_pin[3]);
            delay(5000/t);
        }

        i++;

    }
}

void MainWindow::on_Switching_off_clicked()
{
    turnOff(arr_pin[0]);
    turnOff(arr_pin[1]);
    turnOff(arr_pin[2]);
    turnOff(arr_pin[3]);
    fuck=false;
    off(ui->led3);
    off(ui->led4);
    off(ui->led1);
    off(ui->led2);
    check(ui->check_led1_3,false);
    check(ui->check_led1_4,false);
    check(ui->check_led1_2,false);
    check(ui->check_led1,false);
}