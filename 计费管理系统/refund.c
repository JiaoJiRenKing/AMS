#define _CRT_SECURE_NO_WARNINGS 1
#include"stdio.h"
#include"string.h"
#include"stdlib.h"
#include"time.h"
#include"menu.h"
#include"card.h"
#include"card.h"
#include"card_file.h"
#include"add.h"
#include"recharge.h"
#include"refund.h"
#include"delete.h"

//退费
void Refund() {
	printf("---------退费--------\n");
	card = ReadCard();
	Card* t = card->next;
	if (t == NULL) {
		printf("未添加卡\n");
		return;
	}

	printf("请输入退费卡号<1~18>：");
	char myName[50];
	scanf("%s", myName);

	printf("请输入密码<1~8>：");
	char myPwd[50];
	scanf("%s", myPwd);

	while (t) {
		if (strcmp(t->aName, myName) == 0 && strcmp(t->aPwd, myPwd) == 0) {
			if (t->nStatus == 3) {
				printf("卡号已失效，退费失败\n");
				return;
			}
			else if (t->nStatus == 2) {
				printf("卡号已注销，退费失败\n");
				return;
			}
			else if (t->nStatus == 1) {
				printf("卡号正在使用，退费失败\n");
				return;
			}
			else {
				if (t->fBalance > 0) {
					float money = t->fBalance;
					t->fBalance = 0;
					t->nStatus = 3;
					updateCard(t, t->nStatus);
					printf("退费成功\n");
					printf("------退费信息如下--------\n");
					printf("卡号\t退费金额\t余额\n");
					printf("%s\t%.1f\t\t0.0", t->aName, money);
					return;
				}
				else {
					printf("余额不足，退费失败\n");
					return;
				}
			}
		}
		t = t->next;
	}
	if (!t) {
		printf("账号或密码输入错误\n");
		return;
	}

}

