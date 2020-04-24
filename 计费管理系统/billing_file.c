#define _CRT_SECURE_NO_WARNINGS
#include "model.h"
#include"tool.h"
#include <string.h>
#include <stdio.h>
#include<stdlib.h>
#include <malloc.h>
#include "card_file.h"
#include "billing_file.h"

void add_a_billing_record(billing* p) {
    FILE* fp;
    fp = fopen(billingpath, "a");
    if (fp == NULL) {
	  fp = fopen(billingpath, "w");
	  fp = fopen(billingpath, "a");
	  if (fp == NULL) {
		printf("File Error!");
		system("pause");
		exit(0);
	  }
    }
    fprintf(fp, "%s\n%d##%lld##%lld##%d##%d##%s\n",
	  p->cardID, p->model, p->begin, p->end, p->cost, p->moneyleft,p->managerID);
    fclose(fp);
}

void add_records_from_file(billings_line** head) {
    FILE* fp;
    (*head) = (billings_line*)malloc(sizeof(billings_line));
    billings_line* p = *head, * o = NULL;
    fp = fopen(billingpath, "r");
    if (fp == NULL) {
	  fp = fopen(billingpath, "w");
	  fp = fopen(billingpath, "r");
	  if (fp == NULL) {
		printf("File Error!");
		system("pause");
		exit(0);
	  }
    }
    while (!feof(fp)) {
	  fscanf(fp, "%s", p->a_record.cardID);
	  if (p->a_record.cardID[0] == -51)break;
	  fscanf(fp, "%d##%lld##%lld##%d##%d##",
		&(p->a_record.model), &(p->a_record.begin), &(p->a_record.end), &(p->a_record.cost), &(p->a_record.moneyleft));
	  fgets(p->a_record.managerID, 20, fp);
	  p->next = (billings_line*)malloc(sizeof(billings_line));
	  o = p;
	  p = p->next;
    }
    if (o != NULL)o->next = NULL;
    if (*head == p)*head = NULL;
    free(p);
    fclose(fp);
}