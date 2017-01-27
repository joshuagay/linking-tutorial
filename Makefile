CC = gcc # C compiler
CFLAGS = -fPIC # C flags
LDFLAGS = -shared  # linking flags
RM = rm -f  # rm command

all: 	
	gcc helloname.c -o helloname
	gcc hello-getname.c -o hello_getname
	gcc hello.c name.h name.c -o hello
	gcc -c -fPIC name.c -o name.o
	gcc -shared -Wl,-soname,libname.so -o libname.so  name.o
	gcc hello.c -o hello-dynamic -L. -lname

clean:

## Don't forget to run 	export LD_LIBRARY_PATH=.
