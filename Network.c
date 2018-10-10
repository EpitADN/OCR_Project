//
// Created by root on 05/10/18.
//

#include <stdio.h>
#include <stdlib.h>
#include "Network.h"

/// Manual creation of a neural network
/// \return Network following the user criteria
T_Network* CreateNetwork_Manual(){

    // Creating pointer for the number of layers
    int* nbLayers = NULL;

    // Allocating memory for the number of layers
    nbLayers = malloc(sizeof(int));

    // Exiting if allocation failed
    if (nbLayers == NULL)
        exit(1);

    // Asking the number of layers (repeating until at least 2 layers)
    *nbLayers = 0;
    while (*nbLayers < 2) {
        printf("How many layers should have the network ? ");
        scanf("%d", nbLayers);
    }

    // Initializing pointer
    int** sizeLayers = NULL;

    // Allocating memory for the size of layers
    sizeLayers = malloc(*nbLayers * sizeof(int*));

    // Exiting if allocation failed
    if (sizeLayers == NULL)
        exit(1);

    // Asking how many node have each layer
    for (int i = 0; i < *nbLayers; ++i) {

        // Creating pointer for the size of layer i
        sizeLayers[i] = NULL;

        // Allocating memory for the size of layer i
        sizeLayers[i] = malloc(sizeof(int));

        // Exiting if allocation failed
        if (sizeLayers[i] == NULL)
            exit(1);

        // Asking user, repeating until at least 1 node
        *sizeLayers[i] = 0;
        while (*sizeLayers[i] < 1){
            printf("How many nodes should have layer %d ? ", i + 1);
            scanf("%d", sizeLayers[i]);
        }
    }

    // Initializing pointer
    T_Layer** layers = NULL;

    // Allocating memory for the layers array
    layers = malloc(*nbLayers * sizeof(T_Layer*));

    // Creating layers and put them into array
    T_Position layerPosition;
    for (int j = 0; j < *nbLayers; ++j) {

        if (j == 0)
            layerPosition = FIRST;
        else if (j == *nbLayers - 1)
            layerPosition = LAST;
        else
            layerPosition = MIDDLE;

        layers[j] = InitializeLayer(layerPosition, sizeLayers[j]);
    }

    // Initializing pointer
    T_Network* network = NULL;

    // Allocating memory for the network
    network = malloc(sizeof(T_Network));

    // Exiting if allocation failed
    if (network == NULL)
        exit(1);

    // Setting variables to specified value
    network->nbLayers = nbLayers;
    network->sizeLayers = sizeLayers;
    network->Layers = layers;

    return network;
}


/// Print all the network related variables, including all of its layers and nodes.
/// \param network Pointer to the network to print.
void PrintAllNetworkInfos(T_Network* network){

    printf("Printing exhaustive network infos : \n\n");

    // Print Layers info
    printf("Number of layers : %d \n", *network->nbLayers);
    for (int i = 0; i < *network->nbLayers; ++i) {
        printf("Size of layer %d : %d \n", i+1, *network->Layers[i]->nbNodes);
    }
    printf("\n");

    // Print Nodes info for each layer
    for (int j = 0; j < *network->nbLayers; ++j) {
        printf("Value of nodes in layer %d : \n", j+1);
        for (int k = 0; k < *network->Layers[j]->nbNodes; ++k) {
            printf("Value of node %d-%d : %f \n", j+1, k+1 , network->Layers[j]->nodes[k]->val);
        }
        printf("\n");
    }
    printf("\n");
}

/// Free the memory occupied by a network.
/// \param network Pointer to the network to delete.
void FreeNetwork(T_Network* network){
    for (int i = 0; i < *network->nbLayers; ++i)
        FreeLayer(network->Layers[i]);
    free(network->Layers);
    free(network->sizeLayers);
    free(network->nbLayers);
    free(network);
}