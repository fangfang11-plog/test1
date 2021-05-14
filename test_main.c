#include<reg51.h>
#include<intrins.h>
#include<math.h> 
#include"function.h"
uint read;
Cursor cursor_m;
sbit LED = P1^0;
extern uchar cash ;  //打死一敌人一个现金
extern uchar score;  //过一关得一分
//0x08表示确定，0x04表示暂停，0x02表示光标向上，0x01表示光标向左，0x0f表示向下，0x80表示向右,0XF0表示退出
uint com;
//uint com;
uchar interval;

void main()
{
  

    init();
	com =0;
	cash = 10; //初始现金量
    score = 0; //得分
    while(1){
	    Start_interface();//开始界面		 
        while(com != 0x08);	 //按键触发后进入选择界面
		com = 0;
		clear_all();
	    c_pass_choice(); 
			cursor_m.x = 0;
            cursor_m.y = 0;
		while(com!=0x02&&com!=0x01&&com != 0x0f);
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
			 c_pass4();
			 com = 0;
		 
		 }
		 else if(com ==0x0f)
		 {

		    clear_all();
		 	com = 0;
			c_pass3();
			 com = 0;
					 
		 }

	}

}