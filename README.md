# linking-tutorial

A short and simple tutorial on static and dynamic linking written in C.

This tutorial makes use of the following source files: 

- **helloname.c** This is a simple program that prints Hello, NAME

- **hello-getname.c** We declare and define a function that returns NAME

- **hello.c** We include the name library and call a function in that to get NAME

- **name.h** Header file declaring the getName() function

- **name.c** Source file that defines the getName() function

*NAME* indicates the value of a variable. 


## Quick overview of linking, the C language, and compilers

The C programming language is a "compiled" language, meaning that you
write source code in a human readable language and then you "compile"
that source code and end-up with an "executable" file which is written
in a language that is able to communicate with whatever computer it is
run on. 

The C language is "portable" in teh sense that you don't really need
to know what kind of computer you are going to run it on. If you write
a program to run on Mac OS X or Windows, the C source code will look
the same, but the executable file for Windows is going to be different
than the one for Mac OS X. similarly, the executable file which was
compiled for a 64 bit processor is going to be different than the
executable file which was compiled for a 32 bit processor.

When we say "compile" a program written in the C language, what
actually happens can be understood as a four step process. However, since a program is usually written a series of 



**Step 1: preprocessor**

 * The preprocessor takes in files, which are written in a mix of C
   source code and C macro code and it outputs a file containing only
   source code

**Step 2: compiler**

 * The compiler takes in a source code file and converts it into what
   we call assembler code. Many different languages can all compile to
   the same assembler language, but assembler language itself is not
   written to work on any one particular physical computer
   architecture or operating system.

**Step 3: assembler**

* The assembler takes in a file containing assembler code and it
  outputs an object file. The object file contains instructions that
  are specific to a particular operating system and hardware
  architecture and they usually include references to other object
  files.

(Steps 1 through 3 are usually repeated for each individual source file in the program)

**Step 4: linker**

* The linker takes in one or more object files and outputs an
  executable file. Different object files refer to each other with
  *symbols*; some of the *symbols* refer to objects passed to the
  linker, while other symbols refer to objects that are not passed to
  the linker direclty but which are expected to exist elsewhere on the
  computer where the executable file will be run.


## Reading the code 

### Part 1: helloname.c

    #include<stdio.h>

    int main(){

      char* name="Joshua";

      printf("Hello, %s \n", name); 

      return 0;

    }


In the C programming language, the "entry point" of the program is the
function main(), that is to say, when our program is run, the code
inside of main() is what will be executed first.  

Looking over main(), we see that it essentailly does two things. 

1) In the first line, we *declare* a new variable, `name` and we
*assign* it the string "Joshua". 

2) In the next line we call the function printf() passing it the value
of `name` along with a string. 

While there are various aspects of the C programming language which
may not yet make sense if you do not know the language, the important
takeaways from this very simple program are that we are able to
*declare* new variables and *assign* values to those variables; and
that we can pass the values of variables as arguments to functions and
the function can then use those arguments (in magical and not so magical
ways).

**Compile and execution instructions**

gcc helloname.c -o helloname

./helloname



### Part 2: hello-getname.c

     #include<stdio.h>

     char* getName();


     int main(){

       char* name="";

       name = getName();

       printf("Hello, %s \n", name); // prints "Hello, <name>" followed by newline (\n)

       return 0;
     }


     char* getName(){
       char* aname="Joshua";
       return aname;
     }


In our second example we show that in addition to being able to
declare new variables, you can also *declare* functions. We declare a
function called getName() before the start of the main() function. The
reason why it must be declared before the main() function is because
we intend on calling this function inside of main(). You can see that
after the main() function we define the getName() function. The way C
works is when you compile it, it reads files from top to bottom and
any functions or variables you wish to make use of must be declared
before you *call* them. We can define how a function actually works
separately and later on in the program.

When a function executes it *returns* a value. So inside of main()
when we get to the line `name = getName();`, what is happening is the
function getName() is run and it returns a value and that value is
then assigned to the variable `name`. After this we then pass `name`
to the printf() function just as we did in our first example.

Lower down when we look at our getName() *definition*, you can see
that we declare the variable `aname` and assign it a string. When we
return `aname`, what we are actulaly doing is returning the current
value of the variable, which in this case is the string "Joshua".


gcc hello-getname.c -o hello_getname

./hello_getname 


## Part 3: name.h, name.c, hello.c

     #include<stdio.h>
     #include"name.h"

     int main(){

       char* name="";

       name = getName();

       printf("Hello, %s \n", name);

       return 0;
     }


In part 2 we showed how you can declare functions and put the
definition of that function elsewhere and how you can call the
function. When you are creating a large program, it is sometimes
useful to separate things into various different files. This not only
allows you to organize your code in a logical fashion, it also allows
you to reuse the code more easily throughout different parts of your
program. In this example we show how you can put the declarations of
functions into its own file which we call a *header* file and how we
can put the definitions of thse functions into yet another source
file. A common convention in C programming is to put definitions of
functions are inside of "source" files ending in ".c" and declarations
of inside of "header" files which end in ".h".

In our previous examples we didn't explain the first lines of program
`#include<stdio.h>`. This is an include directive, which is a kind of
C macro instruction. When the assembler sees an include directive it
is funcitonally equivalent to copying all of the contents of the
specified file and pasting in place of wherever the `#include`
statement is made. The file stdio.h is very complicated, but inside it
you will find that it includes a declaration for the function
printf(). Similarily, if you look inside the file name.h, you will see
it contains the following:

     char* getName();

As such, running the preprocessor ont he staement `#include"name.h"`
would result in replacing that line with the line `char* getName();`,
which should look familiar from example 2 above. Likewise the
definition of getName() found in the file name.c is the same
definition of the function as we find at the bottom of example 2.

So the result of the preprocessor/compilation/assembler process are
two object files, one containing hello.c and one containing
name.c. These two object files are then used to produce a single
executable file.


**Compiling and running example 3**

gcc hello.c name.h name.c -o hello

./hello


## Part 4: Dynamically linked library

In this example instead of compiling name.c and hello.c together in
one step, we are going to compile name.c as a "library." Libraries
haev the extension ".so" which stands for "shared object." As the name
implies, this object is designed to be used by other objects.

In this exmaple we are going to use our compiler program to do our
first three steps discussed -- preprocessor, compiler, and assembler
-- but not the third step, linker. This will give us a standalone
object file:

    gcc -c -fPIC name.c -o name.o


Next we take that object file and we call our linker program asking to
generate a 'shared object' file isntead of an executable file. It is
basically just another kind of object file, but with symbolic
references done in a way that executables can "link" to it so that the
operatin system "loads" it during runtime.

    gcc -shared -Wl,-soname,libname.so -o libname.so  name.o

We now have a shared object file, libname.so.

Now we go ahead and compile hello.c, and you we will instruct the
linker to link it to libname.so.

    gcc hello.c -o hello-dynamic -L. -lname

The result of this is an exeutable file called hello-dynamic

If we run hello-dynamic like this: 

    ./hello-dynamic

We get an error saying the libname.so library can't be found. This is because the operating system doesn't know where to find libname.so. We can fix this by letting the OS know where to find it. Using bash (a command line program) you can do that as follows: 

    export LD_LIBRARY_PATH=.

Now run it: 

    ./hello-dynamic

This time it should work. You can examine the shared object files that an executable file links to by using the program ldd. Try it out: 

    ldd hello-dyanmic

Lastly, you can go ahead and make changes to name.c and then repeat the two steps for producing the .so file like this:

    gcc -c -fPIC name.c -o name.o
    gcc -shared -Wl,-soname,libname.so -o libname.so  name.o	

Now if you run hello-dynamic again, this time you will see that the
name that is printed out has changed despite the fact that the
executable file, hello-dynamic, has not changed. This is why we call
these libraries "dynamically loaded" -- because it is only when the
program is executed that we actually load the shared object and run
it.


## Final takeaway

We have shown that you can write all of a program within a single
file, multiple files, or to put some of the code in a library and
other parts in an executable. 

 
