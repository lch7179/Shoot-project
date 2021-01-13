//#pragma once

#ifndef MAIN_H //해당 키워드가 정의되어 있는가
//타입정의, 자료형, 함수의 프로토 타입 물론 구현 소스도 올 수 있지만...관용적으로 정의관련부분만..
#define MAIN_H

#define left     75
#define right	 77
#define spacebar 32
#define leftkey  97
#define rightkey 100

#define maxSCount 30
#define maxECount 7 //나중에 이값을 바꾸어서 한번에 세팅하자
#define maxBCount 9 //총알최대갯수
//씬별로 만들어보자

long curtime, oldtime, elapsedtime;

enum SceneState {Title,Game,Over,Retry};//상태 관리 -switch
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
	int m_posx;    //위치
	int m_posy;
	char shape[3]; //
	int m_life;    //생명
}Creature;

//------------------------전역 변수 선언부----------------------------------

Creature Star[maxSCount] = { 0 };	   //별 20개 만들고 (전역변수로 만든다)
Creature player = { 15,17,"♠",3 };
Creature enemy[maxECount] = { 0 };
Creature Bullet[maxBCount] = { 0 };
Gdata* pdata; //주소로 관리하겠음

int scene = Title;
int count = 5;
int gamestate = state_ready; //레디 상태
long calctime = 0;

void Keyprocess();			  //키입력 로직

void Draw_Char(Creature cr); //화면에 캐릭터 뿌리기
void Int_Char(Creature* cr, int posx, int posy, char* shape, int m_life);

void Intstar();				 //우주 초기화
void Drawstar();			 //우주 그리기

void Drawenemy();			// 적군그리기
void Intenemy();			// 적군초기화
void Moveenemy();			// 적군이동
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