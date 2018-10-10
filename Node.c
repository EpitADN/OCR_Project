//
// Created by root on 05/10/18.
//

#include <stdlib.h>
#include "Node.h"

/// Create a new node with all it's value defaulted to 0.
/// \return New node
T_Node* InitializeNode(T_Nature nature){

    // Initialize pointer
    T_Node* node = NULL;

    // Allocating memory for the node
    node = malloc(sizeof(T_Node));

    // Exiting if allocation failed
    if (node == NULL)
        exit(1);

    // Setting attributes according to nature
    node->nature = nature;

    if (nature != BIAS){
        node->net = 0;
        node->val = 0;
        node->error = 0;
    } else {
        node->net = 0;
        node->val = 1;
        node->error = 0;
    }

    return node;
}


/// Free the memory occupied by a node.
/// \param node Pointer to the node to delete.
void FreeNode(T_Node* node){
    free(node);
}

