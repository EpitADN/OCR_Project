//
// Created by root on 10/11/18.
//

#ifndef OCR_PROJECT_BINARIZER_H
#define OCR_PROJECT_BINARIZER_H

#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <string.h>
#include <dirent.h>
#include "Toolbox_SDL.h"

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


/// Transforms Training Chars associated with a training resource
/// \param duplicatesPath Path to the training folder containing duplicates
/// \param trainingChars Pointer to the concerned trainingChars
/// \param maxChars Expected number of duplicates
/// \param charSize Size (h*w) of a training char
/// \param image Surface to load upon
void TransformTrainingChars(char* duplicatesPath, T_TrainingChar* trainingChars, int maxChars, int charSize, SDL_Surface* image);


/// Transform a Training Char from path (bmp image)
/// \param charPath Path of the Training char
/// \param charSize Size (h*w) of a training char
/// \param image Surface to load upon
/// \return the Training char
T_TrainingChar TransformTrainingChar(char* charPath, int charSize, SDL_Surface* image);


/// Prints info on a training resource
/// \param trainingResource Pointer to the training resource
void PrintTrainingResource(T_TrainingResource* trainingResource);


/// Saves the training resource in one unique binary file
/// \param trainingResource Pointer to the training resource
/// \param path Folder/name to save in
void SaveTrainingResource(T_TrainingResource* trainingResource, char* path);


/// Save a training char to specified file
/// \param trainingChar Pointer to the training char to be saved
/// \param size Size of the training char (height*width)
/// \param fp Save file pointer
void SaveTrainingChar(T_TrainingChar* trainingChar, int size, FILE* fp);


/// Loads the Training Resource from a unique file
/// \param path Path to the file to load
/// \return A pointer to the loaded Training Resource
T_TrainingResource* LoadTrainingResource(char* path);


/// Loads a training char from a file
/// \param size Size of the training file
/// \param fp File pointer to the save
/// \return The training char as double array
T_TrainingChar LoadTrainingChar(int size, FILE* fp);

/// Free the memory occupied by a training resource
/// \param trainingResource Pointer to the resource to delete
void FreeTrainingResource(T_TrainingResource* trainingResource);

#endif //OCR_PROJECT_BINARIZER_H