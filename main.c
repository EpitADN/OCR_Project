#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Trainer.h"
#include "SaveAndLoad.h"

int main (int argc, char* argv[]){

    // Initializing arguments
    char* NAME;
    int ITERATION;
    double NU;
    char directory[] = "Saves/";

    // Reading parameters and auto-setting

    if (argc >= 2)
        NAME = argv[1];
    else
        NAME = "Network";

    if (argc >= 3)
        ITERATION = atoi(argv[2]);
    else
        ITERATION = 20000;

    if (argc >= 4)
        NU = atof(argv[3]);
    else
        NU = 2;

    // Verifying integrity
    if (argc >= 5 || NAME == NULL || ITERATION <= 0 || NU <= 0){
        printf("Error parsing parameters, we got : Name = \"%s\", Iteration = %d, Nu = %lf.\n", NAME, ITERATION, NU);
        exit(-1);
    }


    // Creating Trainer
    T_Trainer* trainer;
    T_Network* network;

    printf("\n");
    printf("Hello, World!\n");
    printf("Parameters used : Name = \"%s\", Iteration = %d, Nu = %lf.\n\n", NAME, ITERATION, NU);

    if (strcmp(NAME, "XOR") == 0){

        // Auto creating XOR
        printf("Automatic creation of XOR...\n\n");
        trainer = CreateTrainerXOR();
        network =  trainer->Network;

    } else {

        // User prompting
        network = CreateNetwork_Manual();
        trainer = CreateTrainer_Manual(network);

    }

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
    Train(trainer, NU, ITERATION);
    printf("\n");

    // Separator
    printf("================================\n\n");

    // Post-Training print
    PrintNetworkTransitions(network);
    printf("\n");
    ShowResults(trainer);

    //Post-Training save
    Save(trainer, NAME, ".bin", directory);

    // Freeing Memory
    FreeTrainer(trainer);

    /*

    //Post-Training load
    T_Trainer* trainer2 = Load(NAME, ".bin", directory);
    T_Network* network2 = trainer2->Network;

    //Post-Load print
    PrintAllNetworkInfos(network2);
    PrintNetworkTransitions(network2);
    ShowResults(trainer2);

    // Freeing Network
    FreeTrainer(trainer2);

     */

    return 0;
}
