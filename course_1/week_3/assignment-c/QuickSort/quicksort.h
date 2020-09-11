/* 
 * @title: QuickSort Header File
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
