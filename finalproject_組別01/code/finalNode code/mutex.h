#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include "main.h"
pthread_mutex_t mutex;
int counter=0;
int pin[] = {396,397,255,481};
int LEDStatus[4]={0};

void turnOn(unsigned int target){
    char s[] = "out";
    gpio_export(target);
    gpio_set_dir(target,"out");
    gpio_set_value(target,1);
}
void turnOff(unsigned int target){  
    gpio_set_value(target,0);
    gpio_unexport(target);
}
void *child(void *arg){
    pthread_mutex_lock(&mutex);
    for(int j = 0 ; j < 4 ; j++){
        if(LEDStatus[j] == 1){
            turnOn(pin[j]);
        }else{
            turnOff(pin[j]);
        }
    }
    sleep(1);
    for(int j = 0 ; j < 4 ; j++){
        if(LEDStatus[j] == 0){
            turnOn(pin[j]);
        }else{
            turnOff(pin[j]);
        }
    }
    sleep(1);
    pthread_mutex_unlock(&mutex);;
    pthread_exit(NULL);
}