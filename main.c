#include <pm.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <project_name> <..libnames>\n", argv[0]);
        return 1;
    }
    char* project_name = (char*) malloc(sizeof(char) * (strlen(argv[1]) + 1));
    memcpy(project_name, argv[1], sizeof(char) * (strlen(argv[1]) + 1));
    printf("Creating project \"%s\"\n", project_name);
#ifdef _WIN32
    mkdir(project_name);
#else
    mkdir(project_name, 0777);
#endif
    chdir(project_name);
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));

    printf("Creating main.c\n");
    fill_main_c(cwd, project_name);

    char** libs = (char**) malloc(sizeof(char*));
    for (int i = 1; i < argc; i++) {
        libs[i-1] = (char*) malloc(sizeof(char) * strlen(argv[i]));
        strcpy(libs[i-1], argv[i]);

        printf("Creating %s.c && %s.h\n", libs[i-1], libs[i-1]);
        fill_lib(cwd, libs[i-1], i==1);
        libs = realloc(libs, sizeof(char*)*(i+1));
    }
    fill_ext(cwd, project_name, libs, argc-1);
    printf("Creating Makefile for C\n");
    
    for (int i = 1; i < argc-1; i++) {
        free(libs[i]);
    }
    free(libs);
    free(project_name);

    printf("Done !\nYou can start coding !\n");
    return EXIT_SUCCESS;
}