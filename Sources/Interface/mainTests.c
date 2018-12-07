//
// Created by root on 05/12/18.
//

#include "../NeuralNetwork/SaveAndLoad.h"

int main(){

    char* trainerPath = "../Saves/Foret_x784_3L.bin";

    T_Trainer* trainer = LoadTrainer(trainerPath);

    SaveNetwork(trainer->Network, "OfficialOCR.bin");

    FreeTrainer(trainer);
}