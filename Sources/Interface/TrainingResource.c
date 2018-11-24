//
// Created by root on 10/11/18.
//

#include "TrainingResource.h"

/// Transforms (initializes) and organizes the training material
/// WARNING : Folder must contain a '_config.txt' file and be correctly structured
/// \param folder Path to the folder containing the sample
/// \return A pointer to the initialized Training Resource
T_TrainingResource* TransformTrainingResource(char* folder) {

    // Allocating memory for config path
    char* config = "_config.txt";

    char* pathConfig = malloc( (strlen(folder)+strlen(config)) * sizeof(char));
    pathConfig[0] = '\0';

    // Concatening path
    strcat(pathConfig, folder);
    strcat(pathConfig, config);

    // Open config file
    FILE* fp;
    if ((fp = fopen(pathConfig, "r")) == NULL){
        printf("Error opening for config file at %s\n", pathConfig);
        exit(1);
    }

    char buffer[60];
    int index;

    // Reading height
    int height = 0;
    if (fgets(buffer, 60, fp) == NULL){
        printf("Error reading height\n");
        exit(1);
    }
    height = atoi(buffer);

    // Reading width
    int width = 0;
    if (fgets(buffer, 60, fp) == NULL){
        printf("Error reading width\n");
        exit(1);
    }
    width = atoi(buffer);

    // Reading number of targets
    int nbTargets = 0;
    if (fgets(buffer, 60, fp) == NULL){
        printf("Error reading number of targets\n");
        exit(1);
    }
    nbTargets = atoi(buffer);

    // Reading targets
    index = 0; char* Targets = malloc(nbTargets * sizeof(char));
    if (fgets(buffer, 60, fp) == NULL){
        printf("Error reading targets\n");
        exit(1);
    }
    while (buffer[index] != '\n'){
        Targets[index] = buffer[index];
        index++;
    }

    // Reading number of duplicates
    int* nbDuplicates = malloc(nbTargets * sizeof(int));
    for (int i = 0; i < nbTargets; ++i) {

        // Reading number of duplicate for target i
        index = 0; nbDuplicates[index] = 0;
        if (fgets(buffer, 60, fp) == NULL){
            printf("Error reading number of duplicates for target %c\n", Targets[i]);
            exit(1);
        }
        nbDuplicates[i] = atoi(buffer);

    }


    // Initialize Training Resource
    T_TrainingResource* trainingResource = malloc(sizeof(T_TrainingResource));
    trainingResource->TrainingChars = malloc(nbTargets * sizeof(T_TrainingChar*));
    trainingResource->size = height*width;
    trainingResource->nbTargets = nbTargets;
    trainingResource->Targets = Targets;
    trainingResource->nbDuplicates= nbDuplicates;

    // Closing config file
    free(pathConfig);
    fclose(fp);

    // Loading Images
    char targetPath[] = "X/";
    for (int j = 0; j < nbTargets; ++j) {

        trainingResource->TrainingChars[j] = malloc(trainingResource->nbDuplicates[j] * sizeof(T_TrainingChar));

        buffer[0] = '\0';
        strcat(buffer, folder);
        strcat(buffer, targetPath);
        buffer[strlen(folder)] = Targets[j];

        printf("Looking in directory %s\n", buffer);
        LoadTrainingChars(buffer, trainingResource);
    }

    return trainingResource;

}


/// Loads Training Chars associated with a training resource
/// \param folder Path to the training folder
/// \param trainingResource Pointer to the concerned trainingResource
void LoadTrainingChars(char* targetFolder, T_TrainingResource* trainingResource){

    DIR* targetDir;

    if ((targetDir = opendir(targetFolder)) == NULL){
        printf("Error opening directory %s :\n", targetFolder);
        exit(1);
    }

    int nbfiles = 0;
    struct dirent* dir;
    while ((dir = readdir(targetDir)) != NULL) {

        if (dir->d_type != DT_REG)
            continue;

        printf(" -- %s\n", dir->d_name);
        nbfiles++;
    }

    printf("Total number of files found : %d\n\n", nbfiles);
    closedir(targetDir);

}

/// Loads a Training Char from path (matrix of values)
/// \param path Path of the Training char
/// \return The Training char
T_TrainingChar LoadTrainingChar(char* path) {

    // TODO
    exit(1);

}


/// Prints info on a training resource
/// \param trainingResource Pointer to the training resource
void PrintTrainingResource(T_TrainingResource* trainingResource) {

    // TODO
    exit(1);

}


/// Saves the training resource in one unique binary file
/// \param trainingResource Pointer to the training resource
/// \param path Folder/name to save in
void SaveTrainingResource(T_TrainingResource* trainingResource, char* path) {

    // TODO
    exit(1);

}


/// Loads the Training Resource from a unique file
/// \param path Path to the file to load
/// \return A pointer to the loaded Training Resource
T_TrainingResource* LoadTrainingResource(char* path) {

    // TODO
    exit(1);

}


/// Free the memory occupied by a training resource
/// \param trainingResource Pointer to the resource to delete
void FreeTrainingResource(T_TrainingResource* trainingResource) {


    for (int i = 0; i < trainingResource->nbTargets; ++i) {
        /*
        for (int j = 0; j < trainingResource->nbDuplicates[i]; ++j) {
            free(trainingResource->TrainingChars[i][j].values);
        }
         */
        free(trainingResource->TrainingChars[i]);
    }
    free(trainingResource->Targets);
    free(trainingResource->nbDuplicates);
    free(trainingResource->TrainingChars);
    free(trainingResource);

}