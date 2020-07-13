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

    

