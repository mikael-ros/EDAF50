# Exercise 4
*Author: Sven Robertz, used with permission (granted 2026-02-04)*

About: Operator overloading, inheritance.

1. Write a class ``Rational`` that describes rational numbers, i.e., numbers like 22/3 or 5/6. All numbers should be in their simplest forms, e.g., 1/2 instead of 2/4 or 3/6. Implement constructs so the program in *[rationaltest.cc](rationaltest.cc)* works correctly, (To convert a number to its simplest form, you must compute the greatest common divisor of the numerator and the denominator. The classical GCD algorithm is Euclid's algorithm, but there are faster algorithms that don't use division. See, for example, Binary GCD.)

2. In *[shapetest.cc](shapetest.cc)* three objects ``aShape``, ``aSqua``, and ``aCircle`` are created, and the ``print()`` function is used to check the identity (type) of each object. Everything seems to work correctly, but when object types are checked in another way the results are wrong. Explain the results and correct the classes so both checks produce the same results. 

3. In *[shapevectortest.cc](shapevectortest.cc)* we assume that we have fixed the error from assignment 2. We now store a mix of Square and Circle objects in a vector. The results are wrong -- the objects seem to lose their type again. Explain why this happens and fix the error.

4. Const objects, references and function overloading

    Study the program *[const.cc](const.cc)* and make sure you understand what happens in each function call. In particular, what are the types of the objects, and what are the types of the references?

    Then uncomment the commented out call and make sure you understand the error message.

5. Function overloading across class hierarchies does not work, as names in a derived class hide names in the base class. Study the file *[overload.cc](overload.cc)* and make sure you understand the errors given by the compiler. Then remove ``example2()`` and change the program so that it compiles and  ``example1()`` outputs
    ```console
    B::f(5)
    D::f()
    B::f(17)
    ```
    You can do this in two ways, either by changing the call or the class.

