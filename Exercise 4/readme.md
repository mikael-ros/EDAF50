# Exercise 4 Solutions
*Author: Mikael*

1. *Write a class ``Rational`` that describes rational numbers, i.e., numbers like 22/3 or 5/6. All numbers should be in their simplest forms, e.g., 1/2 instead of 2/4 or 3/6. Implement constructs so the program in [rationaltest.cc](rationaltest.cc) works correctly, (To convert a number to its simplest form, you must compute the greatest common divisor of the numerator and the denominator. The classical GCD algorithm is Euclid's algorithm, but there are faster algorithms that don't use division. See, for example, Binary GCD.)*

    First, I created [rational.cc](rational.cc) and [rational.h](rational.h), as these were not yet present.

    I used [bitbuffer.cc](../Exercise%203/bitbuffer.cc) and [bitbuffer.h](../Exercise%203/bitbuffer.h) as reference, when trying to understand the structure required.

    See [rational.cc](rational.cc) and [rational.h](rational.h) for my implementation, based on the tests in [rationaltest.cc](rationaltest.cc).

    Some rationale I understood after a while of reasoning is that it seems like things that could be static functions, e.g. the operator ``+`` are defined outside the class body. It makes sense, if you think of those functions as being equivalent to something in Java ``Rational.Add(Rational lhs, Rational rhs)``. You usually wouldn't define it so it could be called like ``lhs.Add(rhs)``. However the operator ``+=`` is defined in the class body, because it does operate directly on a ``Rational`` object.

    I found [this, simple, walkthrough of the Euclidean Algorithm for GCD.](https://www.freecodecamp.org/news/euclidian-gcd-algorithm-greatest-common-divisor/)

    Compiled using:
    ```sh
    g++ rational.cc rationaltest.cc -o rational
    ``` 

    Running:
    ```console
    ./rational
    2/3     (2/3)
    3       (3)
    0       (0)
    4       (4)
    28/3    (28/3)
    31/3    (31/3)
    ```

2. *In [shapetest.cc](shapetest.cc) three objects ``aShape``, ``aSqua``, and ``aCircle`` are created, and the ``print()`` function is used to check the identity (type) of each object. Everything seems to work correctly, but when object types are checked in another way the results are wrong. Explain the results and correct the classes so both checks produce the same results.* 

    Running ``make`` and ``./shapetest`` before changing anything yields:

    ```console
    I'm a Shape
    I'm a Square
    I'm a Circle
    I'm a Shape
    I'm a Shape
    I'm a Shape
    ```

    This is happening because when we run ``.print()``, we are accessing the class' ``print()`` function, which is hiding the superclass ``Shape`` ``print()``. When we instead use ``Shape*``, all of the shapes are accessed as if instances of the superclass ``Shape``. To solve this, we make the superclass method ``virtual``, so that it only get's called on the subclasses if ``print()`` has not been defined for them. We can also add ``override`` to the subclass' ``print()`` functions, but it does not seem to matter in this example.

    Now, the result is:
    ```console
    I'm a Shape
    I'm a Square
    I'm a Circle
    I'm a Shape
    I'm a Square
    I'm a Circle
    ``` 

3. *In [shapevectortest.cc](shapevectortest.cc) we assume that we have fixed the error from assignment 2. We now store a mix of Square and Circle objects in a vector. The results are wrong -- the objects seem to lose their type again. Explain why this happens and fix the error.*

    ``shapevectortest`` was compiled as a result of the previous ``make`` instruction, so we can simply run ``./shapevectortest``, which before changing anything gives us:

    ```console
    I'm a Shape
    I'm a Shape
    I'm a Shape
    I'm a Shape
    I'm a Shape
    I'm a Shape
    I'm a Shape
    I'm a Shape
    I'm a Shape
    I'm a Shape
    ```

    This is happening because the ``Shape``s are now being accessed as ``Shape`` again. We can fix either by explcitly checking and casting the type, or by changing the way the ``Shape``s are stored. In the [given solution](given-solutions/shapevectortest.cc), we can see how they used ``unique_ptr`` along with changing the access method in the print loop. ``unique_ptr`` works for this, because it acts like a middle man. In the prior version, the objects were sliced, but when using ``unique_ptr``, they are only accessed by pointers and thus retain their functionality as if accessed as their subclass.

    Now, after recompiling, we get:

    ```console
    I'm a Circle
    I'm a Circle
    I'm a Circle
    I'm a Square
    I'm a Circle
    I'm a Square
    I'm a Circle
    I'm a Circle
    I'm a Square
    I'm a Circle
    ```


4. *Const objects, references and function overloading*

    *Study the program [const.cc](const.cc) and make sure you understand what happens in each function call. In particular, what are the types of the objects, and what are the types of the references?*

    *Then uncomment the commented out call and make sure you understand the error message.*

    Uncommenting the line and recompiling yields:
    ```console
    const.cc: In function ‘void example()’:
    const.cc:56:9: error: binding reference of type ‘Foo&’ to ‘const Foo’ discards qualifiers
    56 |     bar(cf);
       |         ^~
    const.cc:24:15: note: initializing argument 1 of ‘void bar(Foo&)’
    24 | void bar(Foo& f)
       |          ~~~~~^
    make: *** [<builtin>: const] Error 1
    ```

    - ``foo`` takes a constant reference to a ``Foo`` object
    - ``bar`` takes a reference to a ``Foo`` object
    - ``qux`` takes a reference to a ``Foo`` object
    
    In the first part of ``example()``, both ``foo(ncf)`` and ``bar(ncf)`` are able to execute, because ``ncf`` can be cast either as constant or non-constant.

    In the second part, we are trying to use a constant ``Foo`` object. Trying to retrieve a reference to this yields an error, because if we were able to, we would be able to modify the object directly despite it being constant.  

    There is no given solution for this task, so I had to check my answer with AI. Take this with a grain of salt.



5. *Function overloading across class hierarchies does not work, as names in a derived class hide names in the base class. Study the file [overload.cc](overload.cc) and make sure you understand the errors given by the compiler. Then remove ``example2()`` and change the program so that it compiles and  ``example1()`` outputs*
    ```console
    B::f(5)
    D::f()
    B::f(17)
    ```
    *You can do this in two ways, either by changing the call or the class.*

    Compiling using:

    ```sh
    g++ overload.cc -o overload
    ```

    Yields:

    ```console
    overload.cc: In function ‘void example1()’:
    overload.cc:19:8: error: no matching function for call to ‘D::f(int)’
    19 |     d.f(17);
       |     ~~~^~~~
    • there is 1 candidate
        • candidate 1: ‘void D::f()’
        overload.cc:9:10:
            9 |     void f() {cout << "D::f()\n";}
              |          ^
        • candidate expects 0 arguments, 1 provided
    overload.cc: In function ‘void example2()’:
    overload.cc:24:12: error: ‘d’ was not declared in this scope
    24 |     B& r = d;
       |            ^
    overload.cc:25:8: error: no matching function for call to ‘B::f()’
    25 |     r.f();
       |     ~~~^~
    • there is 1 candidate
        • candidate 1: ‘void B::f(int)’
        overload.cc:5:11:
            5 |      void f(int x) {cout << "B::f(" << x << ")\n";}
              |           ^
        • candidate expects 1 argument, 0 provide
    ```

    1. ``d.f(17)``: yields an error because we are directly accessing the class ``D``, subclass of ``B``, which hides ``f(int x)`` and replaces it with ``f()``. Therefore, the ``int`` (17) being passed through is not valid, as ``f()`` in ``D`` does not expect an ``int`` parameter. 
    2. ``B& r = d``: Because ``d`` was destroyed when we left the scope of ``example1()``, ``d`` is no longer accessible.
    3. ``r.f()``: yields an error, because the ``B`` class expects an ``int`` parameter, which is not being supplied.

    We can make it compile by either:
    1. adding ``using B::f`` in ``D``
    2. or adding a ``f(int x)`` function that calls ``B::f(x)``:
        ```cpp
        void f(int x) {
            B::f(x);
        }
        ```
    I'll do option 1.

    After compiling again, the program now correctly yields:
    ```console
    B::f(5)
    D::f()
    B::f(17)
    ```

