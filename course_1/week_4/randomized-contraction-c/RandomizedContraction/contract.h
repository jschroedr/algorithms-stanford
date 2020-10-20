/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


typedef struct Vertex {
    char * val;
    int elen;
    void ** edges;
} vertex;


typedef struct Edge {
    vertex * head;
    vertex * tail;
} edge;


int contractionAlgorithm(edge ** edges, int * elen, vertex ** vertices, int vlen);
