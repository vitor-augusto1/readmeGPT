#include "../includes/formatString.h"

void remove_new_lines(char *string_pointer)
{
  for (int i = 0; i < strlen(string_pointer); i++){
    if (string_pointer[i] == '\n' || string_pointer[i] == '\\')
      string_pointer[i] = ' ';
  }
}

void remove_duplicate_slash(char *string_pointer)
{
  for (int i = 0; i < strlen(string_pointer); i++){
    if (string_pointer[i] == '/' && string_pointer[i+1] == '/')
      string_pointer[i+1] = '\0';
  }
}
