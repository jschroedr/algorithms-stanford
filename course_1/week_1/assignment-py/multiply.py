


def karatsuba(x: str, y: str) -> int:
    # first, case the inputs to ensure both are of type str
    x = str(x)
    y = str(y)

    # next, calculate the initial input lengths (and the max input length, n)
    x_len = len(x)
    y_len = len(y)

    # if they are both one, simply return basic arithmetic
    if (x_len == 1 and y_len == 1):
        return int(x) * int(y)

    # otherwise, normalize the input lengths of both   
    # ensuring equal length
    if x_len < y_len:
        x = _karatsuba_zero_pad(num=x, digits=y_len - x_len, left=True)
        n = y_len
    elif y_len < x_len:
        y = _karatsuba_zero_pad(num=y, digits=x_len - y_len, left=True)
        n = x_len
    else:
        n = x_len  # they are equal so it does not matter

    # ensuring length % 2 == 0
    if n % 2 != 0:
        x = _karatsuba_zero_pad(num=x, digits=1, left=True)
        y = _karatsuba_zero_pad(num=y, digits=1, left=True)
        n += 1

    j = n // 2 if n % 2 == 0 else (n // 2) + 1

    # calculate the amount of zero padding b and a will need, respectively
    # this is a replacement to performing 10 ** n or 10 ** n/2 calculations
    b_zero_padding = n - j
    a_zero_padding = b_zero_padding * 2
    
    # slice the now normalized inputs
    a = int(x[:j])
    b = int(x[j:])
    c = int(y[:j])
    d = int(y[j:])

    # recursive calls to solve the first two sub-problems
    ac = karatsuba(x=a, y=c)
    bd = karatsuba(x=b, y=d)

    # k: temporary variable used in solving the third subproblem
    k = karatsuba(
        x=a + b,
        y=c + d
    )
   
    # pad the results for the terms which require exponential multiplication
    # note that we pad the right to achieve the exponential equivalent
    a_result = int(_karatsuba_zero_pad(str(ac), a_zero_padding, False))
    b_result = int(_karatsuba_zero_pad(str(k - ac - bd), b_zero_padding, False))

    return a_result + b_result + bd

def _karatsuba_zero_pad(num: str, digits: int, left: bool):
    return ('0' * digits) + num if left else num + ('0' * digits)
