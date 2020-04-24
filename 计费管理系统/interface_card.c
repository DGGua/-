//�Ʒ�Ҳ������
//billing�����
//mallocdewenti
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

char* id_of_card;

//���˵�����
void gotoMenu_card(char* id){
    id_of_card = id;
	printf("��ã�%s��\n",id);
	char inputnumber[5];				//�����û����ݲ������
	//ѭ����ӡ��Ļ
	do {
		printf("�������������������ˡ�����������������\n");
		printf("1���ϻ�\n");
		printf("2���»�\n");
		printf("3����ѯ��ǰ����Ϣ\n");
		printf("4����ѯ���Ѽ�¼\n");
		printf("5��ע����\n");
		printf("0���˳���¼\n");
		printf("��������������������������������������\n");
		printf("����ѡ��ǰ���֣�0~5�������س����в�����"); 
		scanf("%s", inputnumber);
		system("cls");
		if (inputnumber[1] != 0)inputnumber[0] = 0;							//�ж��û������ǲ��ǵ����ַ�
		switch (inputnumber[0]-'0') {
		case 1:system("cls"); gotoGetUp(); break;
		case 2:system("cls"); gotoGetDown(); break;
		case 3:system("cls"); gotoGetInfo(); break;
		case 4:system("cls"); gotoCheckLog(); break;
		case 5:system("cls"); gotoDelete(); break;
		case 0: system("cls");gotoExit(); break;
		default:
			printf("���벻�Ϸ������������룡\n"); 
			system("pause");
			system("cls");
			break;
		}
	} while (inputnumber[0] != '0');
}

//�ϻ�����							    ������
void gotoGetUp() {
    char cardid[20] = { 0 }, password[20] = { 0 };
    int iflegal = 1, ifhasone = 1;
    switch (check_card(id_of_card)->nStatus) {
    case 1:printf("��ǰ�˻��Ѿ��ϻ��������»�\n"); break;
    case 2:printf("��ǰ�˻��ѱ�ע����\n"); break;
    case 3:printf("��ǰ�˻��Ѿ����ڣ�\n"); break;
    default: {
	  printf("�������������ϡ�����������������������\n");
	  printf("�ϻ���֪��\n");
	  printf("4���Ʒ�����ƣ�����һ��İ�һ�봦��\n");
	  printf("1����ǰ�Ʒѱ�׼��%.2fԪ/��\n",moneypersec);
	  printf("6�����»�ʱ���㽫�޷��»�����ֵ������»�\n");
	  printf("7��������ػ���ǼƷ����⣬����ѯ����Ա\n");
	  printf("8����ȡ���ϻ������أ������롰\\��\n");
	  printf("��������������������������������������\n");
	  printf("�Ƿ�ȷ���ϻ�����1/0����");
	  char ans[5];
	  scanf("%s", ans);
	  while (ans[1] != 0 || (ans[0] != '1' && ans[0] != '0')) {
		printf("�����������������루1/0����\n");
		scanf("%s", ans);
	  }
	  if (ans[0] =='0') {
		printf("��ȡ���ϻ����ַ���Ŀ¼\n");
	  }
	  else {
		time_t getuptime = time(NULL);
		char str[20];
		time_ttostring(str, getuptime);
		card* c = check_card_without_free(id_of_card);
		c->lastTimeOfUse = getuptime;
		c->nStatus = 1;
		cards_override();
		printf("%s �� %s �ϻ��ɹ���\n", cardid, str);
		printf("�»�ʱ��ѡ���»���ѡ�����\n");
		
	  }
    }
    }
    system("pause");
    system("cls");
}

//�»�����                        
void gotoGetDown() {
	if (check_card(id_of_card)->nStatus!=1) {
		printf("��ǰ�˻�δ���ϻ����޷��»���\n");
		system("pause");
		system("cls");
	}
	else {
		time_t nowtime=time(NULL);
		time_t getuptime = check_card(id_of_card)->lastTimeOfUse;
		double money_to_pay = moneytopay(getuptime,nowtime);
		if (check_card(id_of_card)->moneyleft < money_to_pay) {
			printf("�������㣡����ϵ����Ա��ֵ���»���\n");
			system("pause");
			system("cls");
		}
		else {
			card* cardnow = check_card_without_free(id_of_card);
			time_t getdowntime = time(NULL);
			cardnow->moneyleft -= money_to_pay;
			create_a_billing_record(0,id_of_card, money_to_pay, cardnow->lastTimeOfUse, getdowntime,cardnow->moneyleft,NULL);
			cardnow->nStatus = 0;
			cardnow->TotalUse += money_to_pay;
			cardnow->lastTimeOfUse = getdowntime;
			cardnow->nUseCount++;
			cards_override();
			printf(" �»��ɹ���\n");
			printf("%-15s%-10s\n��������������������������������\n%-15.2f%-10.2f\n","���λ���","����ʣ��", money_to_pay, check_card(id_of_card)->moneyleft);
			system("pause");
			system("cls");
		}
	}
}

//��ѯ��ǰ����Ϣ
void gotoGetInfo(){
    char time[20],timeofcreate[20];
    time_ttostring(time, check_card(id_of_card)->lastTimeOfUse);
    time_ttostring(timeofcreate, check_card(id_of_card)->timeToCreate);
    printf("�������������顪ѯ�������š�Ϣ������������\n");
    printf("��ѯ��������Ϣ��\n\n%-18s%-8s%-10s%-10s%-15s%-25s%-30s\n",
	  "����","���","��ǰ״̬","ʹ�ô���", "��ʹ�ý��","�½���ʱ��","���һ���»�ʱ��");
    printf("����������������������������������������������������������������������������������������������������������\n");
    printf("%-18s%-8.2f%-10s%-10d%-15.2f%-25s%-30s\n",
	  check_card(id_of_card)->cardID, check_card(id_of_card)->moneyleft, statustostring[check_card(id_of_card)->nStatus], 
	  check_card(id_of_card)->nUseCount, check_card(id_of_card)->TotalUse, timeofcreate, time);
    printf("����������������������������������������������������������������������������������������������������������\n");
    system("pause");
    system("cls");
    return;
}

//��ѯ���Ѽ�¼����               ������
void gotoCheckLog() {
    printf("�������������顪ѯ�������ѡ��ǡ�¼����������\n");
    printf("��ѯ��%s���½���¼��\n\n", id_of_card);
    printf("%-8s%-25s%-25s%-20s%-10s%-20s\n","","��ʼʱ��","����ʱ��","����/��ֵ���","���","��������Ա");
    printf("��������������������������������������������������������������������������������������������\n");
    billings_line *o = check_billing_record_with_id(id_of_card);
    
    while (o != NULL) {
	  char t1[20], t2[20];
	  time_ttostring(t1, o->a_record.begin);
	  time_ttostring(t2, o->a_record.end);
		printf("%-8s%-25s%-25s%-20d%-10d%-20s\n",
		biilingmodeltostring[o->a_record.model],t1,t2, o->a_record.cost, o->a_record.moneyleft,o->a_record.managerID);
	  o = o->next;
    }
    printf("��������������������������������������������������������������������������������������������\n");
    system("pause");
    system("cls");
}

//ע������
void gotoDelete() {
    printf("������������ע������������������������\n");
    printf("ע����֪��\n");
    printf("1����ע�����Կɵ�¼����ѯ���������ϻ�\n");
    printf("2��ע�����û����ᱣ�������û������ᱻ�ٴ�ע��\n");
    printf("3��������������ʾ��ע�������޷��˻���������ȡ��ע��������ϵ����Ա�˷�\n");
    printf("��������������������������������������\n");
    switch (check_card(id_of_card)->nStatus) {
    case 1:printf("��ǰ�������ϻ��������»�����\n");
    case 2:printf("��ǰ����ע����\n");
    case 3:printf("��ǰ���ѹ��ڣ�\n");
    default: {
	  char timea[20], timeofcreate[20];
	  time_ttostring(timea, check_card(id_of_card)->lastTimeOfUse);
	  time_ttostring(timeofcreate, check_card(id_of_card)->timeToCreate);
	  printf("��ѯ��������Ϣ��\n\n%-18s%-8s%-10s%-10s%-15s%-25s%-30s\n",
		"����", "���", "��ǰ״̬", "ʹ�ô���", "��ʹ�ý��", "�½���ʱ��", "���һ���»�ʱ��");
	  printf("����������������������������������������������������������������������������������������������������������\n");
	  printf("%-18s%-8.2f%-10s%-10d%-15.2f%-25s%-30s\n",
		check_card(id_of_card)->cardID, check_card(id_of_card)->moneyleft, statustostring[check_card(id_of_card)->nStatus],
		check_card(id_of_card)->nUseCount, check_card(id_of_card)->TotalUse, timeofcreate, timea);
	  printf("����������������������������������������������������������������������������������������������������������\n");
	  if (check_card(id_of_card)->moneyleft > 0) {
		printf("��ǰ���л������%.2fԪ���Ƿ��������ע����1/0����", check_card(id_of_card)->moneyleft);
		int ans;
		do {
		    scanf("%d", &ans);
		    if (ans == 0) {
			  printf("��ȡ��ע��\n");
			  system("pause");
			  system("cls");
			  return;
		    }
		    else if (ans != 1)printf("�����������������루1/0����");
		} while (ans != 1 && ans != 0);
	  }
	  char password[20];
	  int  iflegal = 0;
	  do {
		iflegal = 1;
		memset(password, 0, sizeof(password));
		printf("���������루���룺��\\������ֹע������");
		scanf("%s", password);
		if (password[0] == 92 && password[1] == 0) {
		    printf("��ȡ��ע��\n");
		    system("pause");
		    system("cls");
		    return;
		}
		if (password[18] != 0 || password[19] != 0)iflegal = 0;
		if (check_card_with_pas(id_of_card, password) == NULL)iflegal = 0;
		if (!iflegal) {
		    printf("������������������\n");
		}
	  } while (!iflegal);
	  card* c = check_card_without_free(id_of_card);
	  c->nStatus = 2;
	  c->moneyleft = 0;
	  c->lastTimeOfUse = time(NULL);
	  cards_override();
	  printf("%s �����ע������\n", id_of_card);
    }
    }
    system("pause");
    system("cls");
}

//�˳�����
void gotoExit() {
	system("cls");
	return;
}
