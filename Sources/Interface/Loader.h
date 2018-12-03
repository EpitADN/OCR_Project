//
// Created by root on 29/11/18.
//

#ifndef OCR_PROJECT_LOADER_H
#define OCR_PROJECT_LOADER_H

#include "../NeuralNetwork/Trainer.h"
#include "TrainingResource.h"


T_Trainer* CreateTrainer_FromResource(T_Network* network, T_TrainingResource* trainingResource);

void FillTrainer_ByLetters(T_TrainingResource* Resource, double** SetsOfInputs, double** SetsOfOutputs, int* nbTotalChars);

void FillTrainer_Balanced(T_TrainingResource* Resource, double** SetsOfInputs, double** SetsOfOutputs, int* nbTotalChars);

char DryRun(T_Network* Network, char* Targets, T_TrainingChar* trainingChar);

char DryRun_FromPath(T_Network* Network, char* Targets, char* imagePath);

#endif //OCR_PROJECT_LOADER_H
