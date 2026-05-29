# 2025-06-03
Attempted 2026-05-29

*Author: Mikael*

Rules for this run:
- no help from the compiler (write all code in here)
- external help (Google, AI, e.t.c.) is allowed when stuck, since I'm trying to learn
    the help used will be listed below the question header

## 1
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

The idea will be to iteratore over the contents, and skip any element that is equal to the previous element. Like in the description, this means that sequences like ``{1, 4, 1, 4}`` are allowed, so we do not need to care about storing what values have already been used. Since reinventing the wheel docks points, we should use ``std::unique`` if possible.

```cpp
template <typename Iter>
// Gives an iterator over the unique elements of the sequence.
// The returned iterator references first.
// operator++() causes the iterator to reference the next unique
// element, or last.
// The resulting object is comparable for equality to Iter.
unique_iter<Iter> unique_subseq(Iter first, Iter last);



```