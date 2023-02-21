#include <json-c/json_object.h>
#include <json-c/json.h>
#include <json-c/json_tokener.h>
#include <string.h>
#include <unistd.h>
#include "includes/request.h"
#include "includes/formatString.h"
#include "includes/generateFinalInput.h"
#include "includes/parseJSON.h"

int main(int argc, char *argv[])
{
  char user_project_information[MAX_INPUT_SIZE * 200]; 
  generate_user_final_input(user_project_information);
  char *api_response = makeAPIrequest(user_project_information);
  const char *generated_text = extract_the_text_from_api_response_json(
    api_response
  );
  if (generated_text == NULL) {
    printf("Error generating the markdown, please try again.");
    return 1;
  }
  FILE *file_pointer;
  file_pointer = fopen("readme.md", "w");
  if (file_pointer == NULL) {
    printf("Error writing the file!\n");
    return 1;
  }
  fprintf(file_pointer, "%s", generated_text);
  fclose(file_pointer);
  return 0;
}
