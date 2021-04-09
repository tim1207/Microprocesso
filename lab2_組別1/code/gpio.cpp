#include "gpio.h"
int main(int argc,char *argv[]){
    int input;
    string led = argv[1];
    string turn = argv[2];
    int arr_pin[] = {396,397,255,481};
    int pin = arr_pin[led[0]-'1'];
    std:: cout << "使用腳位:" << pin <<endl;        
    if(turn =="on"){
        gpio_export(pin);
        gpio_set_dir(pin,"out");
        gpio_set_value(pin,1);
    }else if(turn =="off"){
        gpio_set_value(pin,0);
        gpio_unexport(pin);
    }
    return input;
}