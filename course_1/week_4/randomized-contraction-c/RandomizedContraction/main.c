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
#include "vertex.h";
#include "edge.h";
#include "contract.h";

int vcheckExists(char * val, vertex * vertices, int * vlen) {
    for(int i = 0; i < *vlen; i ++) {
        if(strcmp(vertices[i]->val, val) == 0) {
            return i;
        }
    }
    return -1;
}


vertex * vCreate(char * val, vertex * vertices, int * vlen) {
    vertex * v = malloc(sizeof(vertex *));
    v->elen = 0;
    v->val = val;
    vertices = realloc(vertices, sizeof(vertex *) * (vlen + 1));
    vertices[*vlen] = v;
    *vlen ++;
    return v;
}

vertex * vCheckAndCreate(char * val, vertex * vertices, int * vlen) {
    int vidx = vcheckExists(val, vertices);
    
    if (vidx == -1) {
        
        // if not, then create the head
        return vCreate(val, vertices, vlen);
    
    } else {
        // if so, then use the returned index to get the existing
        return vertices[vidx];
    }
    
}


edge * eCreate(vertex * head, vertex * tail, edge * edges, int * elen) {
    edge * e = malloc(sizeof(edge *));
    e->head = head;
    e->tail = tail;
    edges = realloc(edges, sizeof(edge *) * (elen + 1));
    edges[*elen] = e;
    *elen ++;
    return e;
}


vertex * getHeadVertex(char * val, vertex * vertices, int * vlen) {
    return vCheckAndCreate(val, vertices, vlen);
}

vertex * getTailVertex(vertex * head, char * val, vertex * vertices, int * vlen, edge * edges, int * elen) {
    // for each column (2nd value on in row) ```````````````````````````
    // TODO: when j > 1 (where j is col counter)
    vertex tail = vCheckAndCreate(val, vertices, vlen);

    // AND create an edge, then link the edge to each of the corresponding 
    // vertices
    
    // note this does return an edge * if you decide later you need it
    eCreate(head, tail, edges, elen);
}


void load(char * fname, vertex * vertices, int * vlen, edge * edges, int * elen) {
    // open the file
    FILE * fp = fopen(fname, "r");
    if (fp == NULL) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }
    
    int nread;
    size_t len = 0;
    size_t rows = 1;
    char * line = NULL;
    char * val = malloc(sizeof(char *));
    int valLen = 0;
    
    vertex * head = NULL;
    vertex * tail = NULL;
    
    // @internal using getline from C11 (for safety)
    while(nread = getline(&line, &len, fp) != -1) {
        
        int quit = 0;
           
        int colCount = 0;
        
        while(quit == 0) {
            char c = line[c];
            if(c == '\t' || c == '\n') {
                
                if(colCount == 0) {
                    head = getHeadVertex(val, vertices, vlen);
                } else {
                    tail = getTailVertex(head, val, vertices, vlen, edges, elen);
                }
                valLen = 0;
                colCount ++;
                
                if (c == '\n') {
                    quit = 1;  // is there a better way?
                }
            } else {
                val = realloc(val, sizeof(char *) * (valLen + 1));
                val[valLen] = c;
                valLen ++;
                break;
            }
        }
    }
    // close the file
    // TODO
}


/*
 * 
 */
int main(int argc, char** argv) {
    
    return (EXIT_SUCCESS);
}

