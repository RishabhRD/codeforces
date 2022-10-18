# Codeforces Educational Round 137 Problem D Explanation

## Problem

Given a binary string, choose any 2 (maybe same or intersecting) substrings of
that binary string such that the OR of 2 substrings are maximum. Return the OR
string of 2 substrings.

Returned string shouldn't contain prefix 0s.

Constraints:
- 4 <= n <= 1e6
- Each character of string can be 0 and 1
- For each character of string, 0 and 1 are equally probablistic and randomly chosen.

## Observations

### => Prefix zeros are of no use

```
0001010
```

Here we take any 2 substrings

```
0001010
  01010
```

prefix zero would always be zero in result string and thus would be trimmed.

**STEP 1: So remove prefix zero first**

### => Result string length would be same as given string

**After trimming prefix zeros**, result string length should be same as
given string.

Why?

- It's not possible to create bigger string with bitwise OR

- If we create a smaller string as result, given string str itself is bigger than that \(i.e., ans = str \| str\)

**STEP 2: s1 = str**


Now, bruteforce starts with considering all possible substrings for s2.
But, this gets TLE.
So, we need to observe more.

### => Only need to consider prefix substrings

For any substring \[i, j\], it's better to consider \[0, j\]

Always `(s1  OR [0, j]) >= (s1  OR [i, j])`

Example:
```
11010111001
```
Let's say we consider `1110` substring.
Then considering the prefix substring would give us greater OR.
```
11010111001

11010111001
       1110 (with substring)
-----------
11010111111

11010111001
  110101110 (with prefix substring)
-----------
11110111111
```
And this is obvious because of the fact that prefix substring would have more
bits to OR so more chances of greater OR.

(**WARNING**: It's not same as considering suffix \[i, n - 1\] as it would change the bit position)

So, now we are able to convert our O(n^2) time for calculating all s2 to O(n) time.

### => Only need to consider prefixes that make leftmost zero 1

All prefixes that doesn't make leftmost zero 1 (after OR with s1) would
have smaller OR than the ones that do that and hence, doesn't count in
result.

Example:
```
11010111001

11010111001
  110101110
-----------
11110111111

11010111001
   11010111
-----------
11011111111
```
Clearly the one, that makes leftmost zero one is greater because it has more binary weight.

Thus if leftmost zero is at kth index, we only need consider k prefixes of length \[n - 1, n - k\]

So, we reduce the substring finding time from O(n) -> O(k)

But why this fact is important?
Because it's given that each character of string is randomly chosen. So, there is very less probablity
that this k would big as n (i.e., 1e6) because there are 50% chances of getting a 0 for each character.
So, in string k would surely be low like 25, 26 something.

So, for average case: O(k) ~ O(1)

For worst case: O(k) = O(n)

but because we are given that the string is randomly built, we don't need to consider worst case and consider
average case.

## Algorithm

With all this observations, algorithm is simple as:

- str = trim(given_string)
- s1 = str
- for all possible prefix substring s2 that makes leftmost 0 in s1 1, candidate = s1 ^ s2
- return max of all candidates calculated

Code snippet:
```cpp
#include <algorithm>
#include <iostream>

template <typename T> T read() {
  T t;
  std::cin >> t;
  return t;
}

// precondition: a.len() <= b.len()
std::string string_or(std::string_view a, std::string b) {
  std::transform(std::crbegin(a), std::crend(a), std::crbegin(b),
                 std::rbegin(b), [](auto a, auto b) { return a | b; });
  return b;
}

auto trim(std::string str) {
  auto const first_zero = std::find(std::begin(str), std::end(str), '1');
  str.erase(std::begin(str), first_zero);
  return str;
}

std::string solve() {
  auto const _ = read<int>();
  auto const str = trim(read<std::string>());
  if (str.size() == 0)
    return "0";
  auto const first_zero_idx = std::distance(
      std::begin(str), std::find(std::begin(str), std::end(str), '0'));
  std::string_view s = str;
  auto const n = std::size(str);
  auto max = str;
  for (int i = 1; i <= first_zero_idx; ++i) {
    max = std::max(max, string_or(s.substr(0, n - i), str));
  }
  return max;
}

int main() { std::cout << solve() << std::endl; }
```

## Time Complexity

`string_or` and `std::max` takes O(n) time.

Loop \[1, first_zero_idx\] takes O(1) time **on average**.

Thus time complexity is O(n) **on average**.
(This is what this question expects due to random strings.)

Worst case time complexity is O(n ^ 2).
