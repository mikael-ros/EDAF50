# 2024-05-31
Attempted 2026-05-30

*Author: Mikael*

Personal rules for this run:
- no help from the compiler (write all code in here)
- external help like search engines is okay, but only if completely stuck. No AI
- help from book is allowed, like on the exam

    however CTRL+F is not allowed, as I cannot do that in real life (if only!)

## Attempt
### 1
- Kagi
    - "difference between T {} and T c++"
#### a)

Before the printout, we have added ``v1``, ``v2``, and ``v3``. Based on the implementation of ``add``, addition is performed by looping over all positions of the vectors, adding their values if they are present. The length of the vector is decided by the third argument. Whether or not the first two are shorter or longer does not matter, they'll either be included as far as they go, or cut off. The iteration is performed by incrementing the respective iterators until their ends are reached. The result is stored in ``v3``, which is why it is using ``begin`` and ``end`` rather than the constant ``cbegin`` and ``cend``. 

I've scanned over the code several times, though, and I cant figure out why it's doing what it's doing.

#### b)

Perhaps making the function recursive. E.g by having ``add`` for three parameters call ``add`` for the first two parameters, then ``add`` again on that result and the third parameter.

Since I have not understood why this is happening, I can't come up with anything concrete.

#### c)

I do not understand enough to answer this.

#### d)

If ``T`` is a class, it will be the same in both cases, but as far as I understood, this is not the case if ``T`` is a built-in type, where ``{}`` is better because it explicitly calls the default constructor. Apparantly removing ``{}`` may in some cases lead to garbage values.



### 2
- Kagi
    - "iterator traits"
        - [cppreference](https://en.cppreference.com/cpp/iterator/iterator_traits)
    - "iterator traits lambda"
        - [stackoverflow](https://stackoverflow.com/questions/6742008/what-are-the-typical-use-cases-of-an-iterator-trait)
- C++ Primer, Fifth edition, page 490-492

Some psuedocode first:

```
procedure copy_nth(start, end, out, nth)
    current = start

    while (start != end)
        if ((current - start) % nth) == 0
            out.add(current)
        else
            current++
    
end procedure
```

```cpp
#include <iostream>


using std::copy_if;
using std::ostream_iterator;

template <class It>
void copy_nth(const It* start, const It* end, ostream_iterator out, const int nth)
{
    typedef typename std::iterator_traits<start>::value_type type = *start;
    int i;
    out = copy_if(start, end, [i](const value_type &v) {if (i % nth == 0) {return v} ++i;})
}
```

### 3
- Kagi
    - "custom >> operator c++"
        - [cppreference](https://en.cppreference.com/cpp/language/operators)
- C++ Primer, Fifth edition, page 383-384
- Google
    - "c++ find_if"
        - [cppreference](https://en.cppreference.com/cpp/algorithm/find)
    - "c++ switch case"
        - [w3schools](https://www.w3schools.com/cpp/cpp_switch.asp)
- Took a peek at the solution (disqualifying points on this question)

As the task specifies, ``token`` needs:
- operator ``>>``

    that skips tags, reads special character codes as the character they represent, and all other characters as themselves
- implicit conversion to ``char``

In the assignment, we assume:
- No nested tags
- All tags are enclosed, e.g. <...>

```cpp
// token.h
#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>

class Token {
    public:
        Token(char letter = '') : letter(letter) {}
        Token(string special = '') 
        {
            switch(special)
            {
                case "lt":
                    letter = '<';
                    break;
                case "gt":
                    letter = '>';
                    break;
                case "amp":
                    letter = '&';
                    break;
                default:
                    letter = '';
            }
        }
        operator char() const { return letter; }
        std::istream& operator>>(std::istream& is, Token& t);
    private:
        char letter;
}

#endif
```

Some psuedocode:
```
procedure tokenize(input, token)
    letter = ''
    while (input has letter)
        if (letter != '<' or letter != '>')
            if (letter == '&')
                token.letter = letter interpreted as real letter
            else 
                token.letter = letter
            break
    return input // remaining input
end procedure
```
            


```cpp
// token.cc
#include <iostream>
#include <token.h>
#include <string>

using std::string;
using std::getline;

std::istream& Token::operator>>(std::istream& is, Token& t)
{
    char c;

    while (is.get(c))
    {   
        if (c != '<' || c != '>')
        {
            if (c == '&')
            {
                string special;
                getline(is, special, ';'); // Get until ;
                t = Token(special);
            } else
            {
                t = Token(c);
            }
            break;
        }

    }
    return is;
}
```

### 4

Presumably, this is because the stream would be destroyed when the scope of ``remove_html`` is completed. As part of the destructor, the stream may destruct the source string, leading to a dangling pointer.

### 5

#### ``example1()``
Yes.

``Foo`` does not use any user-defined classes. As such, we can trust the default destructor to call the default destructors of the members.

However, since ``Foo`` is solely being pointed to, only the pointer gets destroyed when we leave the scope of the function. The ``Foo`` object remains in memory.

#### ``example2()``
No.

``unique_ptr`` destroy the object they are pointing to when destroyed, so the object gets destroyed properly when we leave trhe scope of the function.

#### ``example3()``
Yes. For the same reason as ``example1``.

#### ``example4()``
Yes. For the same reason as ``example1``.

#### ``example5()``
Yes. Even though we are using ``unique_ptr``, using ``Foo`` as the type means that ``Foo``'s destructor is called rather than ``Bar``'s, which means ``Bar``'s members are not destroyed.

#### ``example6()``

No, for the same reason as ``example2``.

### 6
Because there's a terminating null, the 8 character string "abcdefgh" is actually 9 characters. In some situations, as array's in C++ do not check bounds, this can lead to the memory position after the ``prefix`` array being written to. If we are unlucky, this is the position of ``nbr``, which can lead to it being 0. In other cases, it leads to undefined behaviour.

---



## Assessment

The questions give: 13 + 9 + 9 + 5 + 9 + 5 = 50. Grading scale is (3/25, 4/33, 5/42).

### 1

Only d is correct. I'll give 0 points.

+0p (=0p)

### 2

I believe the solutions are equivalen, but do not have time to compile and test.

I'll give half points because I had to search online.

+4.5p (=4.5p)

### 3
Because I had to peek at the solutions, this gets 0 points.

+0p (=4.5p)

### 4
Incorrect, or atleast not the answer they sought out.

+0p (=4.5p)

### 5
Correct.

+9p (=13.5p)

### 6
Correct.
+5p (=18.5p)

### Verdict

Final grade would be below passing.

**new**
*inherited from previous exams*
~~improved~~

#### Strengths
- *Knowing what's being asked, even if I don't know how to do it (I can reference the book)*

#### Neutral
- **Not remembering to use include guards and using declarations**
- **Spotting memory leaks**

#### Weaknesses
- *Pointers and references, when to use them and why*
- *When and where implicit type casts happen (if anywhere?)*
- ~~Not remembering to use include guards and using declarations~~
- *Constructors, copy constructors, destructors, assignment operators*
- *Iterators*
- **lvalue**