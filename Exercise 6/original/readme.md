# Exercise 6
*Author: Sven Robertz, used with permission (granted 2026-02-04)*

About: Function templates, containers, algorithms.

1. "Counting sort" is an efficient sorting method if the elements that are to be sorted are integral values in a limited range. You count the number of occurrences of each value and then output each value the correct number of times.

    Example: ``sort {6, 3, 6, 2, -1, 3}``.

    The number of occurrences becomes ``{1, 0, 0, 1, 2, 0, 0, 2}``

    (one ``-1``, no ``0``, no ``1``, one ``2``, two ``3``, no ``4``, no ``5``, two ``6``).  

    Implement the function ``csort`` in csorttest.cc. Sort some million values in the range ``[1, 1000]`` and compare the execution time for ``csort`` with that of ``std::sort``. ``csort`` should be better.

    Sort some thousand values in the range ``[-10 000 000, +10 000 000]`` and compare again.  

2. Write a class ``SequenceGenerator`` to be used in *[generate.cc](generate.cc)*. Deduce from the program text what the class should look like.  

3. Write a program that reads a number of text files, whose names are given on the command line, and prints the 20 most common words in the files along with the total number of occurrences in all files. You may assume that there are only letters and whitespace in the files. Give an error message if a file cannot be opened.

4. The first part of ``TagRemover`` from lab 3 can be implemented using the standard algorithm ``std::copy_if``, by using ``stream iterators<char>`` and a stateful functor that returns false when inside a tag and true otherwise.

    The algorithm ``std::copy_if`` iterates over an iterator range, calling its predicate with each element but only copies the elements for which the predicate returns true.

    The file *[tagremover_alg.cc](tagremover_alg.cc)* contains a skeleton and a simple test. Implement the functor so that it removes tags when used with ``std::copy_if``.

5. ``static_cast`` only allows conversion between types that have a relation (i.e., ``static_cast`` can be seen as the inverse of an implicit type conversion) so from a type system point-of-view ``static_cast`` is safe. But ``static_cast`` allows narrowing so it does not protect against loss of information.

    Write a function template, ``narrow_cast``, that performs a run-time check that no information is lost. Do this by performing a ``static_cast`` of the value to the target type and back and verify that you get the same value. Test it with *[test_narrow_cast.cc](test_narrow_cast.cc)*.

6. In exercise 2 we used static member variables to track allocations of a type. This counting is, however, a generic functionality and instead of duplicating the same code in all classes, we can use templates to make it into a reusable component, similar to "mixins"  in other object oriented languages.

    Here, we can use a pattern called CRTP (the curiously recurring template pattern). The idea is to write code that behaves like it has virtual member functions, but make the dispatch statically. This is done by making the base class a template that has the derived class as a parameter.

    ```cpp
    template <typename Derived>
    class Base;
    ```

    Then, to emulate the virtual dispatch (here of a virtual function ``f()``),  a function in the base class downcasts its this pointer to the subclass and calls ``f()`` through that:

    ```cpp
    static_cast<const Derived*>(this)->f()
    ```

    Note that in this case, the ``Base`` class does not need to have the function ``f()`` if it should behave like a pure virtual function. It is only defined in the derived classes.

    Study the examples *[animal.cc](animal.cc)* (which uses virtual functions) and *[animal_crtp.cc](animal_crtp.cc)* which uses CRTP to implement the template method pattern without using dynamic dispatch.

    Then rewrite *[counted.cc](counted.cc)*, using CRTP to eliminate the duplicated code for counting allocations.