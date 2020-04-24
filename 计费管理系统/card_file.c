#define _CRT_SECURE_NO_WARNINGS
#include "model.h"
#include "tool.h"
#include <stdio.h>
#include<stdlib.h>
#include <malloc.h>
#include "card_file.h"

void cards_override_to_file(cards_line* head) {
    remove(cardpath);
    while (head != NULL) {
	  add_a_card_to_file(&(head->a_card));
	  head = head->next;
    }
}

void add_cards_from_file(cards_line** head) {
	FILE* fp;
	 (*head) = (cards_line*)malloc(sizeof(cards_line));
	 cards_line* p = *head,*o=NULL;
	fp = fopen(cardpath, "r");
	if (fp == NULL) {
		fp = fopen(cardpath, "w");
		fp = fopen(cardpath, "r");
		if(fp==NULL) {
		    printf("File Error!");
		    system("pause");
		    exit(0);
		}
	}
	while (!feof(fp) && p != NULL) {
	    fscanf(fp, "%s", p->a_card.cardID);
	    if (p->a_card.cardID[0] == -51)break;
	    fscanf(fp, "%s", p->a_card.password);
	    fscanf(fp, "%lf##%d##%lf##%d##%d##%lld##%lld##%lld",
		  &(p->a_card.moneyleft), &(p->a_card.nStatus), &(p->a_card.TotalUse),
		  &(p->a_card.nUseCount), &(p->a_card.nDel), &(p->a_card.timeToCreate),
		  &(p->a_card.lastTimeOfUse), &(p->a_card.TimeToEnd));
    	    p->next= (cards_line*)malloc(sizeof(cards_line));
	    o = p;
	    p = p->next;
	}
	if(o!=NULL)o->next = NULL;
	if (*head == p)*head = NULL;
	free(p);
	fclose(fp);
}


void add_a_card_to_file(card*p) {
	FILE* fp;
	fp = fopen(cardpath, "a");
	if (fp == NULL) {
	    fp = fopen(cardpath, "w");
	    fp = fopen(cardpath, "a");
	    if (fp == NULL) {
		  printf("File Error!");
		  system("pause");
		  exit(0);
	    }
	}
	fprintf(fp, "%s\n%s\n%lf##%d##%lf##%d##%d##%lld##%lld##%lld\n",
			p->cardID, p->password, p->moneyleft,
			p->nStatus, p->TotalUse, p->nUseCount,
			p->nDel, p->timeToCreate, p->lastTimeOfUse,
			p->TimeToEnd);
    fclose(fp);
}

