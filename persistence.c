
#include "model.h"

Terminal_T* TERMINAL_LIST_HEAD = NULL;


Terminal_T* persistence_get_head_terminal(void) {
	return TERMINAL_LIST_HEAD;
}

Terminal_T* persistence_add_terminal(Terminal_T* term) {
	if (TERMINAL_LIST_HEAD == NULL) {
		TERMINAL_LIST_HEAD = term;
		return term;
	}
	Terminal_T* rec = TERMINAL_LIST_HEAD;
	while (rec->next != NULL) {
		rec = rec->next;
	}
	rec->next = term;
	return term;
}

Terminal_T* persistence_remove_terminal(long tid) {
	Terminal_T* head = TERMINAL_LIST_HEAD;
	if (tid == head->id) {
		head = head->next;
		return head;
	}
	Terminal_T* rec;
	Terminal_T* prev_rec;
	prev_rec = head;
	rec = head->next;

	while (rec->id != tid) {
		prev_rec = rec;
		rec = rec->next;
	}
	prev_rec->next = rec->next;
	return rec;
}

Terminal_T* persistence_find_terminal(long id) {
	if (TERMINAL_LIST_HEAD == NULL) {
		return NULL;
	}
	if (id == TERMINAL_LIST_HEAD->id) {
		return TERMINAL_LIST_HEAD;
	} else {
		Terminal_T* rec = TERMINAL_LIST_HEAD;
		while (rec->id != id) {
			rec = rec->next;
			if (rec == NULL) {
				return NULL;
			}
		}
		return rec;
	}
	return NULL;
}

Terminal_T* mem_create_terminal(int num_card_types, Card_Type_T * card_types, int num_transaction_types, Transaction_Type_T * transaction_type) {
	static long id = 0;
	Terminal_T* term = malloc(sizeof(Terminal_T));

	term->id = ++id;
	term->num_card_types = num_card_types;
	term->num_transaction_types = num_transaction_types;
	term->card_types = malloc(num_card_types * sizeof(Card_Type_T));
	term->transaction_type = malloc(num_transaction_types * sizeof(Transaction_Type_T));

	int i;
	for (i = 0; i < num_transaction_types; i++) {
		term->transaction_type[i] = transaction_type[i];
	}
	for (i = 0; i < num_card_types; i++) {
		term->card_types[i] = card_types[i];
	}

	return term;
}

void mem_delete_terminal(Terminal_T* term) {
	free(term->card_types);
	free(term->transaction_type);
	free(term);
}

