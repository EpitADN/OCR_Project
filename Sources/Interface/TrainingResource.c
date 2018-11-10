//
// Created by root on 10/11/18.
//

#include "TrainingResource.h"

/// Saves a training char in a binary file
/// \param trainingChar Pointer to the char to save
/// \param path Path to saving location
void SaveTrainingChar(T_TrainingChar* trainingChar, char* path){

    FILE *fp;

    if ((fp = fopen(path,"wb")) == NULL)
    {
        printf("Error opening for save file");
        exit(1);
    }

    fwrite(&trainingChar->target, sizeof(char), 1, fp);
    fwrite(&trainingChar->size, sizeof(int), 1, fp);

    for (int i = 0; i < trainingChar->size; ++i)
        fwrite(&trainingChar->values[i], sizeof(double), 1, fp);

    fclose(fp);
}


/// Loads a training char from a binary file
/// \param path Path to the file to load
/// \return Pointer to the training char
T_TrainingChar* LoadTrainingChar(char* path){

    FILE *fp;

    if ((fp = fopen(path,"rb")) == NULL)
    {
        printf("Error opening for save file");
        exit(1);
    }

    T_TrainingChar* trainingChar = malloc(sizeof(T_TrainingChar));

    fread(&trainingChar->target, sizeof(char), 1, fp);
    fwrite(&trainingChar->size, sizeof(int), 1, fp);

    trainingChar->values = malloc(trainingChar->size * sizeof(double));
    for (int i = 0; i < trainingChar->size; ++i)
        fwrite(&trainingChar->values[i], sizeof(double), 1, fp);

    fclose(fp);

    return trainingChar;
}


/// Initialize and organize the training chars to help for traning
/// \param nbTrainingChars Number of training chars to organize
/// \param TrainingChars Pointer array of the training chars
/// \return A pointer to the initialized Training Resource
T_TrainingResource* InitializeTrainingRessource(int nbTrainingChars, T_TrainingChar** TrainingChars){


    int nbTargets = 0;
    char* Targets = malloc(nbTrainingChars * sizeof(char));
    int* nbDuplicates = malloc(nbTrainingChars * sizeof(int));
    T_TrainingChar*** Duplicates = malloc(nbTrainingChars * sizeof(T_TrainingChar**));


    int iTarget;
    T_TrainingChar* iTrainingChar;

    for (int i = 0; i < nbTrainingChars; ++i) {

        iTarget = 0;

        // Load a trainingChar
        iTrainingChar = TrainingChars[i];

        // Search for already existing target
        while (iTarget < nbTargets && iTrainingChar->target != Targets[iTarget])
            iTarget++;


        if (iTarget == nbTargets) {

            // It's a new target
            nbTargets++;

            // Save the target
            Targets[iTarget] = iTrainingChar->target;
            nbDuplicates[iTarget] = 1;

            // Allocate memory for the upcoming duplicates
            Duplicates[iTarget] = malloc(nbTrainingChars * sizeof(T_TrainingChar*));

            // Save the training char
            Duplicates[iTarget][0] = iTrainingChar;

        } else {

            // It's a duplicate
            nbDuplicates[iTarget]++;

            // Save it with the others
            Duplicates[iTarget][nbDuplicates[iTarget] - 1] = iTrainingChar;

        }

    }

    // Iterated on each Training Char, now we can size down the memory :
    Targets = realloc(Targets, nbTargets * sizeof(char));
    nbDuplicates = realloc(nbDuplicates, nbTargets * sizeof(int));
    for (int jTarget = 0; jTarget < nbTargets; ++jTarget)
        Duplicates[jTarget] = realloc(Duplicates[jTarget], nbDuplicates[jTarget] * sizeof(T_TrainingChar*));


    // Allocation memory for the Resource
    T_TrainingResource* trainingResource = malloc(sizeof(T_TrainingResource));

    // Assigning parameters
    trainingResource->nbTargets = nbTargets;
    trainingResource->Targets = Targets;
    trainingResource->nbDuplicates = nbDuplicates;
    trainingResource->Duplicates = Duplicates;

    return trainingResource;

}