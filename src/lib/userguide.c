#include "../includes/userguide.h"

void show_user_guide()
{
  puts("readmeGPT - commandline readme.md file generator\n");
  puts("\tusage: ./readmegpt [-f <path>]\n");
  puts("\treadmeGPT is a tool for generating readme.md files using AI.");
  puts("\tFlags: \n\t\t-f\tPath to a file/directory.");
  puts("\t\t-h\tDisplays help with available flag, subcommand, and positional value parameters");
  exit(1);
}
