#include "fingerGuessingGame_communicate.h"
using namespace std;
extern Hero *pg_hero;
extern char g_out_buf[20480];
extern int g_msg_len;
void fingerGuessGameAi(char *buffer)
{
	MSG_BEGIN(buffer,g_msg_len)
	MSG_INT(int other)
	
	cout<<"27,0,"<<other<<endl;
	
	pg_hero->fingerGuessingAi(other);
}

void enterFingerGuessGame(char *buffer)
{
	MSG_BEGIN(buffer,g_msg_len)
	MSG_INT(int flag)
	MSG_INT(int money)
	
	cout<<"27,1,"<<flag<<","<<money<<endl;
	
	if (flag==1)		//与电脑对战
	{
		pg_hero->joinFingerGuessingGameAi(money);
	}
	else if (flag==2)		//与人对战
	{
		pg_hero->joinFingerGuessingGame(money);
	}	
}

void exitFingerGuessGame(char *buffer)
{
	cout<<"27,2"<<endl;
	pg_hero->exitFingerGuessingGame();
}

void FingerGuessGamePlayer(char *buffer)
{
	MSG_BEGIN(buffer,g_msg_len)
	MSG_INT(int mine)
	
	cout<<"27,3,"<<mine<<endl;
	
	pg_hero->fingerGuessGamePlayerFight(mine);
	
}