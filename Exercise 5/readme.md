# Exercise 5 Solutions
*Author: Mikael*

1. *Morse code is a method of transmitting text information as a series of short and long signals ('dots' and 'dashes'). For example, the letter 'a' is coded as ``.-``, 'b' as ``-...``, and so on. We ignore spaces between words. Implement the class ``MorseCode``, test with morsetest.cc. The file [morsecode.def](morsecode.def) contains the morse code definitions of the letters a-z. Characters outside this range should be ignored. Hint: in ``decode()``, use an ``v`` to read morse codes from the code string.*

    Some psuedocode, before I get started:

    ```
    definitions = read(morse.def) // Morse.def as an array of codes

    procedure encode(text)
        encoded_text = ""

        for (letter in text)
            index = letter.toLowerCase() as int // Cast to int
            encoded_text += definitions[index]
        
        return encoded_text
    end procedure

    procedure decode(encoded_text)
        decoded_text = ""

        for (signal in encoded_text.split(" ")) // split on spaces
            s = definitions.indexOf(signal) as char // cast as char
            decoded_text += s
        
        return decoded_text
    end procedure
    ```

    If you want to see an implementation using the dictionary built into the [morse.def](morse.def) file, you can see the [given solution](given-solutions/morsecode.cc).

    Also see my changes in [morsetest.cc](morsetest.cc). I thought it would be fun to see before and after.

    Output, after compiling with ``g++ morsecode.cc morsetest.cc -o morse``:

    ```console
     --- text to code to text---
    a man, a plan, a canal - panama
    .- -- .- -. .- .--. .-.. .- -. .- -.-. .- -. .- .-.. .--. .- -. .- -- .-
    AMANAPLANACANALPANAMA

    --- code to text to code ---
    .... . .-.. .-.. --- .-- --- .-. .-.. -..
    HELLOWORLD
    .... . .-.. .-.. --- .-- --- .-. .-.. -..
    ```


2. *The class ``Text`` represents texts that have several lines. The class has noconstructor, no destructor, no copy constructor and no assignment operator. Are these functions not necessary? Supply the class with an iterator so the program in [testtext.cc](testtext.cc) functions correctly. You must make additions to the class, but you may not change the representation of the text.*

3. *The program in [personsorttest.cc](personsorttest.cc) gives a lot of compilation errors. What is the cause of the errors? Fix the program.*

4. *Modify the program in [sortwords.cc](sortwords.cc) so it functions as described in the comments.*

5. *When you wish to store values that are identified by keys you usually would use a map. A map has logarithmic time complexity for insertions, deletions and searches and is normally implemented with a binary search tree. This has some drawbacks -- for example, a map iterator is complex (it must traverse a tree), and the nodes in the tree need space for pointers to children and parent.* 

    *Many applications that use a map are of the type "insert values at the start, then search many times." Then, it would be better to use a sorted vector to store the values (the insertions will be slower but searching will be faster, and the values will occupy less space).*

    *Write a class ``AV`` (for Associative Vector) that functions as a ``std::map`` but stores the values in a sorted vector. Binary search should be used for all searches (there are binary search algorithms in the standard library). You only need to implement the constructs that are used in [avtest.cc](avtest.cc).*

6. *Error handling is both important and slightly complicated when it comes to reading streams.*

    *Study the program [istream_iterator_test.cc](istream_iterator_test.cc). In the input stream ``ss``, there are integral numbers and other strings, so when using an ``istream_iterator<int>``, it will stop when the first item that is not an integral number is encountered.*

    *Add error handling so that the program skips the strings that cannot be converted to integers. Change your program so that it prints:*
    ```console
    1
    17
    [ss: not an int: kalle]
    2
    [ss: not an int: nisse]
    3
    [ss: not an int: pelle]
    ss.eof(): true
    ```

    *Note that ``istream::eof()`` means that the program has tried to read beyond the end-of-file, not that the next symbol is end-of-file.*