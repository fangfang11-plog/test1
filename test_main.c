#include<reg51.h>
#include<intrins.h>
#include<math.h> 
#include"function.h"
sbit b1 = P2^6;
uint read;
Cursor cursor_m;
sbit LED = P1^0;

sbit b2 = P2^7;
extern uchar cash ;  //����һ����һ���ֽ�
extern uchar score;  //��һ�ص�һ��
//0x08��ʾȷ����0x04��ʾ��ͣ��0x02��ʾ������ϣ�0x01��ʾ�������0x0f��ʾ���£�0x80��ʾ����,0XF0��ʾ�˳�
uint com;
//uint com;
uchar interval;

void main()
{


    init();
	com =0;
	cash = 20; //��ʼ�ֽ���
    score = 0; //�÷�
	digital(score);
	
    while(1){
	    Start_interface();//��ʼ����	

        while(com != 0x08);	 //�������������ѡ�����
		com = 0;
		clear_all();
	    c_pass_choice(); 
		cursor_m.x = 0;
        cursor_m.y = 0;

		while(com!=0x02 && com!=0x01&&com != 0x0f);
		 if(com == 0x02)
		 {
		
		     clear_all();
			 com = 0;
			 c_pass1();
		     com = 0;
//		     clear_all();		 		
		
	     }
		 else if (com ==0x01)
		 {
		     clear_all();
		     com = 0;
			 c_pass2();
			 com = 0;
		 
		 }
		 else if(com ==0x0f)
		 {	
		    
			com = 0;
			while(com!=0x02 && com!=0x01&&com != 0x0f);
		    clear_all();

			if(com ==0x02)
			{
			    c_pass3();
			
			}else if(com ==0x01)
			{
			
			  c_pass4();
			
			}
			else if(com ==0x0f)
			{

			   c_pass5();
			
			}
			 com = 0;
					 
		 }
		 

	}

}