#include<reg51.h>
#include<intrins.h>
#include"function.h"

/*******************************************************************************
* 函 数 名         : status_check();
* 函数功能         : 检查LCD目前状态，为忙时不进入操作
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void status_check(){

do{ 
    RD = 0;//读数据
    WR = 1;
    CE = 0;
    CD = 1;

}while(DATA_PORT&0XC0);



}

/*******************************************************************************
* 函 数 名         : write_data(char dat);
* 函数功能         : 向LCD中写入数据
* 输    入         : char
* 输    出         : 无
*******************************************************************************/
void cursor_position()
{

	CD = 0;
    CE=0;                        //LCD使能
	WRIT=0;  
	write_data(0x00);
	write_data(0x00);
	write_com(0X21);
	CE = 1;


}


/*******************************************************************************
* 函 数 名         : write_data(char dat);
* 函数功能         : 向LCD中写入数据
* 输    入         : char
* 输    出         : 无
*******************************************************************************/

void write_data(char dat){

	//status_check();
	CD=0;                         //数据
	CE=0;                        //LCD使能
	WRIT=0;                     //写
	DATA_PORT=dat;             //把数据送到P口
	delay_lcd(1);             //当晶振较高时加延时
	WRIT=1;                  //关写
	CE=1;                   //关使能

}



/*******************************************************************************
* 函 数 名         : write_text(char text)；
* 函数功能       : 	 写文本内容
* 输    入         : char
* 输    出         : 无
*******************************************************************************/

void write_text(char text){

    //status_check();
	CD=0;                //数据
	CE=0;                //LCD使能
	WRIT=0;              //写
	DATA_PORT=text;      //把数据送到P口
	delay_lcd(1);        //当晶振较高时加延时
	WRIT=1;              //关写
	CE=1;                //关使能

}



//--------------------------------------------
//  LM4229初始化函数
//--------------------------------------------
void lcd_init_text(){

	//	status_check();
	write_data(0);
	write_data(0);
	write_com(0x40);            //set text home address
	write_data(30); 
	write_data(0);
	write_com(0x41);            //set text area;
	write_com(0x84);            //text attribute mode
	write_com(0x94);            //text on graphic off

}





/*******************************************************************************
* 函 数 名         : write_com(char com)；
* 函数功能         : 写指令
* 输    入         : 指令
* 输    出         : 无
*******************************************************************************/ 
void write_com(char com){

	CD=1;             //命令
	CE=0;
	WRIT=0;
	DATA_PORT=com;
	delay_lcd(1);        //当晶振较高时加延时
	WRIT=1;
	CE=1;   

}



/*******************************************************************************
* 函 数 名         : clr_lcd(char x,char y,int length);
* 函数功能         : 清屏
* 输    入         : 坐标
* 输    出         : 无
*******************************************************************************/
void clr_lcd(char x,char y,int length){

	int i,place;
	place=x*30+y;
	write_data(place&0xff);
	write_data(place/256);
	write_com(0x24);                //设置
	for(i=0;i<length;i++)
	write_data(0xff);               //写入空格，清屏
	write_com(0xb2);                //关闭自动写


}




/*******************************************************************************
* 函 数 名         : lcd_init_graph()；
* 函数功能         : 图形界面初始化
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void lcd_init_graph(){

	FS1 = 0;
	MD2 = 0;
	write_data(0);           //图形首地址
	write_data(0);
	write_com(0x42);         //图形首地址设置
	write_data(30);
	write_data(0);
	write_com(0x43);          //图形区域设置
	write_com(0x80);          //设置为OR模式
	write_com(0x9a);          //关闭文本显示,开图形显示

}






/*******************************************************************************
* 函 数 名         : display(char*p)；
* 函数功能         : 显示
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void display(char*p){

    uint i ,j;
	uint addr;
	addr  = 0x0800;
	write_data(addr%256);
	write_data(addr/256);
	write_com(0x24);
	for(i = 0;i<128*30;i++){
	
	
	    if(i%30 == 0)
		{
	
		    j++;
		    addr = 0x0800 +	j*30 ;//换行
			write_data(addr%256);
			write_data(addr/256);
			write_com(0x24);
	
		 }

		 write_data(p[i]);          //发送数据
		 write_com(0xc0);

	}


}



/*******************************************************************************
* 函 数 名         : print_text(char x,char y,char a);
* 函数功能         : 指定位置打印字符
* 输    入         : 坐标，字符
* 输    出         : 无
*******************************************************************************/
void print_text(char x,char y,char a){


int place;
place=x*30+y;
write_data(place&0xff);            //写地址低8位
write_data(place/256);             //写地址高8位
write_com(0x24);                   //设置地址
write_com(0xb0);                   //设置数据自动写
write_text(a);
write_com(0xb2);                  //自动复位


}



/*******************************************************************************
* 函 数 名         : text_out(char a)；
* 函数功能         : 打印字符
* 输    入         : 字符
* 输    出         : 无
*******************************************************************************/
void text_out(char a){

write_com(0xb0); //? ? ? //设置数据自动写
write_text(a);
write_com(0xb2); //? ? ?//自动复位


}






/*******************************************************************************
* 函 数 名         : text_location(int place);
* 函数功能         : 字符定位
* 输    入         : 位置
* 输    出         : 无
*******************************************************************************/
void text_location(int place){

write_data(place&0xff); //? //写地址低8位
write_data(place/256); //? ?//写地址高8位
write_com(0x24); //? ? ? //设置地址


}




/*******************************************************************************
* 函 数 名         : text_out(char a)；
* 函数功能         : 打印字符串
* 输    入         : 字符数组
* 输    出         : 无
*******************************************************************************/
void print_string(char* str){

	int i;
	int ch;
	for(i=0;str[i]!='\0';i++)
	{

		ch=asc2lcd(str[i]);
		text_out(ch);

	}					 

}


/*******************************************************************************
* 函 数 名         : delay_lcd(uchar t);
* 函数功能         : 延迟
* 输    入         : 字符
* 输    出         : 无
*******************************************************************************/


void delay_lcd(uchar t){

    for(;t!=0; t--);

}





/*******************************************************************************
* 函 数 名         : asc2lcd(int asc);
* 函数功能         : 将ASCII码进行转换
* 输    入         : 字符
* 输    出         : 
*******************************************************************************/


int asc2lcd(int asc){

    uint r;
    r=asc-32;
    return r;

}












/*******************************************************************************
* 函 数 名         : cursor_on();
* 函数功能         : 显示光标
* 输    入         : 无
* 输    出         : 无	·······················································································································································································`````````````````````````··············``````````````````````···································```````···········``````````````````````·····
*******************************************************************************/
void cursor_on(){


write_com(0xA0);
write_com(0x93);
write_com(0x94); //text on graphic off

}









void write_lcd8(uchar x,uchar y,char *cha)//x为行坐标，y为列坐标																																				·········································
{
    int place;
	int temp_x = x;	 
	int temp_y = y;
    uint i = 0;
	uint j = 0;
	place = x*30+ y;
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
        write_data(cha[i+j]);                                                     
        write_com(0xb2); 	
		
	  }   
	  x++;
	  y = temp_y;	                                                                                                        //自动复位
    
	}

}





void write_lcd16(uchar x,uchar y,char *cha)//x为行坐标，y为列坐标
{
    int place;
	int temp_x = x;	 
	int temp_y = y;
    uint i = 0;
	uint j = 0;
	place = x*30+ y;
    for(i = 0;i < 16;i++)
	{

      for(j=0;j<2;j++)                                                                                                                             //字符设置为16*8
      {
		place = x*30+ y;
		y++;
        write_data(place%256);                                                                                                   //写入地址高位
        write_data(place/256);                                                                                                    //写入地址低位
        write_com(0x24);                                                                                                          //地址设置
        write_com(0xb0);                                                                                                          //设置数据自动写
        write_data(cha[i*2+j]);                                                     
        write_com(0xb2); 	
		
	  }   
	  x++;
	  y = temp_y;	                                                                                                        //自动复位
    
	}
}







void write_lcd24(uchar x,uchar y,char *cha)//x为行坐标，y为列坐标
{
    int place;
	int temp_x = x;	 
	int temp_y = y;
    uint i = 0;
	uint j = 0;
	place = x*30+ y;
    for(i = 0;i < 20;i++)
	{

      for(j=0;j < 3;j++)                                                                                                                             //字符设置为16*8
      {
		place = x*30+ y;
		y++;
        write_data(place%256);                                                                                                   //写入地址高位
        write_data(place/256);                                                                                                    //写入地址低位
        write_com(0x24);                                                                                                          //地址设置
        write_com(0xb0);                                                                                                          //设置数据自动写
        write_data(cha[i*3+j]);                                                     
        write_com(0xb2); 	
		
	  }   
	  x++;
	  y = temp_y;	                                                                                                        //自动复位
    
	}
}










void write_lcd24_24(uchar x,uchar y,char *cha)//x为行坐标，y为列坐标
{
    int place;
	int temp_x = x;	 
	int temp_y = y;
    uint i = 0;
	uint j = 0;
	place = x*30+ y;
    for(i = 0;i < 24;i++)
	{

      for(j=0;j < 3;j++)                                                                                                                             //字符设置为16*8
      {
		place = x*30+ y;
		y++;
        write_data(place%256);                                                                                                   //写入地址高位
        write_data(place/256);                                                                                                    //写入地址低位
        write_com(0x24);                                                                                                          //地址设置
        write_com(0xb0);                                                                                                          //设置数据自动写
        write_data(cha[i*3+j]);                                                     
        write_com(0xb2); 	
		
	  }   
	  x++;
	  y = temp_y;	                                                                                                        //自动复位
    
	}
}





void clear_all()
{

    uint i = 0;
    uint j = 0;
    uint place = i*30 + j;
	for(i = 0;i < 128;i++){
	
	
		for(j = 0;j < 30; j++){
		
			place = i*30+ j;
			write_data(place%256);                                                                                                   //写入地址高位
	        write_data(place/256);                                                                                                    //写入地址低位
	        write_com(0x24);                                                                                                          //地址设置
	        write_com(0xb0);                                                                                                          //设置数据自动写
	        write_data(0X00);                                                     
	        write_com(0xb2); 	
		
		
		}
	
    }

}











void clear_part(uchar x,uchar y,uchar length)
{

    uint i = 0;
    uint j = 0;
    uint place = x*30 + y;
	for(i = 0;i < 16;i++){
	
	
		for(j = 0;j < length; j++){
		
		
			place = (x+i)*30+ j+y;
			write_data(place%256);                                                                                                   //写入地址高位
	        write_data(place/256);                                                                                                    //写入地址低位
	        write_com(0x24);                                                                                                          //地址设置
	        write_com(0xb0);                                                                                                          //设置数据自动写
	        write_data(0X00);                                                     
	        write_com(0xb2); 	
		
		
		}
		
    }

}							   

