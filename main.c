#include <pm.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <project_name>\n", argv[0]);
        return 1;
    }
    char* project_name = (char*) malloc(strlen(argv[1]) + 1);
    memcpy(project_name, argv[1], strlen(argv[1]) + 1);
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
    fill_makefile(cwd, project_name);

    printf("Creating main.c\n");
    fill_main_c(cwd, project_name);

    printf("Creating %s.c && %s.h\n", project_name, project_name);
    fill_lib(cwd, project_name);
    printf("Done !\nYou can start coding !\n");
    return 0;
}