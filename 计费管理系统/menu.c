#define _CRT_SECURE_NO_WARNINGS 1
#include"menu.h"
#include"stdio.h"
#include"stdlib.h"
#include"string.h"
#include"card.h"
#include"card_file.h"
#include"time.h"
#include"add.h"
#include"delete.h"
#include"query.h"
#include"login.h"
#include"logout.h"
#include"refund.h"
#include"recharge.h"


void outputmenu()
{

	int choice;
	printf("学号：1023004801 姓名：林洛漪 班级：计算机类2314\n");

	while (1) {

		printf("\n");
		printf("欢迎进入计费管理系统\n");
		printf("\n");
		printf("-------菜单---------\n");
		printf("\n");
		printf("1.添加卡\n");
		printf("2.查询卡\n");
		printf("3.上机\n");
		printf("4.下机\n");
		printf("5.充值\n");
		printf("6.退费\n");
		printf("7.查询统计\n");
		printf("8.注销卡\n");
		printf("0.退出\n");
		printf("请输入0-8数字来进行选择\n");

		if (scanf("%d", &choice) != 1) {
			// 清空输入缓冲区
			while (getchar() != '\n');
			printf("请输入正确的0-8数字来进行选择\n");
			continue;
		}
		switch (choice) {
		case 0: exit(0); break;
		case 1: Add();  break;
		case 2: Query(); break;
		case 3: Login(); break;
		case 4: Logout(); break;
		case 5: Recharge(); break;
		case 6: Refund(); break;
		case 7:printf("查询统计\n"); break;
		case 8: Delete(); break;
		default:printf("请输入正确的0-8数字来进行选择\n"); break;
		}
	}

}

