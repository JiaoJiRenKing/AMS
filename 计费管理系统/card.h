#pragma once
#include"time.h"
//卡信息结构体
typedef struct Card {
	char aName[50];                //卡号
	char aPwd[50];                  //密码
	int nStatus;				   //卡状态（0-未上机； 1-正在上机； 2-已注销；3-失效）
	time_t tStart;                 //开卡时间
	time_t tEnd;                   //卡的截至时间
	float fTotalUse;               //累计金额
	time_t tLastTime;              //最后使用时间
	int nUseCount;                 //使用次数
	float fBalance;                //余额
	int nDel;                      //删除标识（0-未删除， 1-删除）
	struct Card* next;
}Card;

void AddCard(Card* link, char* n, char* p, float t);
Card* Initial();
Card* QueryCard(Card* card, char name[]);
int DelCard(Card* card, char name[]);