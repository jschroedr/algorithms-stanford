/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


/**
 * swap
 * ===========================================================================
 * 
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
 * 
 * Running time = O(n), where n = rIdx - lIdx + 1 is the length of the input
 * array
 * 
 * @param arr
 * @param lIdx
 * @param rIdx
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
    
    return i;
}


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


void incrementTotalComparisons(int m, int * tcmp) {
    *tcmp = m == 0 ? *tcmp : *tcmp + (m - 1);
}

void quicksort(int * arr, int n, int problem, int * tcmp) {
    
    // base case: return if input length is less than or equal to 1
    if(n <= 1) {
        return;
    }
    
    // choose a suitable pivot to partition by
    int p = choosePivot(arr, n, problem);
    
    // swap the pivot index with the first element
    if(p != 0) {
        swap(arr, 0, p);
    }
    
    // partition arr around p
    p = partition(arr, 0, n - 1);
    
    // handling for when p == 2
    p = p == 2 ? 1 : p;
    
    // calculate the subarray size: m
    int m;
    
    // recursively sort first part and add to total comparisons
    m = p;
    incrementTotalComparisons(m, tcmp);
    quicksort(arr, p, problem, tcmp);
    // recursively sort second part and add to total comparisons
    incrementTotalComparisons(m, tcmp);
    quicksort(&arr[p], n - p, problem, tcmp);
}

