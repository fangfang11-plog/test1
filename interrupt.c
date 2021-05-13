#include<reg51.h>
#include"function.h"

uint num;
sbit LED = P1^0;

extern uchar game1_end;
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



void timer0_init(){

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
    
	TH0 = (65536 - 45972)/256;
    TL0 = (65536 - 45872)%256;
    num++;

	pass1_function();  //进行关卡一时进入关卡一功能


}





/*******************************************************************************
* 函 数 名         : void pass1_function();
* 函数功能         : 进行关卡一实行关卡一功能
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void pass1_function()
{
	 if(game1_end == 0)
	 {

		 if(num > 20 )
		 {
		
			if(num %20 == 0)
			{ 
			 
		    	enemy_move1(); 
			

			}
			 if(num%80 == 0)
			{
			
			 init_enemy();
			 
			}  	   
			if(num % 100 ==0)
			{
			   num = 0;  
			   rebuild_xj();
			  
			    //包括真实与屏幕陷阱的建立
			  
			}
	
		}

	}


}



