#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include "builtin.h"
#include <string.h>
#include <dirent.h> 

#define GREEN  "\x1B[32m"
#define BLUE  "\x1B[34m"

//Prototypes
static void exitProgram(char** args, int argcp);
static void cd(char** args, int argpcp);
static void pwd(char** args, int argcp);


/* builtIn
 ** built in checks each built in command the given command, if the given command
 * matches one of the built in commands, that command is called and builtin returns 1.
 *If none of the built in commands match the wanted command, builtin returns 0;
  */
int builtIn(char** args, int argcp)
{
      if (strcmp(args[0], "pwd") == 0){
    pwd(args, argcp);
    return 1;
  } else if (strcmp(args[0], "exit") == 0){
    exitProgram(args, argcp);
    return 1;
  } else if (strcmp(args[0], "cd") == 0){
    cd(args, argcp);
    return 1;
  } /*else if (strcmp(args[0], "wc") == 0){
    ??(args, argcp);
  }*/
  printf("Use the following commands:\n pwd - print current directory\n");
  printf("exit [value] - exit the shell with the value\n cd - change the current directory");
  printf("?? - don't know yet")
  return 0;


static void exitProgram(char** args, int argcp)
{   
    if (argcp == 1) {
      exit(0);
    }
    exit(atoi(args[1]));
}

static void pwd(char** args, int argpcp)
{
  char * cwd = get_current_dir_name();
  printf("you are currently in: %s", cwd);
  free(cwd);
}


static void cd(char** args, int argcp)
{
  char s[512];
  printf("%s\n", getcwd(s, 512));
  if (chdir(args[1]) == -1){
    printf("directory does not exist")
  }
  printf("%s\n", getcwd(s, 512));
}
static void show_dir_content(char** args, int argpcp)
{
  DIR * directory = opendir(pwd(char** args, int argpcp));
  if(directory == NULL) return;
  struct dirent * dir;
  while ((dir = readdir(directory)) != NULL)
    {
      if(dir-> d_type != DT_DIR)
        printf("%s%s\n",BLUE, dir->d_name);
      else
      if(dir -> d_type == DT_DIR && strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0 )
      {
        printf("%s%s\n",GREEN, dir->d_name);
        char dirpath[255];
        sprintf(dirpath, "%s/%s", path, dir->d_name);
        show_dir_content(dirpath);
      }
    }
    closedir(directory);
}
