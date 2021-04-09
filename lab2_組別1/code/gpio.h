#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
using namespace std;
int gpio_export(unsigned int gpio){
    int fd,len;
    char buff[64];
    fd = open("/sys/class/gpio/export",O_WRONLY);
    if (fd<0){
        perror("gpio/export");
        return fd;
    }

    len = snprintf(buff,sizeof(buff),"%d",gpio);
    write(fd,buff,len);
    close(fd);
    return 0;    
}
int gpio_unexport(unsigned int gpio){
    int fd,len;
    char buff[64];
    fd = open("/sys/class/gpio/unexport",O_WRONLY);
    if (fd<0){
        perror("gpio/unexport");
        return fd;
    }

    len = snprintf(buff,sizeof(buff),"%d",gpio);
    write(fd,buff,len);
    close(fd);
    return 0;    
}
int gpio_set_dir(unsigned int gpio,string dirStatus){
    int fd;
    char buff[64];
    
    snprintf(buff,sizeof(buff),"/sys/class/gpio/gpio%d/direction",gpio);

    fd = open(buff,O_WRONLY);
    if(fd<0){
        perror("gpio/direction");
        return fd;
    }
    if(dirStatus == "out"){
        write(fd,"out",4);
    }else{
        write(fd,"in",3);
    }
    close(fd);
    return 0;
    
}
int gpio_set_value(unsigned int gpio,int value){
    int fd;
    char buff[64];

    snprintf(buff,sizeof(buff),"/sys/class/gpio/gpio%d/value",gpio);

    fd=open(buff,O_WRONLY);
    if(fd<0){
        perror("gpio/set-value");
        return fd;
    }

    if(value == 0 ){
        write(fd,"0",2);
    }else{
        write(fd,"1",2);        
    }
    close(fd);
    return 0;
}

