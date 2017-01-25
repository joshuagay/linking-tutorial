#include<stdio.h>

/* We declare a function */
char* getName();

/* This is where our program starts running */
int main(){

  char* name="";

  name = getName();

  printf("Hello, %s \n", name); // prints "Hello, <name>" followed by newline (\n)

  return 0;
}


/* We now define the function that we previously declared */
char* getName(){
  char* aname="Joshua";
  return aname;
}
