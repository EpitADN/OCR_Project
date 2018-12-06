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
    printf("\n");

    return CreateNetwork_Auto(nbLayers, sizeLayers);
}


/// Automatic creation of a neural network
/// \return Network following the specified arguments
T_Network* CreateNetwork_Auto(int* nbLayers, int** sizeLayers){

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

    // Initialize layers and transitions
    InitializeNetworkLayers(network);
    InitializeNetworkTransitions(network);

    return network;
}


/// Initialize all the network layers following already established variables.
/// \param network Pointer to the network to work on
void InitializeNetworkLayers(T_Network* network){

    // Retrieving network info
    int nbLayers = *network->nbLayers;
    int** sizeLayers = network->sizeLayers;

    // Initializing pointer
    T_Layer** layers = NULL;

    // Allocating memory for the layers array
    layers = malloc(nbLayers * sizeof(T_Layer*));

    // Creating layers and put them into array
    T_Position layerPosition;
    for (int j = 0; j < nbLayers; ++j) {

        if (j == 0)
            layerPosition = FIRST;
        else if (j == nbLayers - 1)
            layerPosition = LAST;
        else
            layerPosition = MIDDLE;

        layers[j] = InitializeLayer(layerPosition, sizeLayers[j]);
    }

    // Adding new layers to the network
    network->Layers = layers;
}


/// Initialize all the network transitions following already established layers.
/// \param network Pointer to the network to work on
void InitializeNetworkTransitions(T_Network* network){

    // Retrieving network info
    int nbLayers = *network->nbLayers;
    T_Layer** layers = network->Layers;

    // Creating pointer
    T_Transition** transitions = NULL;

    // Allocating memory for the transition array
    transitions = malloc( (nbLayers-1) * sizeof(T_Transition*));

    // Exiting if allocation failed
    if (transitions == NULL)
        exit(1);

    // Initializing all transitions and put them into array
    for (int i = 0; i < nbLayers - 1; ++i) {
        transitions[i] = InitializeTransition(layers[i], layers[i+1]);
    }

    // Adding new transitions to the network
    network->Transitions = transitions;
}


/// Print all the network related variables, including all of its layers and nodes.
/// \param network Pointer to the network to print.
void PrintAllNetworkInfos(T_Network* network, int showNodes){

    printf("Printing exhaustive network infos : \n\n");

    // Print Layers info
    printf("Number of layers : %d \n", *network->nbLayers);
    for (int i = 0; i < *network->nbLayers; ++i) {
        printf("Size of layer %d : %d \n", i+1, *network->Layers[i]->nbNodes);
    }
    printf("\n");

    // Print Nodes info for each layer
    if (showNodes) {
        T_Node *jnode;
        for (int j = 0; j < *network->nbLayers; ++j) {
            printf("Value of nodes in layer %d : \n", j + 1);
            for (int k = 0; k < *network->Layers[j]->nbNodes; ++k) {
                jnode = network->Layers[j]->nodes[k];
                printf("Value of node %d-%d : %f|%f|%f \n", j + 1, k + 1, jnode->val, jnode->net, jnode->error);
            }
            printf("\n");
        }
        printf("\n");
    }

}

/// Print all the transitions matrix in order
/// \param network Pointer to the network to print from.
void PrintNetworkTransitions(T_Network* network){

    int nbTransitions = *network->nbLayers - 1;
    T_Transition** transitions = network->Transitions;

    printf("Printing all %d network's transitions :\n\n", nbTransitions);

    T_Transition* transition = NULL;
    double weightjk;
    for (int i = 0; i < nbTransitions; ++i) {
        transition = transitions[i];

        printf("Values of weights in transition %d : \n", i+1);

        for (int j = 0; j < transition->height; ++j) {
            for (int k = 0; k < transition->width; ++k) {
                weightjk = transition->Matrix[j][k];
                if (weightjk > 0)
                    printf("|+%f", transition->Matrix[j][k]);
                else
                    printf("|%f", transition->Matrix[j][k]);
            }
            printf("|\n");
        }
        printf("\n");
    }
}

/// Free the memory occupied by a network.
/// \param network Pointer to the network to delete.
void FreeNetwork(T_Network* network){

    for (int i = 0; i < *network->nbLayers; ++i)
        FreeLayer(network->Layers[i]);
    free(network->Layers);

    for (int j = 0; j < *network->nbLayers - 1; ++j)
        FreeTransition(network->Transitions[j]);
    free(network->Transitions);

    free(network->sizeLayers);
    free(network->nbLayers);
    free(network);
}


/// Set the network inputs according to the user criteria
/// \param network Pointer to the network to set
void SetNetworkInputs_Manual(T_Network* network){

    // Retrieving network info
    int nbInputs = *network->Layers[0]->nbNodes - 1;
    T_Node** firstNodes = network->Layers[0]->nodes;

    printf("Assigning input node values for %d nodes : \n", nbInputs);

    for (int i = 0; i < nbInputs; ++i) {
        printf("Value of input node 1-%d ? ", i + 1);
        scanf("%lf", &firstNodes[i]->val);
    }
    printf("\n");
}


/// Set the network inputs according to the given array.
/// \param inputs Double array setting the value of the input layer.
void SetNetworkInputs_Auto(T_Network* network, double* inputs){

    // Retrieving network info
    int nbInputs = *network->Layers[0]->nbNodes - 1;
    T_Node** firstNodes = network->Layers[0]->nodes;

    // Iterating on each input node
    for (int i = 0; i < nbInputs; ++i)
        firstNodes[i]->val = inputs[i];
}


/// Do a full propagation cycle, inputs needs to be set.
/// \param network Pointer to the network to run
void RunNetwork(T_Network* network){

    // Retrieving network info
    int nbTransitions = *network->nbLayers - 1;

    // Activating each transitions
    for (int i = 0; i < nbTransitions; ++i)
        ActivateTransition(network->Transitions[i]);
}