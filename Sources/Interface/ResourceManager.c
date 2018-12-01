//
// Created by root on 24/11/18.
//

#include <unistd.h>
#include "Loader.h"
#include "../NeuralNetwork/SaveAndLoad.h"

int main(int argc, char* argv[]){


    // Initializing arguments
    char* resourceName;
    char* networkName;
    char* trainerName;

    // Saves parameters
    char* resourceFolder = "./Resource/";
    char* saveFolder = "./Saves/";
    char* extension = ".bin";

    // Verifying numbers of parameters :
    if (argc != 4){
        printf("Bad numbers of parameters : must be called with 'resourceName', 'networkName', and 'trainerName'.");
        exit(-1);
    }

    // Initializing arguments
    resourceName = argv[1];
    networkName = argv[2];
    trainerName = argv[3];

    // Concatening resource path
    char* resourcePath = malloc(strlen(resourceFolder)+strlen(resourceName)+strlen(extension)+1);
    resourcePath[0] = '\0';
    strcat(resourcePath, resourceFolder);
    strcat(resourcePath, resourceName);
    strcat(resourcePath, extension);

    // Concatening network path
    char* networkPath = malloc(strlen(saveFolder)+strlen(networkName)+strlen(extension)+1);
    networkPath[0] = '\0';
    strcat(networkPath, saveFolder);
    strcat(networkPath, networkName);
    strcat(networkPath, extension);

    // Concatening trainer path
    char* trainerPath = malloc(strlen(saveFolder)+strlen(trainerName)+strlen(extension)+1);
    trainerPath[0] = '\0';
    strcat(trainerPath, saveFolder);
    strcat(trainerPath, trainerName);
    strcat(trainerPath, extension);


    // Printing recap
    printf("================================\n\n");

    printf("Hello, World!\n");
    printf("Resource path = '%s',\n"
           "Network path =  '%s',\n"
           "Trainer path =  '%s'.\n\n",
           resourcePath, networkPath, trainerPath);

    // Separator
    printf("================================\n\n");
    // ------------------------------------------------------------ //


    // Creating resource
    T_TrainingResource* trainingResource;


    if( access(resourcePath, F_OK ) != -1 ){

        // Resource already exists : loading it
        printf("Found a existing training resource, loading file... \n");
        trainingResource = LoadTrainingResource(resourcePath);
        printf("Done !\n\n");

    } else {

        // Resource doesn't exist : transforming it
        printf("Training resource not found. Transforming one from '%s' ...\n\n", resourceFolder);
        trainingResource = TransformTrainingResource(resourceFolder);
        printf("\nTransformation complete. Saving resource at '%s' ...\n", resourcePath);
        SaveTrainingResource(trainingResource, resourcePath);
        printf("Done !\n\n");

    }

    // Printing of resource
    PrintTrainingResource(trainingResource);


    // Separator
    printf("\n================================\n\n");
    // ------------------------------------------------------------ //


    // Creating network
    T_Network* network;

    if( access(networkPath, F_OK ) != -1 ){

        // Network already exists : loading it
        printf("Found a existing network save, loading file... \n");
        network = LoadNetwork(networkPath);
        printf("Done !\n\n");

    } else {

        // Network doesn't exist : manual creation
        printf("Network save doesn't exist.\nStarting manual creation of network\n\n");
        network = CreateNetwork_Manual();
        printf("Saving network as '%s'...\n", networkPath);
        SaveNetwork(network, networkPath);
        printf("Done !\n\n");
    }

    // Printing of network
    PrintAllNetworkInfos(network);


    // Separator
    printf("================================\n\n");
    // ------------------------------------------------------------ //


    // Creating Trainer by merging network with resource
    printf("Creating Trainer by merging network with training resource...\n");
    T_Trainer* trainer = CreateTrainer_FromResource(network, trainingResource);
    printf("Trainer successfully created. Saving it as '%s' ...\n", trainerPath);
    SaveTrainer(trainer, trainerPath);
    printf("Done !\n\n");

    // Separator
    printf("================================\n");
    // ------------------------------------------------------------ //

    // Freeing memory
    FreeTrainingResource(trainingResource);
    FreeTrainer(trainer);
    free(resourcePath);
    free(networkPath);
    free(trainerPath);

    return 0;
}