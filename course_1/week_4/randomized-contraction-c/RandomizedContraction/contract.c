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
    // randomly determine the index, handling for size len using technique
    // documented here:
    // http://c-faq.com/lib/randrange.html
    int idx = (int)((double)rand() / ((double)RAND_MAX + 1) * len);
    
    // return the index which the caller can use to slice out the edge
    return idx;
}

vertex ** shuffleVertices(vertex ** vertices, vertex * tail, int vlen) {
    int len = 0;
    vertex ** new = malloc(sizeof(vertex **) * vlen);
    for(int i = 0; i < vlen; i ++) {
        // printf("\n%d:%s", i, vertices[i]->val);
        if(strcmp(vertices[i]->val, tail->val) != 0) {
            new[len] = vertices[i];
            len ++;
        }
    }
    new = realloc(new, sizeof(vertex **) * len);
    return new;
}


void replaceEdgeReferences(edge * e, edge ** edges, int * elen) {
    vertex * head = e->head;
    vertex * tail = e->tail;
    
    for (int i = 0; i < *elen; i ++) {
        if(strcmp(edges[i]->head->val, tail->val) == 0) {
            edges[i]->head = head;
        }
        if(strcmp(edges[i]->tail->val, tail->val) == 0) {
            edges[i]->tail = head;
        }
    }
}


edge ** removeCircularEdges(edge ** edges, int * elen) {
    edge ** new = malloc(sizeof(edge **) * (*elen));
    int len = 0;
    for(int i = 0; i < *elen; i ++) {
        // if the edge is not self-referencing, add it to the new array
        if(strcmp(edges[i]->head->val, edges[i]->tail->val) != 0) {
            new[len] = edges[i];
            len ++;
        }
    }
    // set the new value of elen
    *elen = len;
     
    // remove any unnecessary memory usage
    new = realloc(new, sizeof(edge **) * (len));
    return new;
}


// main function: 
int contractionAlgorithm(edge ** edges, int * elen, vertex ** vertices, int vlen) {
    
    while(vlen > 2) {
        // pick a remaining edge uniformly at random
        int idx = getRandomIndex(*elen - 1);
        edge * e = edges[idx];
        
        // shuffle the vertices to exclude the tail of the given edge
        vertices = shuffleVertices(vertices, e->tail, vlen);
        
        // merge or "contract" u and v into a single vertex
        replaceEdgeReferences(e, edges, elen);
        
        edges = removeCircularEdges(edges, elen);
        
        // since the tail just got merged into the head, we always subtract 1
        vlen = vlen - 1;
    }

    
    // print out the edges
    /*
    printf("\nEDGES IN CUT");
    for(int i = 0; i < *elen; i ++){
        printf("\n\thead: %s, tail: %s", edges[i]->head->val, edges[i]->tail->val);
    }
    */
    
    
    // return the number of edges as the min cut
    return *elen;
}
