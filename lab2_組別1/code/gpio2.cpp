#include "gpio.h"
void turnOn(unsigned int target){
    gpio_export(target);
    gpio_set_dir(target,"out");
    gpio_set_value(target,1);
}
void turnOff(unsigned int target){
    gpio_set_value(target,0);
    gpio_unexport(target);
}

int main(){
    int times;
    cin>>times;
    int arr_pin[4] = {396,397,255,481};
    
    for(int i = 0 ; i < times*2; i++){
        if( i % 2 == 0)
        {
            turnOn(arr_pin[0]);
            turnOn(arr_pin[1]);
            turnOff(arr_pin[2]);
            turnOff(arr_pin[3]);
        }else{
            turnOff(arr_pin[0]);
            turnOff(arr_pin[1]);
            turnOn(arr_pin[2]);
            turnOn(arr_pin[3]);
        }
        sleep(1);
    }
    return 0;
}