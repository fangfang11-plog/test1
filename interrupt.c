#include<reg51.h>
#include"function.h"

uint num;
sbit LED = P1^0;

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


void timer0()interrupt 1
{
    
	TH0 = (65536 - 45972)/256;
    TL0 = (65536 - 45872)%256;
    num++;

	if(num > 39 ){
	
		if(num %40 == 0)
		{
       
	//	init_enemy();
		enemy_move1(); 
		rebuild_xj();
		}

		if(num % 80 ==0){
		    num = 0;
		   init_enemy();
		
		}

	}

}






