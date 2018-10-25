#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Trainer.h"
#include "SaveAndLoad.h"

int main (int argc, char* argv[]){

    // Initializing arguments
    char* NAME;
    int ITERATION;
    double NU;

    // Saves parameters
    char* directory = "Saves/";
    char* extension = ".bin";

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


    // Printing recap
    printf("\n");
    printf("Hello, World!\n");
    printf("Name = \"%s\", Iteration = %d, Nu = %lf.\n\n", NAME, ITERATION, NU);



    // Concatening path
    char *path = malloc(strlen(directory)+strlen(NAME)+strlen(extension)+1);
    strcat(path, directory);
    strcat(path, NAME);
    strcat(path, extension);


    // Creating Trainer
    T_Trainer* trainer;
    T_Network* network;


    if( access(path, F_OK ) != -1 ) {

        // file exists
        printf("Found a save, loading file... ");
        trainer = Load(path);
        network = trainer->Network;
        printf("Done !\n\n");

    } else {

        // file doesn't exist

        if (strcmp(NAME, "XOR") == 0){

            // Auto creating XOR
            printf("Automatic creation of XOR... ");
            trainer = CreateTrainerXOR();
            network =  trainer->Network;
            printf("Done !\n\n");

        } else {

            // User prompting
            network = CreateNetwork_Manual();
            trainer = CreateTrainer_Manual(network);

        }

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
    Save(trainer, path);

    // Freeing Memory
    FreeTrainer(trainer);


    return 0;
}
