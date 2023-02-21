#include <json-c/json_object.h>
#include <json-c/json.h>
#include <json-c/json_tokener.h>
#include <string.h>
#include <unistd.h>
#include "includes/request.h"

int main()
{
  char project_title[100];
  char project_dependencies[MAX_INPUT_SIZE];
  char project_intentions[MAX_INPUT_SIZE];
  char project_requirements[MAX_INPUT_SIZE];
  char usage_examples[MAX_INPUT_SIZE];
  char user_guide[MAX_INPUT_SIZE];
  char license_and_copyright_information[MAX_INPUT_SIZE];
  char final_output[MAX_INPUT_SIZE * 150];

  printf("\nPlease, provide as much information as you can for a very detailed readme\n");
  printf("\nWhat is this project for ?  \n");
  fgets(project_intentions, sizeof(project_intentions), stdin);

  printf("Project title: \n");
  fgets(project_title, sizeof(project_title), stdin);

  printf("User guide (what the user have to do to run it): \n");
  fgets(user_guide, sizeof(user_guide), stdin);

  printf("About the project dependencies (What you've used to create this project): \n");
  fgets(project_dependencies, sizeof(project_dependencies), stdin);

  printf("Project requirements (what the user needs to run your project): \n");
  fgets(project_requirements, sizeof(project_requirements), stdin);

  printf("List some usage examples (what the user is gonna be able to do with your project): \n");
  fgets(usage_examples, sizeof(usage_examples), stdin);

  printf("License and copyright information: \n");
  fgets(
      license_and_copyright_information,
      sizeof(license_and_copyright_information),
      stdin
  );

  strcpy(
      final_output, 
      "Write me an detailed github readme.md file based on the following information and please feel free to add and custom the provided information: "
  );

  strcat(final_output, "project intentions-> ");
  strcat(final_output, project_intentions);
  strcat(final_output, "project title-> ");
  strcat(final_output, project_title);
  strcat(final_output, "project dependencies-> ");
  strcat(final_output, project_dependencies);
  strcat(final_output, "user guide-> ");
  strcat(final_output, user_guide);
  strcat(final_output, "project requirements-> ");
  strcat(final_output, project_requirements);
  strcat(final_output, "usage examples-> ");
  strcat(final_output, usage_examples);
  strcat(final_output, "project license and copyright-> ");
  strcat(final_output, license_and_copyright_information);

  remove_new_lines(final_output);

  // Parse the JSON response
  json_object *root = json_tokener_parse(makeAPIrequest(final_output));
  json_object *choices;
  if (json_object_object_get_ex(root, "choices", &choices)) {
    // Get the generated text from the first choice
    struct json_object *choice = json_object_array_get_idx(choices, 0);
    struct json_object *text;
    json_object_object_get_ex(choice, "text", &text);
    const char *generated_text = json_object_get_string(text);
    //printf("%s", generated_text);
    FILE *file_pointer;
    // string here
    file_pointer = fopen("readme.md", "w");
    if (file_pointer == NULL) {
      printf("Error writing the file!\n");
      return 1;
    }
    fprintf(file_pointer, "%s", generated_text);
    fclose(file_pointer);
  }

  return 0;
}
