//
// Created by root on 10/11/18.
//

#ifndef OCR_PROJECT_BINARIZER_H
#define OCR_PROJECT_BINARIZER_H

#include <stdlib.h>
#include <stdio.h>


typedef struct S_TrainingChar {
    char target;
    int size;
    double* values;
} T_TrainingChar;


typedef struct S_TrainingResource {
    int nbTargets;
    char* Targets;
    int* nbDuplicates;
    T_TrainingChar*** Duplicates;
} T_TrainingResource;


/// Saves a training char in a binary file
/// \param trainingChar Pointer to the char to save
/// \param path Path to saving location
void SaveTrainingChar(T_TrainingChar* trainingChar, char* path);


/// Loads a training char from a binary file
/// \param path Path to the file to load
/// \return Pointer to the training char
T_TrainingChar* LoadTrainingChar(char* path);


/// Initialize and organize the training chars to help for traning
/// \param nbTrainingChars Number of training chars to organize
/// \param TrainingChars Pointer array of the training chars
/// \return A pointer to the initialized Training Resource
T_TrainingResource* InitializeTrainingRessource(int nbTrainingChars, T_TrainingChar** TrainingChars);


/// Print infos on a training resource
/// \param trainingResource Pointer to the training resource
void PrintTrainingRessources(T_TrainingResource* trainingResource);

#endif //OCR_PROJECT_BINARIZER_H