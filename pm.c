#include <pm.h>


void fill_ext(const char* project_path, const char* project_name, char** libs, int size){
    // makefile
    chdir(project_path);
    char* makefile_path = "Makefile";
    char* makefile_content1 = "CXX = gcc\nCFLAGS = -Wall -Werror -fpic -pedantic\nLIBSDIR = -L.\nINCLUDEDIR = -I.\n\nLIBCORENAME = ";
    char* makefile_content2 = "\n\nDEBUG ?= 0\nifeq ($(DEBUG), 1)\n\tCFLAGS += -ggdb -DDEBUG\nendif\n\nifeq ($(OS), Windows_NT)\n\tEXPORT = export.bat\n\tLIBTARGET :=$(LIBCORENAME:=.dll)\n\tCLEANCMD = @del /q *.o *.dll *.exe *.so main.txt\nelse\n\tEXPORT = sh export.sh\n\tLIBTARGET :=lib$(LIBCORENAME:=.so)\n\tLIBSDIR += -L/usr/lib\n\tINCLUDEDIR += -I/usr/include\n\tCLEANCMD = rm -rf *.o *.so *.exe *.dll \nendif\n\nLIBSOURCE = ";
    char* makefile_content3 = "\nLIBSOURCECFILE = $(LIBSOURCE:=.c)\nLIBSOURCEOFILE = $(LIBSOURCE:=.o)\n\nEXESOURCE = main\nTARGET = $(EXESOURCE:=.exe)\nEXESOURCECFILE = $(EXESOURCE:=.c)\nEXESOURCEOFILE = $(EXESOURCE:=.o)\n\nall: $(TARGET)\n\nrun: $(TARGET)\n\t$(EXPORT) $(TARGET)\n\n$(TARGET): $(EXESOURCEOFILE) $(LIBTARGET) \n\t$(CXX) $(EXESOURCEOFILE) -l$(LIBCORENAME) $(LIBSDIR) -o $(TARGET) -lm\n\n$(LIBTARGET): $(LIBSOURCEOFILE) \n\t$(CXX) $(CFLAGS) -shared $(LIBSOURCEOFILE) -o $(LIBTARGET)\n\n.c.o:\n\t$(CXX) $(CFLAGS) $(INCLUDEDIR) -c -o $@ $<\n\nclean: \n\t$(CLEANCMD)\n\t@echo CLEAN";
    
    FILE* makefile = fopen(makefile_path, "wt"); 
    fputs(makefile_content1, makefile);
    fputs(project_name, makefile);
    fputs(makefile_content2, makefile);
    for (int i = 0; i < size; i++) {
        fputs(libs[i], makefile);
        fputs(" ", makefile);
    }
    fputs(makefile_content3, makefile);
    fclose(makefile);

    // export
    FILE* export_sh = fopen("export.sh", "wt");
    fputs("#!/bin/sh\nexport LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.\n./${1}", export_sh);
    fclose(export_sh);

    FILE* export_bat = fopen("export.bat", "wt");
    fputs("@SET PATH=%PATH%;.\n%1", export_bat);
    fclose(export_bat);

    // gitignore
    FILE* gitignore = fopen(".gitignore", "wt");
    fputs("*.o\n*.exe\n*.dll\n*.so", gitignore);
    fclose(gitignore);

    // readme
    FILE* readme = fopen("README.md", "wt");
    fputs("# ", readme);
    fputs(project_name, readme);
    fputs("\n\n## Description\n\n## Compiling\n```sh\nmake run -j4\n```\n\n## Usage\n\n## License", readme);
    fclose(readme);
}

void fill_main_c(const char* project_path, const char* project_name) {
    chdir(project_path);
    char* main_c_path = "main.c";
    char* main_c_content1 = "#include <";
    char* main_c_content2 = ".h>\n\nint main(int argc, char *argv[]) {\n\t/*INSERT CODE HERE*/\n\treturn EXIT_SUCCESS;\n}\n";
    FILE* file = fopen(main_c_path, "wt");

    fputs(main_c_content1, file);
    fputs(project_name, file);
    fputs(main_c_content2, file);
    fclose(file);
}

char* to_upper(char* str, int size) {
    char* newstr = malloc(sizeof(char) * (size + 1));
    for (int i = 0; i < size; i++) {
        newstr[i] = toupper(str[i]);
    }
    newstr[size] = '\0';
    return newstr;
}


void fill_lib(const char* project_path, char* libname, bool first) {
    chdir(project_path);
    int liblen = strlen(libname);
    char* lib_h_path = (char*) malloc(liblen + 2);
    sprintf(lib_h_path, "%s.h", libname);

    char* lib_c_path = (char*) malloc(liblen + 2);
    sprintf(lib_c_path, "%s.c", libname);

    char* lib_h_content1 = "#ifndef __";
    char* lib_h_content2 = "_H__\n#define __";
    char* lib_h_content3 = "_H__\n\n#include <stdio.h>\n#include <stdlib.h>\n\n";
    char* lib_h_prepro = "#define ll long long\n#define ld long double\n#define ull unsigned long long\n#define uld unsigned long double\n\n#define ABS(a)      ((a) < 0 ? -(a) : (a))\n#define MAX(a, b)   ((a + b + ABS(a-b)) / 2)\n#define MIN(a, b)   ((a) < (b) ? (a) : (b))\n#define SWAP(a, b, T)  {T tmp = a; a = b; b = tmp;}\n#define SWAPI(arr, i, j, T) {SWAP(arr[i], arr[j], T);}\n\n\n#define F_OR(i, a, b, s)            for (int i = (a); (s) > 0 ? i < (b) : i > (b); i += (s))\n#define F_OR1(e)                    F_OR(i, 0, e, 1)\n#define F_OR2(i, e)                 F_OR(i, 0, e, 1)\n#define F_OR3(i, b, e)              F_OR(i, b, e, 1)\n#define F_OR4(i, b, e, s)           F_OR(i, b, e, s)\n#define GET5(a, b, c, d, e, ...)    e\n#define F_ORC(...)                  GET5(__VA_ARGS__, F_OR4, F_OR3, F_OR2, F_OR1)\n/**\n * @brief max 4 arguments\n * First : the name of the variable the i in 'for (int i = 0; i < n; i++)' (if ommited 'i') (the last to be ommited)\n * Second : the start of the loop   (if ommited 0)      (the second to be ommited)\n * Third : the end of the loop      (can't be ommited)   \n * Fourth : the step of the loop    (if ommited 1)      (the first to be ommited)\n */\n#define FOR(...) F_ORC(__VA_ARGS__)(__VA_ARGS__)\n\n#ifdef DEBUG\n#define DEBUGPRINT(_msg, ...) fprintf(stderr, \".\\\\%s:%d \" _msg, __FILE__, __LINE__, ##__VA_ARGS__);\n#else\n#define DEBUGPRINT(_msg, ...) // do nothing\n#endif\n\n";
    char* lib_h_endif = "\n\n#endif\n";

    FILE* file_h = fopen(lib_h_path, "wt");
    fputs(lib_h_content1, file_h);
    char* libname_upper = to_upper(libname, liblen);
    fputs(libname_upper, file_h);
    fputs(lib_h_content2, file_h);
    fputs(libname_upper, file_h);
    fputs(lib_h_content3, file_h);
    if (first) {
        fputs(lib_h_prepro, file_h);
    }
    fputs(lib_h_endif, file_h);

    fclose(file_h);

    FILE* file_c = fopen(lib_c_path, "wt");
    fputs("#include <", file_c);
    fputs(libname, file_c);
    fputs(".h>\n\n", file_c);

    fclose(file_c);

    free(libname_upper);
    free(lib_h_path);
    free(lib_c_path);
}

void makefile_only(const char* makefile_path) {
    if (!access("Makefile", F_OK)) {
        printf("Makefile already exists\n");
        printf("Do you want to overwrite it ? (y/n) ");
        char c = getchar();
        if (c != 'y') {
            return;
        }
    }
    chdir(makefile_path);
    FILE* makefile = fopen("Makefile", "wt");
    char* makefile_content = "CC=gcc\nCFLAGS=-Wall -Wextra -Werror -pedantic -lm\n\nifeq ($(DEBUG), 1)\n\tCFLAGS += -ggdb -DDEBUG\nendif\n\nifeq ($(OS), Windows_NT)\n\tCLEANCMD = @del /q *.exe\nelse\n\tCLEANCMD = rm -rf *.exe\nendif\n\n.c:.exe\n\t$(CC) $< $(CFLAGS) -o $@.exe\n\nclean:\n\t$(CLEANCMD)\n";
    fputs(makefile_content, makefile);

    fclose(makefile);
}
