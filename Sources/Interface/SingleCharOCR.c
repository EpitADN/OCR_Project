//
// Created by root on 30/11/18.
//

#include "Loader.h"
#include "../NeuralNetwork/SaveAndLoad.h"

int main(int argc, char* argv[]) {

    // Initializing arguments
    char* networkName;
    char* Targets;
    char* imagePath;

    // Saves parameters
    char* saveFolder = "./Saves/";
    char* extension = ".bin";

    // Verifying numbers of parameters :
    if (argc != 4){
        printf("Bad numbers of parameters : must be called with 'networkName', 'Targets', and 'imagePath'.");
        exit(-1);
    }

    // Initializing arguments
    networkName = argv[1];
    Targets = argv[2];
    imagePath = argv[3];

    // Concatening path
    char* networkPath = malloc(strlen(saveFolder)+strlen(networkName)+strlen(extension)+1);
    networkPath[0] = '\0';
    strcat(networkPath, saveFolder);
    strcat(networkPath, networkName);
    strcat(networkPath, extension);

    // Separator
    printf("================================\n\n");
    // ------------------------------------------------------------ //

    printf("Hello, World!\n");
    printf("Network path = '%s',\n"
           "Possible targets =  '%s',\n"
           "Image path =  '%s'.\n\n",
           networkPath, networkPath, imagePath);

    // Separator
    printf("================================\n\n");
    // ------------------------------------------------------------ //

    printf("Loading network ...\n");
    T_Network* network = LoadNetwork(networkPath);
    printf("Done !\n\n");

    printf("Loading image and analysing... \n");
    DryRun(network, Targets, imagePath);

    // Separator
    printf("\n================================\n");
    // ------------------------------------------------------------ //

    // Freeing memory
    FreeNetwork(network);
    free(networkPath);

}
