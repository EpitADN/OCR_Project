//
// Created by root on 05/10/18.
//

#include <stdlib.h>
#include "Node.h"

/// Create a new node with all it's value defaulted to 0.
/// \return New node
T_Node* InitializeNode(){

    // Allocating memory for the node
    T_Node* node = malloc(sizeof(T_Node));

    // Exiting if allocation failed
    if (node == NULL)
        exit(1);

    // Setting variables to default value
    node->net = 0;
    node->val = 0;
    node->error = 0;

    return node;
}


/// Free the memory occupied by a node.
/// \param node Node to delete.
void FreeNode(T_Node* node){
    free(node);
}

