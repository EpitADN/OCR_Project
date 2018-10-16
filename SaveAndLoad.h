//
// Created by Gireg Roussel on 06/10/2018.
//

#ifndef OCR_SAVEANDLOAD_H
#define OCR_SAVEANDLOAD_H

#include <stdlib.h>
#include "Network.h"
#include <stdio.h>

void SaveNetwork(T_Network* network);

void SaveNetworkInfo(int* nbLayers, int** sizeLayers, FILE* fp);

void SaveTransitions(int* nbLayers, T_Transition** transitions, FILE* fp);

void SaveTransition(T_Transition* transition, FILE* fp);


T_Network* LoadNetwork();

T_Network* LoadNetworkInfo(FILE* fp);

void LoadNetworkTransitions(T_Network* network, FILE* fp);

void LoadNetworkTransition(T_Transition* transition, FILE* fp);

#endif //OCR_SAVEANDLOAD_H