//#pragma once

#ifndef MAIN_H //�ش� Ű���尡 ���ǵǾ� �ִ°�
//Ÿ������, �ڷ���, �Լ��� ������ Ÿ�� ���� ���� �ҽ��� �� �� ������...���������� ���ǰ��úκи�..
#define MAIN_H

#define left     75
#define right	 77
#define spacebar 32
#define leftkey  97
#define rightkey 100

#define maxSCount 30
#define maxECount 7 //���߿� �̰��� �ٲپ �ѹ��� ��������
#define maxBCount 9 //�Ѿ��ִ밹��
//������ ������

long curtime, oldtime, elapsedtime;

enum SceneState {Title,Game,Over,Retry};//���� ���� -switch
enum GameProcess {state_ready,state_play};

typedef struct GameData
{
	int m_score;
	int m_Hiscore;
	int m_playernum;
	int m_stage;
} Gdata;

typedef struct tag_creature
{
	int m_posx;    //��ġ
	int m_posy;
	char shape[3]; //
	int m_life;    //����
}Creature;

//------------------------���� ���� �����----------------------------------

Creature Star[maxSCount] = { 0 };	   //�� 20�� ����� (���������� �����)
Creature player = { 15,17,"��",3 };
Creature enemy[maxECount] = { 0 };
Creature Bullet[maxBCount] = { 0 };
Gdata* pdata; //�ּҷ� �����ϰ���

int scene = Title;
int count = 5;
int gamestate = state_ready; //���� ����
long calctime = 0;

void Keyprocess();			  //Ű�Է� ����

void Draw_Char(Creature cr); //ȭ�鿡 ĳ���� �Ѹ���
void Int_Char(Creature* cr, int posx, int posy, char* shape, int m_life);

void Intstar();				 //���� �ʱ�ȭ
void Drawstar();			 //���� �׸���

void Drawenemy();			// �����׸���
void Intenemy();			// �����ʱ�ȭ
void Moveenemy();			// �����̵�
void Checkenemy();

void IntBullet();
void MoveBullet();
void FireBullet();
void DrawBullet();
void CheckBullet();

void Show_UI();
void ShowTitle();
void ShowRetry();

void timecalc();
void countingtime();
void ingame();




#endif