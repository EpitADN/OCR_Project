//
// Created by corentin on 24/10/18.
//
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "UI.h"
#include "Network.h"
#include "Trainer.h"



int** parser(int* nblayers, char* entre)
{
    int** sizeLayers = malloc(*nblayers * sizeof(int*));

    int ichar = 0;
    int tmp=0;


    for(int isize=0; isize < *nblayers; isize++)
    {
        while(entre[ichar] == ' ')
        {
            ichar++;
        }

        tmp =0;
        while(entre[ichar] != ' ')
        {
            tmp = 10 * tmp + (int)(entre[ichar]);
            ichar++;
        }

        sizeLayers[isize] = malloc(sizeof(int));
        sizeLayers[isize] = tmp;

    }
    return sizeLayers;
}

char* resultat(T_Trainer* trainer)
{
    char *ret = malloc(50000000 * sizeof(char));



     ret  = strcat(ret,"Printing training results : \n\n");

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
        ret = strcat(ret,"Results of set " );
        ret = ret + i;
        ret = strcat(ret,": \n|");
        for (int k = 0; k < lengthInput; ++k)
            ret = ret + (char)(iSetIn[k]);

        // Printings target
        sumTargets = 0;
        ret = strcat(ret,("\nExpected Values : \n|"));
        for (int k = 0; k < lengthOutput; ++k){
            ret = ret + (char)(iSetTarget[k]);
            sumTargets += iSetTarget[k];
        }

        // Printing result
        sumResults = 0;
        ret = strcat(ret,("\nNetwork responded : \n|"));
        for (int k = 0; k < lengthOutput; ++k){
            ret = ret +(char)(iSetOut[k]);
            sumResults += iSetOut[k];
        }

        // Printing error
        if (sumTargets != 0)
            ierror = 100*fabs(sumResults - sumTargets) / fabs(sumTargets);
        else
            ierror = fabs(sumResults) / (0.01);
        ret = strcat(ret,("\nNetwork was off by " ));
        ret = ret + (char)ierror;
        ret = strcat(ret,"%.\n\n");
        globalError += ierror;
    }

    // Printing global error
    globalError /= trainer->nbSets;
    ret = strcat(ret,("Network overall error is : "));
    ret = ret + (char)globalError;
    ret = strcat(ret,"%\n\n");

    return ret;
}

