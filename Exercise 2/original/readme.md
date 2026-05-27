# Exercise 2
*Author: Sven Robertz, used with permission (granted 2026-02-04)*

About: Memory, strings, static class members, integer conversions

1. Run the program *memerrortest.cc* -- it illustrates what happens upon memory-related execution errors. Some errors are detected, some are not. In a larger program, the undetected errors would probably lead to catastrophic errors much later during the execution. Run again, under control of Valgrind or with sanitizers (see lab 1). 

2. Editors for program text usually help with matching of parentheses: when you type a ), ] or } the editor highlights the corresponding left parenthesis. Example (... is a sequence of characters except parentheses):
    ```
    ...(...(...[...]...)...)...{...}...
            |<--|           |<--|
        |<----------|
    |<------------------|
    ```
    Implement the function ``find_left_par`` in the class Editor, test with *editortest.cc*.

3. Classes can have static members, just like in Java. One example is seen in *count_objs.cc*, which uses a static member variable to count how many objects have been created of a class. Implement the static member function void ``Foo::print_count()``, so that the program compiles and running the example program prints

    ```
    Created Foo objects = 1
    Created Foo objects = 2
    Created Foo objects = 3
    Created Foo objects = 3
    ```

    Add functionality to also keep track of how many objects are currently alive in the program. Change the class Foo so that it also counts the number of currently allocated objects. The output of the example program should be something like:

    ```
    Alive Foo objects:1 / 1 created
    Alive Foo objects:2 / 2 created
    Alive Foo objects:1 / 3 created
    Alive Foo objects:0 / 3 created
    ```

4. Study the program *integer_conversion.cc*. Before running it, what do you think the output will be? Then run the program and see. Is the output what you expected?

    Then, compile with warnings for implicit conversions enabled (``-Wconversion`` and ``-Wsign-conversion``). Do you get a warning? Do you understand it? If you have access to both g++ and clang++ (the school computers do), compare the two. (Compile with just ``-Wall`` and ``-Werror`` with both compilers.)
