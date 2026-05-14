
# Exercise 1
*Author: Sven Robertz, used with permission (granted 2026-02-04)*

1. A class ``Date`` describes a date with year, month, and day. Your task is to implement the member functions, one of the constructors and a function to compute the number of days between two dates. The constructor that creates a ``Date`` object representing the current date is already implemented (read about the C functions for date and time handling in the man pages for localtime, if you're interested). You may ignore leap years in the ``next()`` function, if you wish.

    ```sh
    make datetest  
    ./datetest   
    ```

    The command ``make`` without an argument builds (compiles and links) all the programs in this exercise.

2. The class ``Point`` describes a point in the plane. The program *pointtest.cc* allocates a point object in different ways. Study the program and make sure that you understand the different alternatives.

3. Study the program *sizetest.cc*. Try to predict the output from the program, then run the program and check your prediction.

4. A palindrome is a word that reads the same both forwards and backwards. Examples: anna, amanaplanacanalpanama. Write a function that takes a string as parameter and returns true if the word is a palindrome, false otherwise. Also write a program that reads words from the terminal and checks whether they are palindromes. Modify the makefile to build the program.

5. C++ has the One Definition Rule, that says that definitions must occur at most once (for most things). Classes are typically declared in header files, and then care must be to avoid multiple definitions when a header file is included more than once. 
 
    Compile the program in *include_test.cc* and make sure you understand the error message and why it occurs. Then, add include guards to *foo.h* and *bar.h* to fix the error.

6. Modern C++ has two kinds of enumeration types. The old kind of enumeration is ``enum`` which is inherited from C. That has some problems illustrated by the program *enumtest.cc*. Compile the program and make sure you understand the compiler errors. Also, note that enums contain integer values, and you can (perhaps by accident) assign a value that is not part of the enumeration to an enum variable. 

    In modern C++ scoped enums, ``enum class``, has been introduced to address those problems. Change the program to use scoped enums to fix the errors.

