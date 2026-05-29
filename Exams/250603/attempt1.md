# 2025-06-03
Attempted 2026-05-29

*Author: Mikael*

Rules for this run:
- no help from the compiler (write all code in here)
- external help (Google, AI, e.t.c.) is allowed when stuck, since I'm trying to learn
    the help used will be listed below the question header
    any question where I feel like I have used too much external help gets 0 points

## 1
- Google 
    - "find_if"
    - "c++ lambda"
- ChatGPT

    Used to understand the question better. Ultimately ended up using a lot of what it suggested. Tried to learn from the results so I can actually do it on my own
- Peeking at the official solution

### Usage
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

### Implementation
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

## 2
- a peek at the official solution
    sanity check

Because ``o2`` is being interpreted as ``Base``, which along with the fact that ``foo()`` has not been marked ``const foo() override`` in ``Derived`` means that it calls ``foo()`` in ``Base`` instead. 

In ``o3``, the type and value type are the same, so ``foo()`` in ``Derived`` is correctly called rather than ``foo()`` in ``Base``, because it is hiding the previous ``foo()``.

## 3
- a peek at the official solution
    sanity check

### a)

Looking at the output from the sanitizer, we see that the error occurs when ``not_equal_to``is called, which in turn calls ``!=`` which calls ``==``. 

The lack of a user-defined copy-constructor means that only a shallow copy is made. As a result, the destructor, which deletes the ``fn`` and ``ln`` pointers, causes dangling pointers.

### b)

As far as I understand, we don't need to manually delete ``fn`` and ``ln``, they'll be deconstructed automatically. So removing our custom destructor should work by this logic.

(wrong)