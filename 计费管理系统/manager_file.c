#define _CRT_SECURE_NO_WARNINGS
#include "model.h"
#include "tool.h"
#include <stdio.h>
#include<stdlib.h>
#include <malloc.h>
#include "manager_file.h"

void managers_override_to_file(managers_line* head) {
    remove(managerpath);
    while (head != NULL) {
	  add_a_manager_to_file(&(head->a_manager));
	  head = head->next;
    }
}

void add_managers_from_file(managers_line** head) {
    FILE* fp;
    (*head) = (managers_line*)malloc(sizeof(managers_line));
    managers_line* p = *head, * o = NULL;
    fp = fopen(managerpath, "r");
    if (fp == NULL) {
	  fp = fopen(managerpath, "w");
	  fp = fopen(managerpath, "r");
	  if (fp == NULL) {
		printf("File Error!");
		system("pause");
		exit(0);
	  }
    }
    while (!feof(fp)) {
	  fscanf(fp, "%s", p->a_manager.managerID);
	  if (p->a_manager.managerID[0] == -51)break;
	  fscanf(fp, "%s", p->a_manager.password);
	  fscanf(fp, "%d##%lld##%lld",
		&(p->a_manager.level), &(p->a_manager.timeToCreate), &(p->a_manager.lastTimeOfUse));
	  p->next = (managers_line*)malloc(sizeof(managers_line));
	  o = p;
	  p = p->next;
    }
    if (o != NULL)o->next = NULL;
    if (*head == p)*head = NULL;
    free(p);
    fclose(fp);
}


void add_a_manager_to_file(manager* p) {
    FILE* fp;
    fp = fopen(managerpath, "a");
    if (fp == NULL) {
	  fp = fopen(managerpath, "w");
	  fp = fopen(managerpath, "a");
	  if (fp == NULL) {
		printf("File Error!");
		system("pause");
		exit(0);
	  }
    }
    fprintf(fp, "%s\n%s\n%d##%lld##%lld\n",
	  p->managerID, p->password, p->level, p->timeToCreate, p->lastTimeOfUse);
    fclose(fp);
}

