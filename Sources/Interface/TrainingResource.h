//
// Created by root on 10/11/18.
//

#ifndef OCR_PROJECT_BINARIZER_H
#define OCR_PROJECT_BINARIZER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

typedef struct S_TrainingChar {
    double* values;
} T_TrainingChar;


typedef struct S_TrainingResource {
    int size;
    int nbTargets;
    char* Targets;
    int* nbDuplicates;
    T_TrainingChar** TrainingChars;
} T_TrainingResource;


/* STRUCTURE OF RESOURCE FOLDER*
 *
 * --- '_config.txt' file:
 *
 * 28\n     %- Height of chars
 * 28\n     %- Width of chars
 * 3\n      %- Number of targets
 * abc\n    %- Targets as chars
 * 2\n      %- Duplicates of 1st target
 * 3\n      %- Duplicates of 2nd target
 * 4\n      %- etc...
 *
 * --- Folder :
 *
 *  |- TRAINING_FOLDER/
 *      |- _config.txt
 *      |- a /
 *          |- a0.bmp
 *          |- a1.bmp
 *      |- b /
 *          |- b0.bmp
 *          |- b1.bmp
 *          |- b2.bmp
 *      |- c /
 *          |- c0.bmp
 *          |- c1.bmp
 *          |- c2.bmp
 *          |- c3.bmp
 *
 */


/// Transforms (initializes) and organizes the training material
/// WARNING : Folder must contain a '_config.txt' file and be correctly structured
/// \param folder Path to the folder containing the sample
/// \return A pointer to the initialized Training Resource
T_TrainingResource* TransformTrainingResource(char* folder);


/// Loads Training Chars associated with a training resource
/// \param folder Path to the training folder
/// \param trainingResource Pointer to the concerned trainingResource
void LoadTrainingChars(char* targetFolder, T_TrainingResource* trainingResource);


/// Loads a Training Char from path (matrix of values)
/// \param path Path of the Training char
/// \return The Training char
T_TrainingChar LoadTrainingChar(char* path);


/// Prints info on a training resource
/// \param trainingResource Pointer to the training resource
void PrintTrainingResource(T_TrainingResource* trainingResource);


/// Saves the training resource in one unique binary file
/// \param trainingResource Pointer to the training resource
/// \param path Folder/name to save in
void SaveTrainingResource(T_TrainingResource* trainingResource, char* path);


/// Loads the Training Resource from a unique file
/// \param path Path to the file to load
/// \return A pointer to the loaded Training Resource
T_TrainingResource* LoadTrainingResource(char* path);


/// Free the memory occupied by a training resource
/// \param trainingResource Pointer to the resource to delete
void FreeTrainingResource(T_TrainingResource* trainingResource);

#endif //OCR_PROJECT_BINARIZER_H