#include <pm.h>


void fill_makefile(const char* project_path, const char* project_name){
    chdir(project_path);
    char* makefile_path = "Makefile";
    char* makefile_content1 = "CXX = gcc\nCFLAGS = -Wall -Werror -Wextra -fpic -pedantic -g\nLIBSDIR = -L. -L/usr/lib\nINCLUDEDIR = -I. -I/usr/include\n\nLIBCORENAME = ";
    char* makefile_content2 = "\n\nifeq ($(OS), Windows_NT)\n\tEXPORT = export.bat\n\tLIBTARGET :=$(LIBCORENAME:=.dll)\n\tCLEANCMD = @del /q *.o *.dll *.exe *.so main.txt\nelse\n\tEXPORT = sh export.sh\n\tLIBTARGET :=lib$(LIBCORENAME:=.so)\n\tCLEANCMD = rm -rf *.o *.so *.exe *.dll \nendif\n\nLIBSOURCE = ";
    char* makefile_content3 = "\nLIBSOURCECFILE = $(LIBSOURCE:=.c)\nLIBSOURCEOFILE = $(LIBSOURCE:=.o)\n\nEXESOURCE = main\nTARGET = $(EXESOURCE:=.exe)\nEXESOURCECFILE = $(EXESOURCE:=.c)\nEXESOURCEOFILE = $(EXESOURCE:=.o)\n\nall: $(TARGET)\n\nrun: $(TARGET)\n\t$(EXPORT) $(TARGET)\n\n$(TARGET): $(EXESOURCEOFILE) $(LIBTARGET) \n\t$(CXX) $(EXESOURCEOFILE) -l$(LIBCORENAME) $(LIBSDIR) -o $(TARGET) -lm\n\n$(LIBTARGET): $(LIBSOURCEOFILE) \n\t$(CXX) $(CFLAGS) -shared $(LIBSOURCEOFILE) -o $(LIBTARGET)\n\n.c.o:\n\t$(CXX) $(CFLAGS) $(INCLUDEDIR) -c -o $@ $<\n\nclean: \n\t$(CLEANCMD)\n\t@echo CLEAN";
    
    FILE* makefile = fopen(makefile_path, "w"); 
    fputs(makefile_content1, makefile);
    fputs(project_name, makefile);
    fputs(makefile_content2, makefile);
    fputs(project_name, makefile);
    fputs(makefile_content3, makefile);
    fclose(makefile);

    FILE* export_sh = fopen("export.sh", "w");
    fputs("#!/bin/sh\nexport LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.\n./${1}", export_sh);
    fclose(export_sh);

    FILE* export_bat = fopen("export.bat", "w");
    fputs("@SET PATH=%PATH%;.\n%1", export_bat);
    fclose(export_bat);

}

void fill_main_c(const char* project_path, const char* project_name) {
    chdir(project_path);
    char* main_c_path = "main.c";
    char* main_c_content1 = "#include <";
    char* main_c_content2 = ".h>\n\nint main(int argc, char *argv[]) {\n\t/*INSERT CODE HERE*/\n\treturn EXIT_SUCCESS;\n}\n";
    FILE* file = fopen(main_c_path, "w");

    fputs(main_c_content1, file);
    fputs(project_name, file);
    fputs(main_c_content2, file);
    fclose(file);
}

char* to_upper(char* str, int size) {
    char* newstr = malloc(sizeof(char) * size);
    for (int i = 0; i < size; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            newstr[i] = str[i] + 'A' - 'a';
        } else {
            newstr[i] = str[i];
        }
    }
    return newstr;
}


void fill_lib(const char* project_path, char* libname) {
    chdir(project_path);
    int liblen = strlen(libname);
    char* lib_h_path = (char*) malloc(liblen + 2);
    sprintf(lib_h_path, "%s.h", libname);

    char* lib_c_path = (char*) malloc(liblen + 2);
    sprintf(lib_c_path, "%s.c", libname);

    char* lib_h_content1 = "#ifndef __";
    char* lib_h_content2 = "_H__\n#define __";
    char* lib_h_content3 = "_H__\n\n#include <stdio.h>\n#include <stdlib.h>\n\n#endif\n";

    FILE* file_h = fopen(lib_h_path, "w");
    fputs(lib_h_content1, file_h);
    char* libname_upper = to_upper(libname, liblen);
    fputs(libname_upper, file_h);
    fputs(lib_h_content2, file_h);
    fputs(libname_upper, file_h);
    fputs(lib_h_content3, file_h);

    fclose(file_h);

    FILE* file_c = fopen(lib_c_path, "w");
    fputs("#include <", file_c);
    fputs(libname, file_c);
    fputs(".h>\n\n", file_c);

    free(libname_upper);
    free(lib_h_path);
    free(lib_c_path);
}
