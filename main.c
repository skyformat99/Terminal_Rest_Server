#include <microhttpd.h>
#include <regex.h>
#include "model.h"

const uint16_t PORT = 8088;

regex_t ENDS_WITH_DIGIT;
regex_t ENDS_WITH_NOTHING;

int answer_to_connection(void *cls, struct MHD_Connection *connection,
		const char *url, const char *method, const char *version,
		const char *upload_data, size_t *upload_data_size, void **con_cls) {
	int http_status;
	char* response_payload;

	if (strcmp(MHD_HTTP_METHOD_POST, method) == 0) {
		response_payload = rest_handle_create(url, upload_data);
		http_status = MHD_HTTP_CREATED;
	} else if (strcmp(MHD_HTTP_METHOD_GET, method)) {
		if (regexec(&ENDS_WITH_DIGIT, url, strlen(url), NULL, REG_EXTENDED) == 0) {
			response_payload = rest_handle_retrieve_by_id(url, upload_data);
			http_status = MHD_HTTP_OK;
		} else if (regexec(&ENDS_WITH_NOTHING, url, strlen(url), NULL, REG_EXTENDED) == 0) {
			response_payload = rest_handle_retrieve_all(url, upload_data);
			http_status = MHD_HTTP_OK;
		} else {
			response_payload = "";
			http_status = MHD_HTTP_BAD_REQUEST;
		}
	} else if (strcmp(MHD_HTTP_METHOD_DELETE, method)) {
		rest_handle_delete(url, upload_data);
		response_payload = "";
		http_status = MHD_HTTP_NO_CONTENT;
	} else {
		response_payload = "";
		http_status = MHD_HTTP_METHOD_NOT_ALLOWED;
	}

	if (response_payload == NULL) {
		response_payload = "";
		http_status = MHD_HTTP_NOT_FOUND;
	}

	struct MHD_Response *response =
			MHD_create_response_from_buffer(strlen(response_payload), (void*) response_payload, MHD_RESPMEM_PERSISTENT);
	http_status = MHD_queue_response(connection, http_status, response);
	MHD_destroy_response(response);

	return http_status;
}

int main(int argc, char **argv) {
	regcomp(&ENDS_WITH_DIGIT, ".*/[0-9]+", REG_EXTENDED);
	regcomp(&ENDS_WITH_NOTHING, ".*/", REG_EXTENDED);
	struct MHD_Daemon *daemon;
	daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
			&answer_to_connection, NULL, MHD_OPTION_END);
	if (NULL == daemon)
		return 1;
}

