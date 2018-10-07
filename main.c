#include <stdio.h>
#include "Network.h"

int main() {

    printf("\n");

    printf("Hello, World!\n");
    T_Network* network = CreateNetwork_Manual();
    printf("\n");

    PrintAllNetworkInfos(network);

    FreeNetwork(network);

    return 0;
}