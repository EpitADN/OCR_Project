//
// Created by root on 05/12/18.
//

#include "TrainingResource.h"
#include "../NeuralNetwork/SaveAndLoad.h"

int main(){

    char* trainerPath = "Saves/Clairiere_x784_3L.bin";

    T_Trainer* trainer = LoadTrainer(trainerPath);

    PrintAllNetworkInfos(trainer->Network, 0);

    FreeTrainer(trainer);
}