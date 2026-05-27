
# Exercise 2 Solutions
*Author: Mikael*

1. *Run the program memerrortest.cc -- it illustrates what happens upon memory-related execution errors. Some errors are detected, some are not. In a larger program, the undetected errors would probably lead to catastrophic errors much later during the execution. Run again, under control of Valgrind or with sanitizers (see lab 1).*

    ```console
    g++ memerrortest.cc -o memerrortest             
    memerrortest.cc: In function ‘void f4()’:
    memerrortest.cc:43:16: warning: ‘void operator delete(void*, std::size_t)’ called on unallocated object ‘i’ [-Wfree-nonheap-object]
    43 |         delete p;
       |                ^
    memerrortest.cc:40:13: note: declared here
    40 |         int i = 1;
       |             ^
    ```

    After running (several times):

    ```console
    ./memerrortest 20:41:57
    Check memory-related execution errors.
    Function number: 1
    Addressing outside allocated memory.
    
    ./memerrortest 20:42:00
    Check memory-related execution errors.
    Function number: 2
    Accessing unitialized memory.

    ./memerrortest 20:42:02
    Check memory-related execution errors.
    Function number: 3
    Dereferencing null pointer.
    [1]    21246 segmentation fault (core dumped)  ./memerrortest

    ./memerrortest 20:42:04
    Check memory-related execution errors.
    Function number: 4
    Deleting stack-allocated memory.
    free(): invalid pointer
    [1]    21263 IOT instruction (core dumped)  ./memerrortest
    
    ./memerrortest 20:42:05
    Check memory-related execution errors.
    Function number: 5
    Double delete.
    free(): double free detected in tcache 2
    [1]    21280 IOT instruction (core dumped)  ./memerrortest
    ```

    Valgrind gave:

    ```console
    valgrind ./memerrortest
    ==23322== Memcheck, a memory error detector
    ==23322== Copyright (C) 2002-2024, and GNU GPL'd, by Julian Seward et al.
    ==23322== Using Valgrind-3.25.1 and LibVEX; rerun with -h for copyright info
    ==23322== Command: ./memerrortest
    ==23322==
    vex amd64->IR: unhandled instruction bytes: 0x62 0xF1 0x7F 0x48 0x7F 0x84 0x24 0x30 0x0 0x0
    vex amd64->IR:   REX=0 REX.W=0 REX.R=0 REX.X=0 REX.B=0
    vex amd64->IR:   VEX=0 VEX.L=0 VEX.nVVVV=0x0 ESC=NONE
    vex amd64->IR:   PFX.66=0 PFX.F2=0 PFX.F3=0
    ==23322== valgrind: Unrecognised instruction at address 0x402b49d.
    ==23322==    at 0x402B49D: _dl_start (rtld.c:565)
    ==23322==    by 0x402A547: ??? (in /usr/lib/ld-linux-x86-64.so.2)
    ==23322== Your program just tried to execute an instruction that Valgrind
    ==23322== did not recognise.  There are two possible reasons for this.
    ==23322== 1. Your program has a bug and erroneously jumped to a non-code
    ==23322==    location.  If you are running Memcheck and you just saw a
    ==23322==    warning about a bad jump, it's probably your program's fault.
    ==23322== 2. The instruction is legitimate but Valgrind doesn't handle it,
    ==23322==    i.e. it's Valgrind's fault.  If you think this is the case or
    ==23322==    you are not sure, please let us know and we'll try to fix it.
    ==23322== Either way, Valgrind will now raise a SIGILL signal which will
    ==23322== probably kill your program.
    ==23322==
    ==23322== Process terminating with default action of signal 4 (SIGILL): dumping core
    ==23322==  Illegal opcode at address 0x402B49D
    ==23322==    at 0x402B49D: _dl_start (rtld.c:565)
    ==23322==    by 0x402A547: ??? (in /usr/lib/ld-linux-x86-64.so.2)
    ==23322==
    ==23322== HEAP SUMMARY:
    ==23322==     in use at exit: 0 bytes in 0 blocks
    ==23322==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
    ==23322==
    ==23322== All heap blocks were freed -- no leaks are possible
    ==23322==
    ==23322== For lists of detected and suppressed errors, rerun with: -s
    ==23322== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
    [1]    23322 illegal hardware instruction (core dumped)  valgrind ./memerrortest
    ```

    Again, with ``--leak-check=full``:

    ```console
    valgrind --leak-check=full ./memerrortest
    ==23723== Memcheck, a memory error detector
    ==23723== Copyright (C) 2002-2024, and GNU GPL'd, by Julian Seward et al.
    ==23723== Using Valgrind-3.25.1 and LibVEX; rerun with -h for copyright info
    ==23723== Command: ./memerrortest
    ==23723==
    vex amd64->IR: unhandled instruction bytes: 0x62 0xF1 0x7F 0x48 0x7F 0x84 0x24 0x30 0x0 0x0
    vex amd64->IR:   REX=0 REX.W=0 REX.R=0 REX.X=0 REX.B=0
    vex amd64->IR:   VEX=0 VEX.L=0 VEX.nVVVV=0x0 ESC=NONE
    vex amd64->IR:   PFX.66=0 PFX.F2=0 PFX.F3=0
    ==23723== valgrind: Unrecognised instruction at address 0x402b49d.
    ==23723==    at 0x402B49D: _dl_start (rtld.c:565)
    ==23723==    by 0x402A547: ??? (in /usr/lib/ld-linux-x86-64.so.2)
    ==23723== Your program just tried to execute an instruction that Valgrind
    ==23723== did not recognise.  There are two possible reasons for this.
    ==23723== 1. Your program has a bug and erroneously jumped to a non-code
    ==23723==    location.  If you are running Memcheck and you just saw a
    ==23723==    warning about a bad jump, it's probably your program's fault.
    ==23723== 2. The instruction is legitimate but Valgrind doesn't handle it,
    ==23723==    i.e. it's Valgrind's fault.  If you think this is the case or
    ==23723==    you are not sure, please let us know and we'll try to fix it.
    ==23723== Either way, Valgrind will now raise a SIGILL signal which will
    ==23723== probably kill your program.
    ==23723==
    ==23723== Process terminating with default action of signal 4 (SIGILL): dumping core
    ==23723==  Illegal opcode at address 0x402B49D
    ==23723==    at 0x402B49D: _dl_start (rtld.c:565)
    ==23723==    by 0x402A547: ??? (in /usr/lib/ld-linux-x86-64.so.2)
    ==23723==
    ==23723== HEAP SUMMARY:
    ==23723==     in use at exit: 0 bytes in 0 blocks
    ==23723==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
    ==23723==
    ==23723== All heap blocks were freed -- no leaks are possible
    ==23723==
    ==23723== For lists of detected and suppressed errors, rerun with: -s
    ==23723== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
    [1]    23723 illegal hardware instruction (core dumped)  valgrind --leak-check=full ./memerrortest
    ```

    I'm not sure how to interpret the response. I think I did it correctly. Use this as reference if you want. Moving on! 



2. *Editors for program text usually help with matching of parentheses: when you type a ), ] or } the editor highlights the corresponding left parenthesis. Example (... is a sequence of characters except parentheses):*
    ```
    ...(...(...[...]...)...)...{...}...
            |<--|           |<--|
        |<----------|
    |<------------------|
    ```
    *Implement the function ``find_left_par`` in the class Editor, test with editortest.cc.*

    Some psuedocode (not following any standard):

    ```
    right_par = [")","]","}"]
    left_par = ["(","[","{"]

    procedure find_left_par(p)
        if (p < length(text) and text[p] in right_par)  // If position is valid and is a right parenthesis
            count_right_par = 1                         // Number of right parenthesis encountered during travel

            for (i = p - 1; i > 0; i--)                 // Travel left-ward
                if (text[i] in right_par)               // If another right parenthesis
                    count_right_par++                   // Count up, so we ignore corresponding parenthesis
                else if (text[i] in left_par)           // If left parenthesis
                    count_right_par--                   // Decrement right parenthesis count (we have closed one)
                    if (count_right_par == 0)           // If count has become 0, this is the corresponding left parenthesis
                        return i                        // Return position
        return string::npos                             // Return invalid position marker
    end procedure
    ```

    See *editor.cc* for my implementation.
    ```sh
    g++ editortest.cc editor.cc -o editor
    ```
    Run using ``./editor``, or see: 

    ```console
    ./editor 
    11      (11)
    7       (7)
    3       (3)
    27      (27)
    18446744073709551615    (18446744073709551615)
    ```



3. *Classes can have static members, just like in Java. One example is seen in count_objs.cc, which uses a static member variable to count how many objects have been created of a class. Implement the static member function void ``Foo::print_count()``, so that the program compiles and running the example program prints*

    ```
    Created Foo objects = 1
    Created Foo objects = 2
    Created Foo objects = 3
    Created Foo objects = 3
    ```

    See my implementation of this step in *count_objs.cc* on lines commented with ``// Step 1``.

    *Add functionality to also keep track of how many objects are currently alive in the program. Change the class Foo so that it also counts the number of currently allocated objects. The output of the example program should be something like:*

    ```
    Alive Foo objects:1 / 1 created
    Alive Foo objects:2 / 2 created
    Alive Foo objects:1 / 3 created
    Alive Foo objects:0 / 3 created
    ```

    See my implementation of this step in *count_objs.cc* on lines commented with ``// Step 2``.

    Note that I also added a reset function and another example. This is not necessary.

4. *Study the program integer_conversion.cc. Before running it, what do you think the output will be? Then run the program and see. Is the output what you expected?*

    *Then, compile with warnings for implicit conversions enabled (``-Wconversion`` and ``-Wsign-conversion``). Do you get a warning? Do you understand it? If you have access to both g++ and clang++ (the school computers do), compare the two. (Compile with just ``-Wall`` and ``-Werror`` with both compilers.)*

    **Before running:**

    While I see that ``x`` is unsigned, I do not know what this means for the results. I expect all to be -4, but I have a feeling I'll be incorrect.

    **Result:**

    ```console
    g++ integer_conversion.cc -o integer_conversion
    ./integer_conversion

    a = 4.29497e+09
    b = -4
    c = 4294967292
    ```

    ```console
    g++ integer_conversion.cc -o integer_conversion -Wconversion -Wsign-conversion
    integer_conversion.cc: In function ‘int main()’:
    integer_conversion.cc:11:19: warning: conversion to ‘unsigned int’ from ‘int’ may change the sign of the result [-Wsign-conversion]
    11 |     float a = x - y;
       |                   ^
    integer_conversion.cc:11:17: warning: conversion from ‘unsigned int’ to ‘float’ may change value [-Wconversion]
    11 |     float a = x - y;
       |               ~~^~~
    integer_conversion.cc:12:17: warning: conversion to ‘unsigned int’ from ‘int’ may change the sign of the result [-Wsign-conversion]
    12 |     int b = x - y;
       |                 ^
    integer_conversion.cc:12:15: warning: conversion to ‘int’ from ‘unsigned int’ may change the sign of the result [-Wsign-conversion]
    12 |     int b = x - y;
       |             ~~^~~
    integer_conversion.cc:13:18: warning: conversion to ‘unsigned int’ from ‘int’ may change the sign of the result [-Wsign-conversion]
    13 |     long c = x - y;
       |
    ```

    ```console
    g++ integer_conversion.cc -o integer_conversion -Wall -Werror

    # (gave no output)
    ```

    ```console
    clang++ integer_conversion.cc -o integer_conversion -Wall -Werror

    # (gave no output)
    ```

    **Interpretation**

    In ``float a = x - y``, ``y`` is converted implicitly to an unsigned integer, which could change it's meaning if ``y`` was negative. Additionally, the conversion from an unsigned integer to float changes the meaning of the result. -4 becomes a very large float instead.

    In ``int b = x - y``, ``y`` is again converted implicitly. However, as it is a positive number, the result is as expected, e.g. -4 which is correctly interpreted by the signed integer type ``int``.

    In ``long c = x - y``, we again have implicit conversion. The result is interpreted as a very large long, as the unsigned integer result gets converted to signed long.

    (I have tried my best to understand, but I may still be incorrect.)

