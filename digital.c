#include<reg51.h>


uchar  wxcode[8]={0xfe,0xfd,0xfb,0xf7,0xEF,0xDF,0xBF,0X7F};//不可更改
uchar  dxcode[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
uint count;//计数到达50ms的次数，到达20时清0
long  _time;//打开计数器后经历的秒数
uint a[2];//存储个位到千位上的数值

#define dula P1
sbit W1 = P2^5;
sbit W2 = P2^6;


void digital_init(){
	
	W1 = 1;
	dula = 0x00;



}


//显示数字的函数
void display(){

   uchar j = 10;
   uchar i = 0;
   
   for(i = 0;i < 2;i++){
   
 
    W2 = 1;
    dula = dxcode[a[i]];//用a数组中的进行各位赋值
   
 	j=50;
	while(j--);

	dula=0xff;

   }


}
