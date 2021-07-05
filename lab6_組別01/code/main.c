#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include "main.h"
sem_t semaphere;
int pin[] = {396,397,255,481};
int LEDstatus[4]={0};

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
    sem_wait(&semaphere);
    for(int j = 0 ; j < 4 ; j++){        
        if(LEDstatus[j] == 1){
            turnOn(pin[j]);
        }else{
            turnOff(pin[j]);
        }
    }
    sleep(1);
    for(int j = 0 ; j < 4 ; j++){
        if(LEDstatus[j] == 0){
            turnOn(pin[j]);
        }else{
            turnOff(pin[j]);
        }
    }
    sleep(1);
    sem_post(&semaphere);
    pthread_exit(NULL);
}

int main(int argc,char *argv[]){    

    int times = atoi(argv[2]);
    printf("times: %d\n",times);
    
    for(int i = 0 ; i < 4;i++){
        LEDstatus[i]= argv[1][i]-'0';
        turnOn(pin[i]); 
        turnOff(pin[i]);
    }
    sem_init(&semaphere,0,1);
    pthread_t t[times];
    for(int i = 0 ; i < times ;i++){    
        printf("thread[%d] create\n",i);
        pthread_create(&t[i],NULL,child,(void*)times);        
    }

    for(int i = 0 ; i < times;i++){
        pthread_join(t[i],NULL);

    }

    return 0;

}
