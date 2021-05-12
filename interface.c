#include<intrins.h>
#include"function.h"
#include"data.h"
sbit LED = P1^0;
extern Cursor cursor_m;
//extern TA  resist[8][30];//确定防御塔的坐标
//extern Enemy  Di[8][30];
uchar Di_quantity;//地图中敌人数量
Enemy Di[10];
TA resist[10];
uchar resist_quantity;
uchar Di_si ;//死亡敌人个数
//extern TA resist[8][30];//确定防御塔的坐标
//extern Enemy Di[8][30];//用于确定敌人的坐标
/*******************************************************************************
* 函 数 名         : Start_interface()
* 函数功能         : 开始界面显示
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void Start_interface(){
	uint place=0;
    char ch=0x00;
	lcd_init_graph();
	write_lcd24(28,9,da);//28-48
	write_lcd24(28,12,da);
	write_lcd24(28,15,ta);
	write_lcd24(28,18,fang); 
    write_lcd8(49,0,p1);
	write_lcd8(49,1,l);	
    write_lcd8(49,2,e);
    write_lcd8(49,3,a);
    write_lcd8(49,4,s);
  	write_lcd8(49,5,e);
    write_lcd8(49,6,space);
    write_lcd8(49,7,u); 
    write_lcd8(49,8,s); 
    write_lcd8(49,9,i);
     write_lcd8(49,10,n);
     write_lcd8(49,11,g);
     write_lcd8(49,12,space);
     write_lcd8(49,13,h);
     write_lcd8(49,14,a);
	 write_lcd8(49,15,o);
     write_lcd8(49,16,space);
	 write_lcd8(49,17,t);
	 write_lcd8(49,18,o);
	 write_lcd8(49,19,space);
	 write_lcd8(49,20,s);
	 write_lcd8(49,21,t);
	 write_lcd8(49,22,a);
	 write_lcd8(49,23,r);
	 write_lcd8(49,24,t);
	 write_lcd8(49,25,douhao);
     write_lcd8(49,26,s);
     write_lcd8(49,27,t);
     write_lcd8(49,28,o);
     write_lcd8(49,29,p2);
		write_lcd8(65,0,t);
		write_lcd8(65,1,o);
		write_lcd8(65,2,space);
		write_lcd8(65,3,s);
		write_lcd8(65,4,t);
		write_lcd8(65,5,o);
		write_lcd8(65,6,p2);
		write_lcd8(65,7,douhao);
		write_lcd8(65,8,u);
		write_lcd8(65,9,s);
		write_lcd8(65,10,i);
		write_lcd8(65,11,n);	
		write_lcd8(65,12,g);
		write_lcd8(65,13,space);
		write_lcd8(65,14,l);
		write_lcd8(65,15,e);
		write_lcd8(65,16,f);
		write_lcd8(65,17,t);
		write_lcd8(65,18,douhao);
		write_lcd8(65,19,d);
		write_lcd8(65,20,o);
		write_lcd8(65,21,w);
		write_lcd8(65,22,n);
		write_lcd8(65,23,space);
		write_lcd8(65,24,r);
		write_lcd8(65,25,i);
		write_lcd8(65,26,g);
		write_lcd8(65,27,h);
		write_lcd8(65,28,t);
		write_lcd8(65,29,space);
		write_lcd8(81,0,t);
		write_lcd8(81,1,o);
		write_lcd8(81,3,c2);
		write_lcd8(81,4,o);
		write_lcd8(81,5,n);
		write_lcd8(81,6,t);
		write_lcd8(81,7,r);
		write_lcd8(81,8,o);
		write_lcd8(81,9,l);
		write_lcd8(81,11,c2);
		write_lcd8(81,12,u);
		write_lcd8(81,13,r);
		write_lcd8(81,14,s);
		write_lcd8(81,15,o);
		write_lcd8(81,16,r);

}









/*******************************************************************************
* 函 数 名         : cursor_flash(uchar x,uchar y)
* 函数功能         : 光标闪烁
* 输    入         : 坐标
* 输    出         : 无
*******************************************************************************/
void cursor_flash(uchar x,uchar y)//此处x最大值为128，y最大值为30
{//x为行坐标，y为列坐标

    int place;
	int temp_x = x;	 
	int temp_y = y;
    uint i = 0;
	uint j = 0;
	place = x*30+ y;
    com = 0;
	while(1)
	{

	    for(i = 0;i < 16;i++)
		{
	
	      for(j=0;j<1;j++)                                                                                                                             //字符设置为16*8
	      {
			place = x*30+ y;
			y++;
	        write_data(place%256);                                                                                                   //写入地址高位
	        write_data(place/256);                                                                                                    //写入地址低位
	        write_com(0x24);                                                                                                          //地址设置
	        write_com(0xb0);                                                                                                          //设置数据自动写
	        write_data(cursor[i+j]);                                                     
	        write_com(0xb2); 	
			
		  }   
		  x++;
		  y = temp_y;	                                                                                                        //自动复位
	    
		}

		x = temp_x;
		_nop_();
		_nop_();
		_nop_();
		 for(i = 0;i < 16;i++)
		{
	
	      for(j=0;j<1;j++)                                                                                                                             //字符设置为16*8
	      {
			place = x*30+ y;
			y++;
	        write_data(place%256);                                                                                                   //写入地址高位
	        write_data(place/256);                                                                                                    //写入地址低位
	        write_com(0x24);                                                                                                          //地址设置
	        write_com(0xb0);                                                                                                          //设置数据自动写
	        write_data(0x00);                                                     
	        write_com(0xb2); 	
			
		  }   
		  x++;
		  y = temp_y;	                                                                                                        //自动复位
	    
		}
		x = temp_x;
		_nop_();
		_nop_();
		_nop_();
		if(com != 0)
		{
			if(com == 0xF0)
			{
			  
			  com = 0;
		      LED = ~LED ;
			  EA = 0;
			  clear_all();
		
			  break;//退出游戏
			
			
			}
			else
			{
	    	cursor_move(temp_x,temp_y);
		    temp_x = cursor_m.x;
			temp_y = cursor_m.y;
			x = temp_x;
			y = temp_y;
			com = 0;
			}
		}
	}
}



/*******************************************************************************
* 函 数 名         : cursor_move();
* 函数功能         : 移动光标
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/


void cursor_move(uint temp_x,uint temp_y)
{

 while(com != 0){

	 if(com == 0x08)
	 {

	    active_TA1(cursor_m.x/16, cursor_m.y /2);
		com = 0;
	 }
	 else 
	 if(com == 0x02)
	 {
		 clear_part(temp_x,temp_y,2);
		 write_lcd16(temp_x,temp_y,hei);
	     cursor_m.x-=16;
		 com = 0;
		//cursor_flash(cursor_m.x,cursor_m.y);
	 }
	 else if(com ==0x01)
	 {
	 	 clear_part(temp_x,temp_y,2);
	 	 write_lcd16(temp_x,temp_y,hei);
	     cursor_m.y-=2;
		 com = 0;
	//	 cursor_flash(cursor_m.x,cursor_m.y);
	 }
	 else if(com ==0x0f)
	 {
	 	 clear_part(temp_x,temp_y,2);
		 write_lcd16(temp_x,temp_y,hei);
	     cursor_m.x+=16;
	//	 cursor_flash(cursor_m.x,cursor_m.y);
	     com = 0;
	 }
	 else if(com == 0x80){
	 	 clear_part(temp_x,temp_y,2);
	     write_lcd16(temp_x,temp_y,hei);
		 cursor_m.y+=2;
		 com = 0;
	//	 cursor_flash(cursor_m.x,cursor_m.y);
	 }
	 

  }

}
/*******************************************************************************
* 函 数 名         : c_pass1()；
* 函数功能         : 关卡1界面静态显示
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void c_pass1()
{

   	uint count = 0;
	uint x = 8;
	uint y = 15;
   	uint i = 0;
	uint j = 0;	
//	initialize(); 
	//第一列防御塔
	for(; j < y ;j++)
	{
	
		write_lcd16(i ,j*2 ,hei);
//	    resist[0][j].alive = 1;

	}
	  
	j = 0;
	i = 48;

	//第二列防御塔
	for(;j < y -3;j++)
	{
	
		write_lcd16(i ,j*2 ,hei);
//		 resist[3][j].alive = 1;

	} 
	 
	j = 0;
	i = 112;
	for(; j < y ;j++)
	{
	
		write_lcd16(i ,j*2 ,hei);
      //  resist[7][j].alive = 1;

	}

	for(count = 0;count < 6;count++)
	{
	
	    write_lcd16(16*count+16,28,hei);
	//	 resist[count+1][14].alive = 1;

	}
    timer0_init();
    Di_quantity = 0;
	resist_quantity = 0;
	Di_si = 0;
	init_enemy();
	cursor_flash(cursor_m.x,cursor_m.y);

}

/*******************************************************************************
* 函 数 名         : c_pass2()
* 函数功能         : 关卡2界面显示
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void c_pass2()
{
    
	uint x = 100;
	uint y = 30;
   	uint i = 2;
	uint j = 0;
	for(;j < y;j+=2){
	
		write_lcd16(i ,j ,hei);

	}

	j = 0;
	i = 2 + 40;

	for(;j < y - 4;j+=2){
	
		write_lcd16(i ,j ,hei);

	}

	j = 4;
	i = 2 + 40+40;

	for(;j < y ;j+=2){
	
		write_lcd16(i ,j ,hei);

	}



}



/*******************************************************************************
* 函 数 名         : c_pass3();
* 函数功能         : 关卡3界面显示
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void c_pass3()
{
    
	uint x = 100;
	uint y = 30;
   	uint i = 2;
	uint j = 0;
	for(;j < y;j+=2){
	
		write_lcd16(i ,j ,hei);

	}

	j = 0;
	i = 2 + 40;

	for(;j < y -10;j+=2){
	
		write_lcd16(i ,j ,hei);

	}

	j = 10;
	i = 2 + 40 + 40;

	for(;j < y ;j+=2){
	
		write_lcd16(i ,j ,hei);

	}




}







/*******************************************************************************
* 函 数 名         : c_pass_choice();
* 函数功能         : 关卡选择界面
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/


void c_pass_choice(){

     while(com!=0x02&&com!=0x01&&com!=0x0f){
	    write_lcd8(28,9,u);//28-48
		write_lcd8(28,10,p2);

		write_lcd8(28,12,p1);
		write_lcd8(28,13,a);
		write_lcd8(28,14,s);
		write_lcd8(28,15,s);
		write_lcd8(28,17,o);
        write_lcd8(28,18,n);
		write_lcd8(28,19,e);

		write_lcd8(45,9,l);
		write_lcd8(45,10,e); 
		write_lcd8(45,11,f);
		write_lcd8(45,12,t);
		write_lcd8(45,14,p1);
		write_lcd8(45,15,a); 
		write_lcd8(45,16,s);
		write_lcd8(45,17,s);
	    write_lcd8(45,19,t); 
		write_lcd8(45,20,w);
		write_lcd8(45,21,o);

		write_lcd8(62,9,d);
		write_lcd8(62,10,o); 
		write_lcd8(62,11,w);
		write_lcd8(62,12,n);
		write_lcd8(62,14,p1);
		write_lcd8(62,15,a); 
		write_lcd8(62,16,s);
		write_lcd8(62,17,s);
	    write_lcd8(62,19,t); 
		write_lcd8(62,20,h);
		write_lcd8(62,21,r);
		write_lcd8(62,22,e);
		write_lcd8(62,23,e);


	}

}




/*******************************************************************************
* 函 数 名         : print_enemy1(uchar x,uchar y);
* 函数功能         : 打印一个敌人
* 输    入         : 打印的位置坐标
* 输    出         : 
*******************************************************************************/

void print_enemy1(uchar x,uchar y)
{

	write_lcd16(x,y,enemy1);


}


void init_enemy()
{
    if(Di_quantity<10){
	
	print_enemy1(16,0);
   	Di[Di_quantity].x = 1;
	Di[Di_quantity].y = 0;
	Di[Di_quantity].exist = 1; //存在
	Di[Di_quantity].live = 3;//三点血
	Di_quantity++;
	
	}

}
//划分地图为8*15个小块
void to_down(Enemy*di)	 //输入目前位置
{

    clear_part((di->x)*16 ,(di->y)*2 ,2);
	print_enemy1((di->x+1)*16,di->y*2);
    di->x++;

}



void to_left(Enemy*di)	 //输入目前位置
{

    clear_part((di->x)*16 ,(di->y)*2 ,2);
	print_enemy1((di->x)*16,(di->y)*2-2);
    di->y--;

}


void to_right(Enemy*di)	 //输入目前位置
{

    clear_part((di->x)*16 ,(di->y)*2 ,2);
	print_enemy1((di->x)*16,(di->y)*2+2);
    di->y++;

}



void enemy_move1(){

	uint i = 1;
	uint j = 0; 
	uint count = 0;

   	for(count = 0;count < Di_quantity;count++){
		  
	    if(Di[count].exist == 1)
		{
			  if(Di[count].y < 13 &&Di[count].x <4)
			  {
			  	  to_right(&Di[count]);
			  
			  }
			  else if(Di[count].y > 12&&Di[count].x < 6)
			  {
			  
			      to_down(&Di[count]);
			  
			  
			  }
			  else if(Di[count].x > 5)
			  {
	
				to_left(&Di[count]);
	
			  }
	
			  judge_TA1(Di[count].x,Di[count].y,&Di[count]);

		 }
	}
//	for(i = 1 ;i < 8 ;i++){
//	   	 
//	    for(j = 0;j < 30;j++ ){
////		 	print_enemy1((i+1)*16,j);
////			delay();
//
//		 if(Di[i][j].exist == 1)
//		 {//地图上该处存在敌人
//		
//			 print_enemy1(i*16,j);
//		   	 delay();
////				if(i < 7&&Di[i+1][j].exist == 0&&resist[i+1][j].alive==0)//下方无障碍时向下
////				{//向下的坐标中有
////
////				  to_down(i,j); 
////				
////		
////				}
////				else if(Di[i][j].direction == ll&&Di[i][j-1].exist==0&&resist[i][j-1].alive==0){//无障碍时向左
////				
////				    to_left(i,j);
////				
////				}
////				else if(Di[i][j].direction == ll&&(Di[i][j-1].exist!=0||resist[i][j-1].alive!=0)){//向左有障碍时改变方向
////					 
////					 Di[i][j].direction = rr;
////					 to_right(i,j);
////				
////				
////				}
////				else if(Di[i][j].direction == rr&& Di[i][j+1].exist==0&&resist[i][j+1].alive==0){//无障碍时向左
////				
////					to_right(i,j);
////				
////				}
////				else if(Di[i][j].direction == rr&&(Di[i][j-1].exist!=0||resist[i][j-1].alive!=0)){//向右有障碍时向左
////				 
////				 Di[i][j].direction = ll;
////				 to_left(i,j);
////				
////				
////				}
//		
//			 }
//		}
//
//	}
}	   


void delay(){

   uint i,j;
   i = 100;
   j = 1100;
   for(;i > 0;i--){
   
   
     for(j = 1100;j > 0;j--){
	 
	 
	 }
   
   
   } 

}



//激活防御塔
void active_TA1(uchar x,uchar y)
{

    uint count = 0;
	resist[resist_quantity].x = x;
	resist[resist_quantity].y = y;
   	resist[resist_quantity].alive = 1; //存在
	resist[resist_quantity].model = 1;
	resist[resist_quantity].interval = 1;//处于非冷却期
    resist_quantity++;
	if( x == 0&&y != 14)
	{
	
		 write_lcd16(x*16+16,2*y,xj1);
	
	}
	else if(x == 0&&y == 14)
	{
	
		 write_lcd16(x*16 + 16,2*y - 2,xj1);//边角
	
	}
	else if(x != 0&&y == 14)
	{
	
	   write_lcd16(x*16,2*y-2,xj1);
	   write_lcd16(x*16,2*y-4,xj1);
	
	}
	else
	{
	
     write_lcd16(x*16+16,2*y,xj1);
	
	}



}

//传入敌人位置8*15传入
void judge_TA1(uchar x,uchar y,Enemy*di)
{
	 
	uint count = 0;
		
	for(count = 0;count < resist_quantity; count++)
	{
		 
		if(resist[count].x == x-1&&resist[count].y ==y)
		{
		  	LED = ~LED;
			di->live--;//被击中，生命减少
		
			if(di->live ==0)
			{
			    clear_part(16*(di->x),2*(di->y),2);
			   di->x = 0;
			   di->y = 0;
			   di->exist = 0;
			  
			   Di_si++;//死亡个数到达10时游戏结束
			   if(Di_si == 10)
			   {
			   		game_win();
			        //此处添加游戏失败界面
					EA = 0;//游戏失败关闭中断
			//		failed();
			   

			   }

			
			}
		
		
		}
		else if(resist[count].x == x&&(resist[count].y ==y+1||resist[count].y ==y+2))
		{
		
		
			di->live--;//被击中，生命减少
			if(di->live ==0)
			{
			   
			   di->x = 0;
			   di->y = 0;
			   di->exist = 0;
			   Di_si++;//死亡个数到达10时游戏结束
			   if(Di_si == 10)
			   {
			   
			        //此处添加游戏失败界面
					EA = 0;//游戏失败关闭中断
					failed();
			   

			   }
		
		
		}
	
	
	}

}

}

void rebuild_xj()
{
    uint count = 0;
	uint x ;
	uint y ;

    for(count = 0;count < resist_quantity;count++)
	{
			x = resist[count].x;
			y = resist[count].y;


			if( x == 0&&y != 14)
			{
			
				 write_lcd16(x*16+16,2*y,xj1);
			
			}
			else if(x == 0&&y == 14)
			{
			
				 write_lcd16(x*16 + 16,2*y - 2,xj1);//边角
			
			}
			else if(x != 0&&y == 14)
			{
			
			   write_lcd16(x*16,2*y-2,xj1);
			   write_lcd16(x*16,2*y-4,xj1);
			
			}
			else
			{
			
		     write_lcd16(x*16+16,2*y,xj1);
			
			}





	}
  





}





void failed ()
{

  	clear_all();
    write_lcd8(48,15,f);
   write_lcd8(48,17,a);
    write_lcd8(48,19,i);
   write_lcd8(48,21,l);




}



void game_win()
{

   	clear_all();
    write_lcd8(48,15, y);
   write_lcd8(48,17, o);
    write_lcd8(48,19, u);
   write_lcd8(48,23, w);
   write_lcd8(48,25,i);
   write_lcd8(48,27,n);


}