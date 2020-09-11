/* 
 * @title: QuickSort Source File
 * @author: Jake Schroeder 
 * @license:     
 *      This file is part of "QuickSort Algorithm in C" 
 *  
 *      "QuickSort Algorithm in C" is free software: you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation, either version 3 of the License, or
 *      (at your option) any later version.
 * 
 *      "QuickSort Algorithm in C" is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 * 
 *      You should have received a copy of the GNU General Public License
 *      along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/**
 * swap
 * ===========================================================================
 * Helper function to make an in-place swap using a constant amount of 
 * memory.
 * 
 * @param arr
 * @param lIdx
 * @param rIdx
 */
void swap(int * arr, int lIdx, int rIdx) {
    // copy by value into the local memory: temp
    int temp = arr[lIdx];
    
    // copy rIdx into lIdx (by value)
    arr[lIdx] = arr[rIdx];
    
    // copy temp back into rIdx
    arr[rIdx] = temp;
    
}

/**
 * partition
 * ===========================================================================
 * Running time = O(n), where n = rIdx - lIdx + 1 is the length of the input
 * array
 * 
 * @param arr: integer array
 * @param lIdx: lower bound index of the array to start from
 * @param rIdx: upper bound index of the array to end at
 */
int partition(int * arr, int lIdx, int rIdx) {
    
    // initialize the pivot value: p
    int p = arr[lIdx];
    
    // track where the pivot is: i
    int i = lIdx + 1;  // the index after the given pivot
     
    // track what we've seen so far: j
    int j;
    
    // linear scan with swaps
    for(j = lIdx + 1; j <= rIdx; j ++) {

        if (arr[j] < p) {
            // swap j and i
            swap(arr, i, j);

            // iterate i - move the pivot to the right once
            i ++;
        }
        // otherwise arr[j] > arr[lIdx], do nothing
        
    }
    
    // final swap pivot element with the right-most element less than it
    swap(arr, lIdx, (i - 1));
    
    return i - 1;
}

/**
 * choosePivot
 * ===========================================================================
 * Chooses an appropriate pivot value (by index) given a suitable problem
 * type. See "quicksort" for definition of acceptable problem types
 * 
 * Note that problem type 3 will be chosen if problem is not one of the 
 * accepted values
 * 
 * @param arr: integer array
 * @param n: length of integer array
 * @param problem: problem type, one of (1, 2, 3)
 * @return index of the pivot value to use
 */
int choosePivot(int * arr, int n, int problem) {
    if(problem == 1) {
        // problem 1: always use the first element of the array
        return 0;
    } else if (problem == 2) {
        // problem 2: always use the final element of the array
        return n - 1;
    } else {
        // problem 3

        // consider the first, middle and last element of the array
        int first = arr[0];
        int last = arr[n - 1];

        // if n is odd, take the split + 1 : otherwise take the split
        int middleIndex = n % 2 == 0 ? n / 2 : n / 2 + 1;
        middleIndex --;  // make it zero-indexed
        int middle = arr[middleIndex];
        
        // identify which element is the median (between the other two)
        // and return its index as the pivot
        if ((first < middle && middle < last) || (last < middle && middle < first)) {
           return middleIndex; 
        } else if ((middle < first && first < last) || (last < first && first < middle)) {
           return 0; 
        } else {
           return n - 1;   
        }
    }
}

/**
 * incrementTotalComparisons
 * ===========================================================================
 * Increments value of total comparisons as a function of n
 * 
 * @param m: length of the given (sub) array
 * @param tcmp: pointer to the value of total comparisons
 */
void incrementTotalComparisons(int m, int * tcmp) {
    *tcmp = m == 0 ? *tcmp : *tcmp + (m - 1);
}

/**
 * 
 * quicksort
 * ===========================================================================
 * Quickly sorts an integer array by strategically choosing pivots
 * based on problem type. Total comparison count is stored in tcmp,
 * and the supported problem types are:
 * 
 * - 1: always choose the first item in any given sub-array as the pivot
 * - 2: always choose the last item in any given sub-array as the pivot
 * - 3: take the median between the first, middle, and last items and use
 *      the index of that value as the pivot
 * 
 * @param arr: integer array, unsorted
 * @param n: length of integer array
 * @param problem: problem type, one of (1, 2, 3)
 * @param tcmp: pointer to the value for "total comparisons"
 */
void quicksort(int * arr, int n, int problem, int * tcmp) {
    
    // base case: return if input length is less than or equal to 1
    if(n <= 1) {
        return;
    }
    
    // choose a suitable pivot to partition by
    // @internal this takes into consideration problem type
    int p = choosePivot(arr, n, problem);
    
    // swap the pivot index with the first element
    // @internal we do not swap is p is 0 because that is unnecessary
    // p in this case is already where it needs to be
    if(p != 0) {
        swap(arr, 0, p);
    }
    
    // partition array, arr, around pivot, p
    p = partition(arr, 0, n - 1);
    
    // increment the total comparisons, tcmp, as a function of n
    incrementTotalComparisons(n, tcmp);
    
    // calculate the subarray size: m
    int m;
    
    // recursively sort first part and add to total comparisons
    // @internal we know p is the index we should STOP at for the first 
    // sub-array, and therefore it makes for a fine n
    quicksort(arr, p, problem, tcmp);
    
    // recursively sort second part and add to total comparisons
    // @internal we want the total length minus the index AFTER p
    // because p is not included in these recursive sub-arrays
    m = n - (p + 1);
    quicksort(&arr[p + 1], m, problem, tcmp);
}

