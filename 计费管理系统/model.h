#ifndef _MODEL_
#define _MODEL_
#include <time.h>


#define cardpath "data\\card.txt"
#define billingpath "data\\billing.txt"
#define managerpath "data\\manager.txt"

double moneypersec;
char statustostring[][7];
char biilingmodeltostring[][7];

typedef struct _manager {
    char managerID[19];
    char password[19];
    int  level;           // Ȩ�ޣ�0���
    time_t timeToCreate;
    time_t lastTimeOfUse;
} manager;

typedef struct _managers_line {
    manager a_manager;
    struct  _managers_line* next;
}managers_line;

typedef struct _card {
	char cardID[19];
	char password[19];
	double moneyleft;
	int  nStatus;           // ��״̬(0-δ�ϻ���1-�����ϻ���2-��ע����3-ʧЧ)
	double TotalUse;        // �ۼƻ��ѽ��
	int nUseCount;          // ʹ�ô���
	int nDel;               // ɾ����ʶ 0-δɾ��,1-ɾ��
	time_t timeToCreate;
	time_t lastTimeOfUse;
	time_t TimeToEnd;            // ���Ľ�ֹʱ�� 
	
} card;


typedef struct _cards_line {
    card a_card;
    struct _cards_line* next;
}cards_line;


typedef struct _billing {
    int model;		//0-���� 1-��ֵ 2-�˷�
    char cardID[19];
    time_t begin;
    time_t end;
    int cost;
    int moneyleft;
    char managerID[20];
}billing;

typedef struct _billing_line {
    billing a_record;
    struct _billing_line* next;
}billings_line;
#endif