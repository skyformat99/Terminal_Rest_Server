
#import "model.h"
#import <string.h>

const char* rest_handle_create(const char *url, const char *upload_data){
	Terminal_T* new_terminal = parse_terminal(upload_data);
	new_terminal = persistence_add_terminal(new_terminal);
//	printf ("%d", new_terminal->id);
//	printf ("%d", new_terminal->num_transaction_types);
	return print_terminal(new_terminal);
//	return "";
}

long id_from_url(const char* url) {
	long id;
	sscanf(url, "/%d", &id);
	return id;
}

const char* rest_handle_delete(const char *url, const char *upload_data) {
	Terminal_T* removed_terminal = persistence_find_terminal(id_from_url(url));
	if (removed_terminal == NULL) {
		return NULL;
	}
	persistence_remove_terminal(removed_terminal->id);
	mem_delete_terminal(removed_terminal);
	return "";
}

const char* rest_handle_retrieve_by_id(const char *url, const char *upload_data) {
	Terminal_T* found_terminal = persistence_find_terminal(id_from_url(url));
	return print_terminal(found_terminal);
}

const char* rest_handle_retrieve_all(const char *url, const char *upload_data){
	return print_all_terminals();
}
