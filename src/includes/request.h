#ifndef REQUEST_H
#define REQUEST_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <dotenv.h>

#define MAX_INPUT_SIZE 200

static size_t cb(void *data, size_t size, size_t nmemb, void *clientp);
char * return_api_key();
char * makeAPIrequest(char *prompt);

#endif
