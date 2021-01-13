#include <stdio.h> //������� �ڷ���, �޼���, ���̺귯��, �� <  >  : c�� ����
#include"grpengine.h" //������� �� : " " : ����ڰ� ��������
#include <string.h>
#include <conio.h>
#include "main.h"

void main()
{
	pdata = (Gdata*)malloc(sizeof(Gdata));
	pdata->m_score = 0;
			
			
	Intstar();  //���� �ʱ�ȭ
	Intenemy();
	IntBullet(); 
	
	while (1)
	{
		clear_screen(); //ȭ���� ����� �׸���.
		timecalc();
				
		Keyprocess();   //ĳ�����̵�

		switch (scene)
		{
		case Retry:
			Drawstar();
			ShowRetry();
			break;
		case Title: //Ÿ��Ʋ ȭ��.. space�� ������ game���� ������ ������
			Drawstar();
			ShowTitle();
			break;
		case Game:
			
			set_color(7);
			Drawstar();    //���ָ� �׸�
			countingtime();
			
			if (gamestate == state_play)
			{
				ingame();
				
				if (player.m_life == 0)
					scene = Retry;
			}
			Show_UI();     //UI - �÷��̾�, ����, stage
			break;
		}

		gotoxy(0, 20); //����� Ŀ���� ��ο쿡 ���صǾ ����Ŀ�� ��ġ�� �Ʒ��� ������.
		sleeped(70);   //�׸� �� ��� ������
	}

}

void ShowTitle()
{
	gotoxy(12, 5);
	printf("���ð��� 0.1");
	gotoxy(5, 15);
	printf("space �ٸ� ������ ���� ����");
}

void ShowRetry()
{
	gotoxy(12, 5);
	printf("Lose");
	gotoxy(5, 15);
	printf("space �ٸ� ������ Retry");
}

void Draw_Char(Creature cr)
{
	gotoxy(cr.m_posx, cr.m_posy);
	printf("%s", cr.shape);
}
	

void Int_Char(Creature* cr, int posx, int posy, char* shape, int m_life)
{
	cr->m_posx = posx;
	cr->m_posy = posy;
	cr->m_life = m_life;

	strcpy_s(cr->shape, -1, shape); //-1 �ش� ���ڿ��� ���̸� ������	���� �ڵ����� ���
}

void Intstar()
{
	int i;

	for (i = 0; i < maxSCount; i++) //�ʱ�ȭ
	{
		int xpos, ypos; //��������
		xpos = rand() % 35 + 1;
		ypos = rand() % 20 + 1;
		Int_Char(&Star[i], xpos, ypos, ".", 0);//������ ���� ���� ���ڴ�
		rand(); //�����Ǽ�, 0~30000
		//rand�� ������ �ٿ����� ���ڴ�
	}
}


void Drawstar()
{
	int i;
	for (i = 0; i < maxSCount; i++)
	{
		Draw_Char(Star[i]);
	}

}

void Intenemy()
{
	int i;

	for (i = 0; i < maxECount; i++) //�ʱ�ȭ
	{
		int xpos, ypos; //��������
		xpos = rand() % 35 + 1;
		ypos = rand() % 20 - 25;
		//ȭ�鿡 �� �ѷ����� �׽�Ʈ, ������ �÷����� �׽�Ʈ
		//�̻� ������. ��ǥ�� ���� �÷����� ������

		Int_Char(&enemy[i], xpos, ypos, "��", 0);//������ ���� ���� ���ڴ�
		rand(); //�����Ǽ�, 0~30000
		//rand�� ������ �ٿ����� ���ڴ�
	}
}

void Checkenemy()
{
	int i;

	for (i = 0; i < maxECount; i++)
	{
		if ((enemy[i].m_posx - player.m_posx) == 0 && abs(enemy[i].m_posy - player.m_posy) <= 1)
		{
			player.m_life--;
			enemy[i].m_posx = rand() % 35 + 1;//x��ġ�� �٤̳��
			enemy[i].m_posy = 0;//����
			enemy[i].m_life = 0;//��Ȱ��ȭ�� �������� ����
			pdata->m_score += 10;
		}
	}
}


void Show_UI()
{
	
	if (player.m_life >= 0)
	{
		gotoxy(2, 2);
		set_color(10);
		printf("p : %d", player.m_life);

	}
	gotoxy(16, 1);
	set_color(14);
	printf("score : %d", pdata->m_score);
}

void Moveenemy()
{
	int i;

	for (i = 0; i < maxECount; i++)
	{
		enemy[i].m_posy++; //�⺻������ �������µ�
		if (enemy[i].m_posy >= 4)//���� �� �������� Ȱ��ȭ
		{
			enemy[i].m_life = 1;
		}
		if (enemy[i].m_posy >= 20 && enemy[i].m_life == 1)//�Ʒ����� ��Ƽ� ������
		{
			enemy[i].m_posx = rand() % 35 + 1;//x��ġ�� �٤̳��
			enemy[i].m_posy = 0;//����
			enemy[i].m_life = 0;//��Ȱ��ȭ�� �������� ����
		}
	}
}

void Drawenemy()
{
	int i;
	for (i = 0; i < maxECount; i++)
	{
		if(enemy[i].m_life == 1 )
		Draw_Char(enemy[i]);
	}

}

void IntBullet()
{
	int i;

	for (i = 0; i < maxBCount; i++) 
	{
		int xpos, ypos; 
		xpos = player.m_posx;
		ypos = player.m_posy;
		Int_Char(&Bullet[i], xpos, ypos, "��", 0);
	}
}

void MoveBullet() //���ΰ� ��ġ�� ����ٴϴ� �Ѿ�
{
	int i;

	for (i = 0; i < maxBCount; i++)
	{
		if (Bullet[i].m_life == 0)
		{
			Bullet[i].m_posx = player.m_posx;
			Bullet[i].m_posy = player.m_posy;
		}
		if (Bullet[i].m_life == 1)
		{
			Bullet[i].m_posy -= 1;
			if (Bullet[i].m_posy <= 0)
			{
				Bullet[i].m_life = 0;
			}
		}
	}

}

void DrawBullet()
{
	int i;
	for (i = 0; i < maxBCount; i++)
	{
		if(Bullet[i].m_life == 1)
		Draw_Char(Bullet[i]);
	}

}

void FireBullet()
{
	int i;
	for (i = 0; i < maxBCount; i++)
	{
		if (Bullet[i].m_life == 0)
		{
			Bullet[i].m_life = 1;
			break;
		}
	}
}

void CheckBullet()
{
	int i, j;

	for (i = 0; i < maxBCount; i++)
	{
		if (Bullet[i].m_life == 1)
		{
			for (j = 0; j < maxECount; j++)
			{
				if ((enemy[j].m_posx - Bullet[i].m_posx) == 0 && abs(enemy[j].m_posy - Bullet[i].m_posy) <= 1)
				{
					enemy[j].m_posx = rand() % 35 + 1;//x��ġ�� �٤̳��
					enemy[j].m_posy = 0;//����
					enemy[j].m_life = 0;//��Ȱ��ȭ�� �������� ����
					Bullet[i].m_life = 0;
					pdata->m_score += 10;
				}
			}
		}
	}
}

void Keyprocess()
{
	unsigned char ch = 0;


	while (_kbhit())//������ 1�� �˷��ְ� �ȴ����� 0�� �˷���
	{
		ch = _getch();//Ű�Է��� ������ �״�� ���ư��� Ű�Է��� ������ ���ð� �Ǵ� �ڵ�
		switch (ch)
		{
		case spacebar:
			if (scene == Title || scene == Over)
			{
				scene = Game;
			}
			else if (scene == Retry)
			{
				scene = Game;
				player.m_life = 3;
				Intenemy();
				IntBullet();
				player.m_posx = 15;
				player.m_posy = 17;
			}
			else if (scene == Game)
			{
				FireBullet();
			}
			break;
		case leftkey:
		case left:
			player.m_posx--;
			break;
		case rightkey:
		case right:
			player.m_posx++;
			break;
		}
	}
}

void timecalc()
{
	curtime = clock(); //���ξ����ð�
	elapsedtime = curtime - oldtime; //���� �����ð� - ��ó���ð� => ���̽ð�
	oldtime = curtime;
}
void countingtime()
{
	
	curtime = oldtime = clock();

	if (gamestate == state_ready)
	{
		calctime += elapsedtime;
		if (calctime >= 1000)
		{
			count--;
			calctime = 0;
		}
		if (count >= 1)
		{
			gotoxy(10, 8);
			printf("Ready!!!");
			gotoxy(15, 9);
			printf("%d", count);
		}
		else if (count >= 0)
		{
			gotoxy(10, 8);
			printf("Go!");
		}
		else
		{
			count = 5;
			calctime = 0;
			gamestate = state_play;

		}

	}
}
void ingame()
{
	if (player.m_posx <= 1) player.m_posx = 1;
	if (player.m_posx >= 30) player.m_posx = 30; //�̵��� �Ѱ�ġ

	MoveBullet();
	Moveenemy();
	Checkenemy();
	CheckBullet();

	set_color(4);
	Drawenemy();

	set_color(5);
	DrawBullet();

	set_color(1);
	Draw_Char(player);
}
