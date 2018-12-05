//
// Created by root on 29/11/18.
//

#include "Loader.h"


T_Trainer* CreateTrainer_FromResource(T_Network* Network, T_TrainingResource* Resource) {

    // Retrieving info
    int nbTargets = Resource->nbTargets;
    int size = Resource->size;
    int lastlayer = *Network->nbLayers-1;

    // Verifying Compatibility
    if (size != *Network->sizeLayers[0] - 1)
        printf("Resource not compatible with network : Size differs ! (%d vs %d)", size, *Network->sizeLayers[0]);
    if (nbTargets != *Network->sizeLayers[lastlayer])
        printf("Resource not compatible with network : Wrong targets ! (%d vs %d)", nbTargets, *Network->sizeLayers[lastlayer]);


    double** SetsOfInputs = NULL;
    double** SetsOfOutputs = NULL;
    int nbTotalChars = 0;


    //FillTrainer_ByLetters(Resource, SetsOfInputs, SetsOfOutputs, &nbTotalChars);
    FillTrainer_Balanced(Resource, SetsOfInputs, SetsOfOutputs, &nbTotalChars);

    printf("A total of %d images have been added to the trainer.\n", nbTotalChars);

    return CreateTrainer_Auto(Network, nbTotalChars, SetsOfInputs, SetsOfOutputs);
}


void FillTrainer_ByLetters(T_TrainingResource* Resource, double** SetsOfInputs, double** SetsOfOutputs, int* nbTotalChars) {

    // Retrieving info
    int nbTargets = Resource->nbTargets;
    int size = Resource->size;

    // Calculating total number of images
    for (int i = 0; i < nbTargets; ++i)
        *nbTotalChars += Resource->nbDuplicates[i];

    // Allocating memory for sets of inputs and outputs
    SetsOfInputs = malloc(*nbTotalChars * sizeof(double*));
    SetsOfOutputs = malloc(*nbTotalChars * sizeof(double*));


    int iChar = 0;
    for (int iT = 0; iT < nbTargets; ++iT) {
        for (int jD = 0; jD < Resource->nbDuplicates[iT]; ++jD) {

            SetsOfInputs[iChar] = malloc(size*sizeof(double));
            SetsOfOutputs[iChar] = calloc((size_t)nbTargets, sizeof(double));

            for (int i = 0; i < size; ++i)
                SetsOfInputs[iChar][i] = Resource->TrainingChars[iT][jD].values[i];

            SetsOfOutputs[iChar][iT] = 1;

            iChar++;
        }
    }

}


void FillTrainer_Balanced(T_TrainingResource* Resource, double** SetsOfInputs, double** SetsOfOutputs, int* nbTotalChars) {

    // Retrieving info
    int nbTargets = Resource->nbTargets;
    int size = Resource->size;

    // Calculating total number of images
    for (int i = 0; i < nbTargets; ++i){
        if (*nbTotalChars == 0 || Resource->nbDuplicates[i] < *nbTotalChars)
            *nbTotalChars = Resource->nbDuplicates[i];
    }
    *nbTotalChars *= Resource->nbTargets;


    // Allocating memory for sets of inputs and outputs
    SetsOfInputs = malloc(*nbTotalChars * sizeof(double*));
    SetsOfOutputs = malloc(*nbTotalChars * sizeof(double*));


    int iChar = 0;
    for (int jD = 0; jD < Resource->nbDuplicates[0]; ++jD) {
        for (int iT = 0; iT < nbTargets; ++iT) {

            SetsOfInputs[iChar] = malloc(size*sizeof(double));
            SetsOfOutputs[iChar] = calloc(nbTargets, sizeof(double));

            for (int i = 0; i < size; ++i)
                SetsOfInputs[iChar][i] = Resource->TrainingChars[iT][jD].values[i];

            SetsOfOutputs[iChar][iT] = 1;

            iChar++;
        }
    }
}


char DryRun_FromPath(T_Network* Network, char* Targets, char* imagePath) {

    init_sdl();
    SDL_Surface* image;

    T_TrainingChar trainingChar = TransformTrainingChar(imagePath, *Network->sizeLayers[0] - 1, image);

    return DryRun(Network, Targets, &trainingChar);
}


char DryRun(T_Network* Network, char* Targets, T_TrainingChar* trainingChar){

    SetNetworkInputs_Auto(Network, trainingChar->values);
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

    printf("Network is at %d%% sure that this image is a '%c' !\n", (int)(maxValue*100), Targets[maxTarget]);

    return Targets[maxTarget];
}