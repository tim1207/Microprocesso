#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QDebug>
#include <string>
#include <pthread.h>
#include <semaphore.h>
#include "gpio.h"
#define LED1_PIN 396
#define LED2_PIN 397
#define LED3_PIN 255
#define LED4_PIN 481

using namespace std;
string status = "";
int times;
int second;
sem_t semaphore;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->counter->setText("00:00");
    second =0;
}

MainWindow::~MainWindow()
{
    delete ui;

}
void led(int pin,int status){
  gpio_export(pin);
  gpio_set_dir(pin,"out");
  if(status==1){
    gpio_set_value(pin,1);
  }else{
    gpio_set_value(pin,0);
    gpio_unexport(pin);
  }
}
//----------------------------------------------
void* led1_thread(void* arg){
    sem_wait(&semaphore);
    for(int i=0;i<times;i++){
      led(LED1_PIN,status[0]-'0');
      sleep(1);
     led(LED1_PIN,1-(status[0]-'0'));
      sleep(1);
    }

    pthread_exit(NULL);
}
void* led2_thread(void* arg){
    sem_wait(&semaphore);
    for(int i=0;i<times;i++){
      led(LED2_PIN,status[1]-'0');
      sleep(1);
      led(LED2_PIN,1-(status[1]-'0'));
      sleep(1);
    }
    pthread_exit(NULL);
}
void* led3_thread(void* arg){
    //string = (char *)input;

    sem_wait(&semaphore);
    for(int i=0;i<times;i++){
      led(LED3_PIN,status[2]-'0');
      sleep(1);
      led(LED3_PIN,1-(status[2]-'0'));
      sleep(1);
    }
    pthread_exit(NULL);
}
void* led4_thread(void* arg){
    sem_wait(&semaphore);
    for(int i=0;i<times;i++){
      led(LED4_PIN,status[3]-'0');
      sleep(1);
      led(LED4_PIN,1-(status[3]-'0'));
      sleep(1);
    }
    pthread_exit(NULL);
}

void* countTime(void* arg){
    sem_wait(&semaphore);
    QLabel* count =  (QLabel*)arg;
    for(int i=0;i<times*2;i++){
        int min , sec;
        sleep(1);
        second++;
        sec = second % 60;
        min = (second - sec)/60;
        QString str_s,str_m;
        if(sec<10){
            str_s = QString::number(0)+QString::number(sec);
        }
        else{
            str_s = QString::number(sec);
        }
        if(min<10){
            str_m = QString::number(0)+QString::number(min);
        }
        else{
            str_m = QString::number(min);
        }
        count->setText(str_m+":"+str_s);
    }
    pthread_exit(NULL);
}


void MainWindow::on_LED_Shining_clicked()
{

    if(ui->LED1->isChecked())
        status[0] = '1';
    else
        status[0] = '0';
    if(ui->LED2->isChecked())
        status[1] = '1';
    else
        status[1] = '0';
    if(ui->LED3->isChecked())
        status[2] = '1';
    else
        status[2] = '0';
    if(ui->LED4->isChecked())
        status[3] = '1';
    else
        status[3] = '0';
    times = ui->times->text().toInt();
    sem_init(&semaphore,0,0);
    QLabel* count = ui->counter;

    pthread_t led1,led2,led3,led4,count_time;
    pthread_create(&led1,NULL,led1_thread,NULL);
    pthread_create(&led2,NULL,led2_thread,NULL);
    pthread_create(&led3,NULL,led3_thread,NULL);
    pthread_create(&led4,NULL,led4_thread,NULL);
    pthread_create(&count_time,NULL,countTime,(void*)count);
    for(int i=0;i<times*5;i++)
    {
      sem_post(&semaphore);
    }

}
