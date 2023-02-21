#include "../includes/request.h"

struct memory {
  char *response;
  size_t size;
};

static size_t cb(void *data, size_t size, size_t nmemb, void *clientp)
{
  size_t realsize = size * nmemb;
  struct memory *mem = (struct memory *)clientp;
  char *ptr = realloc(mem->response, mem->size + realsize + 1);
  if(ptr == NULL) {
    printf("[ERROR]");
    return 0;  /* out of memory! */
  }
  mem->response = ptr;
  memcpy(&(mem->response[mem->size]), data, realsize);
  mem->size += realsize;
  mem->response[mem->size] = 0;
  return realsize;
}

char * return_api_key()
{
  env_load(".", false);
  char *api_key = getenv("API_KEY");
  return api_key;
}

char * makeAPIrequest(char prompt[MAX_INPUT_SIZE * 5])
{
  CURL *curl;
  CURLcode res;
  char *returned_api_key = return_api_key();
  char *api_key_to_send = malloc(sizeof(returned_api_key) + 200);
  sprintf(api_key_to_send, "Authorization: Bearer %s", returned_api_key);
  struct memory chunk = {0};
  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();
  if (curl) {
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, api_key_to_send);
    char *url = "https://api.openai.com/v1/completions";
    char *data = malloc(strlen(prompt) + 200);
    sprintf(data,
        "{\"model\": \"text-davinci-003\", \"prompt\": \"%s\",\
        \"temperature\": 1.0, \"max_tokens\": 2048, \"top_p\": 1,\
        \"frequency_penalty\": 1, \"presence_penalty\": 0}", 
        prompt
    );
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      fprintf(stderr, "Curl failed: %s\n", curl_easy_strerror(res));
    }
    /* remember to free the buffer */
    free(chunk.response);
    curl_easy_cleanup(curl);
    free(data);
  }
  free(api_key_to_send);
  curl_global_cleanup();
  return chunk.response;
}
