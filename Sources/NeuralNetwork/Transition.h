//
// Created by root on 10/10/18.
//

#ifndef OCR_TRANSITION_H
#define OCR_TRANSITION_H

#include "Layer.h"


typedef struct E_Transition{
    T_Layer* sourceLayer;
    T_Layer* targetLayer;
    int height;
    int width;
    double** Matrix;
} T_Transition;


/// Initialize the transition between two layers.
/// \param sourceLayer Pointer to the layer from which values are taken
/// \param targetLayer Pointer to the layer to which values are calculated
/// \return Pointer to the new transition
T_Transition* InitializeTransition(T_Layer* sourceLayer, T_Layer* targetLayer);


/// Calculate the values of the next layer according to the source (Propagation).
/// \param transition Pointer to the transition to activate
void ActivateTransition(T_Transition* transition);


/// Uses Softmax function to calculate value of nodes
/// \param targetNodes Pointer to nodes array
/// \param nbNodes Number of nodes on the array
void SoftMax(T_Node** targetNodes, int nbNodes);


/// Randomize all the weights of a transition between -1 and 1.
/// \param transition Pointer to the transition to randomize
void RandomizeWeights(T_Transition* transition);


/// Return a random double between two bound. Must be initialised first.
/// \param min Minimum double
/// \param max Maximum double (excluded)
/// \return random double
double rdmWeight(double a, double b);


/// Free the memory occupied by a transition.
/// \param network Pointer to the transition to delete.
void FreeTransition(T_Transition* network);


#endif //OCR_TRANSITION_H
