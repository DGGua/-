#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "model.h"
#include "interface_card.h"
#include "tool.h"
#include "card_manage.h"
#include "billing_manage.h"
#include "manager_manage.h"
#include "interface_manager.h"
#include "interface_card.h"
#include "计费管理系统.h"

int main(void) {
    char inputnumber[5];				//接受用户数据并防溢出
    //循环打印屏幕
    do {
	  printf("——————欢迎来到计费管理系统！——————\n");
	  printf("1、消费者登陆\n");
	  printf("2、管理员登陆\n");
	  printf("0、退出\n");
	  printf("————————————————————————\n");
	  printf("输入选项前数字（0~2）并按回车进行操作：");
	  scanf("%s", inputnumber);
	  system("cls");
	  if (inputnumber[1] != 0)inputnumber[0] = 0;							//判断用户输入是不是单个字符
	  

	  switch (inputnumber[0] - '0') {
	  case 1:gotoLogin_card(); break;
	  case 2:gotoLogin_manager(); break;
	  case 0: system("cls"); break;
	  default:
		printf("输入不合法！请重新输入！\n");
		system("pause");
		system("cls");
		break;
	  }
    } while (inputnumber[0] != '0');
	 
}

void gotoLogin_card() {
    char cardid[20] = { 0 }, password[20] = { 0 };
    int iflegal = 1, ifhasone = 1;
    printf("——————消—费—者—登—录——————\n");
    printf("登录须知：\n");
    printf("1、用户输入卡号和密码登陆计费系统进行其他操作\n");
    printf("2、若有登陆问题，请联系管理员\n");
    printf("3、若取消登录并返回，请输入“\\”\n");
    printf("———————————————————\n");
    do {
	  ifhasone = 0;
	  do {
		iflegal = 1;
		memset(cardid, 0, sizeof(cardid));
		printf("请输入用户名：");
		scanf("%s", cardid);
		if (cardid[0] == 92 && cardid[1] == 0) {
		    system("cls");
		    return;
		}
		if (cardid[18] != 0 || cardid[19] != 0)iflegal = 0;
		if (!iflegal) {
		    printf("输入有误！请重新输入\n");
		}
	  } while (!iflegal);
	  do {
		iflegal = 1;
		memset(password, 0, sizeof(password));
		printf("请输入密码：");
		scanf("%s", password);
		if (password[0] == 92 && password[1] == 0) {
		    system("cls");
		    return;
		}
		if (password[18] != 0 || password[19] != 0)iflegal = 0;
		if (!iflegal) {
		    printf("输入有误！请重新输入\n");
		}
	  } while (!iflegal);


	  if (check_card_with_pas(cardid, password) != NULL) {
		    ifhasone = 1;
		    char str[20];
		    system("cls");
		    gotoMenu_card(cardid);
	  }
	  else {
		ifhasone = 0;
		printf("用户名或密码错误！请重新输入！\n");
	  }
    } while (!ifhasone);
}

void gotoLogin_manager() {
    char managerid[20] = { 0 }, password[20] = { 0 };
    int iflegal = 1, ifhasone = 1;
    printf("——————管理员登陆——————\n");
    printf("登陆须知：\n");
    printf("1、请输入管理员卡号和密码\n");
    printf("2、若取消并返回，请输入“\\”\n");
    printf("———————————————————\n");
    do {
	  do {
		iflegal = 1;
		memset(managerid, 0, sizeof(managerid));
		printf("请输入用户名：");
		scanf("%s", managerid);
		if (managerid[0] == 92 && managerid[1] == 0) {
		    system("cls");
		    return;
		}
		if (managerid[18] != 0 || managerid[19] != 0)iflegal = 0;
		if (!iflegal) {
		    printf("输入有误！请重新输入\n");
		}
	  } while (!iflegal);
	  do {
		iflegal = 1;
		memset(password, 0, sizeof(password));
		printf("请输入密码：");
		scanf("%s", password);
		if (password[0] == 92 && password[1] == 0) {
		    system("cls");
		    return;
		}
		if (password[18] != 0 || password[19] != 0)iflegal = 0;
		if (!iflegal) {
		    printf("输入有误！请重新输入\n");
		}
	  } while (!iflegal);

	  if (check_manager_with_pas(managerid, password) != NULL) {
		ifhasone = 1;
		manager thisone;
		manager* c = check_manager_without_free(managerid);
		c->lastTimeOfUse = time(NULL);
		managercopy(&thisone, c);
		managers_override();
		system("cls");
		gotoMenu_manager(thisone.managerID, thisone.level);
		c = check_manager_without_free(managerid);
		c->lastTimeOfUse = time(NULL);
		managers_override();
	  }
	  else {
		ifhasone = 0;
		printf("用户名或密码错误！请重新输入！\n");
	  }
    } while (!ifhasone);
}