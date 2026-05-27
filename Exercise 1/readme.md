# Exercise 1 Solutions
*Author: Mikael*

1. *A class ``Date`` describes a date with year, month, and day. Your task is to implement the member functions, one of the constructors and a function to compute the number of days between two dates. The constructor that creates a ``Date`` object representing the current date is already implemented (read about the C functions for date and time handling in the man pages for localtime, if you're interested). You may ignore leap years in the ``next()`` function, if you wish.*

    ```sh
    make datetest  
    ./datetest   
    ```

    *The command ``make`` without an argument builds (compiles and links) all the programs in this exercise.*

    OK!

2. *The class ``Point`` describes a point in the plane. The program [pointtest.cc](pointtest.cc) allocates a point object in different ways. Study the program and make sure that you understand the different alternatives.*

    ``f()`` Allocates the point on the stack. As the comment says, this means it is destroyed when the local scope is complete.
    ``g()`` Allocates on the heap, but using a safe pointer. Just like ``f()``, this means it is destroyed when the local scope is complete.
    ``h()`` Allocates on the heap, but does NOT use a safe pointer, opting for a raw pointer instead. This means that the object is not removed unless manually deleted, giving us a memory leak.

3. *Study the program [sizetest.cc](sizetest.cc). Try to predict the output from the program, then run the program and check your prediction.*

    It prints three lines. First, it prints the size of the object p, which will the size of the point's allocated memory e.g. two doubles = 16. Then it prints the size of ``pp``, e.g. the size of the pointer, which will be the size of the memory address. Then it prints the size of ``*pp``, e.g. dereference ``pp``, so the size of the object, again 16.

    I received the printout:
    ```console
    sizeof(p)      = 16
    sizeof(pp)     = 8
    sizeof(*pp)    = 16
    ```

4. *A palindrome is a word that reads the same both forwards and backwards. Examples: anna, amanaplanacanalpanama. Write a function that takes a string as parameter and returns true if the word is a palindrome, false otherwise. Also write a program that reads words from the terminal and checks whether they are palindromes. Modify the makefile to build the program.*

    See my implementation in *[palindrome_run.cc](palindrome_run.cc)*, *[palindrome.cc](palindrome.cc)*, and *[palindrome.h](palindrome.h)* -- in addition to my changes to *[Makefile](Makefile)*.

5. *C++ has the One Definition Rule, that says that definitions must occur at most once (for most things). Classes are typically declared in header files, and then care must be to avoid multiple definitions when a header file is included more than once.*
 
    *Compile the program in [include_test.cc](include_test.cc) and make sure you understand the error message and why it occurs. Then, add include guards to [foo.h](foo.h) and [bar.h](bar.h) to fix the error.*

    ```console   
    gcc include_test.cc -o include_test
    In file included from include_test.cc:2:
    bar.h:6:7: error: redefinition of ‘class Bar’
        6 | class Bar{
        |       ^~~
    In file included from foo.h:1,
                    from include_test.cc:1:
    *bar.h:6:7: note: previous definition of ‘class Bar’
        6 | class Bar{
        |       ^~~
    ```

    Like the error says, Bar is being redefined. This is happening, because *[foo.h](foo.h)* includes *[bar.h](bar.h)*, whilst *[include_test.cc](include_test.cc)* includes both. *[bar.h](bar.h)* is included twice. We can fix this by adding header guards. It is enough to do so on *[bar.h](bar.h)*. See my changes in the related files.

    I compiled using:
    ```sh
    g++ include_test.cc -o include_test
    ```



6. *Modern C++ has two kinds of enumeration types. The old kind of enumeration is ``enum`` which is inherited from C. That has some problems illustrated by the program [enumtest.cc](enumtest.cc). Compile the program and make sure you understand the compiler errors. Also, note that enums contain integer values, and you can (perhaps by accident) assign a value that is not part of the enumeration to an enum variable.*

    *In modern C++ scoped enums, ``enum class``, has been introduced to address those problems. Change the program to use scoped enums to fix the errors.*

    ```console
    g++ enumtest.cc traffic_light.cc eyes.cc -o enumtest
    In file included from  enumtest.cc:2:
    traffic_light.h:1:34: error: ‘green’ conflicts with a previous declaration
        1 | enum traffic_light {red, yellow, green};
        |                                  ^~~~~
    In file included from enumtest.cc:1:
    eyes.h:1:25: note: previous declaration ‘eye_colour green’
        1 | enum eye_colour {brown, green, blue};
        |                         ^~~~~
    enumtest.cc: In function ‘int main()’:
    enumtest.cc:11:24: error: cannot convert ‘eye_colour’ to ‘traffic_light’ in initialization
    11 |     traffic_light tl2 {green};
        |                        ^~~~~
        |                        |
        |                        eye_colour
    ```

    *[eyes.h](eyes.h)* and *[traffic_light.h](traffic_light.h)* have a common enum value ``green``, which is causing the issue. To fix this, we change all enums to ``enum class`` and all usages of the enum values to ``<enum class name>::<enum value>``. See changes in *[enumtest.cc](enumtest.cc)*, *[traffic_light.h](traffic_light.h)*, *[traffic_light.cc](traffic_light.cc)*, *[eyes.h](eyes.h)*, and *[eyes.cc](eyes.cc)*.