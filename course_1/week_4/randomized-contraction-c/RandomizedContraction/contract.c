/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdlib.h>;
#include <string.h>;
#include "vertex.h";
#include "edge.h";


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

void replaceEdgeReference(vertex * old, vertex * new, int eidx) {
    
    // pick out the target edge to replace references on
    edge * e = old->edges[eidx];

    // either replace the head or the tail with the new vertex
    if (strcmp(e->head->val, old->val) == 0) {
        e->head = new;
    } else {
        e->tail = new;
    }
    
    // if the edge is now circular, then destroy it
    int circular = (strcmp(e->head->val, e->tail->val) == 0) ? 1 : 0;
    if (circular == 1) {
        free(e);
    }
}

void shuffleVertices(vertex * vertices, vertex * tail, int vlen) {
    int shuffle = 0;
    for(int i = 0; i < vlen; i ++){
        vertex * v = vertices[i];
        if(strcmp(v->val, tail->val) == 0) {
            shuffle = 1;
        } else {
            if (shuffle == 1) {
                vertices[i - 1] = vertices[i];
            }
        }
    }
}

// keep the head vertex of the edge (just a preference)
// merge two verticies in given edge into a single vertex
    // keep parellel edges
    // locate and eliminate self loops
void mergeVertices(edge e, vertex * vertices, int vlen) {
    
    // for the tail vertex's edges
    vertex * tail = e->tail;
    
    // recalculate the vertices array to exclude the tail
    shuffleVertices(vertices, tail, vlen);
    
    for(int i = 0; i < tail->elen; i ++) {
        // replace all references to the tail with the head
        replaceEdgeReference(e->tail->edges[i], e->head);
    }
}

// main function: 
edge contractionAlgorithm(edge * edges, vertex * vertices, int vlen) {
    int len = vlen;
    
    while(vlen > 0) {
        // pick a remaining edge uniformly at random
        int idx = getRandomIndex(len);
        edge * e = edges[idx];
        
        // merge or "contract" u and v into a single vertex
        mergeVertices(e, vertices);
        
        // since the tail just got merged into the head, we always subtract 1
        vlen --;
    }
    
    // TODO: return cut resembled by two remaining vertices
    edge minCut;
    minCut->head = vertices[0];
    minCut->tail = vertices[1];
    return minCut;
}
