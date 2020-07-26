import sys

from multiply import karatsuba
DEBUG = False

def main() -> None:
    if DEBUG:
        num_1 = '1234121232'
        num_2 = '4321121232'
    else:
        num_1 = '3141592653589793238462643383279502884197169399375105820974944592'
        num_2 = '2718281828459045235360287471352662497757247093699959574966967627'

    result = karatsuba(num_1, num_2)
    true_result = (int(num_1) * int(num_2))
    assert int(result) == true_result, str(int(result)) + ' ' + str(true_result)
    print('SUCCESS: {}'.format(result))
    return


if __name__ == '__main__':
    main()
