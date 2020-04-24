#ifndef _CARD_MANAGE_
#define _CARD_MANAGE_
void create_a_card(card* the_new_card);
card* check_card(char* id);
card* check_card_with_pas(char* id, char* pas);
void add_cards(); 
card* check_card_without_free(char* id);
void free_line(cards_line** headl);
void cards_override();
void free_line_with_override();
cards_line* check_card_mohu(char* id);
#endif
#include "model.h"