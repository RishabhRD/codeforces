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

## Proving techiniques

- If a and b are 2 dependent variables contributing to something, then without
  loss of generality we can define behaviour of a variable and according to
  that behaviour of other variable would be chosen.
