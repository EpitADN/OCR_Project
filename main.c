#include <stdio.h>
#include <stdlib.h>
#include "Network.h"

int main() {

    // User prompting
    printf("\n");
    printf("Hello, World!\n");
    T_Network* network = CreateNetwork_Manual();
    printf("\n");

    // Inputs assignation
    SetNetworkInputs_Manual(network);
    printf("\n");

    // Pre-run printing
    PrintAllNetworkInfos(network);

    // Post-run printing
    RunNetwork(network);
    printf("Network runned !\n\n");
    PrintAllNetworkInfos(network);

    // Freeing memory
    FreeNetwork(network);

    return 0;
}