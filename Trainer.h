//
// Created by root on 13/10/18.
//

#ifndef OCR_TRAINER_H
#define OCR_TRAINER_H

#import <stdio.h>
#import <stdlib.h>
#import <math.h>
#import "Backprop.h"


typedef struct S_Trainer {
    T_Network* Network;
    int nbSets;
    double** SetsOfInputs;
    double** SetsOfTargets;
} T_Trainer;


/// Initialize a Trainer and return a pointer to it.
/// \param network Pointer to the network to train
/// \param nbSets Number of possible set of inputs/ouputs
/// \param SetsOfInputs Pointer to the array of all sets of inputs
/// \param SetsOfTargets Pointer to the array of all sets of targets
/// \return A pointer to the new Trainer
T_Trainer* CreateTrainer_Auto(T_Network* network, int nbSets, double** SetsOfInputs, double** SetsOfTargets);


/// Initialize a Trainer and return a pointer to it, following user's criterias
/// \param network Poiter to the network to train
/// \return A pointer to the new trainer
T_Trainer* CreateTrainer_Manual(T_Network* network);


/// Train the network through i cycle of forward and back propagation
/// \param trainer Pointer to the trainer
/// \param nu Aggressivity of the training
/// \param iteration Number of iteration to go through
void Train(T_Trainer* trainer, double nu, int iteration);


/// Print the results of all sets of inputs.
/// \param trainer Pointer to the trainer
void ShowResults(T_Trainer* trainer);

/// Free the memory occupied by a trainer.
/// \param trainer Pointer to the trainer to delete
void FreeTrainer(T_Trainer* trainer);

#endif //OCR_TRAINER_H
