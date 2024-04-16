#define _CRT_SECURE_NO_WARNINGS 1
#include"stdio.h"
#include"string.h"
#include"stdlib.h"
#include"time.h"
#include"menu.h"
#include"card.h"
#include"card.h"
#include"card_file.h"


//上机
void Login() {
	printf("------上机--------\n");
	card = ReadCard();
	printf("请输入上机卡号<1~18>：");
	char myName[50];
	scanf("%s", myName);
	printf("请输入上机密码<1~8>：");
	char myPwd[50];
	scanf("%s", myPwd);

	//判断卡号是否存在
	Card* t = card->next;        //跳过头结点,头结点是空的
	while (t) {
		if (strcmp(t->aName, myName) == 0) {
			if (strcmp(t->aPwd, myPwd) == 0) {
				if (t->nStatus == 0 && t->fBalance > 0) {					//卡状态							
					/*if (updateCard(t, 1) != 1) {
						printf("文件写入失败！\n");
						return;
					}*/
					printf("上机成功！\n");
					t->nStatus = 1;
					break;
				}
				else if (t->nStatus == 1) {
					printf("该卡已上机\n");
					return;
				}
				else if (t->nStatus == 2) {
					printf("该卡已注销\n");
					return;
				}
				else if (t->nStatus == 3) {
					printf("该卡已失效\n");
					return;
				}
				if (t->fBalance <= 0) {                           //余额不足
					printf("余额不足\n");
					return;
				}
			}
			else {
				printf("账号或密码错误\n");
				return;

			}
		}
		t = t->next;
	}
	if (t == NULL) {
		printf("账号或密码错误\n");
		return;
	}
	printf("卡号\t余额\t上机时间\n");                          //打印上机信息
	time_t tm = time(NULL);
	struct tm* p = localtime(&tm);
	printf("%s\t%.1f\t%04d-%02d-%02d %02d:%02d:%02d\n", t->aName, t->fBalance, p->tm_year + 1900, p->tm_mon + 1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
	//t->tLastTime = tm;
	updateCard(t, 1);
}
