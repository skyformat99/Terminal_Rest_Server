

#include "model.h"
#include <json-c/json.h>
#include "stdio.h"

typedef json_object* json_t;

const char* TRAN_TYPE_K = "transactionType";
const char* CARD_TYPE_K = "cardType";
const char* ID_K = "id";

Terminal_T* parse_terminal(const char* json) {
	json_t body = json_tokener_parse(json);
	int i;

	json_t transaction_types_json = json_object_object_get(body, TRAN_TYPE_K);
	int num_transaction_types = json_object_array_length(transaction_types_json);
	Transaction_Type_T* transaction_types = malloc(num_transaction_types * sizeof(Transaction_Type_T));
	for (i = 0; i < num_transaction_types; i++) {
		char* tran_type = json_object_get_string(json_object_array_get_idx(transaction_types_json, i));
		transaction_types[i] = parse_card_type(tran_type);
	}

	json_t card_types_json = json_object_object_get(body, TRAN_TYPE_K);
	int num_card_types = json_object_array_length(card_types_json);
	Card_Type_T* card_types = malloc(num_card_types * sizeof(Card_Type_T));
	for (i = 0; i < num_card_types; i++) {
		char* card_type = json_object_get_string(json_object_array_get_idx(card_types_json, i));
		card_types[i] = parse_transaction_type(card_type);
	}

	json_object_put(body); // Delete the json object
	return mem_create_terminal(num_card_types, card_types, num_transaction_types, transaction_types_json);
}


json_t json_for_term(const Terminal_T* term) {
	int i;
	json_t body;

	body = json_object_new_object();

	json_object_object_add(body, ID_K, json_object_new_int64(term->id));
//
	json_t transactions_array = json_object_new_array();
	Transaction_Type_T* trans_array = term->transaction_type;
	for (i = 0; i < term->num_transaction_types; i++) {
		printf("\n---%d %d \n", term->num_transaction_types, print_transaction_type(term->transaction_type[i]));
//		char * tran_type = print_transaction_type(term->transaction_type[i]);
//		json_object_array_add(transactions_array, json_object_new_string(tran_type));
	}
	json_object_object_add(body, TRAN_TYPE_K, transactions_array);
//
//	json_t cards_array = json_object_new_array();
//	for (i = 0; i < term->num_card_types; i++) {
//		char * card_type = print_card_type(term->card_types[i]);
//		json_object_array_add(cards_array, json_object_new_string(card_type));
//	}
//	json_object_object_add(body, CARD_TYPE_K, cards_array);

	return body;
}

const char* print_and_dispose(json_t body) {
	const char* ret = json_object_to_json_string(body);

	char* ret2 = malloc(strlen(ret) * sizeof(char));
	strcpy(ret2, ret); // needed because disposing the json object also disposes the string buffer
	json_object_put(body); // Delete the json object

	return ret2;
}

const char* print_terminal(const Terminal_T* term) {
	json_t j = json_for_term(term);
	return print_and_dispose(j);
}

const char* print_all_terminals(void) {
	json_t terms_array = json_object_new_array();
	Terminal_T* rec = persistence_get_head_terminal();
	while (rec != NULL) {
		json_object_array_add(terms_array, json_for_term(rec));
		rec = rec->next;
	}

	return print_and_dispose(rec);
}


Transaction_Type_T parse_transaction_type(const char* str) {
	if (strcasecmp("Cheque", str) == 0) {
		return Cheque;
	} else if (strcasecmp("Savings", str) == 0) {
		return Savings;
	} else if (strcasecmp("Credit", str) == 0) {
		return Credit;
	}
	return UNKNOWN_TRANS;
}

Card_Type_T parse_card_type(const char* str) {
	if (strcasecmp("Visa", str) == 0) {
		return Visa;
	} else if (strcasecmp("MasterCard", str) == 0) {
		return MasterCard;
	} else if (strcasecmp("EFTPOS", str) == 0) {
		return EFTPOS;
	}
	return UNKNOWN_CARD;
}

const char* print_transaction_type(Transaction_Type_T str) {
	printf("%s", str);
	if (Cheque == str) {
		return "Cheque";
	} else if (Savings == str) {
		return "Savings";
	} else if (Credit == str) {
		return "Credit";
	}
	return NULL;
}


const char* print_card_type(Card_Type_T str) {
	if (Visa == str) {
		return "Visa";
	} else if (MasterCard == str) {
		return "MasterCard";
	} else if (EFTPOS  == str) {
		return "EFTPOS";
	}
	return NULL;
}


