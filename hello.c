#include<stdio.h>
#include"./name.h"

int main(){

  char* name="";

  name = getName();

  printf("Hello, %s \n", name); // prints "Hello, <name>" followed by newline (\n)

  return 0;
}
