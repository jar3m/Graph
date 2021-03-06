#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

//Free the memory area that a graph used
void free_graph(struct graph_t *graph) {
    int i;
    for(i=0; i<graph->n_nodes; i++) {
        free(graph->nodes[i]);
    }

    free(graph->nodes);
    free(graph);
}

//Allocate memory for a node
Node *create_node(char label) {
    Node *node;
    node = (Node *)malloc(sizeof(Node));
    node->label = label;
    node->n_neighbors = 0;
    node->neighbors = (Node **)malloc(node->n_neighbors*sizeof(Node *));
    node->weights = (double *)malloc(node->n_neighbors*sizeof(double));
    return node;
}

//Connect a to b
void connect_(Node *a, Node *b, double weight) {
    a->neighbors = (Node **)realloc(a->neighbors,
                                    (a->n_neighbors+1)*sizeof(Node *));
    a->weights = (double *)realloc(a->weights,
                                   (a->n_neighbors+1)*sizeof(double));
    a->neighbors[a->n_neighbors] = b;
    a->weights[a->n_neighbors] = weight;
    a->n_neighbors += 1;
}

/*
 * Returns
 * 1 if the node which its label is 'label' exists in the graph
 * 0 otherwise
 */
//TODO test
Node *get_node(Graph *graph, char label) {
    int i;
    Node *node;
    for(i = 0; i < graph->n_nodes; i++) {
        node = graph->nodes[i];
        if(node->label == label) {
            return node;
        }
    }
    return NULL;
}

/* TODO test */
int node_exists(Graph *graph, char label) {
    return get_node(graph, label) != NULL;
}

//Returns 1 if a is connected to b 0 otherwise
/* TODO test */
int is_connected(Node *a, Node *b) {
    int i;
    Node *neighbor;
    for(i = 0; i < a->n_neighbors; i++) {
        neighbor = a->neighbors[i];
        if(are_same_nodes(neighbor, b)) {
            return 1;
        }
    }
    return 0;
}

//Connect both to represent an undirected path
void connect(Node *node1, Node *node2) {
    connect_(node1, node2, 0);
    connect_(node2, node1, 0);
}

void wconnect(Node *node1, Node *node2, double weight) {
    connect_(node1, node2, weight);
    connect_(node2, node1, weight);
}

//Allocate memory for a graph and set default values
Graph *init_graph() {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->n_nodes = 0;
    graph->nodes = (Node **)malloc(graph->n_nodes*sizeof(Node *));
    return graph;
}

//Returns whether node1 and node2 are same
int are_same_nodes(Node *node1, Node *node2) {
    return node1 == node2 && node1->label == node2->label;
}

//Add a node to a graph
void add_node(Graph *graph, Node *node) {
    graph->nodes = (Node **)realloc(graph->nodes,
                                    (graph->n_nodes+1)*sizeof(Node *));

    graph->nodes[graph->n_nodes] = node;
    graph->n_nodes += 1;
}

//Show the label of a node
void show_node(Node *node, int show_weight) {
    int i;
    printf("%c: ", node->label);
    for(i=0; i<node->n_neighbors; i++) {
        if(show_weight) {
            printf("%c %.1lf  ", node->neighbors[i]->label, node->weights[i]);
        } else {
            printf("%c ", node->neighbors[i]->label);
        }
    }
    printf("\n");
}

//Show a graph
void show_graph(Graph *graph, int show_weight) {
    int i;
    for(i=0; i<graph->n_nodes; i++) {
        printf("  ");
        show_node(graph->nodes[i], show_weight);
    }
}
