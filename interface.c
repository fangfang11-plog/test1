#include<intrins.h>
#include"function.h"
#include"data.h"
sbit LED = P1^0;
extern Cursor cursor_m;
//extern TA  resist[8][30];//ȷ��������������
//extern Enemy  Di[8][30];
uchar Di_quantity;//��ͼ�е�������
Enemy Di[10];
TA resist[10];
uchar resist_quantity;
uchar Di_si ;//�������˸���
//extern TA resist[8][30];//ȷ��������������
//extern Enemy Di[8][30];//����ȷ�����˵�����
/*******************************************************************************
* �� �� ��         : Start_interface()
* ��������         : ��ʼ������ʾ
* ��    ��         : ��
* ��    ��         : ��
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
* �� �� ��         : cursor_flash(uchar x,uchar y)
* ��������         : �����˸
* ��    ��         : ����
* ��    ��         : ��
*******************************************************************************/
void cursor_flash(uchar x,uchar y)//�˴�x���ֵΪ128��y���ֵΪ30
{//xΪ�����꣬yΪ������

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
	
	      for(j=0;j<1;j++)                                                                                                                             //�ַ�����Ϊ16*8
	      {
			place = x*30+ y;
			y++;
	        write_data(place%256);                                                                                                   //д���ַ��λ
	        write_data(place/256);                                                                                                    //д���ַ��λ
	        write_com(0x24);                                                                                                          //��ַ����
	        write_com(0xb0);                                                                                                          //���������Զ�д
	        write_data(cursor[i+j]);                                                     
	        write_com(0xb2); 	
			
		  }   
		  x++;
		  y = temp_y;	                                                                                                        //�Զ���λ
	    
		}

		x = temp_x;
		_nop_();
		_nop_();
		_nop_();
		 for(i = 0;i < 16;i++)
		{
	
	      for(j=0;j<1;j++)                                                                                                                             //�ַ�����Ϊ16*8
	      {
			place = x*30+ y;
			y++;
	        write_data(place%256);                                                                                                   //д���ַ��λ
	        write_data(place/256);                                                                                                    //д���ַ��λ
	        write_com(0x24);                                                                                                          //��ַ����
	        write_com(0xb0);                                                                                                          //���������Զ�д
	        write_data(0x00);                                                     
	        write_com(0xb2); 	
			
		  }   
		  x++;
		  y = temp_y;	                                                                                                        //�Զ���λ
	    
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
		
			  break;//�˳���Ϸ
			
			
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
* �� �� ��         : cursor_move();
* ��������         : �ƶ����
* ��    ��         : ��
* ��    ��         : ��
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
* �� �� ��         : c_pass1()��
* ��������         : �ؿ�1���澲̬��ʾ
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void c_pass1()
{

   	uint count = 0;
	uint x = 8;
	uint y = 15;
   	uint i = 0;
	uint j = 0;	
//	initialize(); 
	//��һ�з�����
	for(; j < y ;j++)
	{
	
		write_lcd16(i ,j*2 ,hei);
//	    resist[0][j].alive = 1;

	}
	  
	j = 0;
	i = 48;

	//�ڶ��з�����
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
* �� �� ��         : c_pass2()
* ��������         : �ؿ�2������ʾ
* ��    ��         : ��
* ��    ��         : ��
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
* �� �� ��         : c_pass3();
* ��������         : �ؿ�3������ʾ
* ��    ��         : ��
* ��    ��         : ��
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
* �� �� ��         : c_pass_choice();
* ��������         : �ؿ�ѡ�����
* ��    ��         : ��
* ��    ��         : ��
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
* �� �� ��         : print_enemy1(uchar x,uchar y);
* ��������         : ��ӡһ������
* ��    ��         : ��ӡ��λ������
* ��    ��         : 
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
	Di[Di_quantity].exist = 1; //����
	Di[Di_quantity].live = 3;//����Ѫ
	Di_quantity++;
	
	}

}
//���ֵ�ͼΪ8*15��С��
void to_down(Enemy*di)	 //����Ŀǰλ��
{

    clear_part((di->x)*16 ,(di->y)*2 ,2);
	print_enemy1((di->x+1)*16,di->y*2);
    di->x++;

}



void to_left(Enemy*di)	 //����Ŀǰλ��
{

    clear_part((di->x)*16 ,(di->y)*2 ,2);
	print_enemy1((di->x)*16,(di->y)*2-2);
    di->y--;

}


void to_right(Enemy*di)	 //����Ŀǰλ��
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
//		 {//��ͼ�ϸô����ڵ���
//		
//			 print_enemy1(i*16,j);
//		   	 delay();
////				if(i < 7&&Di[i+1][j].exist == 0&&resist[i+1][j].alive==0)//�·����ϰ�ʱ����
////				{//���µ���������
////
////				  to_down(i,j); 
////				
////		
////				}
////				else if(Di[i][j].direction == ll&&Di[i][j-1].exist==0&&resist[i][j-1].alive==0){//���ϰ�ʱ����
////				
////				    to_left(i,j);
////				
////				}
////				else if(Di[i][j].direction == ll&&(Di[i][j-1].exist!=0||resist[i][j-1].alive!=0)){//�������ϰ�ʱ�ı䷽��
////					 
////					 Di[i][j].direction = rr;
////					 to_right(i,j);
////				
////				
////				}
////				else if(Di[i][j].direction == rr&& Di[i][j+1].exist==0&&resist[i][j+1].alive==0){//���ϰ�ʱ����
////				
////					to_right(i,j);
////				
////				}
////				else if(Di[i][j].direction == rr&&(Di[i][j-1].exist!=0||resist[i][j-1].alive!=0)){//�������ϰ�ʱ����
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



//���������
void active_TA1(uchar x,uchar y)
{

    uint count = 0;
	resist[resist_quantity].x = x;
	resist[resist_quantity].y = y;
   	resist[resist_quantity].alive = 1; //����
	resist[resist_quantity].model = 1;
	resist[resist_quantity].interval = 1;//���ڷ���ȴ��
    resist_quantity++;
	if( x == 0&&y != 14)
	{
	
		 write_lcd16(x*16+16,2*y,xj1);
	
	}
	else if(x == 0&&y == 14)
	{
	
		 write_lcd16(x*16 + 16,2*y - 2,xj1);//�߽�
	
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

//�������λ��8*15����
void judge_TA1(uchar x,uchar y,Enemy*di)
{
	 
	uint count = 0;
		
	for(count = 0;count < resist_quantity; count++)
	{
		 
		if(resist[count].x == x-1&&resist[count].y ==y)
		{
		  	LED = ~LED;
			di->live--;//�����У���������
		
			if(di->live ==0)
			{
			    clear_part(16*(di->x),2*(di->y),2);
			   di->x = 0;
			   di->y = 0;
			   di->exist = 0;
			  
			   Di_si++;//������������10ʱ��Ϸ����
			   if(Di_si == 10)
			   {
			   		game_win();
			        //�˴������Ϸʧ�ܽ���
					EA = 0;//��Ϸʧ�ܹر��ж�
			//		failed();
			   

			   }

			
			}
		
		
		}
		else if(resist[count].x == x&&(resist[count].y ==y+1||resist[count].y ==y+2))
		{
		
		
			di->live--;//�����У���������
			if(di->live ==0)
			{
			   
			   di->x = 0;
			   di->y = 0;
			   di->exist = 0;
			   Di_si++;//������������10ʱ��Ϸ����
			   if(Di_si == 10)
			   {
			   
			        //�˴������Ϸʧ�ܽ���
					EA = 0;//��Ϸʧ�ܹر��ж�
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
			
				 write_lcd16(x*16 + 16,2*y - 2,xj1);//�߽�
			
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