#include <stdio.h>
#include "Network.h"

int main() {

    printf("\n");

    printf("Hello, World!\n");
    T_Network* network = CreateNetwork_Manual();
    printf("\n");


    printf("Number of layers : %d \n", network->nbLayers);
    for (int i = 0; i < network->nbLayers; ++i) {
        printf("size of layer %d: %d \n", i+1, network->Layers[i]->nbNodes);
    }
    printf("\n");


    for (int j = 0; j < network->nbLayers; ++j) {
        printf("Value of nodes in layer %d : \n", j+1);
        for (int k = 0; k < network->Layers[k]->nbNodes; ++k) {
            printf("Value of node %d-%d : %f \n", j+1, k+1 , network->Layers[j]->nodes[k]->val);
        }
        printf("\n");
    }
    printf("\n");


    FreeNetwork(network);
    return 0;
}