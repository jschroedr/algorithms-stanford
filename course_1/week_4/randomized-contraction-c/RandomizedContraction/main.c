/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: jake
 *
 * Created on October 14, 2020, 8:08 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "contract.h"


int vcheckExists(char * val, vertex ** vertices, int * vlen) {
    for(int i = 0; i < *vlen; i ++) {
        if(strcmp(vertices[i]->val, val) == 0) {
            return i;
        }
    }
    return -1;
}


vertex ** vCreate(char * val, int valLen, vertex ** vertices, int * vlen) {
    char * cpy = malloc(sizeof(char*) * (valLen + 1));
    strncpy(cpy, val, valLen + 1);
    vertex * v = malloc(sizeof(*v));
    v->elen = 0;
    v->val = cpy;
    v->edges = malloc(sizeof(edge));
    vertices = realloc(vertices, (*vlen + 1) * (sizeof(vertex*)));
    if (!vertices) {
        perror("struct allocation failure");
        exit(EXIT_FAILURE);
    }
    vertices[*vlen] = v;
    *vlen = *vlen + 1;
    return vertices;
}


// TODO: need to return vertices AND the index to which we should extract the created vertex
vertex ** vCheckAndCreate(int * vidx, char * val, int valLen, vertex ** vertices, int * vlen) {
    *vidx = vcheckExists(val, vertices, vlen);
    
    if (*vidx == -1) {
        
        // if not, then create the head
        vertices = vCreate(val, valLen, vertices, vlen);
        *vidx = *vlen - 1;  // vidx is the position in the array, zero-indexed
    }
    
    return vertices;
}


edge ** eCreate(vertex * head, vertex * tail, edge ** edges, int * elen) {
    edge * e = malloc(sizeof(*e));
    e->head = head;
    e->tail = tail;
    edges = realloc(edges, sizeof(edge) * (*elen + 1));
    edges[*elen] = e;
    *elen = *elen + 1;
    
    head->edges = realloc(head->edges, sizeof(edge**) * (head->elen + 1));
    head->edges[head->elen] = e;
    head->elen = head->elen + 1;
    
    tail->edges = realloc(tail->edges, sizeof(edge**) * (tail->elen + 1));
    tail->edges[tail->elen] = e;
    tail->elen = tail->elen + 1;
    
    return edges;
}


int edgeExists(vertex * head, vertex * tail, edge ** edges, int * elen) {
    for(int i = 0; i < *elen; i++) {
        if(
                (
                    strcmp(
                        edges[i]->head->val,
                        head->val
                    ) == 0 
                    && 
                    strcmp(
                        edges[i]->tail->val,
                        tail->val
                    ) == 0
                ) || (
                    strcmp(
                        edges[i]->tail->val,
                        head->val
                    ) == 0 
                    && 
                    strcmp(
                        edges[i]->head->val,
                        tail->val
                    ) == 0    
                )
            )
        {
            return 1;
        }
    }
    return 0;
}


int runTrial(char * fname, int * vlen, int * elen) {
    
    vertex ** vertices = malloc(sizeof(vertex**));
    
    edge ** edges = malloc(sizeof(edge**));
    
    *vlen = 0;
    *elen = 0;
    
    // open the file
    FILE * fp = fopen(fname, "r");
    if (fp == NULL) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }
    
    int nread;
    size_t len = 0;
    char * line = NULL;
    char * val = malloc(sizeof(char));
    int valLen = 0;
    
    int * vidx = malloc(sizeof(int*));
    *vidx = 1;
    vertex * head = malloc(sizeof(vertex*));
    vertex * tail = malloc(sizeof(vertex*));
    
    while(nread = getline(&line, &len, fp) != -1) {
           
        int colCount = 0;
        int i = 0;
        while(1) {
            char c = line[i];
            if(!isdigit(c)) {
                val[valLen] = '\0';
                
                if(colCount == 0) {
                    vertices = vCheckAndCreate(vidx, val, valLen, vertices, vlen);
                    head = vertices[*vidx];
                } else {
                    if(!head){
                        perror("head vertex is NULL");
                        exit(EXIT_FAILURE);
                    }
                    vertices = vCheckAndCreate(vidx, val, valLen, vertices, vlen);
                    tail = vertices[*vidx];

                    
                    // if the edge does not already exist...
                    // AND create an edge, then link the edge to each of the corresponding 
                    // vertices
                    if(edgeExists(head, tail, edges, elen) == 0) {
                        edges = eCreate(head, tail, edges, elen);   
                    }

                }
                valLen = 0;
                
                colCount ++;
                
                if (c == '\n') {
                    break;  // is there a better way?
                }
            } else {
                val = realloc(val, sizeof(char *) * (valLen + 2));
                val[valLen] = c;
                valLen ++;
            }
            i ++;
        }
    }
    
    fclose(fp);
    
    int cut = contractionAlgorithm(edges, elen, vertices, *vlen);
    
    // TODO: free up resources for this run
    free(val);
    free(vidx);
    
    return cut;
}


// https://www.programmingsimplified.com/c-program-find-factorial
long long factorial(long long n)
{
  long long c;
  long long r = 1;

  for (c = 1; c <= n; c++) {
      r = r * c;
  }

  return r;
}



// https://www.geeksforgeeks.org/program-calculate-value-ncr/
long nCr(int n, int r) {
    return factorial(n) / (factorial(r) * factorial(n - r));
}


/*
 * 
 */
int main() {
    
    char * fname = "/home/jake/Documents/Learning/algorithms_stanford/course_1/week_4/randomized-contraction-c/RandomizedContraction/data/assignment.txt";
    
    int * vlen = malloc(sizeof(int *));
    int * elen = malloc(sizeof(int *));
    int mincut = runTrial(fname, vlen, elen);
    
    // int nChoose2 = nCr(*vlen, 2);
    // long long trials = nChoose2 * log((float)*vlen);
    int nChoose2 = 0;
    long long trials = *vlen * log((float)*vlen);
    trials --;
    
    printf("\nnchoose2: %d, trials: %d", nChoose2, trials);
    
    // use the current time as seed for the random generator
    srand(time(0));
    
    for(int t = 0; t < trials; t++) {
        // sleep(1);
        int cut = runTrial(fname, vlen, elen);
        printf("\ncut: %d", cut);
        if(cut < mincut) {
            mincut = cut;
            printf("\nmincut: %d", mincut);
        }
    }
    
    // TODO: print out the min cut 
    printf("Min Cut: %d", mincut);
    
    return (EXIT_SUCCESS);
}
