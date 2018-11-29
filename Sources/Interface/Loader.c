//
// Created by root on 29/11/18.
//

#include "Loader.h"


T_Trainer* CreateTrainer_FromResource(T_Network* Network, T_TrainingResource* Resource) {

    // Retrieving info
    size_t nbTargets = Resource->nbTargets;
    int size = Resource->size;
    int lastlayer = *Network->nbLayers-1;

    // Verifying Compatibility
    if (size != *Network->sizeLayers[0] - 1)
        printf("Resource not compatible with network : Size differs ! (%d vs %d)", size, *Network->sizeLayers[0]);
    if (nbTargets != *Network->sizeLayers[lastlayer])
        printf("Resource not compatible with network : Wrong targets ! (%d vs %d)", nbTargets, *Network->sizeLayers[lastlayer]);

    // Calculating total number of images
    int nbTotalChars = 0;
    for (int i = 0; i < nbTargets; ++i)
        nbTotalChars += Resource->nbDuplicates[i];

    // Allocating memory for sets of inputs and outputs
    double** SetsOfInputs = malloc(nbTotalChars * sizeof(double*));
    double** SetsOfOutputs = malloc(nbTotalChars * sizeof(double*));


    int iChar = 0;
    for (int iT = 0; iT < nbTargets; ++iT) {
        for (int jD = 0; jD < Resource->nbDuplicates[iT]; ++jD) {

            SetsOfInputs[iChar] = malloc(size*sizeof(double));
            SetsOfOutputs[iChar] = calloc(nbTargets, sizeof(double));

            for (int i = 0; i < size; ++i)
                SetsOfInputs[iChar][i] = Resource->TrainingChars[iT][jD].values[i];

            SetsOfOutputs[iChar][iT] = 1;

            iChar++;
        }
    }

    return CreateTrainer_Auto(Network, nbTotalChars, SetsOfInputs, SetsOfOutputs);
}


char DryRun(T_Network* Network, char* Targets, char* imagePath) {

    init_sdl();
    SDL_Surface* image;

    T_TrainingChar trainingChar = TransformTrainingChar(imagePath, *Network->sizeLayers[0], image);

    SetNetworkInputs_Auto(Network, trainingChar.values);
    RunNetwork(Network);

    double maxValue = -1;
    int maxTarget = -1;
    int lastLayer = *Network->nbLayers - 1;
    T_Node** outputNodes = Network->Layers[lastLayer]->nodes;

    double ivalue;
    for (int i = 0; i < *Network->sizeLayers[lastLayer]; ++i) {
        ivalue = outputNodes[i]->val;
        if (ivalue > maxValue) {
            maxValue = ivalue;
            maxTarget = i;
        }
    }

    printf("Network is at %d sure that %s is a '%c' !", (int)(maxValue*100), imagePath, Targets[maxTarget]);

    return Targets[maxTarget];
}