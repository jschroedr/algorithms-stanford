/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "contract.h"


// function: pick a remaining edge at random
// make note that behavior is undefined if len > 32767
int getRandomIndex(int len) {
    
    // use the current time as seed for the random generator
    srand(time(0));
    
    // randomly determine the index, handling for size len using technique
    // documented here:
    // http://c-faq.com/lib/randrange.html
    int idx = (int)((double)rand() / ((double)RAND_MAX + 1) * len);
    
    // return the index which the caller can use to slice out the edge
    return idx;
}

vertex ** shuffleVertices(vertex ** vertices, vertex * tail, int vlen) {
    int shuffle = 0;
    for(int i = 0; i < vlen; i ++){
        if(strcmp(vertices[i]->val, tail->val) == 0) {
            shuffle = 1;
        } else {
            if (shuffle == 1) {
                vertices[i - 1] = vertices[i];
            }
        }
    }
    return realloc(vertices, sizeof(vertex **) * (vlen));
}


// keep the head vertex of the edge (just a preference)
// merge two verticies in given edge into a single vertex
    // keep parellel edges
    // locate and eliminate self loops
vertex ** mergeVertices(edge * e, vertex ** vertices, int vlen) {
    
    // for the tail vertex's edges
    vertex * tail = e->tail;
    
    // recalculate the vertices array to exclude the tail
    vertices = shuffleVertices(vertices, tail, vlen);
    
    for(int i = 0; i < tail->elen; i ++) {
        // replace all references to the tail with the head
        if (
                strcmp(
                    ((edge *)tail->edges[i])->head->val,
                    tail->val
                ) == 0) {
            ((edge *)tail->edges[i])->head = e->head;
        } else {
            ((edge *)tail->edges[i])->tail = e->head;
        }
    }
    return vertices;
}

edge ** shuffleEdges(edge ** edges, int * elen) {
    int len = *elen;
    while(1) {
        int shuffle = 0;
        for(int i = 0; i < *elen; i ++) {
            if (shuffle == 1) {
                edges[i - 1] = edges[i];
            } else {
                if(strcmp(edges[i]->head->val, edges[i]->tail->val) == 0) {
                    printf("\nSAME: %s %s", edges[i]->head->val, edges[i]->tail->val);
                    shuffle = 1;
                    len --;
                }
            }
        }
        if (*elen == len) {
            break;
        } else {
            *elen = len;
        }
    }
    edges = realloc(edges, sizeof(edge **) * (*elen));
    return edges;
}


// main function: 
int contractionAlgorithm(edge ** edges, int * elen, vertex ** vertices, int vlen) {
    while(vlen >= 1) {
        printf("\nVLEN: %d", vlen);
        // pick a remaining edge uniformly at random
        int idx = getRandomIndex(*elen - 1);
        edge * e = edges[idx];
        
        // merge or "contract" u and v into a single vertex
        vertices = mergeVertices(e, vertices, vlen);
        
        edges = shuffleEdges(edges, elen);
        
        // since the tail just got merged into the head, we always subtract 1
        vlen = vlen - 1;
    }
    // print out the edges
    printf("\nEDGES IN CUT");
    for(int i = 0; i < *elen; i ++){
        printf("\nhead: %s, tail: %s", edges[i]->head->val, edges[i]->tail->val);
    }
    
    // return the number of edges as the min cut
    return *elen;
}
