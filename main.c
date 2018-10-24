#include <stdio.h>
#include <stdlib.h>
#include "Trainer.h"
#include "SaveAndLoad.h"

int main () {

    // Main constant

    double nu = 2;
    int iteration = 20000;

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
    //PrintAllNetworkInfos(network);
    //PrintNetworkTransitions(network);

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

    //Post-Training save
    Save(trainer, "Save", ".bin");

    // Freeing Memory
    FreeTrainer(trainer);

    //Post-Training load

    T_Trainer* trainer2 = Load("Save", ".bin");
    T_Network* network2 = trainer2->Network;

    //Post-Load print
    PrintAllNetworkInfos(network2);
    PrintNetworkTransitions(network2);

    ShowResults(trainer2);

    // Freeing Network

    FreeTrainer(trainer2);

    return 0;
}