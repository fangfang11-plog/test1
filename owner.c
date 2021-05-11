#include <stdio.h>
#include <reg51.h>
sbit hao = P1^0;
sbit neglect = P1^1;
sbit upup = P1^2;
sbit left = P1^3;
sbit down = P1^4;
sbit right = P1^5;
void initex(){
	TMOD = 0x20;
	TH1 = 253;
	TL1 = 253;
	TR1 = 1;
	SM0 = 0;
	SM1 = 1;
	EA = 1;
	ES = 1;
}
void delay(unsigned int  z)
{
	unsigned int  x,y;
	for(x = z; x > 0; x--)
		for(y = 114; y > 0 ; y--); 		
} 
void main(){
	initex();
	while(1){
		if(hao == 0){
			
			delay (20);
			if(hao == 0){
				
				while(!hao);
				
				SBUF = 0x08;
			}
		}
		if(neglect == 0){
			delay (20);
			if(neglect == 0){
				while(!neglect);
				SBUF = 0x04;
			}
		}
			if(upup == 0){
			delay (20);
			if(upup == 0){
				while(!upup);
				SBUF = 0x02;
			}
		}
			if(left == 0){
			delay (20);
			if(left == 0){
				while(!left);
				SBUF = 0x01;
			}
		}
		if(down == 0){
			delay (20);
			if(down == 0){
				while(!down);
				SBUF = 0x0F;
			}
		}
		if(right == 0){
			
			delay (20);
			if(right == 0){
				
				while(!right);
				
				SBUF = 0x80;
			}
		}

    }
}
void USART_INTR() interrupt 4	//´®¿ÚÖÐ¶Ï
{
	if(TI == 1)
	{
		TI = 0;

		//Delay1s();
	}
}
	
	