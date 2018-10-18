//
// Created by root on 13/10/18.
//

#ifndef OCR_BACKPROP_H
#define OCR_BACKPROP_H

#include "Network.h"


/// Derivative of the activation function
/// \param x
/// \return
double D_F(double x);


/// Reinforce the weights of the last transitions according to targets
/// \param nu Aggressivity of the training
/// \param targets Pointer to the supposed targets array
/// \param prevLayer Pointer to the second to last layer
/// \param outputLayer Pointer to the last Layer
/// \param lastTransition Pointer to the last Transition
void ReinforceWeights_LAST(double nu, double* targets, T_Transition* lastTransition);


/// Reinforce the weights of the actual transitions according to the next one.
/// \param nu Aggressivity of the training
/// \param prevLayer Pointer to the source layer of the actual transition
/// \param actualLayer Pointer to the target layer of the actual transition
/// \param nextLayer Pointer to the next layer following the last two
/// \param actualTransition Pointer to the transition to update
/// \param nextTransition Pointer to the next transition following the actual one
void ReinforceWeights_HIDDEN(double nu, T_Transition* actualTransition, T_Transition* nextTransition);


/// Do a full backpropagation cycle on the network
/// \param network Pointer to the network
/// \param nu Agressivity of the training
/// \param targets Pointer to the supposed targets array
void BackPropagate_AUTO(T_Network* network, double nu, double* targets);


/// Do a full backpropagation cycle on the network, according to user inputs
/// \param network Pointer to the network
void BackPropagate_MANUAL(T_Network* network);

#endif //OCR_BACKPROP_H
