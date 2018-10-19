//
// Created by Gireg Roussel on 06/10/2018.
//

#include "SaveAndLoad.h"

#include <string.h>

void Save(T_Trainer* trainer, char* name, char* extension)
{
    FILE *fp;

    if (strcmp(extension, ".bin") != 0)
    {
        printf("You have to save a file with extension .bin");
        exit(1);
    }

    char* directory = "../SaveTransitions/";

    char *path = malloc(strlen(directory)+strlen(name)+strlen(extension)+1);

    if (path == NULL)
    {
        printf("Malloc impossible");
        exit(1);
    }

    strcat(path, directory);
    strcat(path, name);
    strcat(path, extension);

    if ((fp = fopen(path,"wb")) == NULL)
    {
        printf("Error! opening file");
        // Program exits if the file pointer returns NULL.
        exit(1);
    }

    SaveNetwork(trainer->Network, fp);

    SaveTrainer(trainer, fp);

    fclose(fp);
}


/// This function will save a double array on a binary file.
/// \param Heigth
/// \param Weigth
/// \param Data , double[]data

void SaveNetwork(T_Network* network, FILE *fp)
{
    SaveNetworkInfo(network->nbLayers, network->sizeLayers, fp);
    SaveTransitions(network->nbLayers, network->Transitions, fp);
}

void SaveNetworkInfo(int* nbLayers, int** sizeLayers, FILE* fp)
{
    fwrite(nbLayers, sizeof(int), 1, fp);
    for (int i = 0; i < *nbLayers; ++i)
        fwrite(sizeLayers[i], sizeof(int), 1, fp);
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


void SaveTrainer(T_Trainer* trainer, FILE* fp)
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
    printf("JJJJDBHDHJSJ %d", nbSets);
    fwrite(&nbSets, sizeof(int), 1, fp);
}

void SaveTrainerSetsOfInputs (double** SetsOfInputs, T_Network* network, int nbSets, FILE* fp)
{
    for (int i = 0; i < nbSets; ++i)
    {
        for (int j = 0; j < *network->sizeLayers[0]; ++j)
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
T_Trainer* Load(char* name_extension)
{
    FILE *fp;

    char* directory = "../SaveTransitions/";

    char *path = malloc(strlen(directory)+strlen(name_extension)+1);

    if (path == NULL)
    {
        printf("Malloc impossible");
        exit(1);
    }

    strcat(path, directory);
    strcat(path, name_extension);

    if ((fp = fopen(path,"rb")) == NULL)
    {
        printf("Error! opening file");

        // Program exits if the file pointer returns NULL.
        exit(1);
    }
    T_Network* network = LoadNetwork(fp);
    LoadNetworkTransitions(network, fp);

    T_Trainer* trainer = LoadTrainer(network, fp);

    fclose(fp);

    return trainer;
}

T_Network* LoadNetwork(FILE* fp)
{
    T_Network* network = LoadNetworkInfo(fp);
    LoadNetworkTransitions(network, fp);

    return network;
}

T_Network* LoadNetworkInfo(FILE* fp)
{
    int* nbLayers = malloc(sizeof(int));
    fread(nbLayers, sizeof(int), 1, fp);
    printf("Detected %d layers\n", *nbLayers);

    int** sizeLayers = malloc(*nbLayers * sizeof(int*));
    for (int i = 0; i < *nbLayers; ++i)
    {
        sizeLayers[i] = malloc(sizeof(int));
        fread(sizeLayers[i], sizeof(int), 1, fp);
        printf("Layer number %d has a size of %d\n",i+1, *sizeLayers[i]);
    }

    return CreateNetwork_Auto(nbLayers, sizeLayers, 0);
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

T_Trainer* LoadTrainer(T_Network* network, FILE* fp)
{
    int nbSets = 0;
    fread(&nbSets, sizeof(int), 1, fp);
    printf("Nb of sets : %d", nbSets);

    double** SetsOfInputs = malloc(nbSets * sizeof(double*));
    int Inputs = *network->sizeLayers[0];
    for (int i = 0; i < nbSets; ++i)
    {
        SetsOfInputs[i] = malloc(Inputs * sizeof(double));
        for (int j = 0; j < *network->sizeLayers[0]; ++j)
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