//
// Created by Gireg Roussel on 06/10/2018.
//

#ifndef OCR_SAVEANDLOAD_H
#define OCR_SAVEANDLOAD_H

#include <stdlib.h>
#include <stdio.h>
#include "Network.h"
#include "Trainer.h"

void SaveTrainer(T_Trainer* trainer, char* path);

void SaveNetwork(T_Network* network, char* path);

void SaveNetwork_fp(T_Network* network, FILE *fp);

void SaveNetworkInfo(int* nbLayers, int** sizeLayers, FILE* fp);

void SaveTransitions(int* nbLayers, T_Transition** transitions, FILE* fp);

void SaveTransition(T_Transition* transition, FILE* fp);

void SaveTrainer_fp(T_Trainer* trainer, FILE* fp);

void SaveTrainerInfo (int nbSets, FILE* fp);

void SaveTrainerSetsOfInputs (double** SetsOfInputs, T_Network* network, int nbSets, FILE* fp);

void SaveTrainerSetsOfTargets (double** SetsOfTargets, T_Network* network, int nbSets, FILE* fp);

T_Trainer* LoadTrainer(char* path);

T_Network* LoadNetwork(char* path);

T_Network* LoadNetwork_fp(FILE* fp);

T_Network* LoadNetworkInfo(FILE* fp);

void LoadNetworkTransitions(T_Network* network, FILE* fp);

void LoadNetworkTransition(T_Transition* transition, FILE* fp);

T_Trainer* LoadTrainer_fp(T_Network* network, FILE* fp);

#endif //OCR_SAVEANDLOAD_H