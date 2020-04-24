#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "tool.h"
#include "model.h"
#include "interface_card.h"
#include "card_manage.h"
#include "manager_manage.h"
#include "billing_manage.h"
#include "manager_manage.h"
#include "interface_manager.h"

char* id_of_manager;

void gotoMenu_manager(char* id, int level)
{
    id_of_manager = id;
    printf("��ã�%s�����Ȩ��Ϊ %d\n", id, level);
    char inputnumber[5];				//�����û����ݲ������
    //ѭ����ӡ��Ļ
    do {
	  memset(inputnumber, 12, sizeof(inputnumber));
	  printf("�������������ܡ�������Ա�����ˡ�����������������\n");
	  printf("1���½���\n");
	  printf("2����ѯ�������Ѽ�¼\n");
	  printf("3����ֵ\n");
	  printf("4���˷�\n");
	  if (level < 2) {
		printf("5����һ��\n");
		printf("6���޸Ŀ�״̬\n");
		printf("7���޸Ŀ�����\n");
		printf("8��Ӫҵ����ͳ��\n");
	  }
	  if (level < 1) {
		printf("9���½�����Ա\n");
		printf("10������Աһ��\n");
		printf("11������Աɾ��\n");
		printf("12���Ʒѱ�׼�޸�\n");
	  }
	  printf("0������\n");
	  printf("������������������������������������������������������\n");
	  printf("����ѡ��ǰ���֣�0~%d�������س����в�����", level < 2 ? (level < 1 ? 12 : 8) : 4);
	  scanf("%s", inputnumber);
	  system("cls");
	  int ans = -1;
	  if (inputnumber[2] == 0)ans = (inputnumber[0] - '0') * 10 + inputnumber[1] - '0';							//�ж��û������ǲ��ǵ����ַ�
	  else if (inputnumber[1] == 0)ans = inputnumber[0] - '0';
	  if ((level == 2 && ans > 4) || (level == 1 && ans > 8))printf("���벻�Ϸ������������룡\n");
	  else {
		switch (ans) {
		case 1: gotoCreateCard(); break;
		case 2: gotoCheckCard(); break;
		case 3: gotoRecharge(); break;
		case 4: gotoPayBack(); break;
		case 5:  gotoCheckAllCards(); break;
		case 6: gotoCreateCard(); break;
		case 7: gotoCreateCard(); break;
		case 8: gotoCreateCard(); break;
		case 9: gotoCreateCard(); break;
		case 10: gotoCreateCard(); break;
		case 11: gotoCreateCard(); break;
		case 12: gotoCreateCard(); break;
		case 0: system("cls"); break;
		default:
		    printf("���벻�Ϸ������������룡\n");
		    system("pause");
		    system("cls");
		    break;
		}
	  }
    } while (inputnumber[0] != '0');
}

//�½���
void gotoCreateCard() {
    char cardid[20] = { 0 }, password[20] = { 0 };
    double money;
    int iflegal = 1;
    printf("�������������¡�����������������������\n");
    printf("������֪��\n");
    printf("1���û��������ţ������볤����С��18\n");
    printf("2����������Ϊ10Ԫ������ʱ�ɳ�ֵ���10Ԫ�����0Ԫ���������ֵ��Ԫ\n");
    printf("3����ȡ�������������û���������������������롰\\�����ֵ���0��\n");
    printf("��������������������������������������\n");
    do {
	  iflegal = 1;																		//�жϴ˴������Ƿ�Ϸ��ı���
	  memset(cardid, 0, sizeof(cardid));				//ÿ������ǰ��ʽ��id����
	  printf("�������û��������ţ���");
	  scanf("%s", cardid);
	  if (cardid[0] == 92 && cardid[1] == 0) {				//�ж��Ƿ����˳�����
		system("cls");
		return;
	  }
	  if (cardid[18])iflegal = 0;																				//�ж��Ƿ񳬹���������
	  if (iflegal) {
		card* checkname = check_card(cardid);
		if (checkname != NULL) {
		    printf("�û����ѱ�ʹ�ã�");
		    iflegal = 0;
		}
	  }
	  if (!iflegal)printf("������������������\n");
    } while (!iflegal);
    do {
	  iflegal = 1;																					//�ж��Ƿ��ǺϷ�����
	  memset(password, 0, sizeof(password));										//��ʼ��id����
	  printf("���������룺");
	  scanf("%s", password);
	  if (password[0] == 92 && password[1] == 0) {									    //�ж��Ƿ�Ҫ�˳�
		system("cls");
		return;
	  }
	  if (password[18])iflegal = 0;														    //�ж��Ƿ񳬹���������
	  if (!iflegal)printf("������������������\n");
    } while (!iflegal);
    do {
	  iflegal = 1;
	  money = -1;
	  printf("�������ֵ��");
	  scanf("%lf", &money);
	  if (money == 0) {																    //�ж��Ƿ�Ҫ�˳�
		system("cls");
		return;
	  }
	  if (money < 10)iflegal = 0;
	  if (!iflegal)printf("������������������\n");
    } while (!iflegal);
    if (money != 0) {
	  card newone;
	  strcpy(newone.cardID, cardid);
	  strcpy(newone.password, password);
	  newone.moneyleft = money - 10;
	  newone.nStatus = 0;
	  newone.TotalUse = 0;
	  newone.nUseCount = 0;
	  newone.nDel = 0;
	  newone.timeToCreate = time(NULL);
	  newone.lastTimeOfUse = time(NULL);
	  create_a_billing_record(1, newone.cardID, money - 10, time(NULL), time(NULL), newone.moneyleft,id_of_manager);
	  char str[20];
	  time_ttostring(str, newone.timeToCreate);
	  printf("�����ɹ���\n\n");
	  printf("%-18s%-18s%-10s%-20s\n", "����", "����", "���", "����ʱ��");
	  printf("������������������������������������������������������������������������\n");
	  printf("%-18s%-18s%-10.2lf%-20s\n", newone.cardID, password, money - 10, str);
	  printf("������������������������������������������������������������������������\n");
	  create_a_card(&newone);
	  system("pause");
    }
    system("cls");
    return;
}

//��ѯ��
void gotoCheckCard() {
    printf("�������������顪��ѯ������������������\n");
    printf("��ѯ��֪��\n");
    printf("1��ѡ��ȷ���һ�ģ�����Һ󣬾�ȷ��ģ�����뿨��\n");
    printf("2����ȷ��ѯ����Ϣ����ʾ�ÿ����ʽ�䶯��¼��ģ�����Ҳ�����ʾ\n");
    printf("3����ȡ����ѯ�������û�������������롰\\�����ѯѡ��0��\n");
    printf("��������������������������������������\n");
    int iflegal;
    int ans = -1;
    do {
	  iflegal = 1;
	  ans = -1;
	  printf("������ѡ�1:��ȷ����/2:ģ�����ң���");
	  scanf("%d", &ans);
	  if (ans == 0) {
		printf("��ȡ������\n");
		break;
	  }
	  else if (ans == 1) {
		char id[20];
		printf("�뾫ȷ�����ѯ���ţ�");
		scanf("%s", id);
		if (check_card(id) != NULL) {
		    char time[20], timeofcreate[20];
		    time_ttostring(time, check_card(id)->lastTimeOfUse);
		    time_ttostring(timeofcreate, check_card(id)->timeToCreate);
		    printf("��ѯ��������Ϣ��\n\n%-18s%-18s%-8s%-10s%-10s%-15s%-25s%-30s\n",
			  "����", "����", "���", "��ǰ״̬", "ʹ�ô���", "��ʹ�ý��", "�½���ʱ��", "���һ���»�ʱ��");
		    printf("����������������������������������������������������������������������������������������������������������������������������������������������\n");
		    printf("%-18s%-18s%-8.2f%-10s%-10d%-15.2f%-25s%-30s\n",
			  check_card(id)->cardID, check_card(id)->password, check_card(id)->moneyleft, statustostring[check_card(id)->nStatus],
			  check_card(id)->nUseCount, check_card(id)->TotalUse, timeofcreate, time);
		    printf("����������������������������������������������������������������������������������������������������������������������������������������������\n");
		}
		else {
		    printf("���޴˿����ּ���������һ���˵�\n");
		}
	  }
	  else if (ans == 2) {
		char id[20];
		printf("�������ѯ�Ŀ���Ƭ�Σ�");
		scanf("%s", id);
		cards_line* head = check_card_mohu(id);
		if (head != NULL) {
		    printf("��ѯ��������Ϣ��\n\n%-18s%-18s%-8s%-10s%-10s%-15s%-25s%-30s\n",
			  "����", "����", "���", "��ǰ״̬", "ʹ�ô���", "��ʹ�ý��", "�½���ʱ��", "���һ���»�ʱ��");
		    printf("����������������������������������������������������������������������������������������������������������������������������������������������\n");
		    while (head != NULL) {
			  char time[20], timeofcreate[20];
			  time_ttostring(time,head->a_card.lastTimeOfUse);
			  time_ttostring(timeofcreate, head->a_card.timeToCreate);
			  printf("%-18s%-18s%-8.2f%-10s%-10d%-15.2f%-25s%-30s\n",
				head->a_card.cardID, head->a_card.password, head->a_card.moneyleft, statustostring[head->a_card.nStatus],
				head->a_card.nUseCount, head->a_card.TotalUse, timeofcreate, time);
			  head = head->next;
		    }
		    printf("����������������������������������������������������������������������������������������������������������������������������������������������\n");
		}
		else {
		    printf("��ѯ���������Ϣ���ּ���������һ���˵�\n");
		}
	  }
    } while (ans != 0 && ans != 1 && ans != 2);
    system("pause");
    system("cls");
    return;
}

//��ֵ
void gotoRecharge() {
    char cardid[20],pas[20];
    int iflegal = 0;
    double  val;
    printf("�������������䡪��ֵ������������\n");
    printf("��ֵ��֪��\n");
    printf("1����ȷ�����ֵ����\n");
    printf("2����������ֵ���������ֵ���������Ա������ɳ�ֵ\n");
    printf("3����ȡ����ֵ�����ڿ��Ż��߹���Ա��������������롰\\�����ֵ���0��\n");
    printf("��������������������������������������\n");
    printf("�뾫ȷ�����ֵ���ţ�");
    do {
	  iflegal = 0;
	  scanf("%s", cardid);
	  if (cardid[1] == 0 && cardid[0] == 92) {
		printf("��ȡ����ֵ\n");
		system("pause");
		system("cls");
		return;
	  }
	  if (check_card(cardid) == NULL) {
		printf("���޴˿������������룺");
		iflegal = 0;
	  }
	  else {
		iflegal = 1;
	  }
    } while (!iflegal);
    printf("�������ֵ��");
    do {
	  iflegal = 0;
	  scanf("%lf", &val);
	  if (val == 0) {
		printf("��ȡ����ֵ\n");
		system("pause");
		system("cls");
		return;
	  }
	  else if(val<0){
		printf("�����������������룺");
	  }
	  else {
		iflegal = 1;
	  }
    } while (!iflegal);
    printf("���������Ա�˻����룺");
    do {
	  iflegal = 0;
	  scanf("%s", pas);
	  if (pas[1] == 0 && pas[0] == 92) {
		printf("��ȡ����ֵ\n");
		system("pause");
		system("cls");
		return;
	  }
	  else if (check_manager_with_pas(id_of_manager, pas) == NULL) {
		printf("����������������룺");
	  }
	  else {
		iflegal = 1;
	  }
    } while (!iflegal);
    card* c = check_card_without_free(cardid);
    c->moneyleft += val;
    create_a_billing_record(1, cardid, val, time(NULL), time(NULL), c->moneyleft,id_of_manager);
    printf("��ֵ�ɹ���%s�������%.2fԪ\n", cardid, c->moneyleft);
    cards_override();
    system("pause");
    system("cls");
}

//�˷�
void gotoPayBack() {
    char cardid[20], pas[20];
    int iflegal = 0;
    double  val;
    printf("�������������ˡ����ѡ�����������\n");
    printf("�˷���֪��\n");
    printf("1����ȷ�����˷ѿ���\n");
    printf("2���������˷ѿ��������˷ѽ��������Ա��������˷�\n");
    printf("3����ȡ���˷ѣ����ڿ��Ż��߹���Ա��������������롰\\�����˷ѽ��0��\n");
    printf("4�����˻�ȫ�����ã��˷ѽ��-1��\n");
    printf("��������������������������������������\n");
    printf("�뾫ȷ�����˷ѿ��ţ�");
    do {
	  iflegal = 0;
	  scanf("%s", cardid);
	  if (cardid[1] == 0 && cardid[0] == 92) {
		printf("��ȡ���˷�\n");
		system("pause");
		system("cls");
		return;
	  }
	  if (check_card(cardid) == NULL) {
		printf("���޴˿������������룺");
		iflegal = 0;
	  }
	  else {
		printf("��ѯ��������Ϣ��\n\n%-18s%-8s%-10s%-10s%-15s\n",
		    "����",  "���", "��ǰ״̬", "ʹ�ô���", "��ʹ�ý��");
		printf("������������������������������������������������������������������������������������������������������\n");
		printf("%-18s%-8.2f%-10s%-10d%-15.2f\n",
		    check_card(cardid)->cardID, check_card(cardid)->moneyleft, statustostring[check_card(cardid)->nStatus],
		    check_card(cardid)->nUseCount, check_card(cardid)->TotalUse);
		printf("������������������������������������������������������������������������������������������������������\n");
		iflegal = 1;
	  }
    } while (!iflegal);
    printf("�������˷ѽ�");
    do {
	  iflegal = 0;
	  scanf("%lf", &val);
	  if (val == 0) {
		printf("��ȡ���˷�\n");
		system("pause");
		system("cls");
		return;
	  }
	  else if (val < 0&&val!=-1) {
		printf("�����������������룺");
	  }
	  else {
		iflegal = 1;
	  }
    } while (!iflegal);
    printf("���������Ա�˻����룺");
    do {
	  iflegal = 0;
	  scanf("%s", pas);
	  if (pas[1] == 0 && pas[0] == 92) {
		printf("��ȡ���˷�\n");
		system("pause");
		system("cls");
		return;
	  }
	  else if (check_manager_with_pas(id_of_manager, pas) == NULL) {
		printf("����������������룺");
	  }
	  else {
		iflegal = 1;
	  }
    } while (!iflegal);
    card* c = check_card_without_free(cardid);
    if (val == -1) {
	  val = c->moneyleft;
	  c->moneyleft = 0;
    } 
    else {
	  c->moneyleft -= val;
    }
    create_a_billing_record(2, cardid, val, time(NULL), time(NULL), c->moneyleft,id_of_manager);
    printf("�˷ѳɹ���%s�������%.2fԪ\n", cardid, c->moneyleft);
    cards_override();
    system("pause");
    system("cls");
}

//��һ��
void gotoCheckAllCards() {
    printf("������������������һ������������������\n");
    printf("�������¿���Ϣ��\n\n%-18s%-18s%-8s%-10s%-10s%-15s%-25s%-30s\n",
	  "����", "����", "���", "��ǰ״̬", "ʹ�ô���", "��ʹ�ý��", "�½���ʱ��", "���һ���»�ʱ��");
    printf("����������������������������������������������������������������������������������������������������������������������������������������������\n");
    cards_line* all = check_card_mohu("");
    while (all != NULL) {
	  char timeofcreate[20], timea[20];
	  time_ttostring(timeofcreate, all->a_card.timeToCreate);
	  time_ttostring(timea, all->a_card.lastTimeOfUse);
	  printf("%-18s%-18s%-8.2f%-10s%-10d%-15.2f%-25s%-30s\n",
		all->a_card.cardID, all->a_card.password, all->a_card.moneyleft, statustostring[all->a_card.nStatus],
		all->a_card.nUseCount, all->a_card.TotalUse, timeofcreate, timea);
	  all = all->next;
    }
    system("pause");
    system("cls");
}

//�޸Ŀ�״̬
void gotoChangeStatus() {
    
}