# Proving greedy solutions

## Problem statement

Given coin denominations of 1, 5, 10, 25. Give an algorithm, that can
break a given currency using these denominations in minimum possible coins.

## Greedy apprach

Algorithm: Choose biggest possible coins as much as possible.

Let's first do **Probing Optimal Solution**. It's a technique to get to know
the properties, optimal solution has.

So in probing, we do claim that optimal solution has these properties and then
prove the claim by **Proof By Contradiction**.

### Properties of optimal solution

#### We can't have more than two 10 coins

Proof: For every three 10 coins we can replace them with
a 25 coin and a 5 coin. That is better than having three 10 coins.

Proved.

#### We can't have more than one 5 coins

Proof: For every two 5 coins, we can replace them with one 10 coin. So, that's
better.

Proved.

#### We can't have more than four 1 coins

Proof: For every five 1 coins, we can replace them with one 5 coin. So, that's
better.

Proved.

#### We can't have two 10 coins and one 5 coins at same time

Proof: They total make up to 25. And better to use one 25 coin.

Proved.

#### 10, 5, and 1 coin sum can maximum sum up to 24

Proof:

- Case 1: We maximize the number of 10 coins (that can be 2), then we can't
  have 5 (proved above) and we maximize 1 coins (that can be 4).
  So, 10 \* 2 + 1 \* 4 = 24.

- Case 2: We maximize the number of 5 coins (that can be 1), then possible 10
  coins are 2 only (because of proved above) and we maximize coin 1 (that is 4)
  Then, they sum up to: 10 \* 1 + 5 \* 1 + 1 \* 4 = 19.

Proved.

### Proof

Let's define:

- O\* : Any optimal solution.
- G : Greedy solution.

Greedy solution is not arbitary.
So, in this case, if we are currently processing the largest coin in greedy
algorithm, there can't be any optimal solution that has more largest coin
than greedy solution. (As described by behavior of algorithm).

Let:

- q: #25 in O\*
- q': #25 in G

So, from algorithm, we always know that q' >= q

#### Claim: q' is always equal to q

Proof by contradition:

Suppose q' > q.

But not possible because for every 25 of greedy solution, optimal solution must
have used 1, 5 and 10 coins. But we proved that optimal solution can't make
more than 24 with these coins.

Proved.

Let:

- d : #10 in O\*
- d' : #10 in G

Now, we have used maximum possible 25 (in both optimal(proved above) and greedy),
So, now d <= d'

#### Claim: d == d'

Proof by contradition:

Suppose d < d'.

But not possible. As for every extra 10 in d', solution must have used 1 and 5.
And we have proved we can have no more than four 1s and one 5, that sum ups to 9. So, not possible.

Proved.

Let:

- n : #5 in O\*
- n' : #5 in G

Because optimal solution takes same 25 and 10 that is maximum possible 25 and 10
as of greedy (proved above). So, now n <= n'

#### Claim: n == n'

Proof by contradiction:

Suppose n < n'.

But not possible. As for every extra 5 in n', it must have taken some 1. But
we can have only four 1s, that only sums upto 4. So, not possible.

Proved.

Let

- p : #1 in O\*
- p' : #1 in G

If q == q' && d == d' && n == n' => p == p'.

So, proved that greedy solution always takes same path as optimal solution.

So, O\* = G

And we also proved that optimal solution is unique.

## Problem Statement

Given 2 vectors a, b of size k, rearrange the components of vectors to minimize
the dot product.

```
dot product = sum_on(0, k - 1)(a[i] * b[i])
```

a = <-3, 4, 2>
b = <1, -4, 11>

dot = 3

So, here its all about pairing the components. Order doesn't matter.

So, let's sort the components first vector and we need to come up with a
optimal sorting order of second vector.

And one strategy can be sorting the other vector components in descending
order. And it works.

But we need to ask for the proof.

### Algorithm

Given X = \[x1, x2, ..., xk\], Y = \[y1, y2, ... yk\], where
x1 <= x2 <= x3 <= ... <= xk.

We need to sort Y components in descending order.

### Proof

So, for all i, j st i < j:

xi <= xj

And we claim: yi >= yj for optimal solution.

Let's suppose: yi < yj

Then d = xi yi + xj yj

But if we swap yi and yj

Then d' = xi yj + xj yi

```
d - d' = xi (yi - yj) - xj (yj - yi)
       = (xi - xj) (yi - yj)

xi - xj <= 0
yi - yj < 0

Thus (d - d') >= 0

=> d > d'
```

Thus swapping is better.

So, swapping decreases cost.

So, we know that if there exists any yi yj st yi < yj, then we can swap them
to have better cost. So, our greedy solution would be as good as any optimal
solution. (here we can see that we didn't prove optimal solution is unique).

And because there is no ambiguity in in ordering, we proved it using
**Exchange Arguments**.

## Exchange argument

Using exchange argument, we first show through an exchange that, exchanging
is better. And through a series of exchange on optimal solution, the
cost is always staying the same or going down. So, its kind of mathematical
induction with proof by contradiction involved for help.

Let

```
G = [g1, g2, g3, ..., gn]
O* = [o1, o2, o3, ..., on]
```

1. Label the solution
2. Compare the 2 solutions. We look for the differences. What properties
   greedy have and optimal doesn't and what properties optimal have greedy
   doesn't. In sequence if {s1, s2, ... , si .. sj .. sn}
3. With those properties, if our greedy solution suggests swapping si and sj
   decreases the cost or maintain it the same, then swap it.

   So, with swaps it goes like:

   ```
   O* >= O1* >= O2* >= ... >= Om* = G
   ```

   So, O\* >= G. And O\* should have least cost thus, O\* = G

## Problem statement

Its about a coding platform. We have problems there. Each problem is a tuple:

```
Pi = (mi, di, ti)
```

- mi: maximum(initial) reward of problem
- di: decay rate of reward per second
- ti: time needed to solve that problem

We can skip some problems too. So, in what order we need to solve the problem
such that we get the maximum reward.

Simplification: Let's assume currently that we are gonna solve all the problems.
so, now we just need to come up with an order that leeds to have maximum
reward.

So, here I know, if there was some optimal ordering, I can sort by that
optimal ordering. Just that I don't know what that property is.

So, we can use exchange argument to discover the property to sort by.

Tip: Explore the cost exchange when, you change 2 orderings then what swapping
did to the result.

So, now, in the current problem we have this scenario:

Let's say we have 2 problems P1 and P2 that we need to figure out, which one
should be solved first. We assume the second solved problem would come just
adjacent next to first one. (And by many swaps like that, we can show that it
would be optimal ordering that also covers distant element)

Let's say we solved P1 then P2 then total reward is going to be:

```
r1 = m1 - d1 t1 + m2 - d2 (t1 + t2)
```

And if we solved P2 first then total reward is going to be:

```
r2 = m2 - d2 t2 + m1 - d1 (t1 + t2)
```

So, we want to see when does: r1 >= r2

or, r1 - r2 >= 0

```
r1 - r2 >= 0
=> d1 t2 - d2 t1 >= 0 (By putting values)
=> d1 t2 >= d2 t1
```

So comparator is: d2 t1 < d1 t2

So, solution goes like:

1. Sort by the optimal criteria
2. Run dynamic programming solution (for what problems to take and what not)
   Kind of knapsack style DP.
   ```
   State: which problem I am on, what time we have used till now.
   Transition: solve problem or skip problem
   ```
