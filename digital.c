#include<reg51.h>
#include"function.h"
uchar  dxcode[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};


#define dula P1
sbit W1 = P2^5;
sbit W2 = P2^6;



//显示数字的函数
void digital(uchar score){
   
//    uchar j = 10;
//    uchar i = 0;
//   	 uchar count =0;


	 W1 = 1;
	 W2 = 0;

	 dula = dxcode[score%10];


}
