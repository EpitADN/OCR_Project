//
// Created by Gireg Roussel on 06/10/2018.
//

#include <string.h>
#include <errno.h>
#include "SaveAndLoad.h"

void SaveTrainer(T_Trainer* trainer, char* path)
{
    FILE *fp;

    if ((fp = fopen(path,"wb")) == NULL)
    {
        printf("Error! opening for save file");
        perror("Error open");
        // Program exits if the file pointer returns NULL.
        exit(1);
    }

    SaveNetwork_fp(trainer->Network, fp);

    SaveTrainer_fp(trainer, fp);

    fclose(fp);
}

void SaveNetwork(T_Network* network, char* path)
{
    FILE *fp;

    if ((fp = fopen(path,"wb")) == NULL)
    {
        printf("Error! opening for save file");
        perror("Error open");
        // Program exits if the file pointer returns NULL.
        exit(1);
    }

    SaveNetwork_fp(network, fp);

    fclose(fp);
}


void SaveNetwork_fp(T_Network* network, FILE *fp)
{
    SaveNetworkInfo(network->nbLayers, network->sizeLayers, fp);
    SaveTransitions(network->nbLayers, network->Transitions, fp);
}

void SaveNetworkInfo(int* nbLayers, int** sizeLayers, FILE* fp)
{
    fwrite(nbLayers, sizeof(int), 1, fp);
    int isize;
    for (int i = 0; i < *nbLayers - 1; ++i)
    {
        isize = *sizeLayers[i] - 1;
        fwrite(&isize, sizeof(int), 1, fp);
    }
    fwrite(sizeLayers[*nbLayers - 1], sizeof(int), 1, fp);
}

void SaveTransitions(int* nbLayers, T_Transition** transitions, FILE* fp)
{
    for (int i = 0; i < *nbLayers-1; ++i)
    {
        SaveTransition(transitions[i], fp);
    }
}

void SaveTransition(T_Transition* transition, FILE* fp)
{
    double** matrix = transition->Matrix;

    for (int i = 0; i < transition->height; ++i)
    {
        for (int j = 0; j < transition->width; ++j)
        {
            fwrite(&matrix[i][j], sizeof(double), 1, fp);
        }
    }
}


void SaveTrainer_fp(T_Trainer* trainer, FILE* fp)
{
    T_Network* network = trainer->Network;
    double** SetsOfInputs = trainer->SetsOfInputs;
    int nbSets = trainer->nbSets;
    double** SetsOfTargets = trainer->SetsOfTargets;

    SaveTrainerInfo(nbSets, fp);
    SaveTrainerSetsOfInputs(SetsOfInputs, network, nbSets, fp);
    SaveTrainerSetsOfTargets(SetsOfTargets, network, nbSets, fp);
}

void SaveTrainerInfo (int nbSets, FILE* fp)
{
    fwrite(&nbSets, sizeof(int), 1, fp);
}

void SaveTrainerSetsOfInputs (double** SetsOfInputs, T_Network* network, int nbSets, FILE* fp)
{
    for (int i = 0; i < nbSets; ++i)
    {
        for (int j = 0; j < *network->sizeLayers[0]-1; ++j)
        {
            fwrite(&SetsOfInputs[i][j], sizeof(double), 1, fp);
        }
    }
}

void SaveTrainerSetsOfTargets (double** SetsOfTargets, T_Network* network, int nbSets, FILE* fp)
{
    int lastLayer = *network->nbLayers - 1;
    int Outputs = *network->sizeLayers[lastLayer];
    for (int i = 0; i < nbSets; ++i)
    {
        for (int j = 0; j < Outputs; ++j)
        {
            fwrite(&SetsOfTargets[i][j], sizeof(double), 1, fp);
        }
    }
}

/// This function will load a binary file
/// \return An array of double.
T_Trainer* LoadTrainer(char* path)
{
    FILE *fp;

    if ((fp = fopen(path,"rb")) == NULL)
    {

        printf("Error! opening for load file, %s _ %s\n", strerror(errno), path);
        perror("Error open");


        // Program exits if the file pointer returns NULL.
        exit(1);
    }

    T_Network* network = LoadNetwork_fp(fp);

    T_Trainer* trainer = LoadTrainer_fp(network, fp);

    fclose(fp);

    return trainer;
}

T_Network* LoadNetwork(char* path)
{
    FILE *fp;
    if ((fp = fopen(path,"rb")) == NULL)
    {
        printf("Error! opening for load file, %s _ %s\n", strerror(errno), path);
        perror("Error open");
        // Program exits if the file pointer returns NULL.
        exit(1);
    }

    T_Network* network = LoadNetwork_fp(fp);

    fclose(fp);

    return network;
}

T_Network* LoadNetwork_fp(FILE* fp)
{
    T_Network* network = LoadNetworkInfo(fp);
    LoadNetworkTransitions(network, fp);

    return network;
}

T_Network* LoadNetworkInfo(FILE* fp)
{
    int *nbLayers = malloc(sizeof(int));
    fread(nbLayers, sizeof(int), 1, fp);

    int** sizeLayers = malloc(*nbLayers * sizeof(int*));
    for (int i = 0; i < *nbLayers; ++i)
    {
        sizeLayers[i] = malloc(sizeof(int));
        fread(sizeLayers[i], sizeof(int), 1, fp);
    }
    return CreateNetwork_Auto(nbLayers, sizeLayers);
}

void LoadNetworkTransitions(T_Network* network, FILE* fp)
{
    for (int i = 0; i < *network->nbLayers-1; ++i)
    {
        LoadNetworkTransition(network->Transitions[i], fp);
    }
}

void LoadNetworkTransition(T_Transition* transition, FILE* fp)
{
    double** matrix = transition->Matrix;

    for (int i = 0; i < transition->height; ++i)
    {
        for (int j = 0; j < transition->width; ++j)
        {
            fread(&matrix[i][j], sizeof(double), 1, fp);
        }
    }
}

T_Trainer* LoadTrainer_fp(T_Network* network, FILE* fp)
{
    int nbSets;
    fread(&nbSets, sizeof(int), 1, fp);

    double** SetsOfInputs = malloc(nbSets * sizeof(double*));
    int Inputs = *network->sizeLayers[0]-1;
    for (int i = 0; i < nbSets; ++i)
    {
        SetsOfInputs[i] = malloc(Inputs * sizeof(double));
        for (int j = 0; j < Inputs; ++j)
        {
            fread(&SetsOfInputs[i][j], sizeof(double), 1, fp);
        }
    }

    double** SetsOfTargets = malloc(nbSets * sizeof(double *));
    int lastLayer = *network->nbLayers - 1;
    int Outputs = *network->sizeLayers[lastLayer];
    for (int i = 0; i < nbSets; ++i)
    {
        SetsOfTargets[i] = malloc(Outputs * sizeof(double));
        for (int j = 0; j < Outputs; ++j)
        {

            fread(&SetsOfTargets[i][j], sizeof(double), 1, fp);
        }
    }

    return CreateTrainer_Auto(network, nbSets, SetsOfInputs, SetsOfTargets);
}
