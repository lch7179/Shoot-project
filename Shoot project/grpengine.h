#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<Windows.h> //win32 api ���������� ������ ȭ���� �����.
#include<time.h>
#ifndef __GRPENGINE_H_
#define __GRPENGINE_H_
#define Debug
//#define Release

void clear_screen();
void sleeped(int mil_second);
void set_color(unsigned short color);
void gotoxy(int x, int y);

#endif