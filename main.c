#include <stdio.h>
#include <stdlib.h>
#include "Trainer.h"

int main() {

    // Main constant
    int iteration = 20000;
    double nu = 2;

    // User prompting
    printf("\n");
    printf("Hello, World!\n");
    T_Network* network = CreateNetwork_Manual();
    T_Trainer* trainer = CreateTrainer_Manual(network);

    // Separator
    printf("================================\n");
    printf("================================\n");
    printf("================================\n\n\n");

    // Pre-Training print
    PrintAllNetworkInfos(network);
    PrintNetworkTransitions(network);

    // Separator
    printf("================================\n\n");

    // Training network
    Train(trainer, nu, iteration);
    printf("\n");

    // Separator
    printf("================================\n\n");

    // Post-Training print
    //PrintAllNetworkInfos(network);
    PrintNetworkTransitions(network);
    ShowResults(trainer);

    // Freeing Memory
    FreeTrainer(trainer);

    return 0;
}