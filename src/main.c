#include <json-c/json_object.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <json-c/json.h>
#include <dotenv.h>

#define MAX_INPUT_SIZE 200

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

void makeAPIrequest(char prompt[MAX_INPUT_SIZE * 5])
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
  char api_key[100];
  strcpy(
      api_key, 
      "Authorization: Bearer "
  );
  strcat(api_key, return_api_key());

  struct memory chunk = {0};

  curl_global_init(CURL_GLOBAL_DEFAULT);

  curl = curl_easy_init();
  if (curl) {
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, api_key);

    char *url = "https://api.openai.com/v1/completions";
    char *data = malloc(strlen(prompt) + 200);
    sprintf(data, "{\"model\": \"text-davinci-003\", \"prompt\": \"%s\", \"temperature\": 1.0, \"max_tokens\": 2048, \"top_p\": 1, \"frequency_penalty\": 1, \"presence_penalty\": 0}", prompt);

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cb);
    /* we pass our 'chunk' struct to the callback function */
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
      fprintf(stderr, "Curl failed: %s\n", curl_easy_strerror(res));

    /* remember to free the buffer */
    free(chunk.response);
    curl_easy_cleanup(curl);
    free(data);
  }

  //printf("This is the response: %s", chunk.response);
  curl_global_cleanup();
  return chunk.response;
}


int main()
{
  char project_title[100];
  char project_dependencies[MAX_INPUT_SIZE];
  char project_intentions[MAX_INPUT_SIZE];
  char project_requirements[MAX_INPUT_SIZE];
  char usage_examples[MAX_INPUT_SIZE];
  char license_and_copyright_information[MAX_INPUT_SIZE];
  char final_output[MAX_INPUT_SIZE * 5];

  printf("\nTell me a little bit about this project intentions: \n");
  fgets(project_intentions, sizeof(project_intentions), stdin);

  printf("Project title: \n");
  fgets(project_title, sizeof(project_title), stdin);

  printf("About the project dependencies: \n");
  fgets(project_dependencies, sizeof(project_dependencies), stdin);

  printf("Project requirements: \n");
  fgets(project_requirements, sizeof(project_requirements), stdin);

  printf("List some usage examples: \n");
  fgets(usage_examples, sizeof(usage_examples), stdin);

  printf("License and copyright information: \n");
  fgets(
      license_and_copyright_information,
      sizeof(license_and_copyright_information),
      stdin
  );

  strcpy(
      final_output, 
      "Write me an github readme.md file with the following information: "
  );
  strcat(final_output, "\nproject title: ");
  strcat(final_output, project_title);
  strcat(final_output, "project dependencies: ");
  strcat(final_output, project_dependencies);
  strcat(final_output, "project requirements: ");
  strcat(final_output, project_requirements);
  strcat(final_output, "usage examples: ");
  strcat(final_output, usage_examples);
  strcat(final_output, "project license and copyright: ");
  strcat(final_output, license_and_copyright_information);

  printf("\n%s", final_output);

  return 0;
}
