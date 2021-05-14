#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED
#include<reg51.h>

#define uchar unsigned char
#define uint unsigned int
#define DATA_PORT P0
#define Status int
#define ERROR 0
#define SUCCESS 1
//-------------------------------------------
// �ṹ�嶨��
//------------------------------------------


typedef struct       //���˽ṹ��
{
	uint x,y;       //����
	uint exist;     //���˴������ı���,1Ϊ���ڣ�0������
	uint live;   //�ӵ��Ƿ��ڽ�����״̬��ֵ��1Ϊ���ڽ�����״̬��0Ϊ���ڷǽ�����״̬
	uint attribute; //���ֵ�����������ı��,����Ϊ��ң��ҵģ��ӵ�

} Enemy;

typedef struct TA      //�������ṹ��
{
    uint x;
	uint y;                 //��������ʼ����
	uint level;      //����ͼ��ģ�ͣ�ֵΪ1(��ͨ��,2(˫��)��3���൯��
	uint stop;       //ֻ�ܷ�����ʹ�õĲ�������0����̹�˲����߶�,0Ϊ�����߶�
	uint interval;         //�����ӵ���ȴ��ʱ
	uint alive;     //���Ϊ1�������Ϊ0
}  TA;



typedef struct       //�ҽṹ��
{
	uint x,y;       //����

}Home;


typedef struct cursor      //���˽ṹ��
{
	
	uint x,y;       //����

}Cursor;




				   
#define uu 1
#define ll 2
#define dd 3
#define	rr 4

extern  uint com;
extern  uint read;
extern Cursor cursor_m;

//extern uint com;
//-------------------------------------------
// �ܽŶ��� 
//------------------------------------------
sbit CD=P2^0;// ? ? //����(L)/����(H)ѡ��
sbit WRIT=P2^1; //? ? //д���͵�ƽ��Ч
sbit CE=P2^2; //? ? //ʹ��,�͵�ƽ��Ч
sbit FS1 = P2^3	;//1Ϊ6*8
sbit MD2 = P2^4 ;

extern Cursor cursor_m;
extern uchar code private1[72];
//===========================================
// ��������
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
void initialize();
void delay();
void display_num(uchar x,uchar y,uchar num);
/***********************************************************
*********************************************************/


//��ʼ����

void Start_interface();
void print_enemy1(uchar x,uchar y);
void active_TA1(uchar x,uchar y);
void judge_TA1(uchar x,uchar y,Enemy*di);
void failed ();
void pass1_function();

/*************************************************************
************************************************************/


/*************************************************************
************************************************************/
void print_enemy1(uchar x,uchar y);
void init_enemy();
void enemy_move1();
extern void timer0_init();
void rebuild_xj();
void game_win();
//extern TA resist[10];
//extern Enemy  Di[10];
void judge_home(uchar x,uchar y,Enemy*di);
void c_pass4();

/*************************************************************
************************************************************/



/*************************************************************
************************************************************/


void init();
void scon();
void c_pass1();
void c_pass2();
void c_pass3();
void judge_pao(uchar x,uchar y,Enemy*di);


/*************************************************************
************************************************************/
#endif