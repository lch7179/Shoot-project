#include<stdio.h>
#include"grpengine.h"

void clear_screen()
{
	//ȭ���� ����� �޼��尡 �ʿ�

	//system("cls");
	COORD Coor = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter
		(GetStdHandle(STD_OUTPUT_HANDLE), ' ', 80 * 42, Coor, &dw);
}


void sleeped(int mil_second)
{
	//clock();//���� �ð����� ����
	int result;
	result = mil_second + clock();
	while (result>clock());
}


void set_color(unsigned short color)
{
	//WORD
	/*
	1.�Ķ���(��ο�) 2.���(���) 3.û��(���) 4.����
	//5.��ũ 6.Ȳ�� 7.���̺��� 8.ȸ��
	9.�Ķ���(����) 10.��� 11.û�� 12.���� 13.��ũ 14.��� 15.���
	*/
	SetConsoleTextAttribute
		(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void gotoxy(int x, int y)
{
	//api �޼��� setconsoleCursorposition // Ŀ���� ��ġ�� �����Ѵ�.
	//win32 api > �����ϴ� ���  �޼����� ������ ������.
	//win32 > ���� �˰����̳� ���� �޼����� ����
	//HANDLE //���� ������� ���α׷��� �����Ҽ� �ִ� �ּҳ� �ڷ���
	COORD CurPos = { x, y }; //��ǥ
	//�ܼ�â�� Ŀ���� ��ġ�� �ٲ۴�.
	SetConsoleCursorPosition
		(GetStdHandle(STD_OUTPUT_HANDLE), CurPos);
}
