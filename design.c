#include<windows.h>


//��������
void HideCursor() {//���ع��
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 }; //���ù��ĺ����ɼ��Ľṹ��
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void color(short x) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);//xΪ0-15��ʾ����ɫ��
}

void toxy(int x, int y) {//������ƶ���X,Y���괦
    COORD pos = { x , y };
    HANDLE Out = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(Out, pos);
}