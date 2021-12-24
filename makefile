CC := gcc
WARNING = -Wall

LIB_DIR = ring_buffer
LIB_SOURCES := ${LIB_DIR}/ring_buff.c
LIB_HEADER := ${LIB_DIR}/ring_buff.h ${LIB_DIR}/ring_buff_conf.h

TEST_DIR = tests
TEST_SOURCES := ${TEST_DIR}/main.c
TEST_HEADER := ${TEST_DIR}/main.h

test: ring_buff.o
	${CC}  ${WARNING} ${TEST_SOURCES}  ${LIB_DIR}/ring_buff.o -I/${LIB_HEADER} -o main &&./main \
	&& make clear
	
docs:	

debug:
	${CC}  -g ${WARNING} ${TEST_SOURCES}  ${LIB_DIR}/ring_buff.c -I/${LIB_HEADER} -o main

ring_buff.o:  ${LIB_SOURCES} 
	${CC} -c ${WARNING} ${LIB_SOURCES} && mv $@ ${LIB_DIR}
	
clear:
	rm -rf ${LIB_DIR}/*.o \ 
	rm -rf main		