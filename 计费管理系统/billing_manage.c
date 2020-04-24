#define _CRT_SECURE_NO_WARNINGS
#include "model.h"
#include"tool.h"
#include <string.h>
#include <malloc.h>
#include "card_file.h"
#include "billing_file.h"

billings_line* head_billing = NULL, * last_billing = NULL, * mohuhead_billing = NULL;
billing buf;


 void create_a_billing_record(int model, char* id, double money, time_t from, time_t to, double moneyleft,char* managerID) {
    billing thistime;
    thistime.model = model;
    strcpy(thistime.cardID, id);
    thistime.begin = from;
    thistime.end = to;
    thistime.cost = money;
    thistime.moneyleft = moneyleft;
    if (managerID == NULL) {
	  strcpy(thistime.managerID," ");
    }
    else {
	  strcpy(thistime.managerID, managerID);
    }
    add_a_billing_record(&thistime);
}
 void free_line_billing(billings_line** headl) {
     billings_line* p = *headl, * o = *headl;
     *headl = NULL;
     while (p != NULL) {
	   p = p->next;
	   free(o);
	   o = p;
     }
 }

 billings_line* check_billing_record_with_id(char* id) {
     if (mohuhead_billing != NULL) {
	   free_line_billing(&mohuhead_billing);
     }
     add_records_from_file(&head_billing);
     billings_line* point = head_billing, * p = mohuhead_billing;
     while (point != NULL) {
	   if (strcmp(point->a_record.cardID, id) == 0) {
		 if (mohuhead_billing == NULL) {
		     mohuhead_billing = (billings_line*)malloc(sizeof(billings_line));
		     mohuhead_billing->next = NULL;
		     billingcopy(&(mohuhead_billing->a_record), &(point->a_record));
		     p = mohuhead_billing;
		 }
		 else {
		     p->next = (billings_line*)malloc(sizeof(billings_line));
		     p = p->next;
		     p->next = NULL;
		     billingcopy(&(p->a_record), &(point->a_record));
		 }
	   }
	   point = point->next;
     }
     return mohuhead_billing;

 }