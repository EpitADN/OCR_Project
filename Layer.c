//
// Created by root on 05/10/18.
//

#include <stdlib.h>
#include "Layer.h"

/// Create a new layer with n nodes
/// \param nbNodes number of nodes of the layer
/// \return New layer
T_Layer* InitializeLayer(int nbNodes){

    // Exiting if bad parameters
    if (nbNodes < 1)
        return NULL;

    // Allocating memory for the nodes array
    T_Node** nodes = malloc(nbNodes * sizeof(T_Node*));

    // Exiting if allocation failed
    if (nodes == NULL)
        exit(1);

    // Creating nodes and put them into array
    for (int i = 0; i < nbNodes; ++i) {
        nodes[i] = InitializeNode();
    }

    // Allocating memory for the layer
    T_Layer* layer = malloc(sizeof(T_Layer));

    // Exiting if allocation failed
    if (layer == NULL)
        exit(1);

    // Setting variables to specified value
    layer->nbNodes = nbNodes;
    layer->nodes = nodes;

    return layer;
}


/// Free the memory occupied by a layer.
/// \param layer Layer to delete.
void FreeLayer(T_Layer* layer){
    T_Node** nodes = layer->nodes;
    for (int i = 0; i < layer->nbNodes; ++i)
        FreeNode(nodes[i]);
    free(layer);
}