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

//充值
void Recharge() {
	printf("---------充值-----------\n");
	card = ReadCard();
	Card* t = card->next;
	if (t == NULL) {
		printf("未添加卡\n");
		return;
	}

	printf("请输入充值卡号<1~18>：");
	char myName[50];
	scanf("%s", myName);

	printf("请输入密码<1~8>：");
	char myPwd[50];
	scanf("%s", myPwd);

	printf("请输入充值金额<RMB>：");
	float money;
	scanf("%f", &money);


	while (t) {
		if (strcmp(t->aName, myName) == 0 && strcmp(t->aPwd, myPwd) == 0) {
			if (t->nStatus == 2) {
				printf("该卡已注销,充值失败\n");
				return;
			}
			else if (t->nStatus == 3) {
				t->fBalance += money;
				if (t->fBalance > 0) {
					t->nStatus = 0;
				}
				updateCard(t, t->nStatus);
				break;
			}
			else {
				t->fBalance += money;
				updateCard(t, t->nStatus);
				break;
			}
		}
		t = t->next;
	}
	if (!t) {
		printf("账号或密码错误\n");
		return;
	}
	printf("充值成功\n");
	printf("---------充值信息如下-------\n");
	printf("卡号\t充值金额\t余额\n");
	printf("%s\t%.1f\t\t%.1f\n", myName, money, t->fBalance);
}