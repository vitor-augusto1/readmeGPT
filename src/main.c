#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define MAX_INPUT_SIZE 200


void makeAPIrequest(char prompt[MAX_INPUT_SIZE * 5])
{
  
}


int main()
{
  char project_title[100];
  char project_dependencies[MAX_INPUT_SIZE];
  char project_requirements[MAX_INPUT_SIZE];
  char usage_examples[MAX_INPUT_SIZE];
  char license_and_copyright_information[MAX_INPUT_SIZE];
  char final_output[MAX_INPUT_SIZE * 5];

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

  return 0;
}
