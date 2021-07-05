#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>



#include <map>
#include <string>
#include <iostream>
using namespace std;
void setGPIO(unsigned int gpio, string status)
{
	int io;
	io=open("/dev/demo", O_WRONLY);//對/dev/demo進行唯寫
	if (io<0){
		perror("gpio error");//開檔失敗
		return;
	}
	char buf[10] = {'0'};
	if (status == "on") {
		strcpy(buf,(to_string(gpio)+ " 1").c_str());//gpio跟status放入buf中
	}
	else {
		strcpy(buf, (to_string(gpio) + " 0").c_str());
	}
	cout << buf << endl;
	write(io, buf,8);//寫入
	close(io);//關檔
	return;
}
int main(int argc,char *argv[]){
    char buf[1024] = {0};
    string led = argv[1];
    int arr_pin[] = {396,397,255,481};
    int pin = arr_pin[led[0]-'1'];
    if(argc==3){
	setGPIO(pin,argv[2]);
    }
    if(argc==2){
        FILE *fp = fopen("/dev/demo","w+");
        sprintf(buf,"%d",pin);     
        fwrite(buf,sizeof(pin),1,fp);
        fread(buf,sizeof(buf),1,fp);
        printf("LED%s Status: %s\n",argv[1],buf);
	fclose(fp);
        
     }
	
	return 0;
}
