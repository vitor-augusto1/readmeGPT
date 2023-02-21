#include "../includes/request.h"

void remove_new_lines(char *string_pointer)
{
  for (int i = 0; i < strlen(string_pointer); i++){
    if (string_pointer[i] == '\n')
      string_pointer[i] = ' ';
  }
}
