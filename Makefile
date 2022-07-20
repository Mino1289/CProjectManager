CXX = gcc
CFLAGS = -Wall -Werror -Wextra -fpic -pedantic 
LIBSDIR = -L.
INCLUDEDIR = -I.

LIBCORENAME = pm

ifeq ($(OS), Windows_NT)
	EXPORT = export.bat
	LIBTARGET :=$(LIBCORENAME:=.dll)
	CLEANCMD = @del /q *.o *.dll *.exe *.so
else
	EXPORT = sh export.sh
	LIBTARGET :=lib$(LIBCORENAME:=.so)
	LIBSDIR += -L/usr/lib
	INCLUDEDIR += -I/usr/include
	CLEANCMD = rm -rf *.o *.so *.exe *.dll
endif

LIBSOURCE = pm
LIBSOURCECFILE = $(LIBSOURCE:=.c)
LIBSOURCEOFILE = $(LIBSOURCE:=.o)

EXESOURCE = main
TARGET = $(EXESOURCE:=.exe)
EXESOURCECFILE = $(EXESOURCE:=.c)
EXESOURCEOFILE = $(EXESOURCE:=.o)

all: $(TARGET)

run: $(TARGET)
	$(EXPORT) $(TARGET)

$(TARGET): $(EXESOURCEOFILE) $(LIBTARGET) 
	$(CXX) $(EXESOURCEOFILE) -l$(LIBCORENAME) $(LIBSDIR) -o $(TARGET) -lm

$(LIBTARGET): $(LIBSOURCEOFILE) 
	$(CXX) $(CFLAGS) -shared $(LIBSOURCEOFILE) -o $(LIBTARGET)

.c.o:
	$(CXX) $(CFLAGS) $(INCLUDEDIR) -c -o $@ $<

clean: 
	$(CLEANCMD)
	@echo CLEAN