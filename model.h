

#ifndef SMARTPAY_MODEL_H
#define SMARTPAY_MODEL_H

#include <stdlib.h>
#include <string.h>

typedef enum {
	Visa,
	MasterCard,
	EFTPOS,
	UNKNOWN_CARD
} Card_Type_T;


typedef enum {
	Cheque,
	Savings,
	Credit,
	UNKNOWN_TRANS
} Transaction_Type_T;

struct Terminal_Struct_T{
	long id;
	int num_card_types;
	int num_transaction_types;
	Card_Type_T* card_types;
	Transaction_Type_T* transaction_type;
	struct Terminal_Struct_T* next;
};

typedef struct Terminal_Struct_T Terminal_T;

Transaction_Type_T parse_transaction_type(const char* str);
Card_Type_T parse_card_type(const char* str);
Terminal_T* parse_terminal(const char* json);
const char* print_transaction_type(Transaction_Type_T str);
const char* print_card_type(Card_Type_T str);
const char* print_terminal(const Terminal_T* term);
const char* print_all_terminals(void);


Terminal_T* persistence_add_terminal(Terminal_T* term);
Terminal_T* persistence_get_head_terminal(void);
Terminal_T* persistence_remove_terminal(long id);
Terminal_T* persistence_find_terminal(long id);
Terminal_T* mem_create_terminal(int num_card_types, Card_Type_T * card_types, int num_transaction_types, Transaction_Type_T * transaction_type);
void mem_delete_terminal(Terminal_T* term);

const char* rest_handle_create(const char *url, const char *upload_data);
const char* rest_handle_delete(const char *url, const char *upload_data);
const char* rest_handle_retrieve_by_id(const char *url, const char *upload_data);
const char* rest_handle_retrieve_all(const char *url, const char *upload_data);

#endif // SMARTPAY_MODEL_H
