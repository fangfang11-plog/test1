#include<windows.h>


//辅助函数
void HideCursor() {//隐藏光标
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 }; //设置光标的厚度与可见的结构体
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void color(short x) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);//x为0-15表示字体色，
}

void toxy(int x, int y) {//将光标移动到X,Y坐标处
    COORD pos = { x , y };
    HANDLE Out = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(Out, pos);
}