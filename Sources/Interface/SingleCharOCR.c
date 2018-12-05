//
// Created by root on 30/11/18.
//

#include "Loader.h"
#include "../NeuralNetwork/SaveAndLoad.h"

int main(int argc, char* argv[]) {

    // Base args
    char* defaultNetwork = "Trainer_576_FULL_Balanced";
    char* defaultTargets = "0123456789aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ";

    // Initializing arguments
    char* imagePath;
    char* networkName;
    char* Targets;

    // Saves parameters
    char* saveFolder = "./Saves/";
    char* extension = ".bin";

    // Verifying numbers of parameters :
    if (argc != 2 && argc != 3 && argc != 4){
        printf("Bad numbers of parameters : must be called with 'imagePath', 'networkName', and 'Targets' (last 2 optional).");
        exit(-1);
    }

    // Initializing arguments

    imagePath = argv[1];

    if (argc >= 3)
        networkName = argv[2];
    else
        networkName = defaultNetwork;

    if (argc >= 4)
        Targets = argv[3];
    else
        Targets = defaultTargets;



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
    DryRun_FromPath(network, Targets, imagePath);

    // Separator
    printf("\n================================\n");
    // ------------------------------------------------------------ //

    // Freeing memory
    FreeNetwork(network);
    free(networkPath);

}
