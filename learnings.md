# Learnings

- 1536C: If every partition has same ratio, then combination of some or all
  paritions should also have same ratio. So, let's say we currently have that
  ratio then, maximum number of times we can divide space in that ratio can be
  calculated with storing the frequency of that ratio in hashmap for all the
  prefix.

- 1591D: Dynamic programming with 2 pointers can be powerful. Some times when
  we have O(n^2) time available, we can do something like F(i, j) = F(i + 1, j

  - 1. - f(i, j) kind of stuff

- 1547E: If there is somewhere mod function equation, its easy to break the
  question in two cases. First: where mod evaluates to positive and second where
  mod evaluates to negative. Solve them, and then solve the original question
  with composition function provided.

- 1307C: Series like AP, GP is defined by a pair. i.e., each pair would be part
  of a sequence.

- 1461C: Its easy to calculate the probability of any event pass using 1- all
  events fail.

- 1614C: We define a subset on criteria of including and not including an
  element. Now its a binary criteria and doesn't depend on element in any ways.
  Similary let's say there are only 2 kinds of elements. Now that kind of
  element is included even or odd number of times is also a binary criteria.
  And thus also defines subset. Now there are `2**n` total subsets. There are
  `2**(n - 1)` subsets that does include them. Similarily, there are `2**(n -
1)` subsets that include an element odd number of times. Xor of them should be

1. If that is i bit, then their contribution to sum is (1 << i) _ (1 << (n - 1))
   If that bit is there in any subset, then only it would contribute. That means
   its kind of bitwise or _ (1 << (n - 1))

## Proving techiniques

- If a and b are 2 dependent variables contributing to something, then without
  loss of generality we can define behaviour of a variable and according to
  that behaviour of other variable would be chosen.
