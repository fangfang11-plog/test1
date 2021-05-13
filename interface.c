#include<intrins.h>
#include"function.h"
#include"data.h"
sbit LED = P1^0;
extern Cursor cursor_m;

uchar Di_quantity;//地图中敌人数量

Enemy Di[10];
TA resist[10];
Home home [3];



uchar cash ;  //打死一敌人一个现金
uchar score;  //过一关得一分

uchar game1_end;//为一时关卡一结束
uchar game2_end;
uchar game3_end;

uchar resist_quantity;//防御塔数量

uchar Di_si ;//死亡敌人个数

uchar home_hp; //家的生命值
//extern TA resist[8][30];//确定防御塔的坐标
//extern Enemy Di[8][30];//用于确定敌人的坐标
/*******************************************************************************
* 函 数 名         : Start_interface()
* 函数功能         : 开始界面显示
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void Start_interface()
{

    uint place=0;
    char ch=0x00;
	lcd_init_graph();

	write_lcd24(28,9,da);//28-48
	write_lcd24(28,12,da);
	write_lcd24(28,15,ta);
	write_lcd24(28,18,fang); 


    write_lcd8(49,0,p1);
	write_lcd8(49,1,l);	
    write_lcd8(49,2,e2);
    write_lcd8(49,3,a);
    write_lcd8(49,4,s);
  	write_lcd8(49,5,e2);

    write_lcd8(49,6,space);

    write_lcd8(49,7,u); 
    write_lcd8(49,8,s); 
    write_lcd8(49,9,i);
    write_lcd8(49,10,n);
    write_lcd8(49,11,g);
    write_lcd8(49,12,space);

    write_lcd8(49,13,h2);
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
	write_lcd8(65,15,e2);
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
	write_lcd8(65,27,h2);
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
	   
	   
	    if(game1_end != 0){  //end == 1时表示游戏结束
			 
			 break;

		}
		else
		{
		    for(i = 0;i < 16;i++)	   //光标显现
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

			 for(i = 0;i < 16;i++)//光标灭
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

			if(com != 0)	 //闪烁过程中判断指令是否为0
			{
				if(com == 0xF0)	   //接收退出指令，手动退出游戏
				{
				  
				  com = 0;
				  EA = 0;
				  clear_all();
				  game1_end = 1;

				  //此处设置重置函数
				  break;//退出游戏
				
				
				}
				else			//接收其他执行进入光标移动函数
				{

			    	cursor_move(temp_x,temp_y);	 //
				    temp_x = cursor_m.x;
					temp_y = cursor_m.y;
					x = temp_x;
					y = temp_y;
					com = 0;

				}

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

	 if(com == 0x08)  //用户设置防御塔
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

	//绘图，8*15方式
	//第一列防御塔
	for(; j < y ;j++)
	{
	
		write_lcd16(i ,j*2 ,hei);

	}
	  
	j = 0;
	i = 48;

	//第二列防御塔
	for(;j < y -3;j++)
	{
	
		write_lcd16(i ,j*2 ,hei);

	} 
	 
	for(count = 0;count < 6;count++)
	{
	
	    write_lcd16(16*count+16,28,hei);
	//	 resist[count+1][14].alive = 1;

	}
	
	//显示游戏信息
    write_lcd8(112,2,c1);
    write_lcd8(112,3,a);	
    write_lcd8(112,4,s);//金钱
    write_lcd8(112,5,h2);
    display_num(112,7,cash);
	write_lcd8(112,11,e1);
	write_lcd8(112,12,n);
	write_lcd8(112,13,e2);
	write_lcd8(112,14,m);
//	write_lcd8(112,15,y);
    write_lcd8(112,17,num9);  //敌人个数
    write_lcd8(112,19,h1);
    write_lcd8(112,20,p2);
    write_lcd8(112,22,num3);
	
//draw home
    write_lcd16(70,0,home1);
	write_lcd16(86,0,home2);
	write_lcd16(102,0,home3);


    timer0_init();//初始化定时器0
    Di_quantity = 0;  //敌人数量初始化为0
	resist_quantity = 0;  //防御塔数量初始化为0
	Di_si = 0;
	game1_end = 0;//游戏开始
	game2_end = 0;
//初始化家结构体
	for(count = 0;count < 3;count++){
	
		 home[count].x = 4 + count;
	     home[count].y = 0;
	
	}

	home_hp  = 3;//可接受三个敌人攻击
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
    
   	uint count = 0;
	uint x = 8;
	uint y = 15;
   	uint i = 0;
	uint j = 0;	

	//绘图，8*15方式
	//第一列防御塔
	for(; j < y ;j++)
	{
	
		write_lcd16(i ,j*2 ,hei);

	}
	
   	for(count = 0;count < 6;count++)
	{
	
	    write_lcd16(16*count+16,28,hei);
	//	 resist[count+1][14].alive = 1;

	}

	//显示游戏信息
    write_lcd8(112,2,c1);
    write_lcd8(112,3,a);	
    write_lcd8(112,4,s);//金钱
    write_lcd8(112,5,h2);
    write_lcd8(112,7,num3);
	write_lcd8(112,11,e1);
	write_lcd8(112,12,n);
	write_lcd8(112,13,e2);
	write_lcd8(112,14,m);
//	write_lcd8(112,15,y);
    write_lcd8(112,17,num9);  //敌人个数
    write_lcd8(112,19,h1);
    write_lcd8(112,20,p2);
    write_lcd8(112,22,num3);
	  


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
		write_lcd8(28,19,e2);

		write_lcd8(45,9,l);
		write_lcd8(45,10,e2); 
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
		write_lcd8(62,20,h2);
		write_lcd8(62,21,r);
		write_lcd8(62,22,e2);
		write_lcd8(62,23,e2);


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
    if(Di_quantity<9){
	
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
			  else if(Di[count].y > 12&&Di[count].x < 5)
			  {
			  
			      to_down(&Di[count]);
			  
			  
			  }
			  else if(Di[count].x > 4)
			  {
	
				to_left(&Di[count]);
	
			  }
	
			  judge_TA1(Di[count].x,Di[count].y,&Di[count]);
			  judge_home(Di[count].x,Di[count].y,&Di[count]); //函数判断房子生命为0时要退出游戏
			  if(game1_end == 1){
			   break;
			  
			  }

		 }
	}

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
/*******************************************************************************
* 函 数 名         : active_TA1(uchar x,uchar y);
* 函数功能         : 障碍物都为未激活的防御塔，通过该函数，使防御塔结构体生命存在
* 输    入         : 要激活的防御塔位置
* 输    出         : 无
*******************************************************************************/


void active_TA1(uchar x,uchar y)
{

	if(cash >0 )
	{	//具有现金时才可进行激活防御塔

	    uint count = 0;
		resist[resist_quantity].x = x;
		resist[resist_quantity].y = y;
	   	resist[resist_quantity].alive = 1; //存在
		resist[resist_quantity].model = 1;
		resist[resist_quantity].interval = 0;//处于非冷却期
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
		 write_lcd16(x*16-16,2*y,xj1);
		
		}

		cash--;
		clear_part(112,7,2);
		display_num(112,7, cash);
		
	}


}








/*******************************************************************************
* 函 数 名         : judge_TA1(uchar x,uchar y,Enemy*di)；
* 函数功能         : 判断敌人是否在激活塔的附近，实现在附近时，敌人生命减一，防御塔进入冷却期
* 输    入         : 敌人坐标，敌人结构指针
* 输    出         : 无
*******************************************************************************/





//传入敌人位置8*15传入
void judge_TA1(uchar x,uchar y,Enemy*di)
{
	 
	uint count = 0;
		
		for(count = 0;count < resist_quantity; count++)
		{
	
			 
			if((resist[count].x == x-1||resist[count].x == x+1)&&resist[count].y ==y)
			{
	
				if(resist[count].interval == 0)
				{
				  	LED = ~LED;
					di->live--;//被击中，生命减少
				    resist[count].interval = 1;//进入冷却期
					 
					if(di->live ==0)
					{
					 
					   //显示敌人个数界面
				
					   clear_part(16*(di->x),2*(di->y),2);	 //屏幕
					   di->x = 0;
					   di->y = 0;
					   di->exist = 0;	 //重置结构体
					  
					   Di_si++;//死亡个数到达9时游戏结束
					   clear_part(112,17,2);
					   clear_part(112,7,2);
					   cash++;//死一个敌人加一个现金
					   display_num(112,7,cash);
					   display_num(112,17,9 - Di_si);
		
		
					   if(Di_si == 9)	  //死亡九个游戏成功
					   {	
					        ET0 = 0;//  关中断
					   		game_win();
					        
							break; //跳出循环，减少步骤
					   }
		
					
					}
				}
			
			}
			else if(resist[count].x == x&&(resist[count].y ==y+1||resist[count].y ==y+2))
			{
			
				if(resist[count].interval ==0)
				{
					di->live--;//被击中，生命减少
					resist[count].interval = 1;//进入冷却期
					if(di->live ==0)
					{
					
					   di->x = 0;
					   di->y = 0;
					   di->exist = 0;
					   Di_si++;//死亡个数到达10时游戏结束
					   if(Di_si == 9)
					   {
					   
					        
						    ET0 = 0;//游戏成功关闭中断
							game_win();
							
					   
		
					   }
				
				
				    }

    	      }
		
		}
	
	}

}





/*******************************************************************************
*******************************************************************************/




/*******************************************************************************
* 函 数 名         : judge_home(uchar x,uchar y,Enemy*di)
* 函数功能         : 判断敌人是否与家相碰，实现相碰后家的生命减少，敌人死亡一个
* 输    入         : 敌人坐标，敌人结构指针
* 输    出         : 无
*******************************************************************************/




void judge_home(uchar x,uchar y,Enemy*di)
{

	uint count = 0;
	//通过遍历将家的坐标与敌人目前的坐标作比较
	for(count = 0;count < 3;count++)
	{

		if(home[count].x == di->x && home[count].y == y)
		{
			home_hp--;
			clear_part(112,22,2);
			switch(home_hp){

			case 0 :write_lcd8(112,22,num0);break;
			case 1:write_lcd8(112,22,num1);	break;
			case 2:write_lcd8(112,22,num2);	break;
			default:break;
			
			
			}

			if(home_hp == 0)
			{
				  //家被摧毁
				  score = 0;
				  cash  = 0;
				  ET0 = 0;
				  failed();	 
				  break;
		
			}
		   //敌人与家碰撞后死亡
			 clear_part(16*(di->x),2*(di->y),2);
			 di->x = 0;
			 di->y = 0;
			 di->exist = 0;
			 Di_si++;//死亡个数到达10时游戏结束
			 clear_part(112,17,2);

			   switch(9 - Di_si)
			   {

			   	case 0:	  write_lcd8(112,17,num0); break;
			   	case 1:	  write_lcd8(112,17,num1); break;
				case 2:	  write_lcd8(112,17,num2);break;
			   	case 3:	  write_lcd8(112,17,num3);break;
			   	case 4:	  write_lcd8(112,17,num4);break;
			   	case 5:	  write_lcd8(112,17,num5);break;
			   	case 6:	  write_lcd8(112,17,num6);break;
			  	case 7:	  write_lcd8(112,17,num7);break;
				case 8:	  write_lcd8(112,17,num8);break;
				case 9:	  write_lcd8(112,17,num9);break;
			    default:  break;
				 }
			   if(Di_si == 9)
			   {	
			        ET0 = 0;//游戏成功关闭中断
			   		game_win();
			   		break;

			   }

		
		
	    }

	}


}




/*******************************************************************************
* 函 数 名         : rebuild_xj()
* 函数功能         : 冷却时间过后重新让陷阱显现
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/

void rebuild_xj()
{
    uint count = 0;
	uint x ;
	uint y ;

    for(count = 0;count < resist_quantity;count++)
	{
		
		
			x = resist[count].x;
			y = resist[count].y;
			
		


			resist[count].interval = 0;//关闭冷却期
			
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







/*******************************************************************************
* 函 数 名         :failed ()
* 函数功能         : 失败界面
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/


void failed ()
{

  	clear_all();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
    write_lcd8(48,15,f);
    write_lcd8(48,17,a);
    write_lcd8(48,19,i);
    write_lcd8(48,21,l);
    game1_end = 1;//游戏结束
    LED = ~ LED;
	clear_all();


}



/*******************************************************************************
* 函 数 名         : game_win();
* 函数功能         : 游戏成功界面
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/


void game_win()
{
	score++;
   	clear_all();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
    write_lcd8(48,10, y);
    write_lcd8(48,11, o);
    write_lcd8(48,12, u);
    write_lcd8(48,14, w);
    write_lcd8(48,15,i);
    write_lcd8(48,16,n);
	write_lcd8(64,10,c1);
	write_lcd8(64,11,a);
	write_lcd8(64,12,s);
	write_lcd8(64,13,h2);
	display_num(64,15,cash);


	write_lcd8(64,17,s);
	write_lcd8(64,18,c2);
	write_lcd8(64,19,o);
	write_lcd8(64,20,r);
	write_lcd8(64,21,e2);

	display_num(64,23,score);


	game1_end = 1;//游戏结束，返回主界面
	while(com != 0x08);
	com = 0;
}





/*******************************************************************************
* 函 数 名         : display_num(uchar x,uchar y,uchar num)
* 函数功能         : 游戏成功界面
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void display_num(uchar x,uchar y,uchar num)
{

	switch(num){
	
	case 0:write_lcd8(x,y,num0);break;
    case 1:write_lcd8(x,y,num1);break;
    case 2:write_lcd8(x,y,num2);break;
    case 3:write_lcd8(x,y,num3);break;
    case 4:write_lcd8(x,y,num4);break;
    case 5:write_lcd8(x,y,num5);break;
    case 6:write_lcd8(x,y,num6);break;
    case 7:write_lcd8(x,y,num7);break;
    case 8:write_lcd8(x,y,num8);break;
    case 9:write_lcd8(x,y,num9);break;		
	
	}


}
