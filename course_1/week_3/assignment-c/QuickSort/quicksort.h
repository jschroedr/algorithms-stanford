/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   quicksort.h
 * Author: jake
 *
 * Created on August 27, 2020, 8:15 PM
 */

#ifndef QUICKSORT_H
#define QUICKSORT_H

#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* QUICKSORT_H */

int choosePivot(int * arr, int n, int problem);
void swap(int * arr, int lIdx, int rIdx);
int partition(int * arr, int lIdx, int rIdx);
void quicksort(int * arr, int n, int problem, int * tcmp);
