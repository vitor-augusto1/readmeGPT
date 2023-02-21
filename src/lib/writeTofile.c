#include "../includes/writeTofile.h"

void write_to_a_file(const char *text_to_write, char file_name[])
{
  FILE *file_pointer;
  file_pointer = fopen(file_name, "w");
  if (file_pointer == NULL) {
    printf("Error writing the file!\n");
  }
  fprintf(file_pointer, "%s", text_to_write);
  fclose(file_pointer);
}
