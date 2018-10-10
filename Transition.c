//
// Created by root on 10/10/18.
//

#include <stdlib.h>
#include <time.h>
#include "Transition.h"


/// Initialize the transition between two layers.
/// \param sourceLayer Pointer to the layer from which values are taken
/// \param targetLayer Pointer to the layer to which values are calculated
/// \return Pointer to the new transition
T_Transition* InitializeTransition(T_Layer* sourceLayer, T_Layer* targetLayer){

    // Getting dimensions
    int height = *targetLayer->nbNodes;
    int width = *sourceLayer->nbNodes;

    // Redesigning if target layer has a bias
    if (targetLayer->position != LAST)
        height -= 1;

    // Allocating memory for the Matrices
    double** Tab = malloc(height * sizeof(double*));
    for (int i = 0; i < height; ++i) {
        Tab[i] = malloc(width * sizeof(double));
    }

    // Creating pointer
    T_Transition* transition = NULL;

    // Allocating memory for the transition
    transition = malloc(sizeof(T_Transition));

    // Exiting if allocation failed
    if (transition == NULL)
        exit(1);

    // Setting attributes
    transition->height = height;
    transition->width = width;
    transition->sourceLayer = sourceLayer;
    transition->targetLayer = targetLayer;
    transition->Matrix = Tab;

    RandomizeWeights(transition);

    return transition;
}


/// Calculate the values of the next layer according to the source (Propagation).
/// \param transition Pointer to the transition to activate
void ActivateTransition(T_Transition* transition){

    // Getting all necessary variables
    int height = transition->height;
    int width = transition->width;
    T_Node** sourceNodes = transition->sourceLayer->nodes;
    T_Node** targetNodes = transition->targetLayer->nodes;
    double** Matrix = transition->Matrix;

    // Iterating for each target node
    for (int i = 0; i < height; ++i) {

        targetNodes[i]->net = 0;
        for (int j = 0; j < width; ++j)
            targetNodes[i]->net += sourceNodes[j]->val * Matrix[i][j];

        UpdateVal(targetNodes[i]);
    }
}


/// Randomize all the weights of a transition between -1 and 1.
/// \param transition Pointer to the transition to randomize
void RandomizeWeights(T_Transition* transition){

    // Getting all necessary variables
    int height = transition->height;
    int width = transition->width;
    double ** Matrix = transition->Matrix;

    // Initialize random generator
    srand(time(NULL));

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            Matrix[i][j] = rdmWeight(-1, 1);
        }
    }
}


/// Return a random double between two bound. Must be initialised first.
/// \param min Minimum double
/// \param max Maximum double (excluded)
/// \return random double
double rdmWeight(double a, double b){
    return ( rand()/(double)RAND_MAX ) * (b-a) + a;
}



/// Free the memory occupied by a transition.
/// \param network Pointer to the transition to delete.
void FreeTransition(T_Transition* transition){
    for (int i = 0; i < transition->height; ++i)
        free(transition->Matrix[i]);
    free(transition->Matrix);
    free(transition);
}