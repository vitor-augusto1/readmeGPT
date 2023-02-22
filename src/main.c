#include <json-c/json_object.h>
#include <json-c/json.h>
#include <json-c/json_tokener.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "includes/request.h"
#include "includes/formatString.h"
#include "includes/generateFinalInput.h"
#include "includes/parseJSON.h"
#include "includes/writeTofile.h"
#include "includes/userguide.h"

int main(int argc, char *argv[])
{
  char ch;
  char file_name[100] = "readme.md";
  while ((ch = getopt(argc, argv, "f:")) != EOF) {
    switch (ch) {
      case 'f':
        strcpy(file_name, optarg);
        remove_duplicate_slash(file_name);
        strcat(file_name, "readme.md");
        break;
      case '?':
        show_user_guide();
        break;
      default:
        fprintf(
          stderr,
          "Unknown option: '%s'\nWriting it in the current directory.\n",
          optarg
        );
    }
  }
  argc -= optind;
  argv += optind;
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
  write_to_a_file(generated_text, file_name);
  return 0;
}
