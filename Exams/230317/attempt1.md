# 2023-03-17
Attempted 2026-05-31

*Author: Mikael*

Personal rules for this run:
- no help from the compiler (write all code in here)
- external help like search engines is okay, but only if completely stuck. No AI
- help from book is allowed, like on the exam

    however CTRL+F is not allowed, as I cannot do that in real life (if only!)

## Attempt
### 1

#### a)
Correct.

We are retrieving the result of ``make_person``, which is correctly being assigned to a constant reference to ``auto`` (e.g. it does not matter what type). The use of ``p`` correctly matches the ``print`` function as well.

#### b)
Correct.

Practically, this is the same as the previous example.

#### c)
- C++ Primer, Fifth Edition, page 106-109, 136, 587

Correct.

Using ``auto`` in this fashion is okay, even if the return was ``const``, which it isn't in this case. It should not be an issue to then pass through ``t``. Since there is a version of ``print`` that takes a ``unique_ptr`` as input, this is not an issue either. ``teacher::to_string`` should be correctly called, even if the ``unique_ptr`` is of type ``person``. This is because ``unique_ptr`` downs the object contained within it, and it will be used as if it were a variable ``teacher& t``, whereby the override ``to_string()`` would correctly be used.

#### d)
UB.

We cannot cast ``unique_ptr`` to ``teacher``.

### 2
- C++ Primer, Fifth Edition, page 167-168, 216-217

The compiler ordinarily converts an array to the pointer to it's first element. When we are accessing ``arr``, we are therefore seeing the value of a pointer. Since a pointer is just an address, using the address-of operator (&) on it will just return the address again. This explains the first two outputs.

Using ``sizeof`` is context dependent. ``sizeof(arr)`` returns the ``sizeof`` the type contained, times the number of elements in the array. The size of the ``int`` contained is 4, which gives 4*5 e.g. 20. ``sizeof(&arr)`` retrieves the size of the address, which is 8, because addresses are 64 bits, which is 8 bytes.

### 3
- C++ Primer, Fifth Edition, page 163-164

When initializing a ``char`` array, e.g. a ``string``, we usually have to leave room for null termination, or explicitly put it in there. However, one is automatically inserted at the end when using a normal string construction ("text"). So that's all fine and a red herring.

As discussed previously, an array is a pointer, so when we pass ``str`` to ``print``, we're also fine.

The crux is in the loop, as the compiler error suggests. ``=!`` does not mean ``!=`` or some other novel operator, it's going to be interpreted as ``= !``, e.g. "equal to the logical inverse of". That means that we're actually setting ``pos`` to be equal to the inverse of ``last``. For every integer other than 0, this is 0, e.g. false. Since the second field in a for loop is a predicate, that means that the for loop will stop immediately, before even executing once.

### 4
- C++ Primer, Fifth Edition, page 936, 691-692, 466-467, 718

As in a previous exam I've done, it looks like we need to implement an overload of the shift (>>) operator into our ``Time`` class, which we use as the basis for the processing mechanism.

The text is read through by a stream ``is``, which stores each line as we g in ``line``. This ``line`` string is used to create another stream ``ss``, which stores it's sections in ``event``.

I believe the outer stream is to be ignored, because it looks like that loop only runs once. We only need to worry about the inner loop in this example, and I believe ``event`` is to be interpreted as ""xx:xx yy:yy event_name, because ``std::getline`` uses newline (``\n``) as it's delimeter by default. 

xx:xx is the start time, and yy:yy the duration. When a shift operation fails, we are to return false, so that it prints ``[malformed line ignored]``.

We will also need to overload the + operator, and define a way for ``Time`` to be interpreted as a string.

The psuedocode for this will look something like this:
```
procedure shift(stream, time)
    time = empty vector of size 4
    i = 0
    while (stream has character && i < 4)
        if (character is number)
            time[i] = character as int
            i++
        else if (((i == 2 or i == 1) and character != ":") or i == 3)
            return false // Disqualify
        else if (i == 1 && character == ":") // account for time given in h:mm
            time[1] = time[0]
            time[0] = 0

    for (entry in time)
        if (entry < 0 or entry > 9)
            return false
    
    time.hour = time[0] * 10 + time[1]
    time.minutes = time[2] * 10 + time[3]
    return time.hour < 24 && time.minutes < 60
end procedure
```

The above psuedocode can be improved with teachings from page 936:

```
procedure shift(stream, time)
    line
    while(getline(stream, line) not a number) // step through until numbers are reached
        continue
    
    hours
    if (!stream.getline(hours, 2, ":"))
        return false // happens if we do not encounter : within 2 chars
    
    minutes
    if (!stream.getline(minutes, 2, " "))
        return false // happens if we do not encounter a space within 2 chars
    
    time.hour = hour as int
    time.minutes = minutes as int
    return time.hour < 24 && time.minutes < 60
end procedure
```

and then:

```
procedure add(time1, time2)
    time1.hour += time2.hour
    time1.minutes += time2.minutes

    rest = 0
    if ((rest = time1.minutes % 60) != time1.minutes)
        time1.hour++
        time1.minutes = rest
    
    return time1.hour > 24
end procedure
```

and finally:

```
procedure to_string(time)
    return time.hour + ":" + time.minutes
end procedure
```

Now, in C++:

```cpp
// time.h
#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <string>

using std::string;
using std::to_string;

class Time
{
    public:
        Time(int hours, int minutes) : hours{hours}, minutes{minutes} {}
        bool isValid()
        {
            return hours < 24 && minutes < 60;
        }
        friend bool operator>>(const istream& is, Time& time);
        Time& operator+(Time& left, Time& right);
        operator string() const { return to_string(hours) + ":" + to_string(minutes); }
    private:
        int hours;
        int minutes;
}

#endif
```

```cpp
// time.cc

#include <time.h>

using std::string;
using std::stoi;

bool Time::operator>>(const istream& is, Time& time)
{
    string line;
    while(getline(stream, line) != ) // step through until numbers are reached
        continue;
    
    char hours[2];
    if (!stream.getline(hours, 2, ":"))
        return false // happens if we do not encounter : within 2 chars
    
    char minutes[2];
    if (!stream.getline(minutes, 2, " "))
        return false // happens if we do not encounter a space within 2 chars
    
    time.hours = stoi(hours);
    time.minutes = stoi(minutes);
    return time.isValid();
}

Time& Time::operator+(Time& left, Time& right)
{
    left.hour += right.hour;
    left.minutes += right.hour;

    int rest;
    if ((rest = left.minutes % 60) != left.minutes)
    {
        left.hour++;
        left.minutes = rest;
    }

    return left;
}

```

### 5


---



## Assessment

The questions give: 10 + 5 + 5 + 12 + 11 + 7 = 50. Grading scale is (3/25, 4/33, 5/42).

### 1

+0p (=0p)

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