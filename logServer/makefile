#############################################
# 
#############################################
LocalPath=$(shell pwd)
IncludePath=-I$(LocalPath)/../libserver
IncludePath+=-I$(LocalPath)/../support/libtolua
IncludePath+=-I$(LocalPath)/../support/libluajit/src
IncludePath+=-I$(LocalPath)/../support/libmysql
IncludePath+=-I$(LocalPath)/../../boost_1_63_0
LibraryPath=-L$(LocalPath)/../wk.unix/bin/release/lib
LibraryPath+=-L$(LocalPath)/../wk.unix/bin/release
LibraryPath+=-L$(LocalPath)/../../boost_1_63_0/stage/lib
LibraryPath+=-Wl,-rpath $(LocalPath)/../wk.unix/bin/release
Library=-lserver -lluajit -lmysqlclient -ltolua -lboost_system -lboost_thread

ProjectName=logServer

CppSources=$(wildcard *.cpp)
CppObjects=$(patsubst %.cpp, %.o, $(CppSources))


CFLAGS=-w
CC=g++ -m64 -arch x86_64 -std=c++11 -pagezero_size 10000 -image_base 100000000
COMPILE_INFO=compile release

all:$(CppObjects)
$(CppObjects): %.o: %.cpp
	@echo $(COMPILE_INFO) $<
	@$(CC) $(IncludePath) $(CFLAGS) -c $< -o $@

all:
	@$(CC) $(IncludePath) $(LibraryPath) $(Library) $(CppObjects) -o $(ProjectName)
	@echo compile $(ProjectName) finish


.PHONY: clean
clean:
	@rm -rf $(CppObjects)
	@rm -rf $(ProjectName)
