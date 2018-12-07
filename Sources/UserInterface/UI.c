//
// Created by corentin on 24/10/18.
//
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "UI.h"
#include "../NeuralNetwork/SaveAndLoad.h"
#include "../Interface/Loader.h"
#include "../ImageProcess/mainSegmentation.h"

char* Targets = "0123456789aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ";
char* NetworkPath = "OfficialOCR.bin";

/*
void add_word(char s1[],char s2[])
{
    int i =0;
    while(s1[i] != '\0')
    {
        i++;
    }
    i++;
    s1[i] = ' ';

    int j=0;
    while(s2[j] != '\0')
    {
        s1[i] = s2[j];
        j++;
        i++;
    }
    s1[i+1] = '\0';
}


void Create_Xor_test(char* ret)
{
    T_Trainer* trainer = CreateTrainerXOR();
    Train(trainer, 0.2, 100);



    add_word(ret,"Printing training results : \n\n\0");

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
        add_word(ret,"Results of set \0" );
        ret = ret + i;
        add_word(ret,": \n|\0");
        for (int k = 0; k < lengthInput; ++k)
            tmp = (char)(iSetIn[k]) + '\0';
            add_word(ret,tmp);

        // Printings target
        sumTargets = 0;
        add_word(ret,("\nExpected Values : \n|\0"));
        for (int k = 0; k < lengthOutput; ++k){
            tmp = (char)(iSetTarget[k]) + '\0';
            add_word(ret,tmp);

            sumTargets += iSetTarget[k];
        }

        // Printing result
        sumResults = 0;
         add_word(ret,("\nNetwork responded : \n|\0"));
        for (int k = 0; k < lengthOutput; ++k){
            tmp = (char)(iSetOut[k]) + '\0';
            add_word(ret,tmp);
            sumResults += iSetOut[k];
        }

        // Printing error
        if (sumTargets != 0)
            ierror = 100*fabs(sumResults - sumTargets) / fabs(sumTargets);
        else
            ierror = fabs(sumResults) / (0.01);
        add_word(ret,("\nNetwork was off by '\0'" ));
        tmp = (char)ierror + '\0';
        add_word(ret,tmp);
        
        globalError += ierror;
    }

    // Printing global error
    globalError /= trainer->nbSets;
    add_word(ret,("Network overall error is : \0"));
    tmp = (char)globalError + '\0';
    add_word(ret,tmp);
    add_word(ret,"%\n\n'\0'");

    return ret;
}

void Create_Xor(char* ret)
{   
    T_Trainer* trainer = CreateTrainerXOR();
    Train(trainer, 0.2, 100);

    //Trouver avec tony comment bien affiche le network dans un char
}
*/

char* Result(char* im_path)
{
	printf("Loading network at %s ...\n", NetworkPath);
	T_Network *network = LoadNetwork(NetworkPath);
	
	printf("Done ! Running char through Network...\n");
	char answer = DryRun_FromPath(network, Targets, im_path);
	
	printf("Got : '%c'\n" , answer);
	FreeNetwork(network);

	char* ret = malloc(2*sizeof(char));
	ret[0] = answer;
	ret[1] = '\0';

	return ret;
}

char* Result_withSeg(char* im_path)
{
	T_Network *network = LoadNetwork(NetworkPath);
	char* ret = mainsegmen(im_path, network, Targets);
	FreeNetwork(network);
	return ret;
}
