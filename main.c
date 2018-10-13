#include <stdio.h>
#include <stdlib.h>
#include "Backprop.h"

int main() {

    // User prompting
    printf("\n");
    printf("Hello, World!\n");
    T_Network* network = CreateNetwork_Manual();
    printf("\n");

    // Pre-run printing
    //PrintAllNetworkInfos(network);
    PrintNetworkTransitions(network);

    // Inputs assignation
    SetNetworkInputs_Manual(network);
    printf("\n");

    // Post-run printing
    RunNetwork(network);
    printf("Network runned !\n\n");
    //PrintAllNetworkInfos(network);

    // Reinforcing Network
    BackPropagate_MANUAL(network);
    printf("\n");

    // Post propagation printing
    printf("Network reinforced !\n\n");
    //PrintAllNetworkInfos(network);
    PrintNetworkTransitions(network);

    // Freeing memory
    FreeNetwork(network);

    return 0;
}