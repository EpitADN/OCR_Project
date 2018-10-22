//
// Created by root on 05/10/18.
//

#include <stdlib.h>
#include "Layer.h"

/// Create a new layer with n nodes, adding a bias node if needed.
/// \param position Position of the layer in the network
/// \param nbNodes Pointer to the number of nodes of the layer
/// \return Pointer to the new layer
T_Layer* InitializeLayer(T_Position position, int* nbNodes){

    // Exiting if bad parameters
    if (*nbNodes < 1)
        return NULL;

    // Add place for a bias node if needed
    if (position != LAST)
        *nbNodes += 1;

    // Initialize pointer
    T_Node** nodes = NULL;

    // Allocating memory for the nodes array
    nodes = malloc(*nbNodes * sizeof(T_Node*));

    // Exiting if allocation failed
    if (nodes == NULL)
        exit(1);

    // Creating nodes and put them into array
    int iLastNode = *nbNodes -1;
    T_Nature nodeNature;
    for (int i = 0; i <= iLastNode; ++i) {

        if (i == iLastNode && position != LAST)
            nodeNature = BIAS;
        else if (position == FIRST)
            nodeNature = INPUT;
        else if (position == LAST)
            nodeNature = OUTPUT;
        else
            nodeNature = HIDDEN;

        nodes[i] = InitializeNode(nodeNature);
    }

    // Allocating memory for the layer
    T_Layer* layer = malloc(sizeof(T_Layer));

    // Exiting if allocation failed
    if (layer == NULL)
        exit(1);

    // Setting variables to specified value
    layer->position = position;
    layer->nbNodes = nbNodes;
    layer->nodes = nodes;

    return layer;
}


/// Free the memory occupied by a layer.
/// \param layer Pointer to the layer to delete.
void FreeLayer(T_Layer* layer){
    for (int i = 0; i < *layer->nbNodes; ++i)
        FreeNode(layer->nodes[i]);
    free(layer->nodes);
    free(layer->nbNodes);
    free(layer);
}