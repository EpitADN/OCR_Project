//
// Created by root on 29/11/18.
//

#ifndef OCR_PROJECT_LOADER_H
#define OCR_PROJECT_LOADER_H

#include "../NeuralNetwork/Trainer.h"
#include "TrainingResource.h"


T_Trainer* CreateTrainer_FromResource(T_Network* network, T_TrainingResource* trainingResource);


#endif //OCR_PROJECT_LOADER_H
