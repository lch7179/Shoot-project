#include <stdio.h> //헤더파일 자료형, 메서드, 라이브러리, 값 <  >  : c언어가 제공
#include"grpengine.h" //헤더파일 상동 : " " : 사용자가 직접제작
#include <string.h>
#include <conio.h>
#include "main.h"

void main()
{
	pdata = (Gdata*)malloc(sizeof(Gdata));
	pdata->m_score = 0;
			
			
	Intstar();  //우주 초기화
	Intenemy();
	IntBullet(); 
	
	while (1)
	{
		clear_screen(); //화면을 지우고 그린다.
		timecalc();
				
		Keyprocess();   //캐릭터이동

		switch (scene)
		{
		case Retry:
			Drawstar();
			ShowRetry();
			break;
		case Title: //타이틀 화면.. space를 누르면 game으로 들어갔으면 좋겠음
			Drawstar();
			ShowTitle();
			break;
		case Game:
			
			set_color(7);
			Drawstar();    //우주를 그림
			countingtime();
			
			if (gamestate == state_play)
			{
				ingame();
				
				if (player.m_life == 0)
					scene = Retry;
			}
			Show_UI();     //UI - 플레이어, 점수, stage
			break;
		}

		gotoxy(0, 20); //현재는 커서가 드로우에 방해되어서 최종커서 위치를 아래로 내린다.
		sleeped(70);   //그린 후 잠깐 딜레이
	}

}

void ShowTitle()
{
	gotoxy(12, 5);
	printf("슈팅게임 0.1");
	gotoxy(5, 15);
	printf("space 바를 누르면 게임 시작");
}

void ShowRetry()
{
	gotoxy(12, 5);
	printf("Lose");
	gotoxy(5, 15);
	printf("space 바를 누르면 Retry");
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

	strcpy_s(cr->shape, -1, shape); //-1 해당 문자열의 길이를 컴파일	러가 자동으로 계산
}

void Intstar()
{
	int i;

	for (i = 0; i < maxSCount; i++) //초기화
	{
		int xpos, ypos; //지역변수
		xpos = rand() % 35 + 1;
		ypos = rand() % 20 + 1;
		Int_Char(&Star[i], xpos, ypos, ".", 0);//임의의 수를 쓰면 좋겠다
		rand(); //임의의수, 0~30000
		//rand의 범위를 줄였으면 좋겠다
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

	for (i = 0; i < maxECount; i++) //초기화
	{
		int xpos, ypos; //지역변수
		xpos = rand() % 35 + 1;
		ypos = rand() % 20 - 25;
		//화면에 잘 뿌려지나 테스트, 갯수를 올려봐서 테스트
		//이상 없으면. 좌표를 위로 올려놓고 마무리

		Int_Char(&enemy[i], xpos, ypos, "◈", 0);//임의의 수를 쓰면 좋겠다
		rand(); //임의의수, 0~30000
		//rand의 범위를 줄였으면 좋겠다
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
			enemy[i].m_posx = rand() % 35 + 1;//x위치는 바ㅜ끼어서
			enemy[i].m_posy = 0;//위로
			enemy[i].m_life = 0;//비활성화된 적군으로 세팅
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
		enemy[i].m_posy++; //기본적으로 내려오는데
		if (enemy[i].m_posy >= 4)//조금 더 내려오면 활성화
		{
			enemy[i].m_life = 1;
		}
		if (enemy[i].m_posy >= 20 && enemy[i].m_life == 1)//아래까지 살아서 내려옴
		{
			enemy[i].m_posx = rand() % 35 + 1;//x위치는 바ㅜ끼어서
			enemy[i].m_posy = 0;//위로
			enemy[i].m_life = 0;//비활성화된 적군으로 세팅
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
		Int_Char(&Bullet[i], xpos, ypos, "★", 0);
	}
}

void MoveBullet() //주인공 위치를 따라다니는 총알
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
					enemy[j].m_posx = rand() % 35 + 1;//x위치는 바ㅜ끼어서
					enemy[j].m_posy = 0;//위로
					enemy[j].m_life = 0;//비활성화된 적군으로 세팅
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


	while (_kbhit())//눌리면 1을 알려주고 안눌리면 0을 알려줌
	{
		ch = _getch();//키입력을 받으면 그대로 돌아가고 키입력이 없으면 무시가 되는 코드
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
	curtime = clock(); //새로얻은시간
	elapsedtime = curtime - oldtime; //현재 얻은시간 - 맨처음시간 => 사이시간
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
	if (player.m_posx >= 30) player.m_posx = 30; //이동의 한계치

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
