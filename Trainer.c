//
// Created by root on 13/10/18.
//

#include "Trainer.h"


/// Initialize a Trainer and return a pointer to it.
/// \param network Pointer to the network to train
/// \param nbSets Number of possible set of inputs/ouputs
/// \param SetsOfInputs Pointer to the array of all sets of inputs
/// \param SetsOfTargets Pointer to the array of all sets of targets
/// \return A pointer to the new Trainer
T_Trainer* CreateTrainer_Auto(T_Network* network, int nbSets, double** SetsOfInputs, double** SetsOfTargets){

    // Creating pointer
    T_Trainer* trainer = NULL;

    // Allocating memory for the trainer
    trainer = malloc(sizeof(T_Trainer));

    // Exiting if allocation failed
    if (trainer == NULL)
        exit(1);

    // Setting variables
    trainer->Network = network;
    trainer->nbSets = nbSets;
    trainer->SetsOfInputs = SetsOfInputs;
    trainer->SetsOfTargets = SetsOfTargets;

    // Returning pointer
    return trainer;
}


/// Initialize a Trainer and return a pointer to it, following user's criterias
/// \param network Poiter to the network to train
/// \return A pointer to the new trainer
T_Trainer* CreateTrainer_Manual(T_Network* network){

    printf("Designing trainer for network : \n\n");

    // Retrieving Network info
    int lengthInputs = *network->Layers[0]->nbNodes - 1;
    int lengthTargets = *network->Layers[*network->nbLayers - 1]->nbNodes;

    // Asking number of sets
    int nbSets = 0;
    while (nbSets < 1){
        printf("How many sets of inputs are possible : ");
        scanf("%d", &nbSets);
    }
    printf("\n");

    // Allocating memory for the sets of inputs/outputs
    double** setsOfInputs = malloc(nbSets * sizeof(double*));
    double** setsOfTargets = malloc(nbSets * sizeof(double*));

    // Asking for each individual set
    for (int i = 0; i < nbSets; ++i) {

        setsOfInputs[i] = malloc(lengthInputs * sizeof(double));
        setsOfTargets[i] = malloc(lengthTargets * sizeof(double));

        printf("Designing set number %d : \n -- Inputs : \n", i + 1);
        for (int j = 0; j < lengthInputs; ++j) {
            printf("(%d) Entered value of input node %d ? ", i + 1, j + 1);
            scanf("%lf", &setsOfInputs[i][j]);
        }

        printf(" -- Ouputs : \n");
        for (int k = 0; k < lengthTargets; ++k) {
            printf("(%d) Expected value of output node %d ? ", i + 1, k + 1);
            scanf("%lf", &setsOfTargets[i][k]);
        }
        printf("\n");
    }
    printf("\n");

    return CreateTrainer_Auto(network, nbSets, setsOfInputs, setsOfTargets);
}


/// Train the network through i cycle of forward and back propagation
/// \param trainer Pointer to the trainer
/// \param nu Aggressivity of the training
/// \param iteration Number of iteration to go through
void Train(T_Trainer* trainer, double nu, int iteration){

    // Retrieving trainer infos
    T_Network* network = trainer->Network;
    int nbSets = trainer->nbSets;
    double** setsOfInputs = trainer->SetsOfInputs;
    double** setsOfTargets = trainer->SetsOfTargets;

    // Wishing user good luck
    printf("Started training for %d cycles, Good luck ! \n\n", iteration);

    // Entering cycle process
    double percentage = 0; double milestone = 0;
    for (int i = 0; i < iteration; ++i) {

        percentage = (double)(i*10)/(double)iteration;

        // Do a full cycle
        for (int j = 0; j < nbSets; ++j) {
            SetNetworkInputs_Auto(network, setsOfInputs[j]);
            RunNetwork(network);
            BackPropagate_AUTO(network, nu, setsOfTargets[j]);
        }

        // Print a progress bar
        while (percentage >= milestone){
            printf("[");
            for (int k = 0; k < milestone; ++k)
                printf("=");
            for (int l = 0; l < 10 - milestone; ++l)
                printf("-");
            printf("] Training in process...\n");
            milestone += 1;
        }
    }

    printf("Network trained !\n");
}


/// Print the results of all sets of inputs.
/// \param trainer Pointer to the trainer
void ShowResults(T_Trainer* trainer){

    printf("Printing training results : \n\n");

    // Retrieving network info
    T_Network* network = trainer->Network;
    int** sizeLayers = network->sizeLayers;
    int lengthInput = *sizeLayers[0] - 1;
    int lengthOutput = *sizeLayers[*network->nbLayers - 1];
    T_Node** outputNodes = network->Layers[*network->nbLayers - 1]->nodes;

    // Naming necessary variables
    double* iSetIn; double* iSetTarget; double iSetOut[lengthOutput];
    double sumResults; double sumTargets; double globalError = 0; double ierror;

    // Iterating for each individual set
    for (int i = 0; i < trainer->nbSets; ++i) {

        // Retrieving set
        iSetIn = trainer->SetsOfInputs[i];
        iSetTarget = trainer->SetsOfTargets[i];

        // Updating network
        SetNetworkInputs_Auto(network, iSetIn);
        RunNetwork(network);

        // Retrieving results
        for (int j = 0; j < lengthOutput; ++j)
            iSetOut[j] = outputNodes[j]->val;

        // Printing inputs
        printf("Results of set %d : \n|", i);
        for (int k = 0; k < lengthInput; ++k)
            printf("%f|", iSetIn[k]);

        // Printings target
        sumTargets = 0;
        printf("\nExpected Values : \n|");
        for (int k = 0; k < lengthOutput; ++k){
            printf("%f|", iSetTarget[k]);
            sumTargets += iSetTarget[k];
        }

        // Printing result
        sumResults = 0;
        printf("\nNetwork responded : \n|");
        for (int k = 0; k < lengthOutput; ++k){
            printf("%f|", iSetOut[k]);
            sumResults += iSetOut[k];
        }

        // Printing error
        if (sumTargets != 0)
            ierror = 100*fabs(sumResults - sumTargets) / fabs(sumTargets);
        else
            ierror = fabs(sumResults) / (0.01);
        printf("\nNetwork was off by %f %%.\n\n", ierror);
        globalError += ierror;
    }

    // Printing global error
    globalError /= trainer->nbSets;
    printf("Network overall error is : %f %%\n\n", globalError);
}


/// Free the memory occupied by a trainer.
/// \param trainer Pointer to the trainer to delete
void FreeTrainer(T_Trainer *trainer) {

    FreeNetwork(trainer->Network);

    for (int i = 0; i < trainer->nbSets; ++i) {
        free(trainer->SetsOfInputs[i]);
        free(trainer->SetsOfTargets[i]);
    }
    free(trainer->SetsOfInputs);
    free(trainer->SetsOfTargets);
    free(trainer);
}
