#include<reg51.h>
#include<intrins.h>
#include<math.h> 
#include"function.h"
uint read;
Cursor cursor_m;
sbit LED = P1^0;
//0x08��ʾȷ����0x04��ʾ��ͣ��0x02��ʾ������ϣ�0x01��ʾ�������0x0f��ʾ���£�0x80��ʾ����,0XF0��ʾ�˳�
uint com;
//uint com;

void main()
{
  

    init();
	com =0;
    LED = 0;

    while(1){
	    Start_interface();//��ʼ����		 
        while(com != 0x08);	 //�������������ѡ�����
		com = 0;
		clear_all();
	    c_pass_choice();
		while(com!=0x02&&com!=0x01&&com != 0x0f);
		 if(com == 0x02)
		 {
			cursor_m.x = 0;
            cursor_m.y = 0;
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
		 
		 }
		 else if(com ==0x0f)
		 {

		    clear_all();
		 	com = 0;
			c_pass3();
					 
		 }

	}

}