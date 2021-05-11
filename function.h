#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED
#include<reg51.h>

#define uchar unsigned char
#define uint unsigned int
#define DATA_PORT P0
//-------------------------------------------
// 结构体定义
//------------------------------------------


typedef struct       //敌人结构体
{
	uint x,y;       //坐标
	uint direction; //敌人方向变量
	uint exist;     //敌人存在与否的变量,1为存在，0不存在
	uint live;   //子弹是否处于建立初状态的值，1为处于建立初状态，0为处于非建立初状态
	uint attribute; //区分敌人与防御塔的标记,敌人为玩家（我的）子弹

} Enemy;

typedef struct TA      //防御塔结构体
{
	uint x,y;        //防御塔起始坐标
	uint model;      //坦克图案模型，值为1(普通）,2(双弹)，3（多弹）
	uint stop;       //只能防御塔使用的参数，非0代表坦克不能走动,0为可以走动
	uint live;     //防御塔生命
	uint CT;         //发射子弹冷却计时
	uint attribute;   //是否敌方坦克参数，我的坦克此参数为1,为常量
	uint alive;     //存活为1，不存活为0
}  TA;


typedef struct cursor      //敌人结构体
{
	
	uint x,y;       //坐标

}Cursor;




				   
#define uu 1
#define ll 2
#define dd 3
#define	rr 4

extern  uint com;
extern  uint read;
extern uchar Di_quantity;//地图中敌人数量
extern uchar resist[8][30];//确定防御塔的坐标
extern uchar enemy[8][30];//用于确定敌人的坐标
extern Cursor cursor_m;
extern Enemy Di[10];

//extern uint com;
//-------------------------------------------
// 管脚定义 
//------------------------------------------
sbit CD=P2^0;// ? ? //数据(L)/命令(H)选择
sbit WRIT=P2^1; //? ? //写，低电平有效
sbit CE=P2^2; //? ? //使能,低电平有效
sbit FS1 = P2^3	;//1为6*8
sbit MD2 = P2^4 ;


extern uint num;
extern Cursor cursor_m;
extern uchar code private1[72];
//===========================================
// 函数声明
//-------------------------------------------
void delay_lcd(char);
void write_data(char);
void write_text(char);
void write_com(char);
void clr_lcd(char,char,int);
void lcd_init_graph();
void lcd_init_text();
void text_out(char a);
int asc2lcd(int asc);
void print_string(char* str);
void text_location(int place);
void status_check();
void cursor_position();
void write_lcd8(uchar x,uchar y,char *cha);
void write_lcd16(uchar x,uchar y,char *cha);
void write_lcd24(uchar x,uchar y,char *cha);
void write_lcd24_24(uchar x,uchar y,char *cha);
void clear_all();
void clear_part(uchar x,uchar y,uchar length);
void cursor_flash(uchar x,uchar y);	 
void cursor_move(uint temp_x,uint temp_y);
void c_pass_choice();
/***********************************************************
*********************************************************/


//开始界面

void Start_interface();
void print_enemy1(uchar x,uchar y);




/*************************************************************
************************************************************/


/*************************************************************
************************************************************/
void print_enemy1(uchar x,uchar y);
void init_enemy();
void enemy_move();




/*************************************************************
************************************************************/



/*************************************************************
************************************************************/


void init();
void scon();
void c_pass1();
void c_pass2();
void c_pass3();



/*************************************************************
************************************************************/
#endif