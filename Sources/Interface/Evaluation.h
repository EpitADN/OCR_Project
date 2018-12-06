//
// Created by root on 04/12/18.
//

#ifndef OCR_PROJECT_EVALUATION_H
#define OCR_PROJECT_EVALUATION_H

#include "Loader.h"
#include <time.h>


/// Evaluate the network with N tests from a resource
/// \param network Pointer to the network to evaluate
/// \param trainingResource Pointer to the resource to evaluate with
/// \param nbTest Number of tests to do
/// \return Number of tests the network got right
int Evaluate(T_Network* network, T_TrainingResource* trainingResource, int nbTest);


/// Assumes 0 <= max <= RAND_MAX (Credit to Adam Rosenfield)
/// \param max Max Bound of random
/// \return Returns in the closed interval [0, max]
long random_at_most(long max);

#endif //OCR_PROJECT_EVALUATION_H
