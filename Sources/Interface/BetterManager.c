//
// Created by root on 05/12/18.
//

#include <unistd.h>
#include <stdlib.h>
#include "Evaluation.h"
#include "../NeuralNetwork/SaveAndLoad.h"


int main(int argc, char* argv[]) {

    // Initializing arguments
    char* trainerName;
    char* resourceName;
    int ITERATION;
    double NU;
    int CHECKPOINT;

    // Saves parameters
    char* resourceFolder = "./Resource/";
    char* saveFolder = "./Saves/";
    char* extensionB = ".bin";
    char* extensionT = ".txt";

    // Verifying numbers of parameters :
    if (argc < 3 || argc > 6){
        printf("Bad numbers of parameters : must be called with 'trainerName', 'resourceName', ITERATION, NU, and CHECKPOINT (last 3 optional).\n.");
        exit(-1);
    }

    // Initializing arguments
    trainerName = argv[1];
    resourceName = argv[2];

    // Reading parameters and auto-setting

    if (argc >= 4)
        ITERATION = atoi(argv[3]);
    else
        ITERATION = 100;

    if (argc >= 5)
        NU = atof(argv[4]);
    else
        NU = 0.5;

    if (argc >= 6)
        CHECKPOINT = atoi(argv[5]);
    else
        CHECKPOINT = 5;


    // Verifying integrity
    if (ITERATION <= 0 || NU <= 0 || CHECKPOINT <= 0){
        printf("Error parsing parameters, we got : Iteration = %d, Nu = %lf, Checkpoint = %d.\n", ITERATION, NU, CHECKPOINT);
        exit(-1);
    }


    // Concatening resource path
    char* resourcePath = malloc(strlen(resourceFolder)+strlen(resourceName)+strlen(extensionB)+1);
    resourcePath[0] = '\0';
    strcat(resourcePath, resourceFolder);
    strcat(resourcePath, resourceName);
    strcat(resourcePath, extensionB);

    // Concatening trainer path
    char* trainerPath = malloc(strlen(saveFolder)+strlen(trainerName)+strlen(extensionB)+1);
    trainerPath[0] = '\0';
    strcat(trainerPath, saveFolder);
    strcat(trainerPath, trainerName);
    strcat(trainerPath, extensionB);

    // Concatening data path
    char* dataPath = malloc(strlen(saveFolder)+strlen(trainerName)+strlen(extensionT)+1);
    dataPath[0] = '\0';
    strcat(dataPath, saveFolder);
    strcat(dataPath, trainerName);
    strcat(dataPath, extensionT);


    // Printing recap
    printf("================================\n\n");

    printf("Hello, World!\n");
    printf("Trainer path =  '%s',\n"
           "Resource path = '%s',\n"
           "Data path =  '%s'.\n"
           "Iteration : %d ; Nu = %lf ;\n"
           "Evaluating every %d cycles.\n",
           trainerPath, resourcePath, dataPath,
           ITERATION, NU, CHECKPOINT);

    // Separator
    printf("\n================================\n\n");
    // ------------------------------------------------------------ //


    // Loading Trainer and Resource
    printf("Loading Trainer save at '%s' ... \n", trainerPath);
    T_Trainer* trainer = LoadTrainer(trainerPath);
    printf("Done !\n\nLoading Resource save at '%s' ... \n", resourcePath);
    T_TrainingResource* trainingResource = LoadTrainingResource(resourcePath);
    printf("Done !\n");


    // Separator
    printf("\n================================");
    printf("\n================================");
    printf("\n================================\n\n");
    // ------------------------------------------------------------ //

    // Pre-Training print
    PrintTrainingResource(trainingResource);

    // Separator
    printf("\n================================\n\n");
    // ------------------------------------------------------------ //

    // Pre-Training print
    PrintAllNetworkInfos(trainer->Network, 0);

    // Separator
    printf("================================\n");
    printf("================================\n");
    printf("================================\n\n");
    // ------------------------------------------------------------ //


    printf("TRAINING network and EVALUATING : \n");


    int iCycle = 0;
    int iScore = 0;
    FILE* dataFile;
    char buffer[12];

    while (iCycle < ITERATION) {

        // Separator
        printf("\n================================\n\n");

        // Training and evaluating
        Train(trainer, NU, CHECKPOINT);
        printf("\n");
        iScore = Evaluate(trainer->Network, trainingResource, 100);
        iCycle += CHECKPOINT;

        printf("\nNetwork got a score of %d%% !\n", iScore);

        // Writing score
        dataFile = fopen(dataPath, "a");
        fprintf(dataFile, "%d\n", iScore);
        fclose(dataFile);

        printf("\n'%s' updated.\n", dataPath);
    }


    // Separator
    printf("\n================================");
    printf("\n================================");
    printf("\n================================\n\n");
    // ------------------------------------------------------------ //

    // Post-Training print
    ShowResults(trainer, 28);

    // Saving trainer
    SaveTrainer(trainer, trainerPath);

    // Freeing memory
    FreeTrainingResource(trainingResource);
    FreeTrainer(trainer);
    free(resourcePath);
    free(trainerPath);
    free(dataPath);

}