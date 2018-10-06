//
// Created by root on 05/10/18.
//

#include <stdio.h>
#include <stdlib.h>
#include "Network.h"

/// Manual creation of a neural network
/// \return Network following the user criteria
T_Network* CreateNetwork_Manual(){

    // Variable declaration
    int nbLayers = 0;
    int* sizeLayers = NULL;
    T_Layer** layers = NULL;

    // Asking the number of layers (repeating until at least 2 layers)
    while (nbLayers < 2) {
        printf("How many layers should have the network ? ");
        scanf("%d", &nbLayers);
    }

    // Allocating memory for the size of layers
    sizeLayers = malloc(nbLayers * sizeof(int));

    // Exiting if allocation failed
    if (sizeLayers == NULL)
        exit(1);

    // Asking how many node have each layer
    for (int i = 0; i < nbLayers; ++i) {
        printf("How many nodes layer %d has ? ", i + 1);
        sizeLayers[i] = 0;
        while (sizeLayers[i] < 1)
            scanf("%d", &sizeLayers[i]);
    }

    // Allocating memory for the layers array
    layers = malloc(nbLayers * sizeof(T_Layer**));

    // Creating layers and put them into array
    for (int i = 0; i < nbLayers; ++i) {
        layers[i] = InitializeLayer(sizeLayers[i]);
    }

    // Allocating memory for the network
    T_Network* network = malloc(sizeof(T_Network));

    // Exiting if allocation failed
    if (network == NULL)
        exit(1);

    // Setting variables to specified value
    network->nbLayers = nbLayers;
    network->sizeLayers = sizeLayers;
    network->Layers = layers;

    return network;
}


/// Free the memory occupied by a network.
/// \param network Network to delete.
void FreeNetwork(T_Network* network){
    T_Layer** layers = network->Layers;
    for (int i = 0; i < network->nbLayers; ++i)
        FreeLayer(layers[i]);
    free(network->sizeLayers);
    free(network);
}