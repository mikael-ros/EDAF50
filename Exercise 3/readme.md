# Exercise 3 Solutions
*Author: Mikael*

1. *The program [countobj.cc](countobj.cc) contains a class that has a counter that is incremented when an object of the class is created and decremented when an object is destroyed. The function ``f`` demonstrates that the class seems to function correctly, but the functions ``g`` and ``h``  show otherwise. Correct the class so also ``g`` and ``h`` give correct results.*

    Before amending the change, compiling with:

    ```sh
    g++ countobj.cc -o countobj
    ```

    and running ``./countobj``, gives:

    ```console
    Program start, before f() -- number of objects: 0
    After f(), before g()     -- number of objects: 0
    After g(), before h()     -- number of objects: -1
    After h(), program end    -- number of objects: -1
    ```

    After reading through the given code, it is apparent that:
    - ``f`` creates a ``Counted`` object, and destroys it after (+1 -1 = 0)
    - ``g`` creates a ``Counted`` object, and then reassigns it to another variable (+1 = 1)
    - ``h`` creates two ``Counted``objects, and then reassigns the second one to be equal to the first one (+1 +1 -1 = 1)

    The output does not reflect this however. Running ``g`` should mean we have 1 object, which is destroyed once we leave the scope, and running ``h`` after should give us 1 again, which is destroyed when we leave the scope.

    This is because in both ``g`` and ``h``, we forget to construct ``Counted`` objects. We can either solve this by explicitly making a new ``Counted`` object, or we can define the copy constructor.

    After the changes seen in *[countobj.cc](countobj.cc)*, the program now outputs:

    ```console
    Program start, before f() -- number of objects: 0
    After f(), before g()     -- number of objects: 0
    After g(), before h()     -- number of objects: 0
    After h(), program end    -- number of objects: 0
    ```

2. *We have started to write a class ``SVector`` that we hope will become a usable vector class. (This is a futile attempt, since we cannot hope to write a class that is as good as ``std::vector``.) The test program in [svectortest.cc](svectortest.cc) is intended to demonstrate that the basic functionality of the class is correct, but it gives unexpected results.*  
  
    *What has happened? What is the cause of the error? Correct the class (not the test program so the program gives the expected output.*  
  
    *A similar error to the one demonstrated by the test program may occur in another circumstance. When? Correct the class so this error cannot occur.* 

    Compiling *[svectortest.cc](svectortest.cc)* with the following command:

    ```sh
    g++ svectortest.cc svector.cc -o svectortest
    ```

    And running ``./svectortest``, gives us:

    ```console
    1 2 3 4 5 6 7 8 9 10
    10 20 30 40 50
    free(): double free detected in tcache 2
    [1]    11693 IOT instruction (core dumped)  ./svectortest
    ```

    Studying *[svector.cc](svector.cc)* reveals that the deconstructor calls ``delete`` on itself, causing the "double free". Removing the deconstructor solves the issue.

    Compiling and running, as before, now yields:
    ```console
    1 2 3 4 5 6 7 8 9 10
    10 20 30 40 50
    1 2 3 4 5 6 7 8 9 10
    ```

    e.g. no errors!

    However, looking at the [given solution](given-solutions/svector.cc), reveals that we are actually meant to define a new copy constructor. As it describes, the ``print`` calls implicitly call the copy constructor, and causes the vector to be deconstructed when the scope of ``print`` is exited. As such, the other, better, solution is to define a copy constructor. Since I've understood this after the fact, you're best off comparing [my solution](svector.cc) and the [given solution](given-solutions/svector.cc).


3. *The class ``BitBuffer`` receives bits which are packed in a byte (8 bits). As soon as the buffer is full a byte should be written (as a character) to an ostream with the function ``put(unsigned char ch)``. Implement the class, test with [bitbuffertest.cc](bitbuffertest.cc). As an example, the input ``0 1 0 0 0 0 0 1`` should give the output A.*

    *Manually testing this at the terminal is tedious.  You may want write test cases using for instance a ``std::stringstream``. A quick and dirty way is to script it in the shell. For instance, the command line ``echo "0 1 0 0  0 0 0 1   0 1 0 0  0 0 1 0   0 1 0 0  0 0 1 1" | ./bitbuffertest`` should output ABC.*

    I had to reference the [given solution](given-solutions/bitbuffer.cc) and understand it bit by bit (pun). My solution is therefore identical, plus some comments.

    Compile:
    ```sh
    g++ bitbuffer.cc bitbuffertest.cc -o bitbuffer
    ```

    Running: 
    ```console
    echo "0 1 0 0  0 0 0 1   0 1 0 0  0 0 1 0   0 1 0 0  0 0 1 1" | ./bitbuffer
    ABC
    ```

4. *Random numbers can be used to encrypt texts. You need a random number generator that can be initialized with a seed (the encryption key), so the same sequence of random numbers can be reproduced. The characters are encrypted by adding a random number to each character. We assume that all characters are in the interval ``[0, 256)`` and that the random numbers are in the same interval. The encrypted characters shall also be in this interval. Example:*

    ```
    Character:              A     t     t     a     c     k     !
    Character code:        65   116   116    97    99   107    33 
    Random number:          4   207     6     1    12   255     8 
    Encrypted code:        69    67   122    98   111   106    41 
    Encrypted character:    E     C     z     b     o     j     )
    ```
    *Implement the class ``Crypto``, test with [cryptotest.cc](cryptotest.cc).*

    See my implementation in *[crypto.cc](crypto.cc)*. Mine is less complex than the [given solution](given-solutions/crypto.cc), but I think it's less secure. If I'm not mistaken, assigning a key to rand does so globally, so in a real world situation it might not be great. It assumes that ``rand`` is not used anywhere else. Some googling also reveals that ``rand`` is not made for cryptography. Good thing this is not a real deployment!

    Compile:
    ```sh
    g++ crypto.cc cryptotest.cc -o crypto
    ``` 

    Run:
    ```console
    ./crypto
    Key:       213131312
    Text:      This is a pretty cool example text
    Encrypted: N�Mh��ãNX) �
    Decrypted: This is a pretty cool example text
    ```