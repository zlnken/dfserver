#############################################
# make core project to libserver.so
#############################################
LocalPath=$(shell pwd)
IncludePath=-I$(LocalPath)/../support/libtolua
IncludePath+=-I$(LocalPath)/../support/libluajit/src
IncludePath+=-I$(LocalPath)/../support/libmysql
IncludePath+=-I$(LocalPath)/../../boost_1_63_0

LibraryPath=-L$(LocalPath)/../wk.unix/bin/release/lib
LibraryPath+=-L$(LocalPath)/../../boost_1_63_0/stage/lib


Library=-lluajit -lmysqlclient -ltolua -lboost_system -lboost_thread
ProjectName=libserver.so

CppSources=$(wildcard *.cpp)
CppObjects=$(patsubst %.cpp, %.o, $(CppSources))

CSources=$(wildcard *.c)
CObjects=$(patsubst %.c, %.o, $(CSources))
Objects=$(CObjects)
Objects+=$(CppObjects)

CFLAGS=-w
CC=g++ -m64 -arch x86_64 -std=c++11

COMPILE_INFO=compile release

all:$(CObjects)
$(CObjects): %.o: %.c
	@echo $(COMPILE_INFO) $<
	@gcc -m64 -arch x86_64 $(IncludePath) $(CFLAGS) -c $< -o $@

all:$(CppObjects)
$(CppObjects): %.o: %.cpp
	@echo $(COMPILE_INFO) $<
	@$(CC) $(IncludePath) $(CFLAGS) -c $< -o $@

all:
	@$(CC) $(IncludePath) $(LibraryPath) $(Library) -shared -o $(ProjectName) $(Objects)
	@echo compile $(ProjectName) finish


.PHONY: clean
clean:
	@rm -rf $(Objects)
	@rm -rf $(ProjectName)