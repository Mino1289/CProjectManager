#ifndef __PM_H__
#define __PM_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/stat.h>


void fill_makefile(const char* project_path, const char* project_name, char** libs, int size);

void fill_main_c(const char* project_path, const char* project_name);

char* to_upper(char* str, int size);

void fill_lib(const char* project_path, char* libname, bool first);

#endif