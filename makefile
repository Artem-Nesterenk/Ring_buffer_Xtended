CC := gcc
C++ := g++
WARNING = -Wall

LIB_DIR = ring_buffer
LIB_SOURCES := ${LIB_DIR}/ring_buff.c
LIB_HEADER := ${LIB_DIR}/ring_buff.h ${LIB_DIR}/ring_buff_conf.h

TEST_DIR = tests
TEST_SOURCES := ${TEST_DIR}/tests_main.cpp
TEST_HEADER := ${TEST_DIR}/tests_main.h
TEST_LIBS = -lgtest -lpthread

DOCS_DIR = documentation
BROWSER = firefox

test: ring_buff.o
	${C++}  ${WARNING} ${TEST_SOURCES}  ${LIB_DIR}/ring_buff.o -I/${LIB_HEADER} -o main ${TEST_LIBS} \
	&&./main \
	&& make clear
	
docs:	
	doxygen ${DOCS_DIR}/Doxyfile \
	&& ${BROWSER} ${DOCS_DIR}/html/globals.html
	
debug:
	${CC}  -g ${WARNING} ${TEST_SOURCES}  ${LIB_DIR}/ring_buff.c -I/${LIB_HEADER} -o main

ring_buff.o:  ${LIB_SOURCES} 
	${CC} -c ${WARNING} ${LIB_SOURCES} && mv $@ ${LIB_DIR}
	
clear:
	rm -rf ${LIB_DIR}/*.o \ 
	rm -rf main		