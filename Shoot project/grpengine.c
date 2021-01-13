#include<stdio.h>
#include"grpengine.h"

void clear_screen()
{
	//화면을 지우는 메서드가 필요

	//system("cls");
	COORD Coor = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter
		(GetStdHandle(STD_OUTPUT_HANDLE), ' ', 80 * 42, Coor, &dw);
}


void sleeped(int mil_second)
{
	//clock();//현재 시간값을 얻어옴
	int result;
	result = mil_second + clock();
	while (result>clock());
}


void set_color(unsigned short color)
{
	//WORD
	/*
	1.파란색(어두움) 2.녹색(어둠) 3.청록(어둠) 4.빨강
	//5.핑크 6.황토 7.아이보리 8.회색
	9.파란색(밝음) 10.녹색 11.청록 12.빨강 13.핑크 14.노란 15.흰색
	*/
	SetConsoleTextAttribute
		(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void gotoxy(int x, int y)
{
	//api 메서드 setconsoleCursorposition // 커서의 위치를 세팅한다.
	//win32 api > 공부하는 방법  메서드의 사용법을 익힌다.
	//win32 > 로직 알고리즘이나 문법 메서드의 사용법
	//HANDLE //현재 윈도우즈나 프로그램을 제어할수 있는 주소나 자료형
	COORD CurPos = { x, y }; //좌표
	//콘솔창의 커서의 위치를 바꾼다.
	SetConsoleCursorPosition
		(GetStdHandle(STD_OUTPUT_HANDLE), CurPos);
}
