#define _CRT_SECURE_NO_WARNINGS 1
#include"stdio.h"
#include"string.h"
#include"stdlib.h"
#include"time.h"
#include"menu.h"
#include"card.h"
#include"card.h"
#include"card_file.h"


//下机
void Logout() {
	char myName[50];
	char myPwd[50];
	printf("------下机--------\n");
	card = ReadCard();
	printf("请输入下机卡号<1~18>：");
	scanf("%s", myName);
	printf("请输入下机密码<1~8>：");
	scanf("%s", myPwd);

	Card* t = card->next;
	if (t == NULL) {
		printf("账号或密码输入错误\n");
		return;
	}
	while (t) {
		//判断卡号是否正在上机
		if (strcmp(t->aName, myName) == 0 && strcmp(t->aPwd, myPwd) == 0) {
			if (t->nStatus == 1) {
				t->nStatus = 0;
				time_t tmp = t->tLastTime;

				char p[50];
				struct tm* last_time;
				last_time = gmtime(&tmp); // 将时间转换为UTC时间

				// 假设你的时区是北京时间（东八区），需要调整8个小时的时差
				last_time->tm_hour += 8;
				if (last_time->tm_hour >= 24) {
					last_time->tm_hour -= 24;
				}
				strftime(p, sizeof(p), "%Y-%m-%d %H:%M:%S", last_time); // 格式化时间为字符串

				time_t current_time;
				struct tm* local_time;
				struct tm* lasttime = localtime(&t->tLastTime);//上机时间
				////time(&t->tLastTime); 这是获取当前时间
				//time_t last_time= t->tLastTime;//上机时间
				time(&current_time);
				local_time = localtime(&current_time);
				float spend = difftime(current_time, t->tLastTime) * (1.0 / 360);     //计算消费金额 每小时10元
				t->fTotalUse += spend;
				t->fBalance -= t->fTotalUse;
				//t->tLastTime = current_time;
				if (t->fBalance < 0) {             //判断消费金额是否超过余额
					printf("余额不足,该卡已失效\n");
					t->nStatus = 3;
					updateCard(t, 3);
					return;
				}
				else {
					if (updateCard(t, 0) != 1) {         //更新卡信息
						printf("文件写入失败！\n");
					}
					else {
						printf("下机成功！\n");
						printf("卡号\t消费\t余额\t上机时间\t\t\t下机时间\n");  //打印下机信息
						printf("%s\t%.1f\t%.1f\t%s\t\t",
							t->aName, spend, t->fBalance, p);
						printf("%d-%02d-%02d %02d:%02d:%02d\n", local_time->tm_year + 1900, local_time->tm_mon + 1, local_time->tm_mday,
							local_time->tm_hour, local_time->tm_min, local_time->tm_sec);
					}
				}
				t->tLastTime = current_time;
			}
			else if (t->nStatus == 2) {
				printf("该卡已注销\n");
				return;
			}
			else if (t->nStatus == 3) {
				printf("该卡已失效\n");
				return;
			}
			else {
				printf("该卡未上机\n");
				return;
			}
		}
		t = t->next;
	}

}