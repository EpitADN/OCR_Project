//
// Created by root on 13/10/18.
//

#include <stdio.h>
#include <stdlib.h>
#include "Backprop.h"


/// Derivative of the activation function 'f'.
/// \param x
/// \return f'(x)
double D_F(double x){
    return x*(1-x);
}


/// Reinforce the weights of the last transitions according to targets.
/// \param nu Aggressivity of the training
/// \param targets Pointer to the supposed targets array
/// \param prevLayer Pointer to the second to last layer
/// \param outputLayer Pointer to the last Layer
/// \param lastTransition Pointer to the last Transition
void ReinforceWeights_LAST(double nu, double* targets, T_Layer* prevLayer, T_Layer* outputLayer, T_Transition* lastTransition){

    // Checking if layer is actually the last one
    if (outputLayer->position != LAST)
        return;

    // Retrieving necessary variables
    double** lastMatrix = lastTransition->Matrix;
    T_Node** prevNodes = prevLayer->nodes;
    T_Node** outputNodes = outputLayer->nodes;
    int nbPrev = *prevLayer->nbNodes;
    int nbOutput = *outputLayer->nbNodes;

    // For each output node
    T_Node* iONode;
    for (int i = 0; i < nbOutput; ++i) {

        // Recuperating node and updating it's error value
        iONode = outputNodes[i];
        iONode->error = (targets[i] - iONode->val) * D_F(iONode->val);

        // Updating weights values
        for (int j = 0; j < nbPrev; ++j)
            lastMatrix[i][j] += nu * iONode->error * prevNodes[j]->val;
    }

}


/// Reinforce the weights of the actual transitions according to the next one.
/// \param nu Aggressivity of the training
/// \param prevLayer Pointer to the source layer of the actual transition
/// \param actualLayer Pointer to the target layer of the actual transition
/// \param nextLayer Pointer to the next layer following the last two
/// \param actualTransition Pointer to the transition to update
/// \param nextTransition Pointer to the next transition following the actual one
void ReinforceWeights_HIDDEN(double nu, T_Layer* prevLayer, T_Layer* actualLayer, T_Layer* nextLayer, T_Transition* actualTransition, T_Transition* nextTransition){

    // Checking if layer is actually hidden
    if (actualLayer->position != MIDDLE){
        printf("Layer is not hidden (%d), skipping...", actualLayer->position);
        return;
    }

    // Retrieving necessary variables
    double** actualMatrix = actualTransition->Matrix;
    double** nextMatrix = nextTransition->Matrix;
    T_Node** prevNodes = prevLayer->nodes;
    T_Node** actualNodes = actualLayer->nodes;
    T_Node** nextNodes = nextLayer->nodes;
    int nbPrev = actualTransition->width;
    int nbActual = actualTransition->height;
    int nbNext = nextTransition->height;

    // For each actual node :
    T_Node* jANode; double sum_dmwm;
    for (int i = 0; i < nbActual; ++i) {

        //printf("Calculating error value for node %d : ", i+1);

        // Recuperating actual node
        jANode = actualNodes[i];

        // Updating it's error value, in function of next nodes.
        sum_dmwm = 0;
        for (int j = 0; j < nbNext; ++j){
            //printf("W%d_%d = %lf, dm%d = %lf, product = %lf \n", i+1, j+1, nextMatrix[j][i], j+1, nextNodes[j]->error, nextMatrix[j][i] * nextNodes[j]->error);
            sum_dmwm += nextMatrix[j][i] * nextNodes[j]->error;
        }
        //printf("Sum(Wkm*Dm)) = %lf \n", sum_dmwm);
        jANode->error = D_F(jANode->val) * sum_dmwm;

        // Updating weights values
        for (int k = 0; k < nbPrev; ++k)
            actualMatrix[i][k] += nu * jANode->error * prevNodes[k]->val;
    }
}


/// Do a full backpropagation cycle on the network
/// \param network Pointer to the network
/// \param nu Agressivity of the training
/// \param targets Pointer to the supposed targets array
void BackPropagate_AUTO(T_Network* network, double nu, double* targets){

    //printf("Starting reinforcement of network...\n");

    // Retrieving network info
    T_Layer** layers = network->Layers;
    T_Transition** transitions = network->Transitions;
    int lastL = *network->nbLayers - 1;
    int lastT = lastL - 1;

    // Reinforce the last transition
    ReinforceWeights_LAST(nu, targets, layers[lastL-1], layers[lastL], transitions[lastT]);
    //printf("Reinforced transition %d (last).\n", lastT);

    // Reinforce the other transitions according to the last one
    for (int i = lastT - 1; i >= 0 ; --i) {
        //printf("Reinforced transition %d.\n", i);
        ReinforceWeights_HIDDEN(nu, layers[i], layers[i+1], layers[i+2], transitions[i], transitions[i+1]);
    }
}


/// Do a full backpropagation cycle on the network, according to user inputs
/// \param network Pointer to the network
void BackPropagate_MANUAL(T_Network* network){

    // Asking for nu
    double nu;
    printf("Enter the aggressivity variable (nu) : ");
    scanf("%lf", &nu);

    // Retrieving the number of output nodes
    int nbOutput = *network->Layers[*network->nbLayers - 1]->nbNodes;

    // Allocating memory for the target array
    double* targets = malloc(nbOutput * sizeof(double));

    // Asking for each individual target
    for (int i = 0; i < nbOutput; ++i) {
        printf("Enter the expected output of node %d : ", i + 1);
        scanf("%lf", &targets[i]);
    }
    printf("\n");

    // Applying backpropagation according to user's entries
    BackPropagate_AUTO(network, nu, targets);

    // Freeing memory
    free(targets);
}