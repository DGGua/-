#define _CRT_SECURE_NO_WARNINGS
#include "model.h"
#include"tool.h"
#include <string.h>
#include <malloc.h>
#include "card_file.h"
#include "card_manage.h"

cards_line* head_card = NULL, * last_card = NULL, * mohuhead_card = NULL;
card buf;

void cards_override() {
    free_line_with_override();
}

void free_line_with_override() {
    cards_override_to_file(head_card);
    cards_line* p = head_card;
    while (head_card != NULL) {
	  head_card = head_card->next;
	  free(p);
	  p = head_card;
    }
}

void free_line(cards_line** headl) {
    cards_line* p = *headl,*o=p;
    *headl = NULL;
    while (p!= NULL) {
	  o = p;
	  p= p->next;
	  free(o);
    }
}

void add_cards() {
	add_cards_from_file(&head_card);
}

void create_a_card(card* the_new_card) {
    add_a_card_to_file(the_new_card);
}

card* check_card(char* id) {
      add_cards_from_file(&head_card);
	cards_line* point = head_card;
	while (point != NULL) {
		if (strcmp(id, point->a_card.cardID) == 0) {
			break;
		}
		point = point->next;
	}
	if (point == NULL) {
		free_line(&head_card);
		return NULL;
	}
	else {
		cardcopy(&buf,&(point->a_card));
		free_line(&head_card);
		return &buf;
	}
}

card* check_card_with_pas(char* id, char* pas) { 
	add_cards_from_file(&head_card);
	cards_line* point = head_card;
	while (point != NULL) {
		if (strcmp(id, point->a_card.cardID) == 0&& strcmp(pas, point->a_card.password) == 0) {
			break;
		}
		point = point->next;
	}
	if (point == NULL) {
		free_line(&head_card);
		return NULL;
	}
	else {
		cardcopy(&buf, &(point->a_card));
		free_line(&head_card);
		return &buf;
	}
}

card* check_card_without_free(char* id) {
    add_cards_from_file(&head_card);
    cards_line* point = head_card;
    while (point != NULL) {
	  if (strcmp(id, point->a_card.cardID) == 0) {
		break;
	  }
	  point = point->next;
    }
    if (point == NULL) {
	  return NULL;
    }
    else {
	    return &(point->a_card);
    }
}

cards_line* check_card_mohu(char* id) {
    if (mohuhead_card != NULL) {
	  free_line(&mohuhead_card);
    }
    add_cards_from_file(&head_card);
    cards_line* point = head_card, * p=mohuhead_card;
    char* ask;
    while (point != NULL) {
	  if ((ask=strstr( point->a_card.cardID,id) !=NULL)) {
		if (mohuhead_card == NULL) {
		    mohuhead_card = (cards_line*)malloc(sizeof(cards_line));
		    mohuhead_card->next = NULL;
		    cardcopy(&(mohuhead_card->a_card),&( point->a_card));
		    p = mohuhead_card;
		}
		else{
		    p->next= (cards_line*)malloc(sizeof(cards_line));
		    p = p->next;
		    p->next = NULL;
		    cardcopy(&(p->a_card), &(point->a_card));
		}
	  }
	  point = point->next;
    }
    return mohuhead_card;

}