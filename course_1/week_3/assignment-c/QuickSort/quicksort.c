/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

void swap(int ** arr, int lIdx, int rIdx) {
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
void partition(int ** arr, int lIdx, int rIdx) {
    
    // initialize the pivot value: p
    int p = arr[lIdx];
    
    // track where the pivot is: i
    int i = lIdx + 1;  // the index after the given pivot
     
    // track what we've seen so far: j
    int j;
    
    // linear scan with swaps
    for(j = lIdx + 1; j <= rIdx; j ++) {
        
        // if we have looked at elements
        // don't swap until we have seen elements bigger than the pivot
        if (j > i) {
            
            if (arr[j] < p) {
                // swap j and i
                swap(arr, i, j);

                // iterate i - move the pivot to the right once
                i ++;
            }
            // otherwise arr[j] > arr[lIdx], do nothing
            
        }
        
    }
    
    // final swap pivot element with the right-most element less than it
    swap(arr, lIdx, (i - 1));
    
}