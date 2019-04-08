#############################################
# make core project to libserver.so
#############################################
LocalPath=$(shell pwd)
IncludePath=-I$(LocalPath)/../libluajit/src
LibraryPath=-L$(LocalPath)/../../wk.unix/bin/release/lib
ProjectName=libtolua.a

CSources=$(wildcard *.c)
Objects=$(patsubst %.c, %.o, $(CSources))

CC= gcc -m64 -arch x86_64 -std=gnu99
CFLAGS=-Wall
COMPILE_INFO=compile release

all:$(Objects)
$(Objects): %.o: %.c
	@echo $(COMPILE_INFO) $<
	@$(CC) $(CFLAGS) $(IncludePath) -c $< -o $@

all:
	ar cr $(ProjectName) $(Objects)

.PHONY: clean
clean:
	@rm -rf $(Objects)
	@rm -rf $(ProjectName)