#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#include "pm.h"


void fill_makefile(char *project_path)
{
    chdir(project_path);
    char *makefile_path = "Makefile";
    char *makefile_content = "CFLAGS = -Wall -Wextra -Werror -std=c11 -pedantic\nCC = gcc\nTCWIN = x86_64-w64-mingw32-\n\nbuild:\n\t@$(CC) main.c $(CFLAGS) -o main\n\t@echo \"CC\tmain.c\"\n\t@echo \"EXE\tmain\"\n\nbuildwin:\n\t@$(TCWIN)$(CC) main.c $(CFLAGS) -o main.exe\n\t@echo \"CC\tmain.c\"\n\t@echo \"EXE\tmain.exe\"\n\nclean:\n\t@rm -f main main.exe\n\t@echo \"CLEAN\"\n";
    FILE *file = fopen(makefile_path, "w");
    fprintf(file, "%s", makefile_content);
    fclose(file);
}

void fill_main_c(char *project_path)
{
    chdir(project_path);
    char *main_c_path = "main.c";
    char *main_c_content = "#include <stdio.h>\n\nint main(int argc, char *argv[])\n{\n\t/*INSERT CODE HERE*/\n\treturn 0;\n}\n";
    FILE *file = fopen(main_c_path, "w");
    fprintf(file, "%s", main_c_content);
    fclose(file);
}

void fill_main_h(char *project_path)
{
    chdir(project_path);
    char *main_h_path = "main.h";
    char *main_h_content = "#ifndef __MAIN_H__\n#define __MAIN_H__\n\n#include <stdio.h>\n\nint main(int argc, char *argv[]);\n\n#endif\n";
    FILE *file = fopen(main_h_path, "w");
    fprintf(file, "%s", main_h_content);
    fclose(file);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <project_name>\n", argv[0]);
        return 1;
    }
    char *project_name = argv[1];
    printf("Creating project \"%s\"\n", project_name);
#ifdef _WIN32
    mkdir(project_name);
#else
    mkdir(project_name, 0777);
#endif
    chdir(project_name);
    printf("Creating Makefile for C\n");
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    fill_makefile(cwd);

    printf("Creating main.c && main.h\n");
    fill_main_c(cwd);
    fill_main_h(cwd);
    printf("Done !\nYou can start coding !\n");
    return 0;
}
