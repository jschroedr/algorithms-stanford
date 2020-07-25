#### Reading I

INTRODUCTION:
    Algorithms in general.

    Why are they important, and how can algorithmic ingenuity improve over straightforward solutions?

    Merge Sort Algorithm
        Practical and famous - everyone should know it
        Good warm up for more intricate material
        Canonical introduction to the "divide and conquer" algorithm design paradigm


ASYMPTOTIC ANALYSIS:
    Big-Oh notation and its relatives
    
    Identify a "sweet spot" of granularity for reasoning about algorithms:
        - Suppress second-order details like constant factors and lower-order terms
        - Focus on how the running time scales as input size grows


### Lecture I

Algorithm is a recipe for solving some computational problem

    - Rearrange numbers in sorted orders
    - Shortest path
    - Optimization / task management


Algorithms are essential for any branch of computer science - at Stanford this course is required for every level of degree the department offers

Play a key role in tech innovation - e.g. search engines are the most famous algorithms (page rank)

Performance gains from algorithms have vastly outpaced gains from processor speed

Provides novel lens on processes outside of comp sci and tech
    - Quantum mechanics, economic markets, evolution
        - Each of these can be thought of in algorithmic terms



### Integer Multiplication

Well defined set of rules to convert two numbers into a product

Define problem, describe input, describe desired output as algorithmic, and then steps to get there

    Input: two n-digit numbers, x and y
    Output: product x * y
        Performance is measured by basic operations performed
        "Basic (Primitive) Operation" defined as add or multiply 2 single-digit numbers
        Measurement: Count these operations as a function of (n) the input length

    "Correct" - the algorithm will provide proper intermediate calculations no matter the input

Measurment:
    4 basic operations (one for each digit of the top number)
    + 4 basic operations to carryover

    <= 2n operations per row of partial product in multiplication
    n rows for each digit of the second argument, y

    Therefore 2n-squared operations to form all the partial products

    We STILL need to add these partial products up

    Final addition required another <=2n-squared partial products

    As we think about input number getting bigger and bigger - the grade-school multiplication strategy (partial products) grows at (const) * n-squared

    Quadratic in the input length, n

    If you double the number of digits for x, and y - you double the input - the number of operations goes up by a factor of 4 (since original x and y are 5678 and 1234)

##### The Algorithm Designers Mantra
"Perhaps the most important principle for the good algorithm designer is to refuse to be content"

"Can we do better?" - when faced with a naive or straightforward solution, it is of paramount importance that you must ask this question



### Lecture II

Algorithm space is surprisingly rich

There are other interesting ways to multiply integers together other than the subproduct method

Karatsuba Multiplication - different multiplication method that is more efficient

    1234 * 5678

    Put into pairs

    (a) 12, (b) 34, (c) 56, (d) 78

    Step 1: compute a * c = 672
    Step 2: compute b * d = 2652
    Step 3: compute (a + b)(c + d) = 134 * 46 = 6164
    Step 4: compute 6164 - 2652 - 672
    = 2840
    Step 5: Step 1 padded with four zeros, Step 2 padded with 0 zeros, and Step 4 with two zeros
    6720000 + 2652 + 284000 = 7006652 (this is correct)

There are fundamentally different ways to do very basic things

Does Karatsuba do better than the third grade algorithm?

#### A Recursive Algorithm

Write x = 10^(n/2)a + b and y = 10^(n/2)c + d
Where a, b, c, d are n/2-digit numbers

a = 56, b = 78, c 12, d = 34

x * y   = (10^(n/2)a + b) * (10^(n/2)c + d)  // AKA: [star]
        = 10^n*ac + 10^(n/2)(ad + bc) + bd

NOTE: if the input is odd, you would decompose one of the input numbers by the first five digits and the latter four digits and proceed in the exact same way

[star] involves four relevant products (ac, ad, bc, bd)

Idea: recusively compute ac, ad, bc, bd, then compute * in the straightforwward way

Then, pad ac with n zeros at the end, then add ad + bc and pad result with n/2 zeros then sum up these three terms (term 3 is bd) (gradeschool addition) for the final output

Base Case: Recursive algorithms need a base case - if the input is sufficiently small then you just immediately compute the answer instead of recursing further

    Two numbers with one digit each you multiply and return the result


#### Karasuba Multiplication

Recall [star]: x * y = 10^n *ac + 10^(n/2)(ad + bc) + bd

Three quantities in [star] that we care about

ad + bc we only care about their sum

Can we get away with three instead of four recursive calls?

    Recursively compute ac
    Recursively compute bd
    Recursively compute (a+b)(c+d) = ac + ad + bc + bd
    Gauss's trick: 3rd - 1st - 2nd (cancels out ac, bd)
        ad + bc
    Upshot: only need 3 recursive multiplications!
        (and some additions)
    
Example of "divide and conquer" algorithsms


### Lecture III

About the course

First half of a 10-week undergraduate course

##### Vocabulary for design and analysis of algorithms
    - "Big-Oh" notation
    - "sweet spot" for high-level reaonsing about algorithms

##### Divide and conquer algorithm design paradigm
    - Will apply to: Integer multiplication, sorting, matrix multiplication, closest pair
    - General analysis methods ("Master Method/Theorem")

##### Randomization in algorithm design
    - Will apply to: QuickSort, primality testing, graph partitioning, hashing

##### Primitives for reasoning about graphs
    - Connectivity information, shortest paths, structure of information and social networks
    Computational primitives are almost free
    Computational primitive - running time is barely more than reading the input
    These should be on-the-shelf waiting to be applied at will!
    (sorting is an example of this)

    Graph has verticies and edges - they model networks
    They are more complicated than arrays, but there are useful primitives for describing them that are blazingly fast

##### Use and implementation of data structures
    - Heaps, balanced binary search trees, hashing and some variants (e.g. bloom filters)

    Balaned binary search trees - keep ordering while enabling querying that runs logarithmic to the size of the set

    Hash Tables - keep track of a dynamic set, while supporting extremely fast insert and lookup queries


#### Topics in Sequel Course

Greedy algorithm design paradigm

    e.g. minimal spanning trees, scheduling

Dynamic programming algortihm design paradigm

    e.g. genome sequence alignment and shortest path

NP-complete problems

    problems that cannot be solved by any computational efficient algorithm

    We will explore:
    
        Fast algorithms for special cases

        Fast exact algorithms for special cases

        Exact algorithms that beat brute-force search


Mathematics explains "why" - good algorithmic ideas require non-trivial mathematical analysis to understand properly

This course should help you start to think algorithmically

Need:
- Programming skills (language does not matter)
- Basic discrete math, proofs induction, etc.
- Basic mathematical notation
- Discrete probability
- Calculus - single integral in the analysis of quicksort

Books:
"Mathematics for Computer Science" by Eric Lehman and Tom Leighton
"Algorithm Design" Kleinberg/Tardos, 2005
"Algorithms", 2006 (Cormen/Lesierson/etc.) FREE
"Data Structures and Algorithms: The Basic Toolbox", 2008 -Mehlhorn/Sanders

NOTE:
Will sometimes propose harder "challenge problems"
    - will not be graded; discuss solutions via course forum


### Lecture IV

Merge sort was known back in 1945

Merge sort is an oldie but a goodie - used all the time in practice

Other reasons to study:
    - Good introduction to divide and conquer
        - Improves over selection, insertion, bubble sorts
        - Most transparent application of the divide and conquer paradigm
        - i.e. Benefits
        - Merge sort is better than most obvious, simple sorting algos
            - i.e. (each of these have quadradic performance (scales at n^2 where n is the length of the array))
                - Selection (repeatedly identify minimum of element you have not looked at yet)
                - Insertion (repeatedly maintain the invariant that the prefix of the array is the sorted version of those elements - after 10 loops those first 10 elements will be in sorted order)
                - Bubble Sorts - identify adjacent pairs are out of order and you do swaps until all are in order

Merge sort discussion may not be easy, but it is at least straightforward

Merge Sort analysis motivates guiding principles for algorithm analysis (worst-case and asymptomatic analysis (rate of growth of an algorithms performance))

Analysis generalizes to "Master Method" - recursion tree method (counting up total operations calculated by an algorithm)


#### The Sorting Problem
Input - array of n numbers, unsorted
Output - same numbers, sortd in increasing order

Elements may or may not be distinct

Assume distinct for theoretical purposes

Recursive Algorithm - calls itself on smaller sub-probems, smaller arrays

Split in half, solve left half recursively, solve right half recursively

(recurse)

Now "merge" - combine the recursed components

Walk pointers down each of the two sub-arrays, populating the main array in sorted order


### Lecture V

Recursively sort 1st half of input array

Base case: input is small enough to return trivial answer

Zero or one elements -> return the elements nothing to sort

Break odd-n arrays into chunks (i.e. 9 to 5 and 4)

How do we "merge"?

Populate the output array by traversing pointers in parellel

In Detail: (merge step)

    c = output array [length = n]
    a = 1st recursive call, left half
    b = 2nd ..., right half

    traverse a and b in parellel

    i=1 is counter for a, j for b
    simple pass through output array populating it in increasing order (always taking the smallest from the union of the two sorted subarrays)

    (!) Realize: the min element that you haven't looked at in a and b must be at the front of one of the two lists

    for k=1 to n
        if a(i) < b(j)
            c[k] = a(i)
        else
            c[k] = b(i)
    # also need to handle when a or b runs out of elements, at which point you just run through the remaining of the other!

#### Merge Sort Running Time
Running time cannot be precisely defined

Imagine you are running in debugger - number of operations (lines of code) - how many lines of code get executed?

Running time for merge based on pseudocode:
    Upshot: running time of merge on array of m numbers is <= 4m + 2
        (loop cost + initialization cost)

    Let's just call it 6m since m >= 1 (for future simplicity)

Lines of code to sort an array?
Number of recursive calls is blowing up exponentially
Every recursive call is on a smaller (half size) array
Explosion of sub-problems, but each are very small

Claim: merge sort requires (6n * log2n + 6n) operations to sort n numbers

Simpler sorting methods are quadratic (e.g. constant times n squared), merge sort needs constant time log n (not n squared)

Logarithm: log base 2 of n = n / 2 (keep repeating / 2 until you get a number lower than 1)

log 2 of 1024 is 10

logarithm is much smaller than the input - looks like a curve that becomes very flat very quick as n grows larger

sorting algorithm with log n is much faster than a runnning time with n squared (benefit from the plateau of the log function)



### Lecture VI

This lecture is a mathematical proof of the claim:

    For every input array of n numbers, Merge Sort produces a sorted output array and uses at most (6n)log(2)n + 6(n) operations


Proof of claim (assuming n = power of 2)

    (will use "recursion tree")

    Write out all of the recursive work in a tree structure where the children of a node are the given calls made by that node

    Tree structure will facilitate the analysis of counting the steps

    Root 0 / level 0 (outer call of mergesort)

    Level 1: left half and right half of input array

    Level 2: quarter of right half and input array

    ... Base Case: Array of Size 0 or 1

    What is the level number where the leaves / base case resides?

        QUIZ: Roughly how many levels does this recursion tree have (as a function of n, the length of the input array)?

        Answer: Log2(n) since the computational steps grows by n * log(2)(n)

        It is not squared because that would be a quadratic algorithm, like one of the more straightforward examples given earlier

        The input size is being decreased by a factor of two with each level of recursion, therefore giving us this log(2) factor

        Diving by 2 until you get at most 1 is the exact definition of the logarithmic base two of n

        Since the first level is 0, the total is actually log base 2 + 1

    
Proof of claim:

    Leaves = base cases

    Single element arrays

    At a given level "J" of this recursive problem, how many distinct sub problems are there?

    For each distinct sub problem, what is the input size?

        Since we start with 2, and each step is (previous step) times two, you could say the number of steps is 2^j

        Since the array is broken by 2 continuously each step, you could say the size of the array is n/(2^j) 

        CORRECT

Key in this analysis is to count work level by level

Work done by 2^j steps of merge sort, not the work they are doing

Merge Sort Code:

    Recursive call

    Recursive call

    Call of Merge

We know that of an array of size m, we will have at most 6m lines of code (previously analysis)


<= 2^j + 6(n/2^j)

Number of level-j subproblems + subproblems size at level j times number of lines of code for merge sort subroutine (6, from previous lesson)

2^js cancel each other, and we get an upper bound 6n independent of level J (regardless of the level we are at)

There is a perfect equilibrium between two competing forces - we are creating more subproblems at the same rate that each subproblems size is getting smaller

The amount of work is independent from any level, overall bound becomes simpler

<= 6n (log2(n) + 1)
Work per level * # of levels


Claim: for every input array of n numbers, Merge Sort produces a sorted output array and uses at most (6n)(log2(n)) + 6(n) operations


### Lecture VII

Guiding Principles of Analysis of Algorithms


1: Worst Case Analysis

Our analysis from the last lecture makes no assumptions about the input or what it looks like. 

The worst our algorithm could do as an expression of n

(alternatives are average case analysis and benchmarks)

Average Case Analysis: take the average running time under some assumption about the relative frequencies of inputs

Benchmarks: One agrees of some set of benchmark inputs that are assumed to be typical for the algorithm

Each of these alternatives require domain knowledge

Worst case analysis is appropriate for general purpose subroutines

Worst case analysis is mathematically more tractable - it is usually easier to analyze


2: Won't pay much attention to constant factors, lower-order terms

In our analysis of merge sort, we discussed lines of code in rough terms (4n + 2 became 6n for ease of computation, as a sloppy upper bound)

Don't worry about small changes to the constant factor

Why?
    - way easier mathematically
    - given the level at we are describing and analyzing algorithms at in this course, it would be inappropriate to street unduly about what the constant factors are

    Our algorithms are written in psuedocode - lines of code are ambiguous given how you count different low level computations (i.e. how do you count loop increments?)

    Depending on the language, the lines will deviate further. When the program is compiled into machine code, it deviates further.

    Because we describe algorithms at a level that is language independent, constants (lines of code) don't really matter 

    3: lose very little predictive power (we can get away with it)

        (as we will see)


3: We will focus on the case of the large input sizes - how does the algorithm handle large input sizes?

    e.g. merge sort is better than insertion sort independently of constant factors due to logarithmic versus quadratic functions

    6nlog2(2) + 6n < 1/2(n)2

    The bias is that we are focusing on problems with large n

    Small problems are not worth algorithmic analysis


Is is worth it?

    Even with Moore's Law, our computational ambitions will grow

    So even with faster computers the logarithmic vs quadradic difference will grow larger

        e.g. Running time is proportional to computational increase means computers that are 4x faster computer lead to 4x running time increase

        Running time is proportional to computational increase squared means that 4x faster computer leads to only 2x running time increase



NOTE: small n might lead less scale-able algorithms to be temporarily faster (i.e. insertion sort vs merge sort)

Below 90 inputs insertion sort is faster, above 90 merge sort is faster

At 1500 input size (still small), the difference in running time is 10x, that is insertion sort takes 10x longer than merge sort

The gap becomes huge at scale

You should not be ignorant of constant factors, however

Many optimized programming libraries, they will use algorithm based on problem size



What Is a Fast Algorithm?

fast algo = worst case running time grows slowly as a function of the input size

note: left side is not a mathematical surrogate while right side is

we are looking for the "sweet spot"
mathematical tractability AND predictive power
    - prove theorems while still having predictive power that what the theory advocates will be fast in practice

holy grail: linear time algorithm - number of instructions grows proportional to the input size (not always possible, but the best case scenario - notably better than merge sort)

adopt the three principles as guides to being "fast"


Next series of videos:

formal description of asymtotic + big o notation

more experience applying divide and conquer to problems


## Asymptotic Analysis

The language by performance of algorithms is discussed

### Lecture VII

Motiviation: basic vobab for discussing the design and analysis of algorithms

By no means math for math's sake

Programmers will often say - code x runs in o of n time, and code y runs in o of n-squared time

    "Big Oh" notation

Vocabulary provides a sweet-spot for high-level reasoning about algorithms

Coarse enough to suppress architecture/language/compiler-dependent details

Sharp enough to make useful comparisons between different algorithms (especially for large inputs, the ones that require analysis)

    (i.e. differentiate between better and worse sorting, multiplication, etc.)


#### High Level Idea: "Suppress constant factors and lower-order terms"

Long term if you only remember seven words, remember above^

Lower-order terms become increasingly irrelevant as you focus on large inputs

Constant factors are highly dependent on the environment (too system-dependent)


Example:

    Merge Sort Running Time: 6n * log2 * n + 6n (upper bound)

    n = input length

    Lower Order Term: 6n, growing more slowly than n log(2) n

    Leading Constant Factor: 6

    Drop those two and you get nlog(2)n

    Terminology: running time is Big-O (O) nlogn

#### Big-O of some function = after you've dropped lower order terms and leading constant factor this is what you are left with

When you think about high-level algorithmic comparisons, asymptotic analysis is often the right tool for giving guidance on what will perform better

Once you've committed to the solution, you will want want to optimize the leading constant factor and optimize lower order terms

##### Example: One Loop

    Problem: does array A contain the integer t?

    Given A (array of length n)
    and t (an integer)

    Check each member of the array, if found return true, else return false

    Big-O Notation: (O)n - aka linear of the input length n

    Lines of code executed (worst-case) depends directly on the input length

    Constant number of code lines executed per item in the array (and that constant again, depends on environmental factors)


##### Example: Two Loops

given A, B (arrays of length n)
and t (an integer)

Return true if found false if not

Big O Notation: O(n) - again linear instructions per input n

The number of operations increases, but the relationship to n does not change

This number of operations is a constant that gets suppressed, yielding the same answer for this and the previous example


##### Example: Two Nested Loops

Problem: do array A, B have a number in common?

given arrays A, B of length n

Big O: (O)n^2 - quadradic time algorithm

If you double the input length, the running time will go up by a factor of four

e.g. 2 arrays of len 2 leads to 4 operations, 2 arrays of len 4 leads to 16 operations (worst-case scenario)

For each fixed choice of i(a) and (j)b we do a certain number of operations, the difference is that we perform n-squared iterations total

Note that in the first example we had one for loop completing before another, leading to 2n operations overall (and therefore linear running time)

In other words, for each (n) iterations of the outer for loop, we do (n) iteration of the inner for loop. This gives the n*n (or n^2)


##### Does array A have duplicate entries?

Given array A of length n

Instead of checking entries across arrays, we are checking entries within the same array

NOTE: we start the inner loop (j) at (i+1). Starting j at 0 would lead to an incorrect output because eventually j would equal i, and given that there is only one array that code would report false positives about finding duplicates (it would find the same entry twice)

We also start at i+1 because you only need to compare two entries once. Starting at 0 and skiping when j==i would be wasteful


Big-O: (O)n^2

Running time of this code it is proporational to the running time of the double for loop

We saved iterations versus the previous code, but that is suppressed as a low level factor

Long story short, we still get a quadradic dependence on the input length n



### Lecture VIII

Big O Notation

Big O Notation defines functions that work on the positive integers T(n)

6 + T(n) = function on n = 1, 2, 3, ...

(usually the worst-case running time of an algorithm)

T(n) semantics will typically always be the same

Q: when is t(n) = O(f(n)) where f(n) is nlog(2)n

A: it eventually (for al sufficiently large n), T(n) is bounded above by a constant multiple of f(n)

(picture shows T(n) bounded lower by F(n) and upper by 2F(n))

#### Formal Definition: 
T(n) = O(T(n))  // T of n is equal to Big-O T of N
if and only if there exist constants c, n(0) > 0 such that T(n) <= c * f(n)
for all n >= n(0)

c = quantifies the constant multiple of f(n)

n(0) / n-naught = qualifies that n is sufficiently large (threshold beyond which we assert that f(n) and 2f(n) bound T(n))

In english: we are demonstrating our preference for large inputs in Big O notation of f(n) (T(T(n)) and formally qualifying what input n and constant c are required for this definition

C is 2 in the example (2F(n)), n-naught (n(0)) is the crossing point between t(n) and 2f(n)

In english: C is the constant of the upper bound, and n(0) is the lowest n that is sufficiently large to demonstrate 2f(n) as an upper bound

Prove something is Big O of f(n) is that you exhibit these two constants c and n(0), and it better be the case that for all cases n >= n(0), c * f(n) upper bounds T(n)

It is like you are playing a game, you want to prove that the inequality holds (and opponent is trying to disprove you). You must pick a strategy in choosing a constant c and n(0) that will hold this inequality and your opponent is not allowed to pick an n lower than n(0).

If you have no winning strategy, then it is not Big O of f(n)

e.g. you lose if your opponent can flip this inequality by picking a suitably large value of n

##### Warning: c, n(0) must be independent of n

N should not appear anywhere in your c, n(0) constant definition

Summary: You want to have a bound above for sufficiently large numbers n in order to prove that T(n) is Big O for f(n)


### Lecture IX

Examples

1: 
    Prove formally that if t(n) is some polynomial of degree k

    t(n) = O(n^k)

    Proof: (with constants pulled out of a hat, pre-provided)

    Choose n0 = 1 and c = (sum of absolute values of the coefficients)

    Need to show that n >= 1, T(n) <= c * n^k


2:

    For every k >= 1, n^k is not O(n^k-1)

    (testing that there is no collapse of the poly)

    Proof: by contradiction (prove what you are trying to establish is false)

    Suppose: n^k = O(n^k-1)

    Then 2 constants such that sufficiently large n results in c * nk-1 > n^k

    Cancel n^k-1 from both sides of the inequality (legit since n >= 1)

    n is at most constant c for n >= n(0)

    c + 1 is not bigger than c


### Lecture X

Big O - upper bound or "worst case scenario"

Big Omega - lower bound or "best case scenario"

Big Theta - the tight bound to a function (greater accuracy and meaning than Big-Oh or Big-Omega because it's mathematical definition is more accurate)

Big Theta is the bound that matches closest to the behavior of an algorithm

In industry, this is the most commonly used form of asymptotic algorithm analysis


Example:

T(n) = (1/2)n^2 + 3n

T(n) is a quadratic function, its best case scenario (Big Omega) would be to be linear 

Therefore, Big Omega = Omega(n)

A valid worst-case scenario, though not entirely accurate, could be n^3, since a quadradic function cannot be worst than n^2

Therefore, Big O = O(n^3)

A valid Theta value, a function that accurately depicts actual running time, would be n^2, since the constant drops and the linear term is ignored in big-oh notation due to our focus on the functions impact as n grows large

Prove this by using appropriate constants 

Omega = n0 = 1, c = 1/2
Theta = n0 = 1, c1 = 1/2, c2 = 4
Oh = n0=1, c = 4 


For reference, Little-Oh

Strictly less than relation

Means one function is growing stricly less than another

We have to prove for every constant c, no matter how small, we have to prove that there is some large enough n0 that is bounded above by o(f(n))

i.e. n^k-1 = o(n^k)



### Reading http://discrete.gr/complexity/

Algorithm complexity is something designed to compare two algorithms at the idea level

Algorithsm are programs that perform just a computation, and not other things computers often do like i/o

Complexity analysis allows us to measure how fast a program is when it performs computations.

Complexity analysis is also a tool that allows us to explain how an algorithm behaves as the input grows larger.

#### Counting Instructions

Assume each of these operations costs one "fundamental instruction":

- Assigning a value to a variable
- Lookup up the value of a particular element in the array
- Comparing two values
- Incrementing a value
- Basic arithmetic operations such as additino and multiplication

Branching (if... else) occurs instantly without cost

var m = a[0];  // two instructions, one for assignment and one for looking up a[0]

For loops are two instructions for the first pass:

i = 0;  // assignment
i < n;  // comparison

Each additional loop will cost two instructions as well

i ++;  // assignment
i < n;  // comparison

This code's instructions, without considering the loop body, can therefore be described as 4 + 2n:

var m = a[0];

for (var i = 0; i < n; i++) {
    if(a[i] >= m) {
        m = a[i];
    }
}
    
4 fundemantal instructions at minimum (initialize m with a[0], and start for loop)
PLUS two instructions for each iteration (increment and compare i)

4 + 2n is a mathematical function (f(n)) that gives the number of instructions the algorithm needs given the n

f(n) = 4 + 2n 

#### Worst-Case Analysis

If we consider whether a logic branch may or may not be triggered and the instruction cost that entails, our ability to accurately calculate f(n) is not as easy. Therefore wost-case analysis exists

When does our algorithm need the most instructions to complete?

With the above code, if we are given an array with values in increasing order, our worst-case scenario is 4 lines of code in the for loop body plus the cost calculated earlier (initialization and for loop startup)

f(n) = 4 + 2n + 4n = 6n + 4

Again, this function "f" gives us "n" which is the number of instructions that would be needed in the worst case.

#### Asymptotic Behavior

We will now run "f" through a "filter" which will help us get rid of those minor details that computer scientists prefer to ignore

If an algorithm beats another algorithm for a large input, it is probably true that the faster algorithm remains faster when given an easier, smaller input.

###### From the terms that we are considering, we'll drop all the terms that grow slowly and only keep the ones that grow fast as n becomes larger

6n + 4

4 remaings 4 no matter the input size, so drop it

f(n) = 6n

6n is really a constant multiplier of n - the amount of instructions per loop may vary depending on the environment. Therefore 6n becomes n

f(n) = n

