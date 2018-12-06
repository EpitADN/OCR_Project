//
// Created by root on 05/12/18.
//

#include "TrainingResource.h"
#include "../NeuralNetwork/SaveAndLoad.h"

int main(){

    char* trainerPath = "Saves/Bouee_x784_10L.bin";

    T_Trainer* trainer = LoadTrainer(trainerPath);

    //PrintNetworkTransitions(trainer->Network);

    /*
    double* values;
    for (int i = 0; i < trainer->nbSets; ++i) {
        values = trainer->SetsOfInputs[i];

        for (int j = 0; j < 784; ++j) {
            if (j % 28 == 0)
                printf("\n|");
            printf("%lf|", values[j]);
        }

        printf("\n\n");
    }
    */

     ShowResults(trainer, 28);

     PrintAllNetworkInfos(trainer->Network, 1);



    FreeTrainer(trainer);
}