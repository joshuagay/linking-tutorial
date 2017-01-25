# linking-tutorial
A short and simple tutorial on static and dynamic linking written in C


The purpose of all of these programs is to print the string "Hello, NAME". We get the value of NAME through a variety of different ways.


- **helloname.c** This is a simple program that prints Hello, NAME

- **hello-getname.** We declare and define a function that returns NAME

- **hello.c** We include the name library and call a function in that to get NAME

- **name.h** Header file declaring the getName() function

- **name.c** Source file that defines the getName() function

## TODO

Create Makefile to: 

* Copmile helloname.c -> helloname
* Compile hello-getname.c -> hellogetname
* Create satic library from name.o 
* Create dynamic library from name.o
* Compile hello.c without using library -> hello
* Compile hello.c static linking -> hello-static
* Compile hello.c dynamic linking -> hello-dynamic
** gcc -c -fPIC name.c -o name.o
** gcc -shared -Wl,-soname,libname.so.1 -o libname.so  name.o
** gcc hello.c -o hello-dynamic -L. -lname



Make sure to do 
export LD_LIBRARY_PATH = .


