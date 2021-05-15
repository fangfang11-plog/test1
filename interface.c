#include<intrins.h>
#include<stdilb.h>
#include"function.h"
#include"data.h"
sbit LED = P1^0;
extern Cursor cursor_m;

uchar Di_quantity;//��ͼ�е�������

Enemy Di[10];
TA resist[10];
Home home [3];
uint num;


uchar cash ;  //����һ����һ���ֽ�
uchar score;  //��һ�ص�һ��

uchar game1_end;//Ϊһʱ�ؿ�һ����
uchar game2_end;
uchar game3_end;
uchar game4_end;
uchar game5_end; 
uchar pao_symbol;//�����ж��Ƿ��ڴ��У�����Ϊһ

uchar resist_quantity;//����������

uchar Di_si ;//�������˸���

uchar home_hp; //�ҵ�����ֵ
//extern TA resist[8][30];//ȷ��������������
//extern Enemy Di[8][30];//����ȷ�����˵�����
/*******************************************************************************
* �� �� ��         : Start_interface()
* ��������         : ��ʼ������ʾ
* ��    ��         : ��
* ��    ��         : ��
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
	write_lcd8(49,1,l2);	
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
	
	write_lcd8(65,14,l2);
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
	write_lcd8(81,9,l2);
	
	write_lcd8(81,11,c2);
	write_lcd8(81,12,u);
	write_lcd8(81,13,r);
	write_lcd8(81,14,s);
	write_lcd8(81,15,o);
	write_lcd8(81,16,r);

	game1_end = 1;//��Ϸ����������������
    game2_end = 1;
	game3_end = 1;
	game4_end = 1;
	game5_end = 1;	 

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
	   
	   
	    if(game1_end == 1&&game2_end == 1&&game3_end ==1&&game4_end == 1&&game5_end == 1){  //end == 1ʱ��ʾ��Ϸ����
			 
			 break;

		}
		else
		{
		    for(i = 0;i < 16;i++)	   //�������
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

			 for(i = 0;i < 16;i++)//�����
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

			if(com != 0)	 //��˸�������ж�ָ���Ƿ�Ϊ0
			{
				if(com == 0xF0)	   //�����˳�ָ��ֶ��˳���Ϸ
				{
				  
				  com = 0;
				  EA = 0;
				  clear_all();
				  game1_end = 1;
				  game2_end = 1;
			   	  game3_end = 1;
				  game4_end = 1;
				  game5_end = 1;
				  //�˴��������ú���
				  break;//�˳���Ϸ
				
				
				}
				else			//��������ִ�н������ƶ�����
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
* �� �� ��         : cursor_move();
* ��������         : �ƶ����
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/


void cursor_move(uint temp_x,uint temp_y)
{

 while(com != 0){

	 if(com == 0x08)  //�û����÷�����
	 {
		if((game4_end == 0||game5_end ==0)&&TA_inprove()==1)
		{

	    }
		else
		{

		active_TA1(cursor_m.x/16, cursor_m.y /2);

		}
		com = 0;

	 }
	 else 
	 if(com == 0x02)
	 {
		 clear_part(temp_x,temp_y,2);
		 write_lcd16(temp_x,temp_y,hei);
	     cursor_m.x-=16;
		 com = 0;
	 }
	 else if(com ==0x01)
	 {
	 	 clear_part(temp_x,temp_y,2);
	 	 write_lcd16(temp_x,temp_y,hei);
	     cursor_m.y-=2;
		 com = 0;
	 }
	 else if(com ==0x0f)
	 {
	 	 clear_part(temp_x,temp_y,2);
		 write_lcd16(temp_x,temp_y,hei);
	     cursor_m.x+=16;

	     com = 0;
	 }
	 else if(com == 0x80){

	 	 clear_part(temp_x,temp_y,2);
	     write_lcd16(temp_x,temp_y,hei);
		 cursor_m.y+=2;
		 com = 0;

	 }
	 

  }

}


/*******************************************************************************
* �� �� ��         : c_pass1()��
* ��������         : �ؿ�1������ʾ
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
	game1_end = 0;//��ʼ�ؿ�1
	//��ͼ��8*15��ʽ
	//��һ�з�����
	for(; j < y ;j++)
	{
	
		write_lcd16(i ,j*2 ,hei);

	}
	  
	j = 0;
	i = 32;

	//�ڶ��з�����
	for(;j < y -3;j++)
	{
	
		write_lcd16(i ,j*2 ,hei);

	} 

	j = 2;
	i = 80;

	for(;j < y -1;j++)
	{
	
		write_lcd16(i ,j*2 ,hei);

	} 


	for(count = 0;count < 4;count++)
	{
	
	    write_lcd16(16*count+16,28,hei);

	}
	
	//��ʾ��Ϸ��Ϣ
    write_lcd8(112,2,c1);
    write_lcd8(112,3,a);	
    write_lcd8(112,4,s);//��Ǯ
    write_lcd8(112,5,h2);
    display_num(112,7,cash);
	write_lcd8(112,11,e1);
	write_lcd8(112,12,n);
	write_lcd8(112,13,e2);
	write_lcd8(112,14,m);
//	write_lcd8(112,15,y);
    write_lcd8(112,17,num9);  //���˸���
    write_lcd8(112,19,h1);
    write_lcd8(112,20,p2);
    write_lcd8(112,22,num3);
	
//draw home
    write_lcd16(70,28,home1);
	write_lcd16(86,28,home2);
	write_lcd16(102,28,home3);


    timer0_init();//��ʼ����ʱ��0
    Di_quantity = 0;  //����������ʼ��Ϊ0
	resist_quantity = 0;  //������������ʼ��Ϊ0
	Di_si = 0;
	game1_end = 0;//��Ϸ��ʼ



//��ʼ���ҽṹ��
	for(count = 0;count < 3;count++){
	
		 home[count].x = 4 + count;
	     home[count].y = 14;
	
	}

	home_hp  = 3;//�ɽ����������˹���
	init_enemy();
	cursor_flash(cursor_m.x,cursor_m.y);

	//�����ؿ���
	game1_end = 1;

}





/*******************************************************************************
* �� �� ��         : c_pass3()��
* ��������         : �ؿ�2���澲̬��ʾ
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void c_pass2()
{
	
   	uint count = 0;
	uint x = 8;
	uint y = 15;
   	uint i = 0;
	uint j = 0;	
	game2_end = 0;//��ʼ�ؿ���

	//��ͼ��8*15��ʽ
	//��һ�з�����
	for(; j < y ;j++)
	{
	
		write_lcd16(i ,j*2 ,hei);

	}
	  
	j = 0;
	i = 48;

	//�ڶ��з�����
	for(;j < y -3;j++)
	{
	
		write_lcd16(i ,j*2 ,hei);

	} 
	 
	for(count = 0;count < 6;count++)
	{
	
	    write_lcd16(16*count+16,28,hei);


	}
	
	//��ʾ��Ϸ��Ϣ
    write_lcd8(112,2,c1);
    write_lcd8(112,3,a);	
    write_lcd8(112,4,s);//��Ǯ
    write_lcd8(112,5,h2);
    display_num(112,7,cash);
	write_lcd8(112,11,e1);
	write_lcd8(112,12,n);
	write_lcd8(112,13,e2);
	write_lcd8(112,14,m);
//	write_lcd8(112,15,y);
    write_lcd8(112,17,num9);  //���˸���
    write_lcd8(112,19,h1);
    write_lcd8(112,20,p2);
    write_lcd8(112,22,num3);
	
//draw home
    write_lcd16(70,0,home1);
	write_lcd16(86,0,home2);
	write_lcd16(102,0,home3);


    timer0_init();//��ʼ����ʱ��0
    Di_quantity = 0;  //����������ʼ��Ϊ0
	resist_quantity = 0;  //������������ʼ��Ϊ0
	Di_si = 0;
//	game1_end = 0;//��Ϸ��ʼ
//	game2_end = 0;
//��ʼ���ҽṹ��
	for(count = 0;count < 3;count++)
	{
	
		 home[count].x = 4 + count;
	     home[count].y = 0;
	
	}

	home_hp  = 3;//�ɽ����������˹��� 

	init_enemy();
	cursor_flash(cursor_m.x,cursor_m.y);

	//�����ؿ���
	game2_end = 1;


}






/*******************************************************************************
* �� �� ��         : c_pass3()��
* ��������         : �ؿ�3���澲̬��ʾ
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void c_pass3()
{
	
   	uint count = 0;
	uint x = 8;
	uint y = 15;
   	uint i = 0;
	uint j = 0;	
	game3_end = 0;//��ʼ�ؿ���

	//��ͼ��8*15��ʽ
	//��һ�з�����
	for(; j < y ;j++)
	{
	
		write_lcd16(i ,j*2 ,hei);

	}
	  
	j = 0;
	i = 48;

	//�ڶ��з�����
	for(;j < y -3;j++)
	{
	
		write_lcd16(i ,j*2 ,hei);

	} 
	 
	for(count = 0;count < 6;count++)
	{
	
	    write_lcd16(16*count+16,28,hei);
	//	 resist[count+1][14].alive = 1;

	}
	
	//��ʾ��Ϸ��Ϣ
    write_lcd8(112,2,c1);
    write_lcd8(112,3,a);	
    write_lcd8(112,4,s);//��Ǯ
    write_lcd8(112,5,h2);
    display_num(112,7,cash);
	write_lcd8(112,11,e1);
	write_lcd8(112,12,n);
	write_lcd8(112,13,e2);
	write_lcd8(112,14,m);
//	write_lcd8(112,15,y);
    write_lcd8(112,17,num9);  //���˸���
    write_lcd8(112,19,h1);
    write_lcd8(112,20,p2);
    write_lcd8(112,22,num3);
	
//draw home
    write_lcd16(70,0,home1);
	write_lcd16(86,0,home2);
	write_lcd16(102,0,home3);


    timer0_init();//��ʼ����ʱ��0
    Di_quantity = 0;  //����������ʼ��Ϊ0
	resist_quantity = 0;  //������������ʼ��Ϊ0
	Di_si = 0;
//	game1_end = 0;//��Ϸ��ʼ
//	game2_end = 0;
//��ʼ���ҽṹ��
	for(count = 0;count < 3;count++){
	
		 home[count].x = 4 + count;
	     home[count].y = 0;
	
	}

	home_hp  = 3;//�ɽ����������˹��� 

	init_enemy();
	cursor_flash(cursor_m.x,cursor_m.y);

	//�����ؿ���
	game3_end = 1;

}


/*******************************************************************************
* �� �� ��         : c_pass2()
* ��������         : �ؿ�2������ʾ
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/


void c_pass4()
{
    
   	uint count = 0;
	uint x = 8;
	uint y = 15;
   	uint i = 0;
	uint j = 0;	
	game4_end = 0;
	//��ͼ��8*15��ʽ
	//��һ�з�����

	for(; j < y ;j++)
	{
	
		write_lcd16(i ,j*2 ,hei);

	}
	
	i = 48;
	j = 0 ;
	for(;j < y - 7;j++)
	{
	   
	   write_lcd16(i,j*2,hei);
	
	}


   	for(count = 0;count < 6;count++)
	{
	
	    write_lcd16(16*count+16,28,hei);

	}


	//��ʾ��Ϸ��Ϣ
    write_lcd8(112,2,c1);
    write_lcd8(112,3,a);	
    write_lcd8(112,4,s);//��Ǯ
    write_lcd8(112,5,h2);
    write_lcd8(112,7,num3);
	write_lcd8(112,11,e1);
	write_lcd8(112,12,n);
	write_lcd8(112,13,e2);
	write_lcd8(112,14,m);
//	write_lcd8(112,15,y);
    write_lcd8(112,17,num9);  //���˸���
    write_lcd8(112,19,h1);
    write_lcd8(112,20,p2);
    write_lcd8(112,22,num3);
	  
	timer0_init();//��ʼ����ʱ��0
    Di_quantity = 0;  //����������ʼ��Ϊ0
	resist_quantity = 0;  //������������ʼ��Ϊ0
	Di_si = 0;
//��ʼ���ҽṹ��
	for(count = 0;count < 3;count++){
	
		 home[count].x = 4 + count;
	     home[count].y = 0;
	
	}
	

	home_hp  = 3;//�ɽ����������˹���
	init_enemy();
	cursor_flash(cursor_m.x,cursor_m.y);
    game4_end = 1;

}



/*******************************************************************************
* �� �� ��         : c_pass3();
* ��������         : �ؿ�3������ʾ
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/

void c_pass5()
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
	 	write_lcd8(28,11,maohao);
		write_lcd8(28,12,l1);
		write_lcd8(28,13,e2);
		write_lcd8(28,14,v);
		write_lcd8(28,15,e2);
		write_lcd8(28,16,l2);
        display_num(28,18,1);

		write_lcd8(45,9,l1);
		write_lcd8(45,10,e2); 
		write_lcd8(45,11,f);
		write_lcd8(45,12,t);
		write_lcd8(45,13,maohao);
		write_lcd8(45,14,l2);
		write_lcd8(45,15,e2); 
		write_lcd8(45,16,v);
		write_lcd8(45,17,e2);
	    write_lcd8(45,18,l2); 
		display_num(45,20,2);

		write_lcd8(62,9,d);
		write_lcd8(62,10,o); 
		write_lcd8(62,11,w);
		write_lcd8(62,12,n);
		write_lcd8(62,13,maohao);
		write_lcd8(62,14,l1);
		write_lcd8(62,15,e2); 
		write_lcd8(62,16,v);
		write_lcd8(62,17,e2);
	    write_lcd8(62,18,l2); 
		display_num(62,20,3);
	
		write_lcd8(78,9,r);
		write_lcd8(78,10,i); 
		write_lcd8(78,11,g);
		write_lcd8(78,12,h2);
		write_lcd8(78,13,t);
		write_lcd8(78,14,maohao);
		write_lcd8(78,15,l1); 
		write_lcd8(78,16,e2);
		write_lcd8(78,17,v);
	    write_lcd8(78,18,e2);
		write_lcd8(78,19,l2); 
		display_num(78,21,4);



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
    if(Di_quantity<9){
	
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

void to_up(Enemy*di)	 //����Ŀǰλ��
{

    clear_part((di->x)*16 ,(di->y)*2 ,2);
	print_enemy1((di->x-1)*16,di->y*2);
    di->x--;

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





void enemy_move1()
{

	uint i = 1;
	uint j = 0; 
	uint count = 0;

   	for(count = 0;count < Di_quantity;count++)
	{
		
	    if(Di[count].exist == 1)
		{

			  if(game1_end == 0)
			  {
			  //�ؿ�ֻ��һ��·�����ߣ����ɶ�ܹ���

				  if(Di[count].y < 13 &&Di[count].x <3)
				  {
				  	  to_right(&Di[count]);
				  
				  }
				  else if(Di[count].y > 12&&Di[count].x < 4)
				  {
				  
				      to_down(&Di[count]);
				  
				  
				  }
				  else if(Di[count].x > 3&&Di[count].x<5&&Di[count].y > 0)
				  {
		
					to_left(&Di[count]);
		
				  }
				  else if(Di[count].x > 3&&Di[count].x<6&&Di[count].y < 1)
				  {
				  
				  	to_down(&Di[count]);
				  
				  }
				  else if(Di[count].x > 5)
				  {
	
					  to_right(&Di[count]);
	
				  }



			  }
			  else if(game1_end == 1)
			  {
			  

			  	  if(Di[count].y < 13 &&Di[count].x < 3)
				  {

					  if(Di[count].x == 1&&!(rand()%2))
					  {
					  
					  	 to_down(&Di[count]);
					  
					  }
					  else if(Di[count].x == 2&&!(rand()%2) )
					  {

						  to_up(&Di[count]);

					  }

				  	  to_right(&Di[count]);
				  
				  }
				  else if(Di[count].y > 12&&Di[count].x < 4)
				  {
				  

				      to_down(&Di[count]);
				  
				  
				  } 
				  else if(Di[count].x > 3&&Di[count].x<6&&Di[count].y > 0)
				  {

					if(Di[count].x == 4&&!(rand()%2))
					  {
					  
					  	 to_down(&Di[count]);
					  
					  }
					  else if(Di[count].x == 5&&!(rand()%2) )
					  {

						  to_up(&Di[count]);

					  }
					to_left(&Di[count]);
		
				  }
				  else if(Di[count].x > 3&&Di[count].x<6&&Di[count].y < 1)
				  {
				  
				  	to_down(&Di[count]);
				  
				  }
				  else if(Di[count].x > 5)
				  {
	
					  to_right(&Di[count]);
	
				  }
			  
			  
			  
			  
			  
			  
			  
			  }
			  judge_TA1(Di[count].x,Di[count].y,&Di[count]);
			  judge_pao(Di[count].x,Di[count].y,&Di[count]);
			  
			  judge_home(Di[count].x,Di[count].y,&Di[count]); //�����жϷ�������Ϊ0ʱҪ�˳���Ϸ

			  if(game1_end == 1&&game2_end ==1&&game3_end == 1&&game4_end == 1&&game5_end == 1){

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





//���������
/*******************************************************************************
* �� �� ��         : active_TA1(uchar x,uchar y);
* ��������         : �ϰ��ﶼΪδ����ķ�������ͨ���ú�����ʹ�������ṹ����������
* ��    ��         : Ҫ����ķ�����λ��
* ��    ��         : ��
*******************************************************************************/


void active_TA1(uchar x,uchar y)
{

	if(cash >0 )
	{	//�����ֽ�ʱ�ſɽ��м��������

	    uint count = 0;
		resist[resist_quantity].x = x;
		resist[resist_quantity].y = y;
	   	resist[resist_quantity].alive = 1; //����
		resist[resist_quantity].level = 1;//�ȼ�һ������������
		resist[resist_quantity].interval = 0;//���ڷ���ȴ��
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
		 write_lcd16(x*16-16,2*y,xj1);
		
		}

		cash--;
		clear_part(112,7,2);
		display_num(112,7, cash);
		
	}


}








/*******************************************************************************
* �� �� ��         : judge_TA1(uchar x,uchar y,Enemy*di)��
* ��������         : �жϵ����Ƿ��ڼ������ĸ�����ʵ���ڸ���ʱ������������һ��������������ȴ��
* ��    ��         : �������꣬���˽ṹָ��
* ��    ��         : ��
*******************************************************************************/





//�������λ��8*15����
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
				    resist[count].interval = 1;//������ȴ��
					di->live--;//�����У���������
				 
					 
					if(di->live ==0)
					{
					 
					   //��ʾ���˸�������
				
					   clear_part(16*(di->x),2*(di->y),2);	 //��Ļ
					   di->x = 0;
					   di->y = 0;
					   di->exist = 0;	 //���ýṹ��
					  
					   Di_si++;//������������9ʱ��Ϸ����
					   clear_part(112,17,2);
					   clear_part(112,7,2);
					   cash++;//��һ�����˼�һ���ֽ�
					   display_num(112,7,cash);
					   display_num(112,17,9 - Di_si);
		
		
					   if(Di_si == 9)	  //�����Ÿ���Ϸ�ɹ�
					   {	
					        ET0 = 0;//  ���ж�
					   		game_win();
					        
							break; //����ѭ�������ٲ���
					   }
		
					
					}
				}
			
			}
			else if(resist[count].x == x&&(resist[count].y ==y+1||resist[count].y ==y+2))
			{
			
				if(resist[count].interval ==0)
				{
					di->live--;//�����У���������
					resist[count].interval = 1;//������ȴ��
					if(di->live ==0)
					{
					
					   di->x = 0;
					   di->y = 0;
					   di->exist = 0;
					   Di_si++;//������������10ʱ��Ϸ����
					   if(Di_si == 9)
					   {
					   
					        
						    ET0 = 0;//��Ϸ�ɹ��ر��ж�
							game_win();
							
					   
		
					   }
				
				
				    }

    	      }
		
		}
	
	}

}





/*******************************************************************************
*******************************************************************************/



void judge_pao(uchar x,uchar y,Enemy*di)
{

	 uint count = 0;
	 uchar i = 0;
     for(count = 0;count < resist_quantity; count++)
	 {
	 
	 	 if(resist[count].level != 2)
		 {
		 	continue;
		 
		 }
		 else{
									 
			if(resist[count].x == x)//�������
			{
				//��Ļ��ʾ����
				for(i = 0;i < 30 ;i+=2)
				{
					write_lcd16(16*x, i , ray);//���߻���ֱ������	
					
				}	   
				  clear_part(16*x , 0, 28); 
			}
			if(resist[count].y == y)//�������
			{
				    

				for(i = 16;i < 128 ;i+=16)
				{
					write_lcd16(i , y , ray);//���߻���ֱ������
				}	   
			
			
			}	

			 pao_symbol = 0;
			 di->live = 0;//�����У���������
			 //��ʾ���˸�������

			 di->x = 0;
			 di->y = 0;
			 di->exist = 0;	 //���ýṹ��
			 Di_si++;//������������9ʱ��Ϸ����
		     clear_part(112,17,2);
		     clear_part(112,7,2);
		     cash++;//��һ�����˼�һ���ֽ�
		     display_num(112,7,cash);
		     display_num(112,17,9 - Di_si);

			 resist[count].level = 1;//����
			 write_lcd16(16*resist[count].x,2*resist[count].y,hei);//�ָ�Ϊ������

			 if(Di_si == 9)	  //�����Ÿ���Ϸ�ɹ�
			 {	
			   
			    ET0 = 0;//  ���ж�
			   	game_win();   
				break; //����ѭ�������ٲ���
			 
			 } 
	
	 	}
	
	 }


} 


/*******************************************************************************
* �� �� ��         : judge_home(uchar x,uchar y,Enemy*di)
* ��������         : �жϵ����Ƿ����������ʵ��������ҵ��������٣���������һ��
* ��    ��         : �������꣬���˽ṹָ��
* ��    ��         : ��
*******************************************************************************/




void judge_home(uchar x,uchar y,Enemy*di)
{

	uint count = 0;
	//ͨ���������ҵ����������Ŀǰ���������Ƚ�
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
				  //�ұ��ݻ�
				  score = 0;
				  cash  = 0;
				  ET0 = 0;
				  failed();	 
				  break;
		
			}
		   //���������ײ������
			 clear_part(16*(di->x),2*(di->y),2);
			 di->x = 0;
			 di->y = 0;
			 di->exist = 0;
			 Di_si++;//������������10ʱ��Ϸ����
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
			        ET0 = 0;//��Ϸ�ɹ��ر��ж�
			   		game_win();
			   		break;

			   }

		
		
	    }

	}


}




/*******************************************************************************
* �� �� ��         : rebuild_xj()
* ��������         : ��ȴʱ�������������������
* ��    ��         : ��
* ��    ��         : ��
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
			
		


			resist[count].interval = 0;//�ر���ȴ��
			
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







/*******************************************************************************
* �� �� ��         :failed ()
* ��������         : ʧ�ܽ���
* ��    ��         : ��
* ��    ��         : ��
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
    write_lcd8(48,21,l2);
    game1_end = 1;//��Ϸ����
    LED = ~ LED;
	clear_all();
	game1_end = 1;//��Ϸ����������������
	game2_end = 1;
	game3_end = 1;
	game4_end = 1;
	game5_end = 1;


}



/*******************************************************************************
* �� �� ��         : game_win();
* ��������         : ��Ϸ�ɹ�����
* ��    ��         : ��
* ��    ��         : ��
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


	game1_end = 1;//��Ϸ����������������
	game2_end = 1;
	game3_end = 1;
	game4_end = 1;
	game5_end = 1;
	while(com != 0x08);
	com = 0;
}

Status TA_inprove()	//�ж��Ƿ��Ѵ��ڷ���������������Ϊ��
{
	 uint count = 0;

	 if(cash > 1){

	   
		 for(count = 0;count < resist_quantity;count++){
		 
		 	if(resist[count].x == cursor_m.x/16 && resist[count].y == cursor_m.y / 2)
			{
	
			     resist[count].level = 2;//����
				 write_lcd16(resist[count].x*16,2*resist[count].y,pao);
				 cash -=2;
				 display_num(112,7,cash);
				 return SUCCESS;
			
			}
		 
		 
		 
		 }
	 }
	 return ERROR;


}



/*******************************************************************************
* �� �� ��         : display_num(uchar x,uchar y,uchar num)
* ��������         : ��Ϸ�ɹ�����
* ��    ��         : ��
* ��    ��         : ��
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





/*******************************************************************************
* �� �� ��         : void pass1_function();
* ��������         : ���йؿ�һʵ�йؿ�һ����
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void pass_function()
{

	 if(game1_end == 0)
	 {
			LED = ~LED;
			if(num % 40 == 0)
			{ 
			 
		    	enemy_move1(); 
			

			}
			 if(num % 80 == 0)
			{
			
			 init_enemy();
			 
			}  	   
			if(num % 50 ==0)
			{
			   num = 0;  
			   rebuild_xj();
			  
			    //������ʵ����Ļ����Ľ���
			  
			}

	}
	else if(game2_end == 0)
	{
			
			if(num % 20 == 0)
			{ 
			 
		    	enemy_move1(); 
			

			}
			 if(num % 40 == 0)
			{
			
			 init_enemy();
			 
			}  	   
			if(num % 50 ==0)
			{
			   num = 0;  
			   rebuild_xj();
			  
			    //������ʵ����Ļ����Ľ���
			  
			}
	
	}
	else if(game3_end == 0)
	{
			LED = ~LED;
			if(num % 10 == 0)
			{ 
			 
		    	enemy_move1(); 

			}
			 if(num % 40 == 0)
			{
			
			 init_enemy();
			 
			}  	   
			if(num % 60 ==0)
			{
			   num = 0;  
			   rebuild_xj();
			  
			    //������ʵ����Ļ����Ľ���
			  
			}
	
	}
	else if(game4_end == 0)
	{
			
			if(num % 10 == 0)
			{ 
			 
		    	enemy_move1(); 

			}
			 if(num % 20 == 0)
			{
			
			 init_enemy();
			 
			}  	   
			if(num % 25 ==0)
			{
			   num = 0;  
			   rebuild_xj();
			      //������ʵ����Ļ����Ľ���
			  
			}
	
	}
	else if(game5_end == 0)
	{
			
			if(num % 10 == 0)
			{ 
			 
		    	enemy_move1(); 

			}
			 if(num % 20 == 0)
			{
			
			 init_enemy();
			 
			}  	   
			if(num % 25 ==0)
			{
			   num = 0;  
			   rebuild_xj();
			  
			    //������ʵ����Ļ����Ľ���
			  
			}
	
	}


}
