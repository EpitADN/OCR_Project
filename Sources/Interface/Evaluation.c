//
// Created by root on 04/12/18.
//

#include "Evaluation.h"


/// Evaluate the network with N tests from a resource
/// \param network Pointer to the network to evaluate
/// \param trainingResource Pointer to the resource to evaluate with
/// \param nbTest Number of tests to do
/// \return Number of tests the network got right
int Evaluate(T_Network* network, T_TrainingResource* trainingResource, int nbTest) {

    // Initialize random generator
    srand(time(NULL));

    int score = 0;

    for (int i = 0; i < nbTest; ++i) {

        int itarget = (int)random_at_most(trainingResource->nbTargets - 1);
        int iduplicate = (int)random_at_most(trainingResource->nbDuplicates[itarget] - 1);

        char target = trainingResource->Targets[itarget];
        char output = DryRun(network, trainingResource->Targets, &trainingResource->TrainingChars[itarget][iduplicate]);

        if (target == output)
            score++;
    }

    return score;
}


/// Assumes 0 <= max <= RAND_MAX (Credit to Adam Rosenfield)
/// \param max Max Bound of random
/// \return Returns in the closed interval [0, max]
long random_at_most(long max) {
    unsigned long
    // max <= RAND_MAX < ULONG_MAX, so this is okay.
            num_bins = (unsigned long) max + 1,
            num_rand = (unsigned long) RAND_MAX + 1,
            bin_size = num_rand / num_bins,
            defect   = num_rand % num_bins;

    long x;
    do {
        x = random();
    }
    // This is carefully written not to overflow
    while (num_rand - defect <= (unsigned long)x);

    // Truncated division is intentional
    return x/bin_size;
}