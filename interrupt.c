#include<reg51.h>
#include"function.h"

extern uint num;
sbit LED = P1^0;
extern uchar score;
void init()
{
	
    SCON = 0x50;
    TMOD |= 0x20;
    TH1 = 253;
    TL1 = 253;
    TR1 = 1;
    REN = 1;
	ES = 1;
    EA = 1;

}



void scon() interrupt 4
{
    if(RI)
    {
	    
	//	LED = ~LED;
        com = SBUF;
        RI = 0;
    }


}



void timer0_init()
{

   TMOD |= 0X01;
   TH0 = (65536 - 45972)/256;
   TL0 = (65536 - 45872)%256;
   EA = 1;
   ET0 = 1;
   TR0 = 1;


}




/*******************************************************************************
* 函 数 名         : void timer0()interrupt 1
* 函数功能         : 定时器中断实现敌人移动功能
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void timer0()interrupt 1
{
    

    num++;
	pass_function();  //进行关卡一时进入关卡一功能
	TH0 = (65536 - 45972)/256;
    TL0 = (65536 - 45872)%256;
}





