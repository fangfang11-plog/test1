#include<reg51.h>


uchar  wxcode[8]={0xfe,0xfd,0xfb,0xf7,0xEF,0xDF,0xBF,0X7F};//���ɸ���
uchar  dxcode[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
uint count;//��������50ms�Ĵ���������20ʱ��0
long  _time;//�򿪼���������������
uint a[2];//�洢��λ��ǧλ�ϵ���ֵ

#define dula P1
sbit W1 = P2^5;
sbit W2 = P2^6;


void digital_init(){
	
	W1 = 1;
	dula = 0x00;



}


//��ʾ���ֵĺ���
void display(){

   uchar j = 10;
   uchar i = 0;
   
   for(i = 0;i < 2;i++){
   
 
    W2 = 1;
    dula = dxcode[a[i]];//��a�����еĽ��и�λ��ֵ
   
 	j=50;
	while(j--);

	dula=0xff;

   }


}
