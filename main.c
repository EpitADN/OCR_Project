#include <stdio.h>
#include <stdlib.h>
#include "Network.h"
#include "SaveAndLoad.h"

int main() {

    // User prompting
    printf("\n");
    printf("Hello, World!\n");
    T_Network* network = CreateNetwork_Manual();
    printf("\n");

    // Pre-save printing
    PrintAllNetworkInfos(network);

    // Saving network
    //SaveNetwork(network, "../", "SaveConnections.bin");
    SaveNetwork(network);

    // Freeing memory
    FreeNetwork(network);

    //T_Network* network2 = LoadNetwork("../", "SaveConnections.bin");
    T_Network* network2 = LoadNetwork();

    //Post load printing
    PrintAllNetworkInfos(network2);

    // Freeing memory
    FreeNetwork(network2);

    return 0;
}