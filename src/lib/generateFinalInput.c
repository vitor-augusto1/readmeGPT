#include "../includes/generateFinalInput.h"
#include "../includes/formatString.h"

#define MAX_INPUT_SIZE 200

void generate_user_final_input(char *final_output)
{
  char project_title[MAX_INPUT_SIZE];
  char project_dependencies[MAX_INPUT_SIZE];
  char project_intentions[MAX_INPUT_SIZE];
  char project_requirements[MAX_INPUT_SIZE];
  char usage_examples[MAX_INPUT_SIZE];
  char user_guide[MAX_INPUT_SIZE];
  char license_and_copyright_information[MAX_INPUT_SIZE];

  printf("Project title:\n");
  fgets(project_title, sizeof(project_title), stdin);
  printf("\nProject description (Your goal with this project and what do you used to create it):\n");
  fgets(project_intentions, sizeof(project_intentions), stdin);
  printf("Installation (How the user can install your project):\n");
  fgets(user_guide, sizeof(user_guide), stdin);
  printf("Project usage (step by step to run your project):\n");
  fgets(usage_examples, sizeof(usage_examples), stdin);
  printf("project dependencies:\n");
  fgets(project_dependencies, sizeof(project_dependencies), stdin);
  printf("Project requirements (tell the user what he needs to do in order to run your project without any error):\n");
  fgets(project_requirements, sizeof(project_requirements), stdin);
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
  strcat(final_output, "the project title: ");
  strcat(final_output, project_title);
  strcat(final_output, "project description/mygoals with this project: ");
  strcat(final_output, project_intentions);
  strcat(final_output, "this is how the user can install my project: ");
  strcat(final_output, user_guide);
  strcat(final_output, "this is how the user can use it: ");
  strcat(final_output, usage_examples);
  strcat(final_output, "the project dependencies: ");
  strcat(final_output, project_dependencies);
  strcat(final_output, "this is what the user needs to run without any errors: ");
  strcat(final_output, project_requirements);
  strcat(final_output, "project license and copyright: ");
  strcat(final_output, license_and_copyright_information);
  remove_new_lines(final_output);
}
