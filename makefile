CC	= gcc
CFLAGS	= -g -Wall -pthread
#LIBS	= -lEGL -lGLESv2 -Wall -lm -lX11

#Book examples related files
#BASEDIR	= opengles2_book_examples
#COMMONS	= $(COMMON)/esShader.o $(COMMON)/esShapes.o $(COMMON)/esTransform.o $(COMMON)/esUtil.o $(COMMON)/vn200_linux_async_easy.o $(COMMON)/vn200.o $(COMMON)/vncp_services.o $(COMMON)/vndevice.o
COMMONS	=  $(COMMON)/vn200.o $(COMMON)/vncp_services.o $(COMMON)/vndevice.o $(COMMON)/bluetooth_top.o

#project
PROJBASE	= ./
COMMON	= $(PROJBASE)/common
INCDIRS	= $(PROJBASE)/inc
MAIN	= $(PROJBASE)/main.o
BIN	= $(PROJBASE)/bin/project.out

#opengl test
SANDBOX	= opengl_sandbox/opengl_test
TEST_O	= $(SANDBOX)/opengl_test.o

#Cleanup
O2CLEAN	= $(COMMONS) $(MAIN) $(BIN)

default: project

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCDIRS) -c $< -o $@

project: $(MAIN) $(COMMONS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $(BIN)

opengl_test: $(TEST_O) $(COMMONS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(O2CLEAN)
