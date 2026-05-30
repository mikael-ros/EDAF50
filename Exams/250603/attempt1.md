# 2025-06-03
Attempted 2026-05-29

*Author: Mikael*

Rules for this run:
- no help from the compiler (write all code in here)
- external help (Google, AI, e.t.c.) is allowed when stuck, since I'm trying to learn

    the help used will be listed below the question header

    any question where I feel like I have used too much external help gets 0 points
- help from book is allowed, like on the exam

    however CTRL+F is not allowed, as I cannot do that in real life (if only!)

## Attempt
### 1
- Google 
    - "find_if"
    - "c++ lambda"
- ChatGPT

    Used to understand the question better. Ultimately ended up using a lot of what it suggested. Tried to learn from the results so I can actually do it on my own
- Peeking at the official solution

#### Usage
```cpp
template<typename It1, typename It2>
void print_elems(It1 first, It2 last)
{
    for(;first != last; ++first) cout << *first << " ";
    cout << "\n";
}
void example()
{
    std::vector<int> vi{1,1,1,1,2,2,3,4,5,5,5}; // input
    std::vector<int> expi{1,2,3,4,5}; // expected
    auto it = unique_subseq(begin(vi), end(vi));
    cout << "Actual result: ";
    print_elems(it, end(vi));
    cout << "Expected result: ";
    print_elems(begin(expi), end(expi));
}
```

#### Implementation
The idea will be to iterate over the contents, and skip any element that is equal to the previous element. Like in the description, this means that sequences like ``{1, 4, 1, 4}`` are allowed, so we do not need to care about storing what values have already been used. Since reinventing the wheel docks points, we should use ``std::unique`` if possible.

``unique_iter`` will need to define operators:
- ``++``
- ``!=``
- ``*``

``unique_subseq`` can be defined as a template that simply constructs an ``unique_iter``.
```cpp
template <typename Iter>
// Gives an iterator over the unique elements of the sequence.
// The returned iterator references first.
// operator++() causes the iterator to reference the next unique
// element, or last.
// The resulting object is comparable for equality to Iter.
unique_iter<Iter> unique_subseq(Iter first, Iter last)
{
    return unique_iter<Iter>(first, last);
}
```

The ``unique_iter`` header can then be defined as:
```cpp
#ifndef UNIQUE_ITER_H
#define UNIQUE_ITER_H

template <typename Iter>
class unique_iter {
    public:
        using value_type = typename std::iterator_traits<Iter>::value_type;
        unique_iter(Iter first, Iter last) : current(first), last(last) {}

        unique_iter& operator++() {
            current = std::find_if(current, last, [=](const value_type& v){return v != *current});
            // Find first element where value of element is not equal to the current element
            return *this;
        }

        bool operator!=(const Iter& other) {
            return other != current; 
        }

        value_type& operator*() { // Needed so print_elems works
            return *current; 
        }

    private:
        Iter current;
        Iter last;
}

#endif
```

### 2
- a peek at the official solution
    sanity check

Because ``o2`` is being interpreted as ``Base``, which along with the fact that ``foo()`` has not been marked ``const foo() override`` in ``Derived`` means that it calls ``foo()`` in ``Base`` instead. 

In ``o3``, the type and value type are the same, so ``foo()`` in ``Derived`` is correctly called rather than ``foo()`` in ``Base``, because it is hiding the previous ``foo()``.

### 3
- a peek at the official solution
    sanity check

#### a)

Looking at the output from the sanitizer, we see that the error occurs when ``not_equal_to``is called, which in turn calls ``!=`` which calls ``==``. 

The lack of a user-defined copy-constructor means that only a shallow copy is made. As a result, the destructor, which deletes the ``fn`` and ``ln`` pointers, causes dangling pointers.

#### b)

As far as I understand, we don't need to manually delete ``fn`` and ``ln``, they'll be deconstructed automatically. So removing our custom destructor should work by this logic.

(wrong)

### 4
- C++ Primer, Fifth Edition, page 709

I believe what we may want here is a function object. So I'll reference that, since I've forgotten how they work. We'll basically want to override the ``()`` operator.

We'll want something like:

```cpp
class Counter {
    public:
        Counter(int start = 0) : current{start} {}
        int operator() (int add = 1) {return current += add;}
        operator int() const {return current;} // Cast overload, so Counter can be read as int
    private:
        int current;
};
```

### 5
#### a)
Because the first parameter in ``concat`` is actually a constant ``char`` pointer to the beginning of the string, adding integers to it shifts the pointer over; At best leading to results like the one given, and at worst leading to unexpected behaviour.

#### b)
We could:

```cpp
std::string concat(const char* str, int i)
{
    return std::string(str) + std::to_string(i);
}
```
(e.g. explicitly cast int as a ``string`` and add it)

### 6
- C++ Primer, Fifth Edition, page 405, 407, 463

First some psuedocode:
```
procedure print_matching_lines(phrase, fname):
    file = open(fname)

    if file gave error:
        print("error")
        return 1

    for each line in file:
        if line contains phrase:
            print(line) 

    return 0
end procedure
```

The difficulties here are:
- how does C++ throw errors, and how do we catch them?
- how do I loop over a file input stream?

```cpp
#include <string>
#include <iostream>
#include <fstream>

using std::cout;
using std::cerr;
using std::endl;
using std::string;

int print_matching_lines(const string& phrase, const string& fname)
{
    ifstream input(fname);
    if (!input) {
        cerr << "Could not open file " << fname << endl;
        return 1;
    }

    string line;
    while(read(input, line)) {
        if (line.find(phrase) != string::npos) { // If phrase is found in line
            cout << line << endl;
        }
    }
    
    input.close(); // Close file stream
    return 0;
}
```

---

## Assessment

The questions give: 10 + 5 + 9 + 10 + 6 + 10 = 50. Grading scale is (3/25, 4/33, 5/42).

### 1
0 points, used too much help.

+0p (=0p)

### 2
Half points, used help.

+2.5p (=2.5p)

### 3

a) was correct, b) was not. I used some help, so half points.

+2.25p (=4.75p)

### 4
Used permissible help and answer is functionally equivalent to official solution. Full points.

+10p (=14.75p)

### 5
Correct and used permissible help. Full points.

+6p (=20.75p)

### 6
Correct and used permissible help. Full points.

+10p (30.75p)

### Verdict

Final grade would be passing, e.g. 3. 

#### Strengths
- Knowing what's being asked, even if I don't know how to do it (I can reference the book)

#### Weaknesses
- Pointers and references, when to use them and why
- When and where implicit type casts happen (if anywhere?)
- Not remembering to use include guards and using declarations
- Constructors, copy constructors, destructors, assignment operators
- Iterators